#include "owcpa.h"
#include "poly.h"
#include "sample.h"
#include "helper_print.h"

static inline uint8_t mod3(uint8_t a) /* a between 0 and 9 */
{
  int16_t t, c;
  a = (a >> 2) + (a & 3); /* between 0 and 4 */
  t = a - 3;
  c = t >> 5;
  return (uint8_t)(t ^ (c & (a ^ t)));
}

static int owcpa_check_ciphertext(const unsigned char *ciphertext)
{
  /* A ciphertext is log2(q)*(n-1) bits packed into bytes.  */
  /* Check that any unused bits of the final byte are zero. */

  uint16_t t = 0;

  t = ciphertext[tDiTRU_CIPHERTEXTBYTES - 1]; // last byte 
  t &= 0xff << ( 8-(7 & (tDiTRU_LOGQ * (tDiTRU_PACK_DEG-1)))); // creates the mask to preserve only meaningful bits of last byte setting unused bits to zero 
  /* We have 0 <= t < 256 */
  /* Return 0 on success (t=0), 1 on failure */
  return (int)(1 & ((~t + 1) >> 15)); // checks for non zero unused bits 0 if not found 1 if found that means error
}

static int owcpa_check_r(const poly *r)
{
  /* A valid r has coefficients in {0,1,q-1} and has r[N-1] = 0 */
  /* Note: We may assume that 0 <= r[i] <= q-1 for all i        */

  int i;
  uint32_t t = 0;
  uint16_t c;
  for (i = 0; i < ORDER - 1; i++)
  {
    c = r->coeffs[i];
    t |= (c + 1) & (tDiTRU_Q - 4); /* 0 iff c is in {-1,0,1,2} */
    t |= (c + 2) & 4; /* 1 if c = 2, 0 if c is in {-1,0,1} */
  }
  t |= r->coeffs[ORDER - 1]; /* Coefficient n-1 must be zero */

  /* We have 0 <= t < 2^16. */
  /* Return 0 on success (t=0), 1 on failure */
  return (int)(1 & ((~t + 1) >> 31));
}

#ifdef tDiTRU_HPS
static int owcpa_check_m(const poly *m)
{
  /* Check that m is in message space, i.e.                  */
  /*  (1)  |{i : m[i] = 1}| = |{i : m[i] = 2}|, and          */
  /*  (2)  |{i : m[i] != 0}| = NTRU_WEIGHT.                  */
  /* Note: We may assume that m has coefficients in {0,1,2}. */

  int i;
  uint32_t t = 0;
  uint16_t ps = 0;
  uint16_t ms = 0;
  for (i = 0; i < ORDER; i++) // N should be checked again for dihedral
  {
    ps += m->coeffs[i] & 1;
    ms += m->coeffs[i] & 2;
  }
  t |= ps ^ (ms >> 1); /* 0 if (1) holds */
  t |= ms ^ tDiTRU_WEIGHT; /* 0 if (1) and (2) hold */

  /* We have 0 <= t < 2^16. */
  /* Return 0 on success (t=0), 1 on failure */
  return (int)(1 & ((~t + 1) >> 31));
}
#endif

void owcpa_keypair(unsigned char *pk,
           unsigned char *sk,
           const unsigned char seed[tDiTRU_SAMPLE_FG_BYTES])
{
  int i;

  poly x1, x2, x3, x4, x5;

  poly *f = &x1, *g = &x2, *invf_mod3 = &x3;
  poly *fg = &x3, *invfg = &x4, *tmp = &x5;
  poly *invh = &x3, *h = &x3;

  sample_fg_tDiTRU(f, g, seed);

  poly_S3_inv_tDiTRU(invf_mod3, f);

  poly_S3_tobytes(sk, f);
  poly_S3_tobytes(sk + tDiTRU_PACK_TRINARY_BYTES, invf_mod3);

  /* Lift coeffs of f and g from Z_p to Z_q */
  poly_Z3_to_Zq_tDiTRU(f);
  poly_Z3_to_Zq_tDiTRU(g);

#ifdef tDiTRU_HPS
  /* g = 3*g */
  for (i = 0; i < ORDER; i++)
    g->coeffs[i] = 3 * g->coeffs[i];
#endif

  poly_Rq_mul_tDiTRU(fg, f, g, False);

  poly_Rq_inv_tDiTRU(invfg, fg);

  poly_Rq_mul_tDiTRU(tmp, invfg, f, False);

  poly_Sq_mul_tDiTRU(invh, f, tmp);

  poly_Sq_tobytes(sk + 2 * tDiTRU_PACK_TRINARY_BYTES, invh);

  poly_Rq_mul_tDiTRU(tmp, g, invfg, False);
  poly_Rq_mul_tDiTRU(h, g, tmp, False);
  
  // printf("The public key \n");
  // print_poly_values(h);
  poly_Rq_sum_zero_tobytes(pk, h);
}

void owcpa_enc(unsigned char *c,
         const poly *r,
         const poly *m,
         const unsigned char *pk)
{
  int i;
  poly x1, x2;
  poly *h = &x1, *liftm = &x1;
  poly *ct = &x2;

  poly_Rq_sum_zero_frombytes(h, pk);
  // printf("The public key in the encryption function \n");
  // print_poly_values(h);

  poly_Rq_mul_tDiTRU(ct, r, h, False);

  poly_lift(liftm, m);

  for (i = 0; i < ORDER; i++)
    ct->coeffs[i] = ct->coeffs[i] + liftm->coeffs[i];
 
  poly_Rq_sum_zero_tobytes(c, ct);
}

int owcpa_dec(unsigned char *rm,
        const unsigned char *ciphertext,
        const unsigned char *secretkey)
{
  int i;
  int fail;
  poly x1, x2, x3, x4;

  poly *c = &x1, *f = &x2, *cf = &x3;
  poly *mf = &x2, *finv3 = &x3, *m = &x4;
  poly *liftm = &x2, *invh = &x3, *r = &x4;
  poly *b = &x1;

  poly_Rq_sum_zero_frombytes(c, ciphertext);
  
  poly_S3_frombytes_tDiTRU(f, secretkey);
  poly_Z3_to_Zq_tDiTRU(f);

  poly_Rq_mul_tDiTRU(cf, c, f, False);

  poly_Rq_to_S3(mf, cf);

  poly_S3_frombytes_tDiTRU(finv3, secretkey + tDiTRU_PACK_TRINARY_BYTES);

  poly_S3_mul_tDiTRU(m, mf, finv3);

  poly_S3_tobytes(rm + tDiTRU_PACK_TRINARY_BYTES, m);

  fail = 0;

  /* Check that the unused bits of the last byte of the ciphertext are zero */
  fail |= owcpa_check_ciphertext(ciphertext);

  /* For the IND-CCA2 KEM we must ensure that c = Enc(h, (r,m)).             */
  /* We can avoid re-computing r*h + Lift(m) as long as we check that        */
  /* r (defined as b/h mod (q, Phi_n)) and m are in the message space.       */
  /* (m can take any value in S3 in NTRU_HRSS) */
#ifdef tDiTRU_HPS
  fail |= owcpa_check_m(m);
#endif

  /* b = c - Lift(m) mod (q, x^n - 1) */
  poly_lift(liftm, m);

  for (i = 0; i < ORDER; i++)
    b->coeffs[i] = (c->coeffs[i] - liftm->coeffs[i]);

  /* r = b / h mod (q, Phi_n) */

  poly_Sq_frombytes(invh, secretkey + 2 * tDiTRU_PACK_TRINARY_BYTES);

  poly_Sq_mul_tDiTRU(r, b, invh);

  /* NOTE: Our definition of r as b/h mod (q, Phi_n) follows Figure 4 of     */
  /*   [Sch18] https://eprint.iacr.org/2018/1174/20181203:032458.            */
  /* This differs from Figure 10 of Saito--Xagawa--Yamakawa                  */
  /*   [SXY17] https://eprint.iacr.org/2017/1005/20180516:055500             */
  /* where r gets a final reduction modulo p.                                */
  /* We need this change to use Proposition 1 of [Sch18].                    */

  /* Proposition 1 of [Sch18] shows that re-encryption with (r,m) yields c.  */
  /* if and only if fail==0 after the following call to owcpa_check_r        */
  /* The procedure given in Fig. 8 of [Sch18] can be skipped because we have */
  /* c(1) = 0 due to the use of poly_Rq_sum_zero_{to,from}bytes.             */
  fail |= owcpa_check_r(r);

  poly_trinary_Zq_to_Z3_tDiTRU(r);

  poly_S3_tobytes(rm, r);

  return fail;
}
