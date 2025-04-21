/* Based on supercop-20200702/crypto_core/invhrss701/simpler/core.c */

#include "poly.h"
#include <stdio.h>
#include "helper_print.h"
static inline uint8_t mod3(uint8_t a) /* a between 0 and 9 */
{
  int16_t t, c;
  a = (a >> 2) + (a & 3); /* between 0 and 4 */
  t = a - 3;
  c = t >> 5;
  return (uint8_t) (t^(c&(a^t)));
}

/* return -1 if x<0 and y<0; otherwise return 0 */
static inline int16_t both_negative_mask(int16_t x,int16_t y)
{
  return (x & y) >> 15;
}

void poly_S3_inv(poly *r, const poly *a)
{
  poly f, g, v, w;
  size_t i,loop;
  int16_t delta,sign,swap,t;
  
  for (i = 0;i < N;++i) v.coeffs[i] = 0;
  for (i = 0;i < N;++i) w.coeffs[i] = 0;
  w.coeffs[0] = 1;

  for (i = 0;i < N;++i) f.coeffs[i] = 1;
  for (i = 0;i < N-1;++i) g.coeffs[N-2-i] = mod3((a->coeffs[i] & 3) + 2*(a->coeffs[N-1] & 3));
  g.coeffs[N-1] = 0;

  delta = 1;

  for (loop = 0;loop < 2*(N-1)-1;++loop) {
    for (i = N-1;i > 0;--i) v.coeffs[i] = v.coeffs[i-1];
    v.coeffs[0] = 0;

    sign = mod3((uint8_t) (2 * g.coeffs[0] * f.coeffs[0]));
    swap = both_negative_mask(-delta,-(int16_t) g.coeffs[0]);
    delta ^= swap & (delta ^ -delta);
    delta += 1;

    for (i = 0;i < N;++i) {
      t = swap&(f.coeffs[i]^g.coeffs[i]); f.coeffs[i] ^= t; g.coeffs[i] ^= t;
      t = swap&(v.coeffs[i]^w.coeffs[i]); v.coeffs[i] ^= t; w.coeffs[i] ^= t;
    }

    for (i = 0;i < N;++i) g.coeffs[i] = mod3((uint8_t) (g.coeffs[i]+sign*f.coeffs[i]));
    for (i = 0;i < N;++i) w.coeffs[i] = mod3((uint8_t) (w.coeffs[i]+sign*v.coeffs[i]));
    for (i = 0;i < N-1;++i) g.coeffs[i] = g.coeffs[i+1];
    g.coeffs[N-1] = 0;
  }

  sign = f.coeffs[0];
  for (i = 0;i < N-1;++i) r->coeffs[i] = mod3((uint8_t) (sign*v.coeffs[N-2-i]));
  r->coeffs[N-1] = 0;


  // printf("delta % d \n", delta);
}
void poly_S3_inv_tDiTRU(poly *r , const poly *a){

  /*
  Input: -a: an element to be inverted in Z3[x]/<phi_{N}(x), y^2=-1, xy=yx^{N-1}> 
  The input has coefficients in {0,1,2}
  */
  //printf("Dihedral is here\n");



  // printf("input is: ");
  // print_poly_values(a);
  poly x1, x2, x3, x4, x5, x6;
  poly *u=&x1, *v=&x2;
  poly *u1=&x3, *v1=&x4;
  poly *uu1=&x5, *vv1=&x6;
  for(int i=0;i<N-1;i++){
    u->coeffs[i]=a->coeffs[i];
  }
  u->coeffs[N-1]=0;
  
  // printf("u initial");
  // print_poly_values(u);
  for(int i=N;i<ORDER-1;i++){
    v->coeffs[i-N]=a->coeffs[i];
  }
  v->coeffs[N-1]=0;
  rotinv_S3(u,u1);
  // print_poly_values(u1);
  // printf("conjeguate in S for u1:");
  // print_poly_values(u1);

  rotinv_S3(v,v1);
  // print_poly_values(v1);
  // printf("conjeguate in S for v1: ");
  // print_poly_values(v1);
  

  poly_S3_mul(uu1,u,u1);
  // printf("uu1: ");
  // print_poly_values(uu1);

  poly_S3_mul(vv1,v,v1);
  // printf("vv1: ");
  // print_poly_values(vv1);

  get_minus_S3(vv1); //newly added for twisted dihderal
  poly_trinary_Zq_to_Z3(vv1);
  // printf("-vv1");
  // print_poly_values(vv1);

  poly *c = u;
  for(int i=0;i<N;i++){
    c->coeffs[i]= mod3(vv1->coeffs[i]+2*uu1->coeffs[i]);  //Instead of substracting the last coefficient, as the coefficients in {0,1,2}, we add 2*last_coefficient
  }
  poly temp ;
  poly *temp1= &temp;
  poly *c_inv = uu1;
  
  poly_S3_inv(c_inv,c);
  poly_S3_mul(temp1, c, c_inv);
  
   
  // printf("checking the inverse in CN \n");
  // for  (int i=0;i<N;i++){
  //   printf(" %d",temp1->coeffs[i]);
     
  //   }
  //   printf("new line \n");

  poly *b = vv1;
  
  // printf("f1");
  // print_poly_values(v);
  // printf("c_inv");
  // print_poly_values(c_inv);
  poly_S3_mul(b,v,c_inv);
  // printf("b");
  // print_poly_values(b);
  poly *umin = u1;
  get_minus_S3(umin);
  poly_S3_mul(v1,umin,c_inv);
  for(int i=0;i<N;i++){
    r->coeffs[i]=(v1->coeffs[i]);
  }  
  
  
  for(int i=N;i<(ORDER);i++){
    r->coeffs[i]=(b->coeffs[i-N]);
   }
  
 
}

