#include<stdio.h>
#include "kem.h"
#include "api.h"


int crypto_kem_keypair(unsigned char *pk,unsigned char *sk){
// {  printf("inside the ntru kemn keypair function");
   int i= CCA_keypair(pk,sk);
   return i;
} 


int  crypto_kem_enc(unsigned char *ct,unsigned char *ss,const unsigned char *pk){
//  printf("\n inside ntru kem enc");
   // unsigned char* secret_seed=malloc(SAMPLE_IID_BYTES);
      
    // unsigned char* shared_secret=malloc(PACK_TRINARY_BYTES);
    unsigned char secret_seed[N2_SAMPLE_M_BYTES];
    unsigned char shared_secret[PACK_TRINARY_BYTES];
    // printf("after this fn");
    // Term x1;
    // Term * shared_secret_3 =&x1;

    Term shared_secret_3[N2];
   
    randombytes(secret_seed, N2_SAMPLE_M_BYTES);
    sample_lm(shared_secret_3,secret_seed);
    poly_S3m_tobytes(shared_secret,shared_secret_3);
    int i = CCA_encrypt(ct, shared_secret,pk);
    crypto_hash_sha3512(shared_secret, shared_secret, PACK_TRINARY_BYTES);
    // crypto_hash_sha3512(shared_secret+CRYPTO_BYTES,pk, PUBLICKEYBYTES);
    // crypto_hash_sha3512(shared_secret,  shared_secret,CRYPTO_BYTES+LENGTH_OF_HASH);
    memcpy(ss,shared_secret,LENGTH_OF_HASH);
    // free(shared_secret);
    // free(secret_seed);
    return i;
    
}
int crypto_kem_dec(unsigned char *ss,const unsigned char* ct, const unsigned char* sk, const unsigned char *pk){   
  //  unsigned char* shared_secret=malloc(PACK_TRINARY_BYTES);
  unsigned char shared_secret[PACK_TRINARY_BYTES];
   int i= CCA_decrypt(shared_secret,ct,sk,pk);
    crypto_hash_sha3512(shared_secret, shared_secret, PACK_TRINARY_BYTES);
    // crypto_hash_sha3512(shared_secret+CRYPTO_BYTES,pk,CRYPTO_BYTES);
    // crypto_hash_sha3512(shared_secret,shared_secret,CRYPTO_BYTES+LENGTH_OF_HASH);
    memcpy(ss,shared_secret,LENGTH_OF_HASH);
    // free(shared_secret);
return i;
}