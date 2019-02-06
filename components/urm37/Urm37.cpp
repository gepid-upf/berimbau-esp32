/**
 * @file Urm37.cpp
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief URM37v3.2 library for ESP32.
 */

#include <Urm37.h>

#include <freertos/task.h>

#include <math.h>

const char *Urm37::TAG = "URM37";

// https://www.freertos.org/a00124.html
void IRAM_ATTR pwm_isr(void *obj)
{
    Urm37 *urm = (Urm37*)obj;

    // Clear intr flag
    switch(urm->rmt_channel){
    case RMT_CHANNEL_0:
        RMT.int_clr.ch0_rx_end = 1;
        break;
    case RMT_CHANNEL_1:
        RMT.int_clr.ch1_rx_end = 1;
        break;
    case RMT_CHANNEL_2:
        RMT.int_clr.ch2_rx_end = 1;
        break;
    case RMT_CHANNEL_3:
        RMT.int_clr.ch3_rx_end = 1;
        break;
    case RMT_CHANNEL_4:
        RMT.int_clr.ch4_rx_end = 1;
        break;
    case RMT_CHANNEL_5:
        RMT.int_clr.ch5_rx_end = 1;
        break;
    case RMT_CHANNEL_6:
        RMT.int_clr.ch6_rx_end = 1;
        break;
    case RMT_CHANNEL_7:
        RMT.int_clr.ch7_rx_end = 1;
    default:
        break;
    }

    // Checks if pulse in level is LOW and gets duration
    uint16_t duration = 0;
    if(!RMTMEM.chan[urm->rmt_channel].data32[0].level0){
        duration = (uint16_t)RMTMEM.chan[urm->rmt_channel].data32[0].duration0;
    } else if(!RMTMEM.chan[urm->rmt_channel].data32[0].level1){
        duration = (uint16_t)RMTMEM.chan[urm->rmt_channel].data32[0].duration1;
    }

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if(duration){ // If duration is 0, means that pulse was longer than 25ms = fail
        urm->value = duration;
        xSemaphoreGiveFromISR(urm->mtx, &xHigherPriorityTaskWoken);
        if(xHigherPriorityTaskWoken)
            portYIELD_FROM_ISR();
    }
    // If fail to pulse in, don't release semaphore. Let the task semaphore timeout.

}

Urm37::Urm37(gpio_num_t _trigger, gpio_num_t _pwm, rmt_channel_t _rmt_channel) : 
                trigger(_trigger), pwm(_pwm), rmt_channel(_rmt_channel), value(0)
{

}

void Urm37::config_gpio()
{
    // Configure the trigger output.
    gpio_config_t io_conf;
    //no intr
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output
    io_conf.mode = GPIO_MODE_OUTPUT;
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //disable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    //select the pins to configure
    io_conf.pin_bit_mask = BIT(trigger);
    gpio_config(&io_conf);
    
    gpio_set_level(trigger, 1); // Stays as HIGH

    // Configure input if needed. MCPWM or RC?
/*
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = BIT(pwm);
    gpio_config(&io_conf);
*/
}

void Urm37::config_rmt()
{
    rmt_config_t rmt_rx;
    // Common config
    rmt_rx.channel = rmt_channel;
    rmt_rx.gpio_num = pwm;
    rmt_rx.clk_div = 80; // 1MHz clock, period=1us
    rmt_rx.mem_block_num = 1;
    rmt_rx.rmt_mode = RMT_MODE_RX;

    // Rx config
    rmt_rx.rx_config.filter_en = true;
    rmt_rx.rx_config.filter_ticks_thresh = 50; // 3cm is the minimum = 150us
    rmt_rx.rx_config.idle_threshold = 25000; // 50000us is the failure signal. But 25000 is the max resolution.
    rmt_config(&rmt_rx);

    // Don't install. Not using default interrupt, nor ringbuffer
    //rmt_driver_install(rmt_channel, 0, ESP_INTR_FLAG_IRAM);
    rmt_isr_register(pwm_isr, this, ESP_INTR_FLAG_IRAM, nullptr);
    rmt_set_rx_intr_en(rmt_channel, true);
}


bool Urm37::pulse_trigger()
{
    // Critical section: pulse the correct timing
    portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;
    portENTER_CRITICAL(&myMutex);

    rmt_rx_stop(rmt_channel);

    gpio_set_level(trigger, 0);
    ets_delay_us(4);
    gpio_set_level(trigger, 1);

    rmt_rx_start(rmt_channel, true);

    // End of the critical section
    portEXIT_CRITICAL(&myMutex);

    return xSemaphoreTake(mtx, 50 / portTICK_PERIOD_MS); // 50 us is the failure time
}


void Urm37::init()
{
    mtx = xSemaphoreCreateBinary();

    config_gpio();
    config_rmt();
}

uint16_t Urm37::get_distance_cm()
{
    return (uint16_t)round(value/50.0); // No need for critical section on read <= reg size
}

uint16_t Urm37::get_pulse_us()
{
    return value;
}