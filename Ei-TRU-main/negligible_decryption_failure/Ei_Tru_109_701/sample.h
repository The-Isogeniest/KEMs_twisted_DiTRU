#ifndef SAMPLE_H
#define SAMPLE_H

#include "params.h"
#include "poly.h"
#include "poly_r.h"
#include "crypto_sort_int32.h"

#define sample_lf CRYPTO_NAMESPACE(sample_lf)
#define sample_fixed_type_lf_t CRYPTO_NAMESPACE(sample_fixed_type_lf_t)
#define sample_fixed_type_lf CRYPTO_NAMESPACE(sample_fixed_type_lf)
void sample_fixed_type_lf(int *r, const unsigned char u[N3_SAMPLE_BYTES]);
void sample_lf(Term* r,const unsigned char u[N3_SAMPLE_BYTES+T_SAMPLE_BYTES]);
void sample_fixed_type_lf_t(int *r, const unsigned char u[T_SAMPLE_BYTES]);

#define sample_lg CRYPTO_NAMESPACE(sample_lg)
#define sample_fixed_type_lg CRYPTO_NAMESPACE(sample_fixed_type_lg)
void sample_lg(Term* r,const unsigned char u[N3_SAMPLE_BYTES]);
void sample_fixed_type_lg(int *r, const unsigned char u[N3_SAMPLE_BYTES]);

#define sample_lphi CRYPTO_NAMESPACE(sample_lphi)
#define sample_phi CRYPTO_NAMESPACE(sample_phi)
void sample_lphi(Term* r,const unsigned char u[N3_SAMPLE_BYTES]);
void sample_phi(Term* phi,const Term* h, const Term* m);

#define sample_lm CRYPTO_NAMESPACE(sample_lm)
#define sample_fixed_type_lm CRYPTO_NAMESPACE(sample_fixed_type_lm)
#define sample_mask CRYPTO_NAMESPACE(sample_mask)
void sample_lm(Term *r, const unsigned char u[N3_SAMPLE_M_BYTES]);
void sample_fixed_type_lm(int *r, const unsigned char u[N3_SAMPLE_M_BYTES]);
void sample_mask(Term* mask,unsigned char t_seed[LENGTH_OF_HASH]);


#endif




