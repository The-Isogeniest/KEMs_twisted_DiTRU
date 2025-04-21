//Credits :https://homepage.cs.uiowa.edu/~dwjones/bcd/mod.shtml
#include "sample.h"
#include "rng.h"
#include "crypto_hash_sha3256.h"
#include <string.h>


uint32_t mod6( uint32_t a ) {
    uint32_t b = a & 1;           /* b = a mod 2 */
    a = a >> 1;			  /* a = a / 2   */

    /* now use code for a mod 3 */
    a = (a >> 16) + (a & 0xFFFF); /* sum base 2**16 digits */
    a = (a >>  8) + (a & 0xFF);   /* sum base 2**8 digits  */
    a = (a >>  4) + (a & 0xF);    /* sum base 2**4 digits  */
    a = (a >>  2) + (a & 0x3);    /* sum base 2**2 digits  */
    a = (a >>  2) + (a & 0x3);    /* sum base 2**2 digits  */
    a = (a >>  2) + (a & 0x3);    /* sum base 2**2 digits  */
    if (a > 2) a = a - 3;

    return b + (a << 1);
}

void sample_fixed_type_lf(int *r, const unsigned char u[N3_SAMPLE_BYTES])
{
    int32_t s[N3-1];
    int i;

    // Use 31 bits of u per word
    for (i = 0; i < (N3-1)/8; i++)
    {
        s[8*i+0] =                              (u[31*i+ 0] << 1) + (u[31*i+ 1] << 9) + (u[31*i+ 2] << 17) + ((uint32_t) u[31*i+ 3] << 25);
        s[8*i+1] = ((u[31*i+ 3] & 0x80) >> 6) + (u[31*i+ 4] << 2) + (u[31*i+ 5] << 10) + (u[31*i+ 6] << 18) + ((uint32_t) u[31*i+ 7] << 26);
        s[8*i+2] = ((u[31*i+ 7] & 0xc0) >> 5) + (u[31*i+ 8] << 3) + (u[31*i+ 9] << 11) + (u[31*i+10] << 19) + ((uint32_t) u[31*i+11] << 27);
        s[8*i+3] = ((u[31*i+11] & 0xe0) >> 4) + (u[31*i+12] << 4) + (u[31*i+13] << 12) + (u[31*i+14] << 20) + ((uint32_t) u[31*i+15] << 28);
        s[8*i+4] =  ((u[31*i+15] & 0xf0) >> 3)+ (u[31*i+ 16] << 5) + (u[31*i+ 17] << 13) + (u[31*i+ 18] << 21) + ((uint32_t) u[31*i+ 19] << 29);
        s[8*i+5] = ((u[31*i+ 19] & 0xf8) >> 2) + (u[31*i+ 20] << 6) + (u[31*i+ 21] << 14) + (u[31*i+ 22] << 22) + ((uint32_t) u[31*i+ 23] << 30);
        s[8*i+6] = ((u[31*i+ 23] & 0xfc) >> 1) + (u[31*i+ 24] << 7) + (u[31*i+ 25] << 15) + (u[31*i+26] << 23) + ((uint32_t) u[31*i+27] << 31);
        s[8*i+7] = ((u[31*i+27] & 0xfe)) + (u[31*i+28] << 8) + (u[31*i+29] << 16) + ((uint32_t) u[31*i+30] << 24);
    }

    int leftOut = (N3 - 1) - ((N3 - 1) / 8) * 8;

    switch(leftOut){
        case 2:
        s[8*i+0] =                              (u[31*i+ 0] << 1) + (u[31*i+ 1] << 9) + (u[31*i+ 2] << 17) + ((uint32_t) u[31*i+ 3] << 25);
        s[8*i+1] = ((u[31*i+ 3] & 0x80) >> 6) + (u[31*i+ 4] << 2) + (u[31*i+ 5] << 10) + (u[31*i+ 6] << 18) + ((uint32_t) u[31*i+ 7] << 26);
        break;

        case 4:
        s[8*i+0] =                              (u[31*i+ 0] << 1) + (u[31*i+ 1] << 9) + (u[31*i+ 2] << 17) + ((uint32_t) u[31*i+ 3] << 25);
        s[8*i+1] = ((u[31*i+ 3] & 0x80) >> 6) + (u[31*i+ 4] << 2) + (u[31*i+ 5] << 10) + (u[31*i+ 6] << 18) + ((uint32_t) u[31*i+ 7] << 26);
        s[8*i+2] = ((u[31*i+ 7] & 0xc0) >> 5) + (u[31*i+ 8] << 3) + (u[31*i+ 9] << 11) + (u[31*i+10] << 19) + ((uint32_t) u[31*i+11] << 27);
        s[8*i+3] = ((u[31*i+11] & 0xe0) >> 4) + (u[31*i+12] << 4) + (u[31*i+13] << 12) + (u[31*i+14] << 20) + ((uint32_t) u[31*i+15] << 28);
        break;

        case 6:
        s[8*i+0] =                              (u[31*i+ 0] << 1) + (u[31*i+ 1] << 9) + (u[31*i+ 2] << 17) + ((uint32_t) u[31*i+ 3] << 25);
        s[8*i+1] = ((u[31*i+ 3] & 0x80) >> 6) + (u[31*i+ 4] << 2) + (u[31*i+ 5] << 10) + (u[31*i+ 6] << 18) + ((uint32_t) u[31*i+ 7] << 26);
        s[8*i+2] = ((u[31*i+ 7] & 0xc0) >> 5) + (u[31*i+ 8] << 3) + (u[31*i+ 9] << 11) + (u[31*i+10] << 19) + ((uint32_t) u[31*i+11] << 27);
        s[8*i+3] = ((u[31*i+11] & 0xe0) >> 4) + (u[31*i+12] << 4) + (u[31*i+13] << 12) + (u[31*i+14] << 20) + ((uint32_t) u[31*i+15] << 28);
        s[8*i+4] =  ((u[31*i+15] & 0xf0) >> 3)+ (u[31*i+ 16] << 5) + (u[31*i+ 17] << 13) + (u[31*i+ 18] << 21) + ((uint32_t) u[31*i+ 19] << 29);
        s[8*i+5] = ((u[31*i+ 19] & 0xf8) >> 2) + (u[31*i+ 20] << 6) + (u[31*i+ 21] << 14) + (u[31*i+ 22] << 22) + ((uint32_t) u[31*i+ 23] << 30);
        break;

        default:break;

    }


    for (i = 0; i<2*N; i++) s[i] |=  1;
        
    crypto_sort_int32(s,N3-1);

    for(i=0; i<N3-1; i++)
        r[i] = ((uint16_t) (s[i] & 1));

    r[N3-1] = 0;   
}

void sample_fixed_type_lf_t(int *r, const unsigned char u[T_SAMPLE_BYTES])
{


    int32_t s[2*N];
    int i;

    for (i = 0; i < (2*N); i++)
    {
        s[i] = (u[4*i+0]) + (u[4*i+1]<<8) + (u[4*i+2]<<16) + (u[4*i+3]<<24);
    }

    for(int i = 0;i<2*N;i++){
        r[i] = mod6(s[i]);
    }

    

}

void sample_lf(Term* r,const unsigned char u[N3_SAMPLE_BYTES+T_SAMPLE_BYTES]){

    int arr[N3];

    sample_fixed_type_lf(arr,u);

    int map[6][2] = {{1,0},{-1,0},{0,1},{0,-1},{-1,-1},{1,1}};

    int coeffValues[2*N];

    sample_fixed_type_lf_t(coeffValues,u+N3_SAMPLE_BYTES);

    int j = 0;

    for(int i = 0;i<N3;i++){
        if(arr[i]==1){
            r[i].a = map[coeffValues[j]][0];
            r[i].b = map[coeffValues[j]][1];
            j++;

        }
        else{
            r[i].a = 0;
            r[i].b = 0;
        }
    }

}


void sample_fixed_type_lg(int *r, const unsigned char u[N3_SAMPLE_BYTES]){

    int32_t s[N3-1];
    int i;

    for (i = 0; i < (N3 - 1)/8; i++)
    {
        s[8*i+0] =                              (u[29*i+ 0] << 3) + (u[29*i+ 1] << 11) + (u[29*i+ 2] << 19) + ((uint32_t) u[29*i+ 3] << 27);
        s[8*i+1] = ((u[29*i+ 3] & 0xe0) >> 2) + (u[29*i+ 4] << 6) + (u[29*i+ 5] << 14) + (u[29*i+ 6] << 22) + ((uint32_t) u[29*i+ 7] << 30);
        s[8*i+2] = ((u[29*i+ 7] & 0xfc) << 1) + (u[29*i+ 8] << 9) + (u[29*i+ 9] << 17) + ((uint32_t)u[29*i+10] << 25);
        s[8*i+3] = ((u[29*i+10] & 0x80) >> 4) + (u[29*i+11] << 4) + (u[29*i+12] << 12) + (u[29*i+13] << 20) + ((uint32_t) u[29*i+14] << 28);
        s[8*i+4] =  ((u[29*i+14] & 0xf0) >> 1)+ (u[29*i+ 15] << 7) + (u[29*i+ 16] << 15) + (u[29*i+ 17] << 23) + ((uint32_t) u[29*i+ 18] << 31);
        s[8*i+5] = ((u[29*i+ 18] & 0xfe) <<2) + (u[29*i+ 19] << 10) + (u[29*i+ 20] << 18) + ((uint32_t) u[29*i+ 21] << 26);
        s[8*i+6] = ((u[29*i+ 21] & 0xc0) >> 3) + (u[29*i+ 22] << 5) + (u[29*i+ 23] << 13) + (u[29*i+24] << 21) + ((uint32_t) u[29*i+25] << 29);
        s[8*i+7] = ((u[29*i+25] & 0xf8)) + (u[29*i+26] << 8) + (u[29*i+27] << 16) + (u[29*i+28] << 24);
    }

    int leftOut = (N3  - 1) - ((N3  - 1) / 8) * 8;

    i = (N3 - 1)/8;

    switch(leftOut){

        case 2:
        s[8*i+0] =                              (u[29*i+ 0] << 3) + (u[29*i+ 1] << 11) + (u[29*i+ 2] << 19) + ((uint32_t) u[29*i+ 3] << 27);
        s[8*i+1] = ((u[29*i+ 3] & 0xe0) >> 2) + (u[29*i+ 4] << 6) + (u[29*i+ 5] << 14) + (u[29*i+ 6] << 22) + ((uint32_t) u[29*i+ 7] << 30);
        break;

        case 4:
        s[8*i+0] =                              (u[29*i+ 0] << 3) + (u[29*i+ 1] << 11) + (u[29*i+ 2] << 19) + ((uint32_t) u[29*i+ 3] << 27);
        s[8*i+1] = ((u[29*i+ 3] & 0xe0) >> 2) + (u[29*i+ 4] << 6) + (u[29*i+ 5] << 14) + (u[29*i+ 6] << 22) + ((uint32_t) u[29*i+ 7] << 30);
        s[8*i+2] = ((u[29*i+ 7] & 0xfc) << 1) + (u[29*i+ 8] << 9) + (u[29*i+ 9] << 17) + ((uint32_t)u[29*i+10] << 25);
        s[8*i+3] = ((u[29*i+10] & 0x80) >> 4) + (u[29*i+11] << 4) + (u[29*i+12] << 12) + (u[29*i+13] << 20) + ((uint32_t) u[29*i+14] << 28);
        break;

        case 6:
        s[8*i+0] =                              (u[29*i+ 0] << 3) + (u[29*i+ 1] << 11) + (u[29*i+ 2] << 19) + ((uint32_t) u[29*i+ 3] << 27);
        s[8*i+1] = ((u[29*i+ 3] & 0xe0) >> 2) + (u[29*i+ 4] << 6) + (u[29*i+ 5] << 14) + (u[29*i+ 6] << 22) + ((uint32_t) u[29*i+ 7] << 30);
        s[8*i+2] = ((u[29*i+ 7] & 0xfc) << 1) + (u[29*i+ 8] << 9) + (u[29*i+ 9] << 17) + ((uint32_t)u[29*i+10] << 25);
        s[8*i+3] = ((u[29*i+10] & 0x80) >> 4) + (u[29*i+11] << 4) + (u[29*i+12] << 12) + (u[29*i+13] << 20) + ((uint32_t) u[29*i+14] << 28);
        s[8*i+4] =  ((u[29*i+14] & 0xf0) >> 1)+ (u[29*i+ 15] << 7) + (u[29*i+ 16] << 15) + (u[29*i+ 17] << 23) + ((uint32_t) u[29*i+ 18] << 31);
        s[8*i+5] = ((u[29*i+ 18] & 0xfe) <<2) + (u[29*i+ 19] << 10) + (u[29*i+ 20] << 18) + ((uint32_t) u[29*i+ 21] << 26);
        break;

        default:break;
    }

    int S = (2*N)/3 * 3;

    for(int i = 0;i<S;i = i + 3){

        unsigned char randomval_seed[4];

        randombytes(randomval_seed,4);

        int randomValue = (u[0]) + (u[1]<<8) + (u[2]<<16) + (u[3]<<24);

        int set = randomValue & 1;

        int start = (set==0)?1:4;

        for(int j = 0;j<3;j++){
            s[i+j] |= (start++);
        }    
    }

    crypto_sort_int32(s,N3-1);

    for(int i = 0;i<N3-1;i++){
        r[i] = (s[i] & 7);
    }

    r[N3 - 1] = 0;
}

void sample_lg(Term* r,const unsigned char u[N3_SAMPLE_BYTES]){

    int arr[N3];

    sample_fixed_type_lg(arr,u);

    int map[7][2] = {{0,0},{1,0},{0,1},{-1,-1},{-1,0},{0,-1},{1,1}};

    int cnt = 0;

    for(int i = 0;i<N3;i++){
        r[i].a = map[arr[i]][0];
        r[i].b = map[arr[i]][1];

        if(r[i].a!=0 || r[i].b!=0){
            cnt++;
        }
    }

}


void sample_fixed_type_lm(int *r, const unsigned char u[N3_SAMPLE_BYTES])
{
    int32_t s[N3];
    int i;

    for (i = 0; i < (N3); i++)
    {
        s[i] = (u[4*i+0]) + (u[4*i+1]<<8) + (u[4*i+2]<<16) + (u[4*i+3]<<24);
    }

    for(int i = 0;i<(N3);i++){
        r[i] = (s[i] & 3);
    }

    // r[N-1] = 0;
}

void sample_lm(Term *r, const unsigned char u[N3_SAMPLE_BYTES]){
    int map[4][2] = {{0,0},{1,0},{0,1},{2,2}};

    int arr[N3];

    sample_fixed_type_lm(arr,u);

    for(int i = 0;i<N3;i++){
        r[i].a = map[arr[i]][0];
        r[i].b = map[arr[i]][1];
    }
}



void sample_mask(Term* mask,unsigned char t_seed[LENGTH_OF_HASH]){
    unsigned char uniformbytes[N3_SAMPLE_M_BYTES];
    int filled = 0;

    sha3_512(t_seed,t_seed,LENGTH_OF_HASH);

    while(filled<N3_SAMPLE_M_BYTES){
        int rem = N3_SAMPLE_M_BYTES - filled;
        if(rem>=LENGTH_OF_HASH){
            memcpy(uniformbytes+filled,t_seed,LENGTH_OF_HASH);
        }
        else{
            memcpy(uniformbytes+filled,t_seed,rem);
            
        }
        filled += LENGTH_OF_HASH;
        sha3_512(t_seed,t_seed,LENGTH_OF_HASH);
    }
    sample_lm(mask,uniformbytes);
}


void sample_lphi(Term* r,const unsigned char u[N3_SAMPLE_BYTES]){
    sample_lg(r,u);
}  

void sample_phi(Term* phi,const Term* h, const Term* m){
    unsigned char r_seed[2*LENGTH_OF_HASH];

    sha3_512(r_seed,(unsigned char*)(m), N3*2);
    sha3_512(r_seed+LENGTH_OF_HASH,(unsigned char*)(h), N3*2);

    int filled = 0;

    unsigned char uniformbytes[N3_SAMPLE_BYTES];

    sha3_512(r_seed,r_seed,LENGTH_OF_HASH*2);

    while(filled<N3_SAMPLE_BYTES){
        int rem = N3_SAMPLE_BYTES - filled;
        if(rem>=LENGTH_OF_HASH){
            memcpy(uniformbytes+filled,r_seed,LENGTH_OF_HASH);
        }
        else{
            memcpy(uniformbytes+filled,r_seed,rem);
        }
        filled += LENGTH_OF_HASH;
        sha3_512(r_seed,r_seed,LENGTH_OF_HASH);
    }
    sample_lphi(phi,uniformbytes);

    
}

