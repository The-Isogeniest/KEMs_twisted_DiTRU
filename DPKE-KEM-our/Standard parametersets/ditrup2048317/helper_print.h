#ifndef HELPER_PRINT_H
#define HELPER_PRINT_H

#include "params.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "poly.h"

// Function declarations

#define print_poly_values CRYPTO_NAMESPACE(print_poly_values)
#define print_poly_values_n CRYPTO_NAMESPACE(print_poly_values_n)
void print_poly_values(const poly *r);
void print_poly_values_n(const poly *r);


#endif // HELPER_PRINT_H
