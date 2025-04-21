#ifndef INVERSE_H
#define INVERSE_H

#include "poly_r.h"
#include "poly.h"

// Term zero = {0,0};

#define deg CRYPTO_NAMESPACE(deg)
#define is_degree_one CRYPTO_NAMESPACE(is_degree_one)
int deg(Term *a,int len);
int is_degree_one(Term* a,int len);

#define division_by_x CRYPTO_NAMESPACE(division_by_x)
#define multiply_by_x CRYPTO_NAMESPACE(multiply_by_x)
void division_by_x(Term* a, int len);
void multiply_by_x(Term* a, int len);

#define unit CRYPTO_NAMESPACE(unit)
#define minus CRYPTO_NAMESPACE(minus)
#define round1 CRYPTO_NAMESPACE(round1)
#define norm_Zw CRYPTO_NAMESPACE(norm_Zw)
Term unit(Term u);
Term minus(Term A, Term B);
int round1(int c,int d);
int norm_Zw(Term element);

#define minus_Zw CRYPTO_NAMESPACE(minus_Zw)
#define red_q_etru CRYPTO_NAMESPACE(red_q_etru)
#define egcd_etru CRYPTO_NAMESPACE(egcd_etru)
#define find_inverse CRYPTO_NAMESPACE(find_inverse)
void minus_Zw(Term* a, Term *b, Term mod, Term* res,int len);
void red_q_etru(Term element,Term q, Term *res);
void egcd_etru(Term A,Term q,Term* r);
Term find_inverse(Term A,Term mod);

#define multiply_by_constant CRYPTO_NAMESPACE(multiply_by_constant)
#define reverse CRYPTO_NAMESPACE(reverse)
#define shiftRight_k CRYPTO_NAMESPACE(shiftRight_k)
#define swapArrays CRYPTO_NAMESPACE(swapArrays)
void multiply_by_constant(Term constant, Term* a,Term *res,int len,Term q);
void reverse(int i,int j,Term* a);
void shiftRight_k(Term *arr, int k,int len);
void swapArrays(Term* a,Term* b,int len);

#define Almost_inverse_ZpwCn CRYPTO_NAMESPACE(Almost_inverse_ZpwCn)
#define Almost_inverse_ZpwCnC3 CRYPTO_NAMESPACE(Almost_inverse_ZpwCnC3)
int Almost_inverse_ZpwCn(Term *a, int mod,Term* a_inv,int n);
int Almost_inverse_ZpwCnC3(Term *f,int mod,Term *res);

#define inverse_zq CRYPTO_NAMESPACE(inverse_zq)
#define inverse_zw CRYPTO_NAMESPACE(inverse_zw)
#define print_h  CRYPTO_NAMESPACE(print_h)


int inverse_zq(int x, int q);
Term inverse_zw(Term A, Term q);


void print_h();
#endif