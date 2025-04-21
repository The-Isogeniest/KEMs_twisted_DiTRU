#ifndef PACK3_CnC3_H
#define PACK3_CnC3_H

#include "poly.h"


#define mod3 CRYPTO_NAMESPACE(mod3)
static uint16_t mod3(uint16_t a);


#define poly_S3_tobytes CRYPTO_NAMESPACE(poly_S3_tobytes)
#define poly_S3_frombytes CRYPTO_NAMESPACE(poly_S3_frombytes)
#define poly_S3m_tobytes CRYPTO_NAMESPACE(poly_S3m_tobytes)
#define poly_S3m_frombytes CRYPTO_NAMESPACE(poly_S3m_frombytes)
void poly_S3_tobytes(unsigned char msg[PPKE_MESSAGEBYTES], const Term *a);
void poly_S3_frombytes(Term *r, const unsigned char msg[PPKE_MESSAGEBYTES]);
void poly_S3m_tobytes(unsigned char msg[PPKE_MESSAGEBYTES], const Term *a);
void poly_S3m_frombytes(Term *r, const unsigned char msg[PPKE_MESSAGEBYTES]);

#endif