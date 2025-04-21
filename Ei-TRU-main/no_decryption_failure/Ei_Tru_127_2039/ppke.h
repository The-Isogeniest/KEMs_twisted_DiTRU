#ifndef PPKE_H
#define PPKE_H


#include "poly_r.h"
#include "sample.h"
#include "rng.h"
#include "crypto_sort_int32.h"
#include "crypto_hash_sha3256.h"
// #include "packq_CnC3.h"
// #include "pack3_CnC3.h"



#define ppke_keypair CRYPTO_NAMESPACE(ppke_keypair)
int ppke_keypair(unsigned char *pk, unsigned char* sk,unsigned char arr_seed[N3_SAMPLE_FG_BYTES]);

// group_ring* H, group_ring* M,Term *phi,Term P,Term q,group_ring*E
#define ppke_encrypt CRYPTO_NAMESPACE(ppke_encrypt)
void ppke_encrypt(unsigned char* c,Term* phi, Term *h, Term* m);

// group_ring *F, group_ring* E,Term P, Term q, group_ring *A
#define ppke_decrypt CRYPTO_NAMESPACE(ppke_decrypt)
void ppke_decrypt(Term *a, const unsigned char * ciphertext, Term *f);

#endif
