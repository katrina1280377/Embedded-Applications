#ifndef COMPLEX_H
#define COMPLEX_H

/*! FILE: complex.h
 *  Complex Header file for complex number functions
 *
 *  This file contains the prototypes for the complex number functions
 *  implemented in complex.c
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complex numbers together
 *  \param a The first addend
 *  \param b The second addend
 */
Complex add ( Complex a, Complex b );

/*! Negate a complex number
 *  \param a The complex number to negate
 */
Complex negate ( Complex a );

/*! Multiply two complex numbers together
 *  \param a The first factor
 *  \param b The second factor
 */
Complex multiply ( Complex a, Complex b );

/*! Calculate the magnitude of a complex number
 *  \param a The complex number
 */
double magnitude ( Complex a );

#endif