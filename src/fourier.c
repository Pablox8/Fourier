#include "../inc/fourier.h"
#include <stdlib.h>
#include <math.h>

/**
 * Compares the amplitude of the 2 arguments (a and b) in descending order and returns:
 * 
 *     -1: If the amplitude of a is greater than the amplitude of b.
 *      1: If the amplitude of a is smaller than the amplitude of b.
 *      0: If the amplitude of a and b are equal.
 * 
 * Used to sort an array of FourierCoeffs.
 */
int compare_amplitude_desc(const void* a, const void* b) {
    FourierCoeff* coeff_a = (FourierCoeff*)a;
    FourierCoeff* coeff_b = (FourierCoeff*)b;
    
    if (coeff_a->amplitude > coeff_b->amplitude) return -1;
    if (coeff_a->amplitude < coeff_b->amplitude) return 1;
    
    return 0;
}

/**
 * Sorts the array by amplitude in descending order.
 */
void sort_by_amplitude_desc(FourierCoeff* coeffs, int N) {
    qsort(coeffs, N, sizeof(FourierCoeff), compare_amplitude_desc);
}

/**
 * Computes the Discrete Fourier Transform (DFT) of a sequence of complex points.
 * Returns an array of Fourier coefficients sorted by descending amplitude.
 * 
 * The coefficients are usually sorted by frequency rather than amplitude, 
 * but I prefer how the epicycles look like when sorting by amplitude.
 */
FourierCoeff* DFT(Complex *points, int N) {
    FourierCoeff* coeffs = (FourierCoeff *)malloc(sizeof(FourierCoeff) * N);
    if (!coeffs) return NULL;

    int start_k = -N / 2;
    int end_k = start_k + N;
    int c_index = 0;

    for (int k = start_k; k < end_k; k++) {
        Complex sum = { 0.0f, 0.0f };
        
        for (int n = 0; n < N; n++) {
            float angle = 2.0f * PI * k / N * n;
            Complex x_n = points[n];
            Complex exp = {
                cosf(angle),
                -sinf(angle)
            };

            Complex result = multiply(x_n, exp);
            sum = add(sum, result);
        }
        sum.x = sum.x / N;
        sum.y = sum.y / N;

        coeffs[c_index].frequency = k;
        coeffs[c_index].amplitude = modulus(sum);
        coeffs[c_index].phase = argument(sum);

        c_index++;
    }

    sort_by_amplitude_desc(coeffs, N);

    return coeffs;
}