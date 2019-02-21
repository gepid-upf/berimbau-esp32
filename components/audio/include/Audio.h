/**
 * @file Audio.h
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief Audio class for manage the DAC in the WAV sample frequency.
 * Currently only ~44.1KHz
 */

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <vector>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <driver/timer.h>

#include <Lpf.h>

class Audio {
public:
    /**
     * @brief Audio output ISR.
     * 
     * @param *nullpar nullptr.
     */
    friend void IRAM_ATTR dac_timing(void *nullpar);

    /**
     * @brief Voice constructor.
     * 
     * @param *_sample_data Pointer to the sample array.
     * @param _sample_size Size of the sample.
     */
    Audio(const int16_t *_sample_data, const uint16_t _sample_size, bool apply_dsp = true);

    /**
     * @brief Sets a voice active or inactive.
     * 
     * @notes Use with caution. It has a critical section inside.
     * 
     * @param active Wich to activate or deactivate the voice.
     */
    void set_active(bool active = true);

    /**
     * @brief Gets the sample length.
     * 
     * @returns The number of WORDs in the sample.
     */
    uint32_t get_length();

    /**
     * @brief Configures and runs the Audio hardware task.
     * 
     * @note This needs precise timing, so it is not a task, it runs inside an interrupt.
     * 
     * @param _timer_group The timer group number to run the interrupt.
     * @param _timer_num The timer number of the group to run the interrupt.
     */
    static void init(timer_group_t _timer_group = TIMER_GROUP_0, timer_idx_t _timer_num = TIMER_0);

    /**
     * @brief Sets the muffling DSP effect frequency cutoff.
     * 
     * @note Set to 20000+ to disable effect.
     * 
     * @param cutoff The frequency in Hz to LPF cut.
     */
    static void set_muffle_cutoff(uint32_t cutoff);

    /**
     * @brief Gets the playing state of the voice.
     * 
     * @returns True if playing
     */
    bool is_playing();

    static uint8_t get_voices_count();

    static Audio *get_voice_ptr(uint8_t index);

private:
    const int16_t *sample_data;
    const uint16_t sample_size;
    bool apply_dsp;
    volatile uint16_t it;
    volatile bool playing;

    /**
     * @brief Gets the next sample from the array.
     * 
     * @returns The WORD-size sample.
     */
    int16_t get_next();

    static const char *TAG;
    static std::vector<Audio*> voices;
    //static uint8_t shift_n;
    static timer_group_t timer_group;
    static timer_idx_t   timer_num;
    static timg_dev_t *tmrg_ptr;
    static Lpf muffle;

    /**
     * @brief Enable the two DAC channels
     */
    static void dac_config();

    /**
     * @brief Configures the interrupt timer.
     * 
     * @note It uses the Timer Group 0 Timer 0. Watch out when other libraries use this.
     */
    static void timer_config();

};

#endif /* _AUDIO_H_ */