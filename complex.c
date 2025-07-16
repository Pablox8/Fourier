#include "complex.h"
#include <math.h>

/**
 * Adds two complex numbers and returns the result.
 */
Complex add(Complex c1, Complex c2) {
    Complex result;
    result.x = c1.x + c2.x;
    result.y = c1.y + c2.y;
    return result;
}

/**
 * Multiplies two complex numbers and returns the result.
 */
Complex multiply(Complex a, Complex b) {
    Complex result;
    result.x = a.x * b.x - a.y * b.y;
    result.y = a.x * b.y + a.y * b.x;
    return result;
}

/**
 * Returns the modulus of a complex number.
 */
float modulus(Complex c) {
    return sqrtf(c.x * c.x + c.y * c.y);
}

/**
 * Returns the argument of a complex number.
 */
float argument(Complex c) {
    return atan2f(c.y, c.x);
}