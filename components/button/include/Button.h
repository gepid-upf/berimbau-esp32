/**
 * @file Button.h
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief Headers for the Button class that manages buttons with interruptions and debouncing.
 */

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <stdint.h>
#include <vector> // STL vector (C++)

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <driver/gpio.h>

class Button {
public:
    /**
     * @brief Button state interrupt.
     * 
     * @param *button The gpio number the button is attached to.
     */
    friend void IRAM_ATTR gpio_isr_handler(void* button);

    /**
     * Button State enumerator
     */
    enum class State {
        UNPRESSED,
        PRESSED,
        UNRELEASED
    };

    /**
     * @brief Class constructor.
     * 
     * @param _gpio_num is the gpio integer number the button is connected.
     */
    Button(gpio_num_t _gpio_num);

    /**
     * @brief Gets the state of the button.
     * 
     * @returns
     *      State::PRESSED case pressed.
     *      State::UNRELEASED case still pressed after a get.
     *      State::UNPRESSED case released.
     */
    State get_state();

    /**
     * @brief Configures all the buttons objects and runs the task and interrupt
     * to update the Button::State.
     * 
     * @param *nullpar nullptr.
     */
    static void task(void *nullpar);

private:
    // Object variables
    gpio_num_t gpio_num;
    uint32_t last_press;
    uint32_t last_unpress;
    State pin_state;
    SemaphoreHandle_t mtx;
    
    // Object functions
    /**
     * @brief Updates the Button::State while debouncing.
     * 
     * @param level The logic level of the interrupt that ocurred.
     * @param current_ms The time in ms the interrupt ocurred.
     */
    void update(bool level, uint32_t current_ms);

    /**
     * @brief Gets the GPIO number the button is connected to.
     * 
     * @returns The integer number of the GPIO.
     */
    gpio_num_t get_num();

    // Class constants
    static const char *TAG;
    static const uint32_t DEBOUNCE_MS = 50;

    // Class variables
    static std::vector<Button*> buttons;
    static xQueueHandle gpio_evt_queue;

    // Class functions
    /**
     * @brief Configures all buttons GPIO
     */
    static void config_gpio();
};

#endif /* _BUTTON_H_ */