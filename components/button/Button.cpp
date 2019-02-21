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
 * @brief Source for the Button class that manages buttons with interruptions and debouncing.
 */

#include <Button.h>

#include <freertos/task.h>

#include <Interface.h>

std::vector<Button*> Button::buttons;
const char *Button::TAG = "Button";
xQueueHandle Button::gpio_evt_queue = nullptr;

// https://github.com/espressif/esp-idf/blob/65d01336d39e666cca4f465dcb89b633e3f6c90a/examples/peripherals/gpio/main/gpio_example_main.c
// ISR
void IRAM_ATTR gpio_isr_handler(void* button)
{
    static uint32_t DRAM_ATTR gpio_num;
    gpio_num = (uint32_t)button;
    xQueueSendFromISR(Button::gpio_evt_queue, &gpio_num, nullptr);
}

// Object functions
Button::Button(gpio_num_t _gpio_num) : gpio_num(_gpio_num), last_press(0),
                                        last_unpress(0), pin_state(State::UNPRESSED)
{
    mtx = xSemaphoreCreateMutex();
    buttons.push_back(this);
}

gpio_num_t Button::get_num()
{
    return gpio_num;
}

void Button::update(bool level, uint32_t current_tick)
{
    xSemaphoreTake(mtx, portMAX_DELAY);
    switch(pin_state){
    case State::UNPRESSED:
        if(!level && current_tick - last_unpress > DEBOUNCE_MS){
            pin_state = State::PRESSED;
            last_press = current_tick;
        }        
        break;
    case State::PRESSED:
    case State::UNRELEASED:
        if(level && current_tick - last_press > DEBOUNCE_MS){
            pin_state = State::UNPRESSED;
            last_unpress = current_tick;
        }
        break;
    }
    xSemaphoreGive(mtx);
}

Button::State Button::get_state()
{
    State ret;
    xSemaphoreTake(mtx, portMAX_DELAY);
    switch(pin_state){
    case State::PRESSED:
        pin_state = State::UNRELEASED;
        ret = State::PRESSED;
        break;
    default:
        ret = pin_state;
        break;
    }
    xSemaphoreGive(mtx);
    return ret;
}

// Class functions
void Button::config_gpio()
{
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    
    // ESP_INTR_FLAG_IRAM
    gpio_install_isr_service(0);

    for(int i = 0; i < buttons.size(); i++){
        gpio_set_direction(buttons[i]->get_num(), GPIO_MODE_INPUT);
        gpio_set_intr_type(buttons[i]->get_num(), GPIO_INTR_ANYEDGE);
        if(buttons[i]->get_num() < 34) gpio_set_pull_mode(buttons[i]->get_num(), GPIO_PULLUP_ONLY);
        gpio_isr_handler_add(buttons[i]->get_num(), gpio_isr_handler, (void*)buttons[i]->get_num());
        gpio_intr_enable(buttons[i]->get_num());
    }
    
}

void Button::task(void *nullpar)
{
    config_gpio();

    uint32_t current_tick;
    uint32_t io_num = 0; 
    bool io_level = false;

    Interface::loaded();
    
    while(true){
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)){  // Queue acts as Semaphore, but receives a value.
            io_level = gpio_get_level((gpio_num_t)io_num);          // Get the logic level that interrupted
            current_tick = xTaskGetTickCount() * portTICK_PERIOD_MS; // And the tick that ocurred
            for(int i = 0; i < buttons.size(); i++) {
                if(io_num == buttons[i]->get_num()){                // Updates wich button triggered the interrupt.
                    buttons[i]->update(io_level, current_tick);
                    break;
                }
            }
        }
    }
}