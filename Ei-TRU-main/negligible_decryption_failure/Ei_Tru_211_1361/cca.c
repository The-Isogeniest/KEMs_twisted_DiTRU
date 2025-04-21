#include "cca.h"
#include "packq_CnC3.h"
#include "pack3_CnC3.h"

int CCA_keypair(unsigned char* pk,unsigned char *sk){
    
    unsigned char arr_seed[N3_SAMPLE_FG_BYTES];
    randombytes(arr_seed,N3_SAMPLE_FG_BYTES);

    int ret_val = ppke_keypair(pk,sk,arr_seed);  

    return ret_val;
}

int CCA_encrypt(unsigned char *c,const unsigned char *m,const unsigned char *pk){
    Term h[N3];
    Term phi[N3];
    Term mprime[N3];

    poly_S3m_frombytes(mprime,m);
    poly_unpack_Sq_frombytes(h,pk);
    sample_phi(phi,h,mprime);
    ppke_encrypt(c,phi,h,mprime);
    
    return 0;
}

int CCA_decrypt(unsigned char *m, const unsigned char* ciphertext, const unsigned char *secretkey, const unsigned char* publickey){
    
    Term h[N3];
    Term f[N3];
    Term phi[N3];
    Term message[N3];



    poly_unpack_Sq_frombytes(h,publickey);

    poly_S3_frombytes(f,secretkey);

    f[0].a += 1;

    ppke_decrypt(message,ciphertext,f);

    Term copy_message[N3];
    for(int i = 0;i<N3;i++){
        copy_message[i] = message[i];
    }

    

    sample_phi(phi,h,copy_message);

    unsigned char cprime[CHAR_BYTES];

    ppke_encrypt(cprime,phi,h,copy_message);

    

    for(int i = 0;i<(CHAR_BYTES);i++){
        if(cprime[i]!=ciphertext[i]){
            printf("decryption failure\n");
            return -1;
        }
    }

   

    poly_S3m_tobytes(m,message);
    return 0;
}
