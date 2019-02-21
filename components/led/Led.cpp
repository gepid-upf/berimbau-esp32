/**
 * @file Led.cpp
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief Source file for managing the LED blink.
 */

#include <Led.h>

#include <freertos/task.h>

#include <Interface.h>

std::vector<Led*> Led::leds;
const char *Led::TAG = "LED";

Led::Led(gpio_num_t _gpio_num) : gpio_num(_gpio_num), stop_time(0), lit(false)
{
    mtx = xSemaphoreCreateMutex();
    leds.push_back(this);
}

gpio_num_t Led::get_num()
{
    return gpio_num;
}

void Led::blink(uint16_t delay_ms)
{
    xSemaphoreTake(mtx, portMAX_DELAY);
    lit = true;
    stop_time = xTaskGetTickCount() + delay_ms / portTICK_PERIOD_MS;
    gpio_set_level(gpio_num, 1);
    xSemaphoreGive(mtx);
}

void Led::turn_off()
{
    xSemaphoreTake(mtx, portMAX_DELAY);
    lit = false;
    gpio_set_level(gpio_num, 0);
    xSemaphoreGive(mtx);
}

void Led::check()
{
    xSemaphoreTake(mtx, portMAX_DELAY);
    if(lit && stop_time <= xTaskGetTickCount()){
        lit = false;
        gpio_set_level(gpio_num, 0);
    }
    xSemaphoreGive(mtx);
}

void Led::init()
{
    uint32_t gpio_sel = 0;

    for(int i = 0; i < leds.size(); i++){
        gpio_sel |= BIT(leds[i]->get_num());
    }

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
    io_conf.pin_bit_mask = gpio_sel;
    gpio_config(&io_conf);

    for(int i = 0; i < leds.size(); i++){
        gpio_set_level(leds[i]->get_num(), 0);
    }
}

void Led::task(void *nullpar)
{
    init();

    Interface::loaded();

    while(true){
        for(int i = 0; i < leds.size(); i++){
            leds[i]->check();
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}