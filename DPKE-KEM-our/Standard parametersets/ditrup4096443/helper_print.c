#include "helper_print.h"
#include <stdio.h>
#include "poly.h"





// Function to print polynomial values for r 
void print_poly_values(const poly *r) {
    // printf("Polynomial coeff values are here:\n");
    for (int i = 0; i < ORDER; i++) {
        printf("%d, ", r->coeffs[i]);
    }
    printf("\n");
}

// Function to print polynomial values for r 
void print_poly_values_n(const poly *r) {
    // printf("Polynomial coeff values are here:\n");
    for (int i = 0; i < N; i++) {
        printf("%d, ", r->coeffs[i]);
    }
    printf("\n");
}

