#include "api.h"
#include "cmov.h"
#include "crypto_hash_sha3256.h"
#include "kem.h"
#include "owcpa.h"
#include "params.h"
#include "rng.h"
#include "sample.h"
#include "helper_print.h"
#include "helper_print.h"

// API FUNCTIONS 
int crypto_kem_keypair(unsigned char *pk, unsigned char *sk)
{
  unsigned char seed[tDiTRU_SAMPLE_FT_BYTES];

  randombytes(seed, tDiTRU_SAMPLE_FT_BYTES);

  owcpa_keypair(pk, sk, seed);
  
  randombytes(sk + tDiTRU_OWCPA_SECRETKEYBYTES, tDiTRU_PRFKEYBYTES);

  return 0;
}

int crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk)
{ 
  poly r, m;
  unsigned char rm[tDiTRU_OWCPA_MSGBYTES];
  unsigned char rm_seed[tDiTRU_SAMPLE_RM_BYTES];

  randombytes(rm_seed, tDiTRU_SAMPLE_RM_BYTES);

  sample_rm_tDiTRU(&r, &m, rm_seed);
  
  poly_S3_tobytes(rm, &r);
  poly_S3_tobytes(rm + tDiTRU_PACK_TRINARY_BYTES, &m);
  crypto_hash_sha3256(k, rm, tDiTRU_OWCPA_MSGBYTES);
   
  poly_Z3_to_Zq_tDiTRU(&r);

  owcpa_enc(c, &r, &m, pk);

  return 0;
}

int crypto_kem_dec(unsigned char *k, const unsigned char *c, const unsigned char *sk)
{
  int i, fail;
  unsigned char rm[tDiTRU_OWCPA_MSGBYTES];
  unsigned char buf[tDiTRU_PRFKEYBYTES + tDiTRU_CIPHERTEXTBYTES];

  fail = owcpa_dec(rm, c, sk);
  /* If fail = 0 then c = Enc(h, rm). There is no need to re-encapsulate. */
  /* See comment in owcpa_dec for details.                                */

  crypto_hash_sha3256(k, rm, tDiTRU_OWCPA_MSGBYTES);
  /* shake(secret PRF key || input ciphertext) */
  for (i = 0; i < tDiTRU_PRFKEYBYTES; i++)
    buf[i] = sk[i + tDiTRU_OWCPA_SECRETKEYBYTES];
  for (i = 0; i < tDiTRU_CIPHERTEXTBYTES; i++)
    buf[tDiTRU_PRFKEYBYTES + i] = c[i];
  crypto_hash_sha3256(rm, buf, tDiTRU_PRFKEYBYTES + tDiTRU_CIPHERTEXTBYTES);

  cmov(k, rm, tDiTRU_SHAREDKEYBYTES, (unsigned char) fail);

  return 0;
}
