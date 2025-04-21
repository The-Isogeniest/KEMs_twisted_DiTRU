#include "ppke.h"
#include "inverse.h"
#include "packq_CnC3.h"
#include "pack3_CnC3.h"
#include <stdio.h>

int ppke_keypair(unsigned char *pk, unsigned char* sk,unsigned char arr_seed[N3_SAMPLE_FG_BYTES]){
    Term q = {Q,0};
    Term P = {p_,0};

    Term h[N3];
    Term g[N3];
    Term f[N3];

    int flag = 0;

    Term fq[N3];
    int loop = 0;
    while(flag==0){

        // printf("In loop\n");
        loop++;
        sample_lf(f,arr_seed);
        poly_Zw_mul_p(f,P,N3);
        poly_S3_tobytes(sk,f);
        f[0].a += 1;
        flag = Almost_inverse_ZpwCnC3(f,Q,fq);
      
        if(flag==0){

            randombytes(arr_seed,N3_SAMPLE_FG_BYTES);
        }
        

    }

   

    sample_lg(g,arr_seed+N3_SAMPLE_F_BYTES);
    Zw_CnC3_multiply(fq,g,h);
    ZwCnC3_mod_q(h,q,h);
    poly_pack_Sq_tobytes(pk,h);
    printf("Key generated successfully\n");

    return loop;

    

}

// group_ring* H, group_ring* M,Term *phi,Term P,Term q,group_ring*E

void ppke_encrypt(unsigned char* c,Term* phi, Term *h, Term* m){
    // printf("Encrypting message\n");
    Term P = {p_,0};
    Term q = {Q,0};


    Term e[N3];
    poly_Zw_mul_p(h,P,N3);
    Zw_CnC3_multiply(h,phi,e);

    Term mask[N3];

    unsigned char t_seed[LENGTH_OF_HASH];

    sha3_512(t_seed,(unsigned char*)(&e),N3*2);

    sample_mask(mask,t_seed);

    ZwCnC3_sub(m,mask,m);//
    ZwCnC3_mod_q(m,P,m);// M = M - MASK

    ZwCnC3_add(e,m,e);

    ZwCnC3_mod_q(e,q,e);

    poly_pack_Sq_tobytes(c,e);

}



// group_ring *F, group_ring* E,Term P, Term q, group_ring *A

void ppke_decrypt(Term *a, const unsigned char * ciphertext, Term *f){
    


    Term P = {p_,0};
    Term q = {Q,0};

    Term e[N3];

    poly_unpack_Sq_frombytes(e,ciphertext);
    Zw_CnC3_multiply(f,e,a);
    ZwCnC3_mod_q(a,q,a);// A = E*F

    ZwCnC3_mod_q(a,P,a);
    Term t[N3];
    ZwCnC3_sub(e,a,t);
    ZwCnC3_mod_q(t,q,t);
    Term mask[N3];

    unsigned char t_seed[LENGTH_OF_HASH];

    sha3_512(t_seed,(unsigned char*)(&t),N3*2);
    sample_mask(mask,t_seed);
    ZwCnC3_add(a,mask,a);
    ZwCnC3_mod_q(a,P,a);

}
