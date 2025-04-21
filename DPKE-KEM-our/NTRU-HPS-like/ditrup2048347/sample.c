#include "sample.h"
#include <stdio.h>

// void sample_fg(poly *f, poly *g, const unsigned char uniformbytes[tDiTRU_SAMPLE_FG_BYTES])
// {


// #ifdef tDiTRU_HPS
//   sample_iid(f,uniformbytes);
//   sample_fixed_type(g,uniformbytes+tDiTRU_SAMPLE_IID_BYTES);
// #endif
// }

void sample_fg_tDiTRU(poly *f, poly *g, const unsigned char uniformbytes[tDiTRU_SAMPLE_FG_BYTES ]){

  
 
     poly x1,x2,x3,x4;
     poly *f0 = &x1 ,*f1 = &x2;
     poly *g0 = &x3 ,*g1 = &x4;

     //sample_iid_tDiTRU(f,uniformbytes );
          
     sample_fixed_type(f0,uniformbytes, (d_f)/2 , 0);
  
     sample_fixed_type(f1,uniformbytes+tDiTRU_SAMPLE_FT_BYTES, d_f-d_f/2 , 1);
  

     sample_fixed_type(g0,uniformbytes+2*tDiTRU_SAMPLE_FT_BYTES, (d_f)/2 , 0);
     
     sample_fixed_type(g1 , uniformbytes+3*tDiTRU_SAMPLE_FT_BYTES, (d_f+1)/2, 0);

      for(int i=0;i<N;i++)
      {
        f->coeffs[i] = f0->coeffs[i];
        f->coeffs[N+i] = f1->coeffs[i];
        g->coeffs[i] = g0->coeffs[i];
        g->coeffs[N+i] = g1->coeffs[i];
      }

     
   
 

}

void sample_rm(poly *r, poly *m, const unsigned char uniformbytes[tDiTRU_SAMPLE_RM_BYTES])
{


#ifdef tDiTRU_HPS
  sample_iid(r,uniformbytes);
  sample_fixed_type(m,uniformbytes+tDiTRU_SAMPLE_FT_BYTES ,d_f,0);  // take d need to be checked and bit.
#endif
}
void sample_rm_tDiTRU(poly*r,poly*m,const unsigned char uniformbytes[tDiTRU_SAMPLE_RM_BYTES]){
    poly x1,x2,x3,x4;
     poly *f0 = &x1 ,*f1 = &x2;
     poly *g0 = &x3 ,*g1 = &x4;

     //sample_iid_tDiTRU(f,uniformbytes );
          
     sample_fixed_type(f0,uniformbytes, (d_f)/2 , 0);
  
     sample_fixed_type(f1,uniformbytes+tDiTRU_SAMPLE_FT_BYTES, d_f-d_f/2 , 0);
  

     sample_fixed_type(g0,uniformbytes+2*tDiTRU_SAMPLE_FT_BYTES, (d_f)/2 , 0);
     
     sample_fixed_type(g1 , uniformbytes+3*tDiTRU_SAMPLE_FT_BYTES, (d_f+1)/2, 0);

      for(int i=0;i<N;i++)
      {
        r->coeffs[i] = f0->coeffs[i];
        r->coeffs[N+i] = f1->coeffs[i];
        m->coeffs[i] = g0->coeffs[i];
        m->coeffs[N+i] = g1->coeffs[i];
      }
}


#ifdef tDiTRU_HPS
void sample_fixed_type(poly *r, const unsigned char *u, int d ,int bit )
{
  
  // Assumes NTRU_SAMPLE_FT_BYTES = ceil(30*(n-1)/8)

  int32_t s[N];
  int i;

  // Use 30 bits of u per word
  for (i = 0; i < (N)/4; i++)
  {
    s[4*i+0] =                              (u[15*i+ 0] << 2) + (u[15*i+ 1] << 10) + (u[15*i+ 2] << 18) + ((uint32_t) u[15*i+ 3] << 26);
    s[4*i+1] = ((u[15*i+ 3] & 0xc0) >> 4) + (u[15*i+ 4] << 4) + (u[15*i+ 5] << 12) + (u[15*i+ 6] << 20) + ((uint32_t) u[15*i+ 7] << 28);
    s[4*i+2] = ((u[15*i+ 7] & 0xf0) >> 2) + (u[15*i+ 8] << 6) + (u[15*i+ 9] << 14) + (u[15*i+10] << 22) + ((uint32_t) u[15*i+11] << 30);
    s[4*i+3] =  (u[15*i+11] & 0xfc)       + (u[15*i+12] << 8) + (u[15*i+13] << 16) + ((uint32_t) u[15*i+14] << 24);
  }
  int dif = N-(N/4)*4;
  //printf("dif %d \n", dif);
  i = (N)/4;
if (dif ==1)// (N) = 1 mod 4
{
  s[4*i+0] =                              (u[15*i+ 0] << 2) + (u[15*i+ 1] << 10) + (u[15*i+ 2] << 18) + ((uint32_t) u[15*i+ 3] << 26);
}

else if (dif ==2)// (N) = 2 mod 4
{
  s[4*i+0] =                              (u[15*i+ 0] << 2) + (u[15*i+ 1] << 10) + (u[15*i+ 2] << 18) + ((uint32_t) u[15*i+ 3] << 26);
  s[4*i+1] = ((u[15*i+ 3] & 0xc0) >> 4) + (u[15*i+ 4] << 4) + (u[15*i+ 5] << 12) + (u[15*i+ 6] << 20) + ((uint32_t) u[15*i+ 7] << 28);
}

else// (N) = 3 mod 4
{ 
  s[4*i+0] =                              (u[15*i+ 0] << 2) + (u[15*i+ 1] << 10) + (u[15*i+ 2] << 18) + ((uint32_t) u[15*i+ 3] << 26);
  s[4*i+1] = ((u[15*i+ 3] & 0xc0) >> 4) + (u[15*i+ 4] << 4) + (u[15*i+ 5] << 12) + (u[15*i+ 6] << 20) + ((uint32_t) u[15*i+ 7] << 28);
  s[4*i+2] = ((u[15*i+ 7] & 0xf0) >> 2) + (u[15*i+ 8] << 6) + (u[15*i+ 9] << 14) + (u[15*i+10] << 22) + ((uint32_t) u[15*i+11] << 30);
}



  
  for (i = 0; i<d; i++) {s[i] |=  1;}

  for (i = d; i<2*d; i++) {s[i] |=  2;}
  s[2*d]=bit;
  

  
  crypto_sort_int32(s,N-1);

  for(i=0; i<N; i++)
    r->coeffs[i] = ((uint16_t) (s[i] & 3));
    r->coeffs[N-1] = 0;

}
#endif










void sample_fixed_type_tDiTRU(poly *r, const unsigned char u[tDiTRU_SAMPLE_FT_BYTES])
{
  // Assumes NTRU_SAMPLE_FT_BYTES = ceil(30*(n-1)/8)

  int32_t s[ORDER-1];
  int i;

  // Use 30 bits of u per word
  for (i = 0; i < (N-1)/4; i++)
  {
    s[4*i+0] =                              (u[15*i+ 0] << 2) + (u[15*i+ 1] << 10) + (u[15*i+ 2] << 18) + ((uint32_t) u[15*i+ 3] << 26);
    s[4*i+1] = ((u[15*i+ 3] & 0xc0) >> 4) + (u[15*i+ 4] << 4) + (u[15*i+ 5] << 12) + (u[15*i+ 6] << 20) + ((uint32_t) u[15*i+ 7] << 28);
    s[4*i+2] = ((u[15*i+ 7] & 0xf0) >> 2) + (u[15*i+ 8] << 6) + (u[15*i+ 9] << 14) + (u[15*i+10] << 22) + ((uint32_t) u[15*i+11] << 30);
    s[4*i+3] =  (u[15*i+11] & 0xfc)       + (u[15*i+12] << 8) + (u[15*i+13] << 16) + ((uint32_t) u[15*i+14] << 24);
  }
#if (N - 1) > ((N - 1) / 4) * 4 // (N-1) = 2 mod 4
  i = (N-1)/4;
  s[4*i+0] =                              (u[15*i+ 0] << 2) + (u[15*i+ 1] << 10) + (u[15*i+ 2] << 18) + ((uint32_t) u[15*i+ 3] << 26);
  s[4*i+1] = ((u[15*i+ 3] & 0xc0) >> 4) + (u[15*i+ 4] << 4) + (u[15*i+ 5] << 12) + (u[15*i+ 6] << 20) + ((uint32_t) u[15*i+ 7] << 28);
#endif

  for (i = 0; i<tDiTRU_WEIGHT/2; i++) s[i] |=  1;

  for (i = tDiTRU_WEIGHT/2; i<tDiTRU_WEIGHT; i++) s[i] |=  2;

  crypto_sort_int32(s,N-1);

  for(i=0; i<N-1; i++)
    r->coeffs[i] = ((uint16_t) (s[i] & 3));

  r->coeffs[N-1] = 0;

//second loop:


   for (i = N; i < (5*N-1)/4; i++)
  {
    s[4*i+0] =                              (u[15*i+ 0] << 2) + (u[15*i+ 1] << 10) + (u[15*i+ 2] << 18) + ((uint32_t) u[15*i+ 3] << 26);
    s[4*i+1] = ((u[15*i+ 3] & 0xc0) >> 4) + (u[15*i+ 4] << 4) + (u[15*i+ 5] << 12) + (u[15*i+ 6] << 20) + ((uint32_t) u[15*i+ 7] << 28);
    s[4*i+2] = ((u[15*i+ 7] & 0xf0) >> 2) + (u[15*i+ 8] << 6) + (u[15*i+ 9] << 14) + (u[15*i+10] << 22) + ((uint32_t) u[15*i+11] << 30);
    s[4*i+3] =  (u[15*i+11] & 0xfc)       + (u[15*i+12] << 8) + (u[15*i+13] << 16) + ((uint32_t) u[15*i+14] << 24);
  }
#if (5*N - 1) > ((5*N - 1) / 4) * 4 // (N-1) = 2 mod 4
  i = (N-1)/4;
  s[4*i+0] =                              (u[15*i+ 0] << 2) + (u[15*i+ 1] << 10) + (u[15*i+ 2] << 18) + ((uint32_t) u[15*i+ 3] << 26);
  s[4*i+1] = ((u[15*i+ 3] & 0xc0) >> 4) + (u[15*i+ 4] << 4) + (u[15*i+ 5] << 12) + (u[15*i+ 6] << 20) + ((uint32_t) u[15*i+ 7] << 28);
#endif

  for (i = 0; i<tDiTRU_WEIGHT/2; i++) s[i] |=  1;

  for (i = tDiTRU_WEIGHT/2; i<tDiTRU_WEIGHT; i++) s[i] |=  2;
    
  crypto_sort_int32(s+N,ORDER-1);

  for(i=0; i<N-1; i++)
    r->coeffs[i] = ((uint16_t) (s[i] & 3));

  r->coeffs[N-1] = 0;
}
