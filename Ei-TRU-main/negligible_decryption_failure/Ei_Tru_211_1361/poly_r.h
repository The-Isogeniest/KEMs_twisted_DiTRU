#ifndef POLY_R_H
#define POLY_R_H

#include "poly.h"

#include <stdlib.h>

typedef struct
{
    Term *a;
    Term *b;
    Term *c;
}group_ring;

#define poly_ZwCnC3_mul CRYPTO_NAMESPACE(poly_ZwCnC3_mul)
void poly_ZwCnC3_mul(group_ring* z, group_ring* a,int t,group_ring* result);

#define poly_ZwCnC3_add CRYPTO_NAMESPACE(poly_ZwCnC3_add)
void poly_ZwCnC3_add(group_ring* z, group_ring* a,group_ring* result);

#define poly_ZwCnC3_sub CRYPTO_NAMESPACE(poly_ZwCnC3_sub)
void poly_ZwCnC3_sub(group_ring* z, group_ring* a,group_ring* result);

#define poly_ZwCnC3_mod CRYPTO_NAMESPACE(poly_ZwCnC3_mod)
void poly_ZwCnC3_mod(group_ring* z, Term q,group_ring* result);

#define poly_ZwCnC3_print CRYPTO_NAMESPACE(poly_ZwCnC3_print)
void poly_ZwCnC3_print(group_ring* r);

#define poly_to_CnC3 CRYPTO_NAMESPACE(poly_to_CnC3)
void poly_to_CnC3(Term* p,group_ring* result);

#define CnC3_to_poly CRYPTO_NAMESPACE(CnC3_to_poly)
void CnC3_to_poly(group_ring* R, Term* a);


#endif







