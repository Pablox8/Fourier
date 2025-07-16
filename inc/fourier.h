#ifndef FOURIER_H
#define FOURIER_H

#include "complex.h"

/** 
 * Each Fourier coefficient encapsulates the amplitude and phase of a sinusoidal wave
 * of a determined frequency. 
 * 
 * Fourier coefficient definition:
 *     frequency: The velocity at which the epicycle is rotating
 *     amplitude: The radius of the epicycle
 *     phase: The angle that the epicycle has rotated so far
 */
typedef struct f_coeff {
    int frequency;
    float amplitude;
    float phase;
} FourierCoeff;

/**
 * Computes the Discrete Fourier Transform (DFT) of a sequence of complex points.
 * Returns an array of Fourier coefficients sorted by descending amplitude.
 * 
 * The coefficients are usually sorted by frequency rather than amplitude, 
 * but I prefer how the epicycles look like when sorting by amplitude.
 */
FourierCoeff* DFT(Complex *, int);

#endif