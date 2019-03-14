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

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <Game.h>
#include <Interface.h>
#include <Audio.h>
#include <Button.h>
#include <Led.h>

#include "moeda.h" // Just for testing
#include "presa.h"
#include "caxixi.h"
#include "solta.h"

// Members that are added to a static vector inside the class must be initialized here.
static Button b_moeda(GPIO_NUM_39);
static Button b_caxixi(GPIO_NUM_36);
static Button b_presa(GPIO_NUM_34);
static Button b_solta(GPIO_NUM_35);

static Button b_blue(GPIO_NUM_17);
static Button b_red(GPIO_NUM_18);
static Button b_green(GPIO_NUM_19);
static Button b_pink(GPIO_NUM_16);

static Button b_left(GPIO_NUM_23);
static Button b_right(GPIO_NUM_22);
static Button b_up(GPIO_NUM_32);
static Button b_down(GPIO_NUM_33);

static Audio DRAM_ATTR a_moeda(moeda_data, moeda_length);
static Audio DRAM_ATTR a_caxixi(caxixi_data, caxixi_length, false);
static Audio DRAM_ATTR a_solta(solta_data, solta_length);
static Audio DRAM_ATTR a_presa(presa_data, presa_length);

static Led l_moeda(GPIO_NUM_5);
static Led l_caxixi(GPIO_NUM_4);
static Led l_presa(GPIO_NUM_0);
static Led l_solta(GPIO_NUM_2);

static const char* TAG = "MAIN";

extern "C" void app_main()
{
    Interface::pre_init(); // Init the LCD and the Semaphore first for loading screen

    Interface::set_button(&b_blue, Interface::Direction::D_X);
    Interface::set_button(&b_red, Interface::Direction::D_O);
    Interface::set_button(&b_green, Interface::Direction::D_T);
    Interface::set_button(&b_pink, Interface::Direction::D_S);

    Interface::set_button(&b_right, Interface::Direction::D_RIGHT);
    Interface::set_button(&b_left, Interface::Direction::D_LEFT);
    Interface::set_button(&b_up, Interface::Direction::D_UP);
    Interface::set_button(&b_down, Interface::Direction::D_DOWN);

    Game::set_button(&b_moeda, Game::Instrument::MOEDA);
    Game::set_button(&b_caxixi, Game::Instrument::CAXIXI);
    Game::set_button(&b_presa, Game::Instrument::PRESA);
    Game::set_button(&b_solta, Game::Instrument::SOLTA);

    Game::set_audio(&a_moeda, Game::Instrument::MOEDA);
    Game::set_audio(&a_caxixi, Game::Instrument::CAXIXI);
    Game::set_audio(&a_presa, Game::Instrument::PRESA);
    Game::set_audio(&a_solta, Game::Instrument::SOLTA);

    Game::set_led(&l_moeda, Game::Instrument::MOEDA);
    Game::set_led(&l_caxixi, Game::Instrument::CAXIXI);
    Game::set_led(&l_presa, Game::Instrument::PRESA);
    Game::set_led(&l_solta, Game::Instrument::SOLTA);

    xTaskCreate(Interface::task, "Interface Task", 16384, nullptr, 6, nullptr);

    Audio::init();  // TimerG0 Timer0 interrupt 44.1KHz for Audio.

    xTaskCreate(Button::task, "Button_task", 2048, nullptr, 11, nullptr);   // Updates the Button status.
    xTaskCreate(Game::task, "Game task", 8192, nullptr, 10, nullptr);
    xTaskCreate(Led::task, "LED Task", 2048, nullptr, 8, nullptr);  // Sets and updates led status
    xTaskCreate(Game::urm_task, "URM Task", 2048, nullptr, 7, nullptr); // Sets the muffle cutoff based on URM
}