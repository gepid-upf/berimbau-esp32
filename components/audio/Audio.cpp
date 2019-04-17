/**
 * @file Audio.cpp
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief Source file for managing the timing of the audio DAC output.
 */

#include <Audio.h>

#include <driver/dac.h>

#include <freertos/task.h> // vTaskDelay()

#include <math.h> // ceil() log2()

#include <Interface.h>

const char *Audio::TAG = "Audio";
std::vector<Audio*> DRAM_ATTR Audio::voices;
//uint8_t Audio::shift_n = 0;
timer_group_t Audio::timer_group = TIMER_GROUP_0;
timer_idx_t DRAM_ATTR  Audio::timer_num = TIMER_0;
timg_dev_t  DRAM_ATTR *Audio::tmrg_ptr = nullptr;
Lpf DRAM_ATTR Audio::muffle(44101, 21000);

void IRAM_ATTR dac_timing(void *nullpar)
{
    static int32_t DRAM_ATTR out = 0;
    static int DRAM_ATTR i = 0;

    // Update timer status
    Audio::tmrg_ptr->hw_timer[Audio::timer_num].update = 1;
    // Can't have pointer to bitfield.
    switch(Audio::timer_num){
    case TIMER_0:
        Audio::tmrg_ptr->int_clr_timers.t0 = 1;
        break;
    case TIMER_1:
        Audio::tmrg_ptr->int_clr_timers.t1 = 1;
    default:
        break;
    }
    Audio::tmrg_ptr->hw_timer[Audio::timer_num].config.alarm_en = 1;

    // Actual ISR

    // MIX!
    // This will be shifted n bits to right, to the value of 32768 that is the
    // center of the wave.
    out = 0; // << Audio::shift_n;

    for(i = 0; i < Audio::voices.size(); i++){
        if(Audio::voices[i]->is_playing() && Audio::voices[i]->apply_dsp)
            out += Audio::voices[i]->get_next();
    }

    // Apply DSP effects
    out = Audio::muffle.update(out);

    // Sum signals not succetible to dsp effects.
    for(i = 0; i < Audio::voices.size(); i++){
        if(Audio::voices[i]->is_playing() && !Audio::voices[i]->apply_dsp)
            out += Audio::voices[i]->get_next();
    }

    out += 32768; // Make positive with center in  2^15
    // Shift n bits to right to maintain up to 16 bit resolution.
    //out >>= Audio::shift_n;

    dac_output_voltage(DAC_CHANNEL_1, (uint8_t)((uint32_t)out >> 8)); // MSB
    dac_output_voltage(DAC_CHANNEL_2, (uint8_t)out); // LSB
}

// Object functions
Audio::Audio(const int16_t *_sample_data, const uint32_t _sample_size, bool _apply_dsp) : 
                                                                        sample_data(_sample_data),
                                                                        sample_size(_sample_size),
                                                                        apply_dsp(_apply_dsp),
                                                                        it(0),
                                                                        playing(false)
{
    voices.push_back(this);
}

bool IRAM_ATTR Audio::is_playing()
{
    return playing;
}

int16_t IRAM_ATTR Audio::get_next()
{
    static int16_t DRAM_ATTR ret;
    ret = sample_data[it++];
    if(it >= sample_size) playing = false;
    return ret;
}

uint32_t Audio::get_length()
{
    return sample_size;
}

void Audio::set_active(bool active)
{
    // Critical section: ensure all logic is done without the ISR calling get_next() or is_playing()
    portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;
    portENTER_CRITICAL(&myMutex);

    playing = active;
    it = 0;

    // Leave critical section
    portEXIT_CRITICAL(&myMutex);
}

void Audio::set_muffle_cutoff(uint32_t cutoff)
{
    muffle.set_cutoff(cutoff);
}

// https://github.com/sankarcheppali/esp_idf_esp32_posts/blob/master/timer_group/main/timer_group.c
// Class functions
void Audio::timer_config()
{
    timer_config_t conf;
    conf.divider = 2; // 40MHz timing clock
    conf.counter_dir = TIMER_COUNT_UP;
    conf.counter_en = TIMER_PAUSE;
    conf.alarm_en = TIMER_ALARM_EN;
    conf.intr_type = TIMER_INTR_LEVEL;
    conf.auto_reload = TIMER_AUTORELOAD_EN;
    timer_init(timer_group, timer_num, &conf);
   
    // Ensure is paused
    timer_pause(timer_group, timer_num);

    // Auto reload to 0
    timer_set_counter_value(timer_group, timer_num, 0x00000000ULL);

    // Compare match interrupt value (22,675us ~= 44.1KHz)
    timer_set_alarm_value(timer_group, timer_num, 907);

    // Enable interrupt
    timer_enable_intr(timer_group, timer_num);

    // Set the function wich the interrupt will run
    // ESP_INTR_FLAG_IRAM can't be used because dac_output_voltage is outside IRAM
    timer_isr_register(timer_group, timer_num, dac_timing, nullptr, 0, nullptr);

    // Enable the timer
    timer_start(timer_group, timer_num);
}

void Audio::dac_config()
{
    dac_output_enable(DAC_CHANNEL_1);
    dac_output_enable(DAC_CHANNEL_2);
}

void Audio::init(timer_group_t _timer_group, timer_idx_t _timer_num)
{
    //shift_n = ceil(log2(voices.size()));
    timer_group = _timer_group;
    timer_num = _timer_num;

    switch(timer_group){
    case TIMER_GROUP_0:
        tmrg_ptr = &TIMERG0;
        break;
    case TIMER_GROUP_1:
        tmrg_ptr = &TIMERG1;
    default:
        break;
    }

    dac_config();
    timer_config();

    Interface::loaded();
}

uint8_t Audio::get_voices_count()
{
    return voices.size();
}

Audio *Audio::get_voice_ptr(uint8_t index)
{
    return voices[index];
}