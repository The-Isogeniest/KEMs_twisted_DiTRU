#ifndef POLY_H
#define POLY_H

#include "params.h"
#include <stddef.h>
#include <stdint.h>

#define MODQ(X) ((X) & (tDiTRU_Q-1))

typedef struct{
  uint16_t coeffs[ORDER];
} poly;

#define poly_mod_3_Phi_n CRYPTO_NAMESPACE(poly_mod_3_Phi_n)
#define poly_mod_q_Phi_n CRYPTO_NAMESPACE(poly_mod_q_Phi_n)
#define poly_mod_3_Phi_n_tDiTRU CRYPTO_NAMESPACE(poly_mod_3_Phi_n_tDiTRU)
#define poly_mod_q_Phi_n_tDiTRU CRYPTO_NAMESPACE(poly_mod_q_Phi_n_tDiTRU)
#define rotinv CRYPTO_NAMESPACE(rotinv)
#define rotinv_S CRYPTO_NAMESPACE(rot_inv_S)
#define get_minus CRYPTO_NAMESPACE(get_minus)
#define get_minus_S3 CRYPTO_NAMESPACE(get_minus_S3)
#define rotinv_S3 CRYPTO_NAMESPACE(rotinv_S3)

void poly_mod_3_Phi_n(poly *r);
void poly_mod_q_Phi_n(poly *r);
void poly_mod_3_Phi_n_tDiTRU(poly *r);
void poly_mod_q_Phi_n_tDiTRU(poly *r);
void rotinv(poly *r1, poly *r2);
void rotinv_S(poly *r1, poly *r2);
void rotinv_S3(poly *r1, poly *r2);
void get_minus(poly *r);
void get_minus_S3(poly *r);



#define poly_Sq_tobytes CRYPTO_NAMESPACE(poly_Sq_tobytes)
#define poly_Sq_frombytes CRYPTO_NAMESPACE(poly_Sq_frombytes)
void poly_Sq_tobytes(unsigned char *r, const poly *a);
void poly_Sq_frombytes(poly *r, const unsigned char *a);

#define poly_Rq_sum_zero_tobytes CRYPTO_NAMESPACE(poly_Rq_sum_zero_tobytes)
#define poly_Rq_sum_zero_frombytes CRYPTO_NAMESPACE(poly_Rq_sum_zero_frombytes)
void poly_Rq_sum_zero_tobytes(unsigned char *r, const poly *a);
void poly_Rq_sum_zero_frombytes(poly *r, const unsigned char *a);

#define poly_S3_tobytes CRYPTO_NAMESPACE(poly_S3_tobytes)
#define poly_S3_frombytes CRYPTO_NAMESPACE(poly_S3_frombytes)
#define poly_S3_frombytes_tDiTRU CRYPTO_NAMESPACE(poly_S3_frombytes_tDiTRU)
void poly_S3_tobytes(unsigned char msg[tDiTRU_PACK_TRINARY_BYTES], const poly *a);
void poly_S3_frombytes(poly *r, const unsigned char msg[tDiTRU_PACK_TRINARY_BYTES]);
void poly_S3_frombytes_tDiTRU(poly *r, const unsigned char msg[tDiTRU_PACK_TRINARY_BYTES]);

#define poly_Sq_mul CRYPTO_NAMESPACE(poly_Sq_mul)
#define poly_Rq_mul CRYPTO_NAMESPACE(poly_Rq_mul)
#define poly_S3_mul CRYPTO_NAMESPACE(poly_S3_mul)
#define poly_Rq_mul_tDiTRU CRYPTO_NAMESPACE(poly_Rq_mul_tDiTRU)
#define poly_lift CRYPTO_NAMESPACE(poly_lift)
#define poly_Rq_to_S3 CRYPTO_NAMESPACE(poly_Rq_to_S3)
#define poly_S3_inv_tDiTRU CRYPTO_NAMESPACE(poly_S3_inv_tDiTRU)
#define poly_Sq_mul_tDiTRU CRYPTO_NAMESPACE(poly_Sq_mul_tDiTRU)
#define poly_S3_mul_tDiTRU CRYPTO_NAMESPACE(poly_S3_mul_tDiTRU)
void poly_Sq_mul(poly *r, const poly *a, const poly *b);
void poly_Rq_mul(poly *r, const poly *a, const poly *b);
void poly_S3_mul(poly *r, const poly *a, const poly *b);
void poly_Rq_mul_tDiTRU(poly *r, const poly *a, const poly *b, bool a_trinary);
void poly_lift(poly *r, const poly *a);
void poly_Rq_to_S3(poly *r, const poly *a);
void poly_S3_inv_tDiTRU(poly *r , const poly *a);
void poly_Sq_mul_tDiTRU(poly *r, const poly *a, const poly *b);
void poly_S3_mul_tDiTRU(poly *r, const poly *a, const poly *b);

#define poly_R2_inv CRYPTO_NAMESPACE(poly_R2_inv)
#define poly_Rq_inv CRYPTO_NAMESPACE(poly_Rq_inv)
#define poly_S3_inv CRYPTO_NAMESPACE(poly_S3_inv)
#define poly_Rq_inv_tDiTRU CRYPTO_NAMESPACE(poly_Rq_inv_tDiTRU)
#define poly_Sq_inv CRYPTO_NAMESPACE(poly_Sq_inv)
void poly_R2_inv(poly *r, const poly *a);
void poly_Rq_inv(poly *r, const poly *a);
void poly_S3_inv(poly *r, const poly *a);
void poly_Rq_inv_tDiTRU(poly *r, const poly *a);
void poly_Sq_inv(poly *r, const poly *a);

#define poly_Z3_to_Zq CRYPTO_NAMESPACE(poly_Z3_to_Zq)
#define poly_Z3_to_Zq_tDiTRU CRYPTO_NAMESPACE(poly_Z3_to_Zq_tDiTRU)
#define poly_trinary_Zq_to_Z3 CRYPTO_NAMESPACE(poly_trinary_Zq_to_Z3)
#define poly_trinary_Zq_to_Z3_tDiTRU CRYPTO_NAMESPACE(poly_trinary_Zq_to_Z3_tDiTRU)


void poly_Z3_to_Zq(poly *r);
void poly_trinary_Zq_to_Z3(poly *r);
void poly_trinary_Zq_to_Z3_tDiTRU(poly *r);
void poly_Z3_to_Zq_tDiTRU(poly *r);
#endif

#define get_minus CRYPTO_NAMESPACE(get_minus)
void get_minus(poly *u);
