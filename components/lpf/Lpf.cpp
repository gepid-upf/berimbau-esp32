/**
 * @file Lpf.cpp
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief Sources for single-pole low-pass filter.
 */

#include <Lpf.h>

#include <esp_attr.h>

Lpf::Lpf(uint32_t sample_freq, uint32_t cutoff) : Fs(sample_freq)
{
    y = 0;
    alpha = (double)cutoff/Fs;
}

void Lpf::set_cutoff(uint32_t cutoff)
{
    alpha = double(cutoff)/Fs;
}

int32_t IRAM_ATTR Lpf::update(int32_t x)
{
    y += alpha*(x - y);
    return y;
}