#ifndef PARAMS_H
#define PARAMS_H

#define tDiTRU_HPS
#define N 419
#define ORDER 2*N
#define tDiTRU_LOGQ 12

#ifndef CRYPTO_NAMESPACE
#define CRYPTO_NAMESPACE(s) s
#endif

/* Do not modify below this line */

#define PAD32(X) ((((X) + 31)/32)*32)

#define tDiTRU_Q (1 << tDiTRU_LOGQ)
#define tDiTRU_WEIGHT (tDiTRU_Q/8 - 2)

#define d_f 255 //weight of d_f and d_r
#define d_g 255 //weight of d_g 

#define tDiTRU_SEEDBYTES       32
#define tDiTRU_PRFKEYBYTES     32
#define tDiTRU_SHAREDKEYBYTES  32

#define tDiTRU_SAMPLE_IID_BYTES  (N-1)
#define tDiTRU_SAMPLE_FT_BYTES   ((30*(N-1)+7)/8)
#define tDiTRU_SAMPLE_FG_BYTES   (4*tDiTRU_SAMPLE_FT_BYTES) //sampling each half separately
#define tDiTRU_SAMPLE_RM_BYTES   (tDiTRU_SAMPLE_IID_BYTES+tDiTRU_SAMPLE_FT_BYTES)

#define tDiTRU_PACK_DEG (ORDER-1)
#define tDiTRU_PACK_TRINARY_BYTES    ((tDiTRU_PACK_DEG+4)/5)

#define tDiTRU_OWCPA_MSGBYTES       (2*tDiTRU_PACK_TRINARY_BYTES)
#define tDiTRU_OWCPA_PUBLICKEYBYTES ((tDiTRU_LOGQ*(tDiTRU_PACK_DEG-1)+7)/8) //We substract one coeff for the public key
#define tDiTRU_OWCPA_SECRETKEYBYTES (2*tDiTRU_PACK_TRINARY_BYTES + tDiTRU_OWCPA_PUBLICKEYBYTES)
#define tDiTRU_OWCPA_BYTES          ((tDiTRU_LOGQ*(tDiTRU_PACK_DEG-1)+7)/8)// We substract one coeff for the ciphertext

#define tDiTRU_PUBLICKEYBYTES  (tDiTRU_OWCPA_PUBLICKEYBYTES)
#define tDiTRU_SECRETKEYBYTES  (tDiTRU_OWCPA_SECRETKEYBYTES + tDiTRU_PRFKEYBYTES)
#define tDiTRU_CIPHERTEXTBYTES (tDiTRU_OWCPA_BYTES)


#define bool int
#define False 0
#define True 1

#endif
