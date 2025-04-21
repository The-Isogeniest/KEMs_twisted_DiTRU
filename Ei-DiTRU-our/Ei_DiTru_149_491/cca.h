#ifndef CCA_H
#define CCA_H

#include "ppke.h"
#include "sample.h"


#define CCA_keypair CRYPTO_NAMESPACE(CCA_keypair)
int CCA_keypair(unsigned char* pk,unsigned char *sk);

#define CCA_encrypt CRYPTO_NAMESPACE(CCA_encrypt)
int CCA_encrypt(unsigned char *c,const unsigned char *m,const unsigned char *pk);

#define CCA_decrypt CRYPTO_NAMESPACE(CCA_decrypt)
int CCA_decrypt(unsigned char *m, const unsigned char* ciphertext, const unsigned char *secretkey, const unsigned char* publickey);

#endif