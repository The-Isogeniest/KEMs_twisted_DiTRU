#include "ppke.h"
#include "inverse.h"
#include "packq_CnC3.h"
#include "pack3_CnC3.h"
#include  "helper.h"
#include <stdio.h>

int ppke_keypair(unsigned char *pk, unsigned char* sk,unsigned char arr_seed[N2_SAMPLE_FG_BYTES]){
    Term q = {Q,0};
    Term P = {p_,0};

    Term h[N2];
    Term g[N2];
    Term f[N2];

    Term check[N2];

    int flag = 0;

    Term fq[N2];
    int loop = 0;
    while(flag==0){

        // printf("In loop\n");
        loop++;
        sample_lf(f,arr_seed);
        

        poly_Zw_mul_p(f,P,N2);

        // printf("private key before packing \n");
        poly_S3_tobytes(sk,f);
        // print_element(f, N2);

        // printf("private key after packing \n");
        // poly_S3_frombytes(f,sk);
        // print_element(f, N2);
        f[0].a += 1;

        // printf("sampled f is: ");
        // print_element(f, N2);
        flag = Almost_inverse_ZpwDN(f,Q,fq);


        // printf("check the multiplication is 1:");

        // Zw_DN_multiply(f,fq,check);
        // ZwDN_mod_q(check,q,check);

        // print_element(check, N2);
        if(flag==0){

            randombytes(arr_seed,N2_SAMPLE_FG_BYTES);
        }
        

    }

   

    sample_lg(g,arr_seed+N2_SAMPLE_F_BYTES);
    // printf("g is \n");
    // print_element(g, N2);

    // printf("fq is \n");
    // print_element(fq, N2);

    Zw_DN_multiply(fq,g,h);
    ZwDN_mod_q(h,q,h);
    // printf("public key before packing \n");
    // print_element(h,N2);

    

    poly_pack_Sq_tobytes(pk,h);

    // printf("public key after packing \n");

    // poly_unpack_Sq_frombytes(h,pk);
    // print_element(h,N2);

    printf("Key generated successfully\n");
    
    // printf("checking the key generated successfully!");
    // Zw_DN_multiply(f,h,check);
    // ZwDN_mod_q(check,q,check);
    
    // printf("g is \n");
    // print_element(g, N2);
    // printf("g prime \n");
    // print_element(check, N2);


    // printf("public key before packing is \n");
    // print_element(h,N2);
    return loop;

    

}

// group_ring* H, group_ring* M,Term *phi,Term P,Term q,group_ring*E

void ppke_encrypt(unsigned char* c,Term* phi, Term *h, Term* m){
    // printf("Encrypting message\n");


    // printf("original message \n");
    // print_element(m, N2);


    // printf("phi here: ");
    // print_element(phi, N2);

    Term P = {p_,0};
    Term q = {Q,0};

    // printf("inside the encryption function, h is: \n");
    // print_element(h, 2*N);
    Term e[N2];
    poly_Zw_mul_p(h,P,N2);
    Zw_DN_multiply(h,phi,e);

    Term mask[N2];

    unsigned char t_seed[LENGTH_OF_HASH];

    sha3_512(t_seed,(unsigned char*)(&e),N2*2);

    sample_mask(mask,t_seed);

    // printf("mask inside the encryption \n");
    // printf("\n");
    // print_element(mask, N2);

    ZwDN_sub(m,mask,m);//
    ZwDN_mod_q(m,P,m);// M = M - MASK

    ZwDN_add(e,m,e);

    ZwDN_mod_q(e,q,e);

    poly_pack_Sq_tobytes(c,e);
    // printf("packed ciphertex: ");
    // print_element(e,N2);

}



// group_ring *F, group_ring* E,Term P, Term q, group_ring *A

void ppke_decrypt(Term *a, const unsigned char * ciphertext, Term *f){
     


    // printf("print f inside the decryption function \n");
    // print_element(f,N2);
    // printf("\n");
    Term P = {p_,0};
    Term q = {Q,0};

    Term e[N2];
    
   
    poly_unpack_Sq_frombytes(e,ciphertext);
    // printf("unpacked ciphertext");
    // printf("\n");
    // print_element(e,N2);
    Zw_DN_multiply(f,e,a);
    ZwDN_mod_q(a,q,a);// A = E*F

    ZwDN_mod_q(a,P,a);
    Term t[N2];
    ZwDN_sub(e,a,t);
    ZwDN_mod_q(t,q,t);
    Term mask[N2];

    unsigned char t_seed[LENGTH_OF_HASH];

    sha3_512(t_seed,(unsigned char*)(&t),N2*2);
    sample_mask(mask,t_seed);

    // printf("print mask inside the decryption function \n");
    // print_element(mask, N2);
    // printf("\n");
    ZwDN_add(a,mask,a);
    ZwDN_mod_q(a,P,a);


    // printf("retrieved message \n");
    // print_element(a, N2);

}
