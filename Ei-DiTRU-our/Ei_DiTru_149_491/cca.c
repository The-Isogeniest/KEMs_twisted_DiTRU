#include "cca.h"
#include "packq_CnC3.h"
#include "pack3_CnC3.h"

int CCA_keypair(unsigned char* pk,unsigned char *sk){
    
    unsigned char arr_seed[N2_SAMPLE_FG_BYTES];
    randombytes(arr_seed,N2_SAMPLE_FG_BYTES);

    int ret_val = ppke_keypair(pk,sk,arr_seed);  

    return ret_val;
}

int CCA_encrypt(unsigned char *c,const unsigned char *m,const unsigned char *pk){
    Term h[N2];
    Term phi[N2];
    Term mprime[N2];

    poly_S3m_frombytes(mprime,m);


    // printf("Encryption \n");
    
    // printf("Encryption: the message \n");
    // print_element(mprime, N2);
    // printf("\n");

    poly_unpack_Sq_frombytes(h,pk);
    

    // printf("Encryption: the public key \n");
    // print_element(h,N2);
    // printf("\n");

    sample_phi(phi,h,mprime);

    // printf("Encryption: phi generated in encryption");
    // print_element(phi,N2);
    // printf("\n");

    ppke_encrypt(c,phi,h,mprime);
    
    return 0;
}

int CCA_decrypt(unsigned char *m, const unsigned char* ciphertext, const unsigned char *secretkey, const unsigned char* publickey){
    
    Term h[N2];
    Term f[N2];
    Term phi[N2];
    Term message[N2];




    // printf("Decryption \n");
    poly_unpack_Sq_frombytes(h,publickey);

    // printf("Decryption: h \n");
    // print_element(h, N2);
    // printf("\n");

    poly_S3_frombytes(f,secretkey);

    f[0].a += 1;

    ppke_decrypt(message,ciphertext,f);

    

    Term copy_message[N2];
    for(int i = 0;i<N2;i++){
        copy_message[i] = message[i];
    }

    
    // printf("Decryption: the message \n");
    // print_element(copy_message, N2);
    // printf("\n");
    sample_phi(phi,h,copy_message);
    // printf("Decryption phi \n");
    // print_element(phi, N2);
    // printf("\n");

    unsigned char cprime[CHAR_BYTES];

    // printf("phi generated in decryption");
    // print_element(phi, N2);
    // printf("\n");
    // printf("\n");

    ppke_encrypt(cprime,phi,h,copy_message);

    
    // printf("%d \n", CHAR_BYTES);
    for(int i = 0;i<(CHAR_BYTES);i++){
        if(cprime[i]!=ciphertext[i]){
            // printf("%d", i);
            printf("decryption failure\n");
            return -1;
        }
    }

   

    poly_S3m_tobytes(m,message);
    return 0;
}
