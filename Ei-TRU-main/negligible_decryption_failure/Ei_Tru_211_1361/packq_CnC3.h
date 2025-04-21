#ifndef PACKQ_CnC3_H
#define PACKQ_CnC3_H

#include "poly.h"
#include<stdio.h>

#define poly_pack_Sq_tobytes CRYPTO_NAMESPACE(poly_pack_Sq_tobytes)
#define poly_unpack_Sq_frombytes CRYPTO_NAMESPACE(poly_unpack_Sq_frombytes)
void poly_pack_Sq_tobytes(unsigned char *r, Term *a);
void poly_unpack_Sq_frombytes(Term *r, const unsigned char *a);

#endif
