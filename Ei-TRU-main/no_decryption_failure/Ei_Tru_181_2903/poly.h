#ifndef POLY_H
#define POLY_H

#include "params.h"
#include "uint32.h"
#include <stdio.h>

#include <stddef.h>
#include <stdint.h>

typedef struct{
    int a;
    int b;
}Term;



#define poly_Zw_add CRYPTO_NAMESPACE(poly_Zw_add)
#define poly_Zw_add3 CRYPTO_NAMESPACE(poly_Zw_add3)
#define poly_Zw_sub CRYPTO_NAMESPACE(poly_Zw_sub)
void poly_Zw_add(const Term* a, const Term* b, Term *r);
void poly_Zw_add3(const Term* a, const Term* b,const Term* c, Term *r);
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

#define Zw_CnC3_multiply CRYPTO_NAMESPACE(Zw_CnC3_multiply)
void Zw_CnC3_multiply(Term *f, Term *g, Term *r);

#define ZwCnC3_add CRYPTO_NAMESPACE(ZwCnC3_add)
#define ZwCnC3_sub CRYPTO_NAMESPACE(ZwCnC3_sub)
#define ZwCnC3_mod_q CRYPTO_NAMESPACE(ZwCnC3_mod_q)
void ZwCnC3_add(const Term* a, const Term *b, Term* r);
void ZwCnC3_sub(const Term* a, const Term *b, Term* r);
void ZwCnC3_mod_q(const Term* a, Term q, Term* r);


#endif









