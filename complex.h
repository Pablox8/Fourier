#ifndef COMPLEX_H
#define COMPLEX_H

#include "raylib.h"

/**
 * Raylib Vector2 definition:
 *     float x
 *     float y
 * 
 * Complex number representation:
 *     z = x + i*y
 */
typedef Vector2 Complex;

/**
 * Adds two complex numbers and returns the result.
 */
Complex add(Complex, Complex);

/**
 * Multiplies two complex numbers and returns the result.
 */
Complex multiply(Complex, Complex);

/**
 * Returns the modulus of a complex number.
 */
float modulus(Complex);

/**
 * Returns the argument of a complex number.
 */
float argument(Complex);

#endif