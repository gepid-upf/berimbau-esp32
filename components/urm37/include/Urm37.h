/**
 * @file Urm37.h
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief URM37v3.2 library for ESP32. PLEASE NOTE: To use this, use a logic level
 * converter to drop the PWM pin to 3.3v.
 */

#ifndef _URM37_H_
#define _URM37_H_

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <driver/gpio.h>
#include <driver/rmt.h>

class Urm37 {
public:

    /**
     * @brief RMT rx finished. PWM input pulse received.
     * 
     * @param *obj Object that called the isr.
     */
    friend void IRAM_ATTR pwm_isr(void *obj);

    /**
     * @brief Class constructor.
     * 
     * @param _trigger The GPIO the trigger pin is connected.
     * @param _pwm The GPIO the PWM input is connected.
     * @param _rmt_channel The RMT channel to use for PWM capture.
     */
    Urm37(gpio_num_t _trigger, gpio_num_t _pwm, rmt_channel_t _rmt_channel = RMT_CHANNEL_0);

    /**
     * @brief Configures everything to setup the URM37
     */
    void init();

    /**
     * @brief Pulses the trigger pin.
     * 
     * @return true if response arrived.
     *         false if failed.
     */
    bool pulse_trigger();

    /**
     * @brief Gets the last distance measured in cm.
     * 
     * @return 0 if never measured.
     *         3 - 500 cm of the last sucessful measure.
     */
    uint16_t get_distance_cm();

    /**
     * @brief Gets the distance PWM pulse in us
     * 
     * @return 0 if never measured.
     *         150 - 25000 us of the last sucessful measure.
     */
    uint16_t get_pulse_us();

private:
    gpio_num_t trigger;
    gpio_num_t pwm;
    rmt_channel_t rmt_channel;
    uint16_t value;
    SemaphoreHandle_t mtx;

    /**
     * @brief Initializes the trigger and pwm GPIOs.
     */
    void config_gpio();

    /**
     * @brief Configures the remote control peripheral for PWM capture.
     */
    void config_rmt();

    static const char *TAG;

};

#endif /* _URM37_H_ */