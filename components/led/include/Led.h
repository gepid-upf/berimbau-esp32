/**
 * @file Led.h
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief Led class for parallel blink.
 */

#ifndef _LED_H_
#define _LED_H_

#include <vector>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <driver/gpio.h>

class Led {
public:
    /**
     * @brief Class constructor. Defines the GPIO the Led is connected.
     * 
     * @param _gpio_num The GPIO number the LED is.
     */
    Led(gpio_num_t _gpio_num);

    /**
     * @brief Turns on the Led and sets the turn off time
     * 
     * @param delay_ms The time to keep on.
     */
    void blink(uint16_t delay_ms);

    /**
     * @brief Turns off the led immediately
     */
    void turn_off();

    /**
     * @brief Configures and runs the task.
     * 
     * @param *nullpar nullptr.
     */
    static void task(void *nullpar);

private:
    gpio_num_t gpio_num;
    uint64_t stop_time;
    bool lit;

    SemaphoreHandle_t mtx;

    /**
     * @brief Gets the GPIO number of the LED.
     * 
     * @returns The GPIO port int value.
     */
    gpio_num_t get_num();

    /**
     * @brief Checks if time to turn off has arrived.
     */
    void check();


    static std::vector<Led*> leds;
    static const char *TAG;

    /**
     * @brief Configures all GPIOs
     */
    static void init();

};

#endif /* _LED_H_ */