 #include "poly.h"
 #include "helper_print.h"
#include <stdio.h>

 static inline uint8_t mod3(uint8_t a) /* a between 0 and 9 */
{
  int16_t t, c;
  a = (a >> 2) + (a & 3); /* between 0 and 4 */
  t = a - 3;
  c = t >> 5;
  return (uint8_t) (t^(c&(a^t)));
}

/* Map {0, 1, 2} -> {0,1,q-1} in place */
void poly_Z3_to_Zq(poly *r)
{
  int i;
  for(i=0; i<N; i++)
    r->coeffs[i] = r->coeffs[i] | ((-(r->coeffs[i]>>1)) & (tDiTRU_Q-1));
}
void poly_Z3_to_Zq_tDiTRU(poly *r)
{
  int i;
  for(i=0; i<N; i++)
    r->coeffs[i] = r->coeffs[i] | ((-(r->coeffs[i]>>1)) & (tDiTRU_Q-1));
  for(i=N; i<ORDER; i++)
    r->coeffs[i] = r->coeffs[i] | ((-(r->coeffs[i]>>1)) & (tDiTRU_Q-1));
}

/* Map {0, 1, q-1} -> {0,1,2} in place */
void poly_trinary_Zq_to_Z3(poly *r)
{
  int i;
  for(i=0; i<N; i++)  
  {
    r->coeffs[i] = MODQ(r->coeffs[i]);
    r->coeffs[i] = 3 & (r->coeffs[i] ^ (r->coeffs[i]>>(tDiTRU_LOGQ))); 
  }
}
void poly_trinary_Zq_to_Z3_tDiTRU(poly *r)
{
  int i;
  for(i=0; i<ORDER; i++)
  {
    r->coeffs[i] = MODQ(r->coeffs[i]);
    r->coeffs[i] = 3 & (r->coeffs[i] ^ (r->coeffs[i]>>(tDiTRU_LOGQ-1))); 
  }
 
}

void poly_Sq_mul(poly *r, const poly *a, const poly *b)
{
  poly_Rq_mul(r, a, b);
  poly_mod_q_Phi_n(r);
}

void poly_S3_mul(poly *r, const poly *a, const poly *b)
{
  poly_Rq_mul(r, a, b);
  poly_mod_3_Phi_n(r);
}

void poly_S3_mul_tDiTRU(poly *r, const poly *a, const poly *b)
{ 
  poly f,g,h;
  poly *x1=&f; 
  poly *x2=&g;
  poly *x3= &h;

  poly_Rq_mul_tDiTRU(r, a, b, True);
  for(int i=0; i<N ; i++){
     x1->coeffs[i]=r->coeffs[i];
     x2->coeffs[i]=r->coeffs[N+i];
  }

  poly_mod_3_Phi_n(x1);
  poly_mod_3_Phi_n(x2);


  for(int i=0; i<N ; i++){
    r->coeffs[i]=x1->coeffs[i];
    r->coeffs[N+i]=x2->coeffs[i];
  }
}

void poly_Rq_inv_tDiTRU(poly *r, const poly *a){

  

 
  poly x1, x2, x3, x4, x5, x6, x7;
  poly *u=&x1, *v=&x2;
  poly *u1=&x3, *v1=&x4;
  poly *uu1=&x5, *vv1=&x6;
  for(int i=0;i<N;i++){
    u->coeffs[i]=a->coeffs[i];
  }

 
  for(int i=N;i<ORDER;i++){
    v->coeffs[i-N]=a->coeffs[i];
  }
 

  rotinv(u,u1);
  rotinv(v,v1);
  
  
  poly_Rq_mul(uu1,u,u1);
  poly_Rq_mul(vv1,v,v1);
 
  get_minus(vv1); //newly added for twisted dihderal 

  poly *c = u;


    for(int i=0;i<N;i++){
    c->coeffs[i]= MODQ(vv1->coeffs[i]- uu1->coeffs[i]);
  }
 
  poly temp ;
  poly *temp1= &temp;
  poly *c_inv = &x7;
  poly_Rq_inv(c_inv,c);
  poly_Rq_mul(temp1, c, c_inv);
  // printf("rq inv verify:\n");
  // for(int i=0;i<N;i++){
  //   printf(" %d",((temp1->coeffs[i])));
     
  //   }

  //   printf("new line \n");
  
  poly *b = vv1;
  
  poly_Rq_mul(b,v,c_inv);
  poly *umin = u1;
  get_minus(umin);
  poly_Rq_mul(v1,umin,c_inv);
  for(int i=0;i<N;i++){
    r->coeffs[i]=v1->coeffs[i];
  }  
  
  for(int i=N;i<(ORDER);i++){
    r->coeffs[i]=b->coeffs[i-N];
  }
  
  
 
}

void poly_Sq_mul_tDiTRU(poly *r, const poly *a, const poly *b){
  poly_Rq_mul_tDiTRU(r, a,b,False);
  poly_mod_q_Phi_n_tDiTRU(r);
}

static void poly_R2_inv_to_Rq_inv(poly *r, const poly *ai, const poly *a)
{
#if tDiTRU_Q <= 256 || tDiTRU_Q >= 65536
#error "poly_R2_inv_to_Rq_inv in poly.c assumes 256 < q < 65536"
#endif

  int i;
  poly b, c;
  poly s;

  // for 0..4
  //    ai = ai * (2 - a*ai)  mod q
  for(i=0; i<N; i++)
    b.coeffs[i] = -(a->coeffs[i]);

  for(i=0; i<N; i++)
    r->coeffs[i] = ai->coeffs[i];

  poly_Rq_mul(&c, r, &b);
  c.coeffs[0] += 2; // c = 2 - a*ai
  poly_Rq_mul(&s, &c, r); // s = ai*c

  poly_Rq_mul(&c, &s, &b);
  c.coeffs[0] += 2; // c = 2 - a*s
  poly_Rq_mul(r, &c, &s); // r = s*c

  poly_Rq_mul(&c, r, &b);
  c.coeffs[0] += 2; // c = 2 - a*r
  poly_Rq_mul(&s, &c, r); // s = r*c

  poly_Rq_mul(&c, &s, &b);
  c.coeffs[0] += 2; // c = 2 - a*s
  poly_Rq_mul(r, &c, &s); // r = s*c
}

void poly_Rq_inv(poly *r, const poly *a)
{
  poly ai2;
  poly_R2_inv(&ai2, a);
  poly_R2_inv_to_Rq_inv(r, &ai2, a);

}
void poly_Sq_inv(poly *r, const poly *a)
{
  poly ai2;
  poly_R2_inv(&ai2, a);
  poly_R2_inv_to_Rq_inv(r, &ai2, a);  
}
