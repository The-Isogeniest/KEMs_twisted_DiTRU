#ifndef SAMPLE_H
#define SAMPLE_H

#include "params.h"
#include "poly.h"

#ifdef tDiTRU_HPS
#include "crypto_sort_int32.h"
#endif

#define sample_fg CRYPTO_NAMESPACE(sample_fg)
#define sample_rm CRYPTO_NAMESPACE(sample_rm)
#define sample_rm_tDiTRU CRYPTO_NAMESPACE(sample_rm_tDiTRU)
#define sample_fg_tDiTRU CRYPTO_NAMESPACE(sample_fg_tDiTRU)


void sample_fg(poly *f, poly *g, const unsigned char uniformbytes[tDiTRU_SAMPLE_FG_BYTES]);
void sample_fg_tDiTRU(poly *f, poly *g, const unsigned char uniformbytes[tDiTRU_SAMPLE_FG_BYTES]);
void sample_rm(poly *r, poly *m, const unsigned char uniformbytes[tDiTRU_SAMPLE_RM_BYTES]);
void sample_rm_tDiTRU(poly *r, poly *m, const unsigned char uniformbytes[tDiTRU_SAMPLE_RM_BYTES]);

#define sample_iid CRYPTO_NAMESPACE(sample_iid)
#define sample_iid_tDiTRU CRYPTO_NAMESPACE(sample_iid_tDiTRU)
void sample_iid(poly *r, const unsigned char uniformbytes[tDiTRU_SAMPLE_IID_BYTES]);
void sample_iid_tDiTRU(poly *r, const unsigned char uniformbytes[tDiTRU_SAMPLE_IID_BYTES]);
#ifdef tDiTRU_HPS /* hps needs sample_fixed_type */
#define sample_fixed_type CRYPTO_NAMESPACE(sample_fixed_type)
#define sample_fixed_type_tDiTRU CRYPTO_NAMESPACE(sample_fixed_type_tDiTRU)
void sample_fixed_type(poly *r, const unsigned char uniformbytes[tDiTRU_SAMPLE_FT_BYTES],int d, int bit);
void sample_fixed_type_tDiTRU(poly *r, const unsigned char uniformbytes[tDiTRU_SAMPLE_FT_BYTES]);
#endif

#endif
