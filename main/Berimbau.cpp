/**
 * @file Berimbau.cpp
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief Berimbau is a digital toy to help kids with music learning.
 */

/**
 * Pin assignment:
 *      GPIO25  -   DAC Channel 1 (MSB)
 *      GPIO26  -   DAC Channel 2 (LSB)
 * 
 *      GPIO23  -   Button "Moeda"
 *      GPIO22  -   Button "Presa"
 *      GPIO18  -   Button "Caxixi"
 *      GPIO19  -   Button "Solta"
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <Audio.h>
#include <Button.h>
#include <Led.h>
#include <Urm37.h>

#include "moeda.h" // Just for testing
#include "presa.h"
#include "caxixi.h"
#include "solta.h"

static Button b_moeda(GPIO_NUM_23);
static Button b_caxixi(GPIO_NUM_22);
static Button b_solta(GPIO_NUM_19);
static Button b_presa(GPIO_NUM_18);

static Audio a_moeda(moeda_data, moeda_length);
static Audio a_caxixi(caxixi_data, caxixi_length, false);
static Audio a_solta(solta_data, solta_length);
static Audio a_presa(presa_data, presa_length);

static Led l_moeda(GPIO_NUM_5);
static Led l_caxixi(GPIO_NUM_17);
static Led l_solta(GPIO_NUM_4);
static Led l_presa(GPIO_NUM_16);

static Urm37 urm(GPIO_NUM_2, GPIO_NUM_15);

static const char* TAG = "MAIN";

static void btn_tmp_task(void *param)
{
    while(true){
        vTaskDelay(10 / portTICK_PERIOD_MS);
        // Check buttons. Can be done outside of ISR (dont need 44.1KHz, maybe 1KHz is OK)
        if(b_moeda.get_state() == Button::State::PRESSED) {
            a_moeda.set_active();
            a_solta.set_active(false); // Moeda (coin) presses the string and the solta (loose) sound stops.
            l_moeda.blink(a_moeda.get_length()/44.101);
            l_solta.turn_off();
        }
        if(b_presa.get_state() == Button::State::PRESSED){
            a_presa.set_active();
            a_solta.set_active(false);
            l_presa.blink(a_presa.get_length()/44.101);
            l_solta.turn_off();
        }
        if(b_caxixi.get_state() == Button::State::PRESSED){
            a_caxixi.set_active();
            l_caxixi.blink(a_caxixi.get_length()/44.101);
        }
        if(b_solta.get_state() == Button::State::PRESSED){
            a_solta.set_active();
            l_solta.blink(a_solta.get_length()/44.101);
        }
    }
}

static void urm_task(void *nullpar)
{
    urm.init();

    while(true){
        if(urm.pulse_trigger()) // No need for vTaskDelay. It already has a semaphore inside.
            Audio::set_muffle_cutoff(urm.get_pulse_us()*20);
    }
}

extern "C" void app_main()
{
    Audio::init();  // TimerG0 Timer0 interrupt 44.1KHz for Audio.
    xTaskCreate(Button::task, "Button_task", 2048, nullptr, 11, nullptr);   // Updates the Button status.
    xTaskCreate(Led::task, "LED Task", 2048, nullptr, 8, nullptr);
    
    xTaskCreate(btn_tmp_task, "Temp Button Task", 2048, nullptr, 10, nullptr);  // Test task
    xTaskCreate(urm_task, "URM Task", 2048, nullptr, 7, nullptr);  // Test task
}