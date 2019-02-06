/**
 * @file Lpf.h
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @copyright
 * Copyright 2018 Angelo Elias Dalzotto
 * 
 * @brief Single-pole low-pass filter. Instructions in:
 * https://www.embeddedrelated.com/showarticle/779.php
 */

#ifndef _LPF_H_
#define _LPF_H_

#include <stdint.h>

class Lpf {
public:
    /**
     * @brief Class constructor. Sets basic parameters.
     * 
     * @param sample_freq The sampling frequency of the signal to be modified.
     * @param cutoff The cutoff frequency of the filter.
     */
    Lpf(uint32_t sample_freq = 44100, uint32_t cutoff = 20000);
    
    /**
     * @brief Changes the cutoff frequency of the filter.
     * 
     * @param cutoff The new cutoff frequency.
     */
    void set_cutoff(uint32_t cutoff);
    
    /**
     * @brief Filters the current input and returns the output.
     * 
     * @param x The input of the filter.
     * 
     * @return The output of the filter "y";
     */
    int32_t update(int32_t x);

private:
    uint32_t Fs; // sample frequency
    int32_t y;   // Output
    double alpha; // alpha = Fs/Fc

};

#endif /* _LPF_H_ */