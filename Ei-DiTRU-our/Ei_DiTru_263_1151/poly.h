#ifndef POLY_H
#define POLY_H

#include "params.h"
#include "uint32.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>


typedef struct{
    int a;
    int b;
}Term;


typedef struct
{
    Term *a;
    Term *b;
}group_ring;



#define poly_Zw_add CRYPTO_NAMESPACE(poly_Zw_add)
#define poly_Zw_add2 CRYPTO_NAMESPACE(poly_Zw_add2) //added newly
#define poly_Zw_sub2 CRYPTO_NAMESPACE(poly_Zw_sub2)
#define poly_Zw_sub CRYPTO_NAMESPACE(poly_Zw_sub)

void poly_Zw_add(const Term* a, const Term* b, Term *r);
void poly_Zw_add2(const Term* a, const Term* b, Term *r);
void poly_Zw_sub2(const Term* a, const Term* b, Term *r); //added newly to substract two polynomials over Z[w]D_N
void poly_Zw_sub(const Term* a, const Term* b, Term *r);

#define poly_Zw_mul CRYPTO_NAMESPACE(poly_Zw_mul)
#define poly_Zw_mul_mod_q CRYPTO_NAMESPACE(poly_Zw_mul_mod_q)
#define Zw_add CRYPTO_NAMESPACE(Zw_add)
#define Zw_sub CRYPTO_NAMESPACE(Zw_sub)
#define multiply_terms CRYPTO_NAMESPACE(multiply_terms)

#define Zw_multiply CRYPTO_NAMESPACE(Zw_multiply)
#define poly_Zw_mul_p CRYPTO_NAMESPACE(poly_Zw_mul_p)
#define isSame CRYPTO_NAMESPACE(isSame)

Term Zw_multiply(Term t1, Term t2);
Term Zw_add(Term t1, Term t2);
Term Zw_sub(Term t1, Term t2);
Term multiply_terms(Term t1, Term t2);




int isSame(Term A,Term B);
void poly_Zw_mul(const Term* f, const Term* g, Term *r);
void poly_Zw_mul_mod_q(const Term* f, const Term* g, Term q,Term *r);
void poly_Zw_mul_p(Term *r, Term P,int len);

#define poly_Zw_mod_q CRYPTO_NAMESPACE(poly_Zw_mod_q)
#define poly_div_rat CRYPTO_NAMESPACE(poly_div_rat)
Term poly_div_rat(Term A, Term q);
void poly_Zw_mod_q(const Term* a, Term q, Term *r);

#define poly_Zw_print CRYPTO_NAMESPACE(poly_Zw_print)
void poly_Zw_print(Term *p,int len);

#define poly_Zw_shift_t CRYPTO_NAMESPACE(poly_Zw_shift_t)
void poly_Zw_shift_t(const Term*f ,int t, Term *r);

#define poly_Zw_cmp CRYPTO_NAMESPACE(poly_Zw_cmp)
int poly_Zw_cmp(const Term* a, const Term *b,int len);

#define Zw_DN_multiply CRYPTO_NAMESPACE(Zw_DN_multiply)
void Zw_DN_multiply(Term *f, Term *g, Term *r);

#define ZwDN_add CRYPTO_NAMESPACE(ZwDN_add)
#define ZwDN_sub CRYPTO_NAMESPACE(ZwDN_sub)
#define ZwDN_mod_q CRYPTO_NAMESPACE(ZwDN_mod_q)
void ZwDN_add(const Term* a, const Term *b, Term* r);
void ZwDN_sub(const Term* a, const Term *b, Term* r);
void ZwDN_mod_q(const Term* a, Term q, Term* r);

#define rotinv CRYPTO_NAMESPACE(rotinv)
void rotinv(const Term* a, Term *b);

#define poly_to_CnC3 CRYPTO_NAMESPACE(poly_to_CnC3)
void poly_to_DN(Term* p,group_ring* result);


#endif









