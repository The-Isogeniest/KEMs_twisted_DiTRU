#include "poly.h"
#include "helper_print.h"
static inline uint8_t mod3(uint8_t a) /* a between 0 and 9 */
{
  int16_t t, c;
  a = (a >> 2) + (a & 3); /* between 0 and 4 */
  t = a - 3;
  c = t >> 5;
  return (uint8_t) (t^(c&(a^t)));
}
void poly_Rq_mul(poly *r, const poly *a, const poly *b)
{
  int k,i;

  for(k=0; k<N; k++)
  {
    r->coeffs[k] = 0;
    for(i=1; i<N-k; i++)
      r->coeffs[k] += a->coeffs[k+i] * b->coeffs[N-i];
    for(i=0; i<k+1; i++)
      r->coeffs[k] += a->coeffs[k-i] * b->coeffs[i];
  }
}
void get_minus(poly *u){
  /*
    Input: a polynomial u in R_q.
    Output: the minus of this polynomial; each coefficient is replaced by (Q-its value)
  */
  for(int i=0;i<N;i++){
    u->coeffs[i] = MODQ(tDiTRU_Q-u->coeffs[i]);
  }
}
void get_minus_S3(poly *u){
  /*
     Input:  a polynomial with coefficients in {0,1,2}
     Output: The polynomial with -{the coefficients in place}
  */
  for(int i=0;i<N;i++){
    u->coeffs[i] = mod3(2*u->coeffs[i]); //maps 1 to 2, 2 to 1 and 0 to 0
  }
}

void rotinv(poly *u, poly *u1){           //ring one for R ring and zero for S ring
  u1->coeffs[0]=u->coeffs[0];
  for(int i=1;i<N;i++){
    u1->coeffs[i] = u->coeffs[N-i];
  }
}
void rotinv_S(poly *u , poly *u1){
  u1->coeffs[0]=u->coeffs[0];
  for(int i=1;i<N;i++){
    u1->coeffs[i] = u->coeffs[N-i];
  }
  for(int i=0;i<N;i++){
    u1->coeffs[i] = u1->coeffs[i]-u1->coeffs[N-1];
  }
}


void rotinv_S3(poly *u, poly *u1)
{
  /* Input:  -u1 a polynomial, the input has coefficients in {0,1,2}
     Output: -The conjegute in S3 
  */
  u1->coeffs[0]=u->coeffs[0];
  for(int i=1;i<N;i++){
    u1->coeffs[i] = u->coeffs[N-i];
  }
  for(int i=0;i<N;i++){
    u1->coeffs[i] = mod3(u1->coeffs[i]+2*u1->coeffs[N-1]);
  }
}
void poly_Rq_mul_tDiTRU(poly *r, const poly *a, const poly *b, bool trinary_a){
  /*
  Rq_mul_tDiTRU: - Input: a,b: two polynomials from the underlying tDiTRU ring
                          trinary_a: a boolean value; True idicates the first input is trinary, False otherwise
                 - Output: r: the result of multiplication
  */

  poly x0,x1,x2,x3, x4,x5,x6;
  poly *a0 =&x0, *a1=&x1, *b0=&x2, *b1=&x3, *tmp1=&x4, *tmp2=&x5, *tmp3=&x6;
  int i;

  for(i=0;i<N;i++)
  {
    a0->coeffs[i] = a->coeffs[i];
    b0->coeffs[i] = b->coeffs[i];
    a1->coeffs[i] = a->coeffs[N+i];
    b1->coeffs[i] = b->coeffs[N+i];
  }
    poly_Rq_mul(tmp1, a0,b0);
    rotinv(a1,tmp3);   

    if (trinary_a)
    {
       get_minus_S3(tmp3);
    }
    else
    {
      get_minus(tmp3);
    }
  

    poly_Rq_mul(tmp2,tmp3,b1);

    for(i=0;i<N;i++)
      {
        r->coeffs[i] = MODQ(tmp1->coeffs[i]+tmp2->coeffs[i]);
      }

    poly_Rq_mul(tmp1, a1,b0);


    rotinv(a0,tmp3 );                  
    poly_Rq_mul(tmp2,tmp3,b1);

     for(i=0;i<N;i++)
      {
        r->coeffs[N+i] = MODQ(tmp1->coeffs[i]+tmp2->coeffs[i]);
      }
}

