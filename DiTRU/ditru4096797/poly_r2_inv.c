/* Based on supercop-20200702/crypto_core/invhrss701/simpler/core.c */

#include "poly.h"

/* return -1 if x<0 and y<0; otherwise return 0 */
static inline int16_t both_negative_mask(int16_t x,int16_t y)
{
  return (x & y) >> 15;
}


/* return -1 if x!=0; else return 0 */
static int int16_nonzero_mask(int16_t x)
{
  uint16_t u = x; /* 0, else 1...65535 */
  uint32_t v = u; /* 0, else 1...65535 */
  v = -v; /* 0, else 2^32-65535...2^32-1 */
  v >>= 31; /* 0, else 1 */
  return -v; /* 0, else -1 */
}


int poly_R2_inv(poly *r, const poly *a)
{
 
  // printf("inside the function \n");
  // print_polynomial_array(N, a);
  uint16_t f[N+1], g[N+1], v[N+1], w[N+1];

  size_t i, loop;
  int16_t delta,sign,swap,t;

  for (i = 0;i < N+1;++i) v[i] = 0;
  for (i = 0;i < N+1;++i) w[i] = 0;
  w[0] = 1;

  for (i = 0;i < N;++i) f[i] = 0;
  f[0]=1; f[N]=1;

  for (i = 0;i < N;++i) g[N-1-i] = (a->coeffs[i] & 1);
  g[N] = 0;

  // printf(" g inside the function \n");
  // for(i=0;i<N;i++)
  //    printf("%d, ", g[i]);
  // printf("\n");

  delta = 1;

  for (loop = 0;loop < 2*N-1;++loop) {
    for (i = N;i > 0;--i) v[i] = v[i-1];
    v[0] = 0;

    sign = g[0] & f[0];
    swap = both_negative_mask(-delta,-(int16_t) g[0]);
    delta ^= swap & (delta ^ -delta);
    delta += 1;
    
    // printf("loop %d \n", loop);
    // printf("delta %d \n", delta);

    // if (loop==10)
    // {
    //   break;
    // }

  

    for (i = 0;i < N+1;++i) {
      t = swap&(f[i]^g[i]); f[i] ^= t; g[i] ^= t;
      t = swap&(v[i]^w[i]); v[i] ^= t; w[i] ^= t;
    }

    for (i = 0;i < N+1;++i) g[i] = g[i]^(sign&f[i]);

    for (i = 0;i < N+1;++i) w[i] = w[i]^(sign&v[i]);

    for (i = 0;i < N;++i) g[i] = g[i+1];
    g[N] = 0;
  }

  // printf("\n delta after the loop: %d \n ", delta);

  for (i = 0;i < N;++i) r->coeffs[i] = v[N-1-i];
  

  return int16_nonzero_mask(delta);
}




#define POLY_R2_ADD(I,A,B,S,N)        \
   for(I=0; I<N; I++)        \
   { A.coeffs[I] ^= B.coeffs[I] * S;  }

#define POLY_S3_FMADD(I,A,B,S,N)                    \
   for(I=0; I<N; I++)                            \
   { A.coeffs[I] = mod3(A.coeffs[I] + S * B.coeffs[I]); }

/* If swap is 0 then don't swap, If swap is 1 then swap*/
static void cswappoly(poly *a, poly *b, int swap, int n)
{
  int i;
  uint16_t t;
  swap = -swap;
  for(i=0;i<n;i++)
  {
    t = (a->coeffs[i] ^ b->coeffs[i]) & swap;
    a->coeffs[i] ^= t;
    b->coeffs[i] ^= t;
  }
}


static inline void poly_divx(poly *a, int s, int n)
{
  int i;

  for(i=1; i<n; i++)
    a->coeffs[i-1] = (s * a->coeffs[i]) | (!s * a->coeffs[i-1]);
  a->coeffs[n-1] = (!s * a->coeffs[n-1]);
}

static inline void poly_mulx(poly *a, int s, int n)
{
  int i;

  for(i=1; i<n; i++)
    a->coeffs[n-i] = (s * a->coeffs[n-i-1]) | (!s * a->coeffs[n-i]);
  a->coeffs[0] = (!s * a->coeffs[0]);
}


// void poly_R2_inv_v2(poly *r, const poly *a)
// {
//   /* Schroeppel--Orman--O'Malley--Spatscheck
//    * "Almost Inverse" algorithm as described
//    * by Silverman in NTRU Tech Report #14 */
//   // with several modifications to make it run in constant-time

//   //Take care N should be the order of the group for cyclic and half the order for dihedral
//   int i, j;
//   int k = 0;
//   uint16_t degf = N-1;
//   uint16_t degg = N;
//   int sign, t, swap;
//   int done = 0;
//   poly b, f, g;
//   poly *c = r; // save some stack space
//   poly *temp_r = &f;

//   /* b(X) := 1 */
//   for(i=1; i<N+1; i++)
//     b.coeffs[i] = 0;
//   b.coeffs[0] = 1;

//   /* c(X) := 0 */
//   for(i=0; i<N+1; i++)
//     c->coeffs[i] = 0;

//   /* f(X) := a(X) */
//   for(i=0; i<N; i++)
//     f.coeffs[i] = a->coeffs[i] & 1;
//   f.coeffs[N]=0;

//   /* g(X) := 1 + X^{N} */ //over R2
//   for(i=0; i<N; i++)
//     g.coeffs[i] = 0;
//   g.coeffs[0]=1;
//   g.coeffs[N]=1;

//   for(j=0;j<2*(N)-1;j++)
//   {
//     sign = f.coeffs[0];
//     swap = sign & !done & ((degf - degg) >> 15);
//     cswappoly(&f, &g, swap,N+1);
//     cswappoly(&b, c, swap,N+1);
//     t = (degf ^ degg) & (-swap);
//     degf ^= t;
//     degg ^= t;
//     POLY_R2_ADD(i, f, g, sign*(!done),N+1);
//     POLY_R2_ADD(i, b, (*c), sign*(!done),N+1);
//     poly_divx(&f, !done, N+1);
//     poly_mulx(c, !done, N+1);
//     degf -= !done;
//     k += !done;
//     done = 1 - (((uint16_t)(-degf)) >> 15);
//  }
// }


