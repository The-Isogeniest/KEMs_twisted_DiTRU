#ifndef Ei_TRUKEM_H
#define Ei_TRUKEM_H

#include <stdlib.h>
#include <stdio.h>
#include "ppke.h"
#include "sample.h"
#include <string.h>
#include "params.h"
#include "cca.h"
#include "poly.h"
#include "crypto_hash_sha3256.h"
#include "rng.h"
#include "poly.h"
#include "pack3_CnC3.h"

#define crypto_kem_keypair CRYPTO_NAMESPACE(keypair)
#define crypto_kem_enc  CRYPTO_NAMESPACE(enc)
#define crypto_kem_dec CRYPTO_NAMESPACE(dec)

int crypto_kem_keypair(unsigned char *pk,unsigned char *sk);
int crypto_kem_enc(unsigned char *ct,unsigned char *ss,const unsigned char *pk);
int crypto_kem_dec(unsigned char *ss,const unsigned char* ct, const unsigned char* sk,const unsigned char *pk);

#endif