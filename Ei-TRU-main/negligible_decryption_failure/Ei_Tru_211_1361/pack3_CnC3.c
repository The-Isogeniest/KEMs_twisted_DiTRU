#include "pack3_CnC3.h"

static uint16_t mod3(uint16_t a)
{
  uint16_t r;
  int16_t t, c;

  r = (a >> 8) + (a & 0xff); // r mod 255 == a mod 255
  r = (r >> 4) + (r & 0xf); // r' mod 15 == r mod 15
  r = (r >> 2) + (r & 0x3); // r' mod 3 == r mod 3
  r = (r >> 2) + (r & 0x3); // r' mod 3 == r mod 3

  t = r - 3;
  c = t >> 15;

  return (c&r) ^ (~c&t);
}



void poly_S3_tobytes(unsigned char msg[PPKE_MESSAGEBYTES], const Term *a)
{
  int arr[2*N3];

  int k = 0;

  for(int i = 0;i<N3;i++){
    arr[k] = a[i].a;
    if(arr[k]==-2){
      arr[k] = 1;
    }
    k++;
    arr[k] = a[i].b;
    if(arr[k]==-2){
      arr[k] = 1;
    }
    k++;
  }


  int i;
  unsigned char c;
#if PACK_DEG > (PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  int j;
#endif

  for(i=0; i<PACK_DEG/5; i++)
  {
    c =        arr[5*i+4] & 255;
    c = (3*c + arr[5*i+3]) & 255;
    c = (3*c + arr[5*i+2]) & 255;
    c = (3*c + arr[5*i+1]) & 255;
    c = (3*c + arr[5*i+0]) & 255;

    
    msg[i] = c;
  }
#if PACK_DEG > (PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  i = PACK_DEG/5;
  c = 0;
  for(j = PACK_DEG - (5*i) - 1; j>=0; j--)
    c = (3*c + arr[5*i+j]) & 255;
  msg[i] = c;
#endif
}

void poly_S3_frombytes(Term *r, const unsigned char msg[PPKE_MESSAGEBYTES])
{
  int arr[2*N3];
  int i;
  unsigned char c;
#if PACK_DEG > (PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  int j;
#endif

  for(i=0; i<PACK_DEG/5; i++)
  {
    c = msg[i];
    arr[5*i+0] = c;
    arr[5*i+1] = c * 171 >> 9;  // this is division by 3
    arr[5*i+2] = c * 57 >> 9;  // division by 3^2
    arr[5*i+3] = c * 19 >> 9;  // division by 3^3
    arr[5*i+4] = c * 203 >> 14;  // etc.
  }
#if PACK_DEG > (PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  i = PACK_DEG/5;
  c = msg[i];
  for(j=0; (5*i+j)<PACK_DEG; j++)
  {
    arr[5*i+j] = c;
    c = c * 171 >> 9;
  }
#endif
  // arr[2*N3-1] = 0;
  // poly_mod_3_Phi_n(r);

  // for(int i = 0;i<2*N3;i++){
  //   printf("%d ",arr[i]%3);
  // }
  // printf("\n");

  for(int i = 0;i<2*N3;i++){
    arr[i] = mod3(arr[i]);
    if(arr[i]==1){
      arr[i] = -2;
    }
  }

  int k = 0;

  for(int i = 0;i<N3;i++){
    r[i].a = arr[k++];
    r[i].b = arr[k++];
  }

}

void poly_S3m_tobytes(unsigned char msg[PPKE_MESSAGEBYTES], const Term *a)
{
  int arr[2*N3];

  int k = 0;

  for(int i = 0;i<N3;i++){
    arr[k] = a[i].a;
    if(arr[k]==-1){
      arr[k] = 2;
    }
    k++;
    arr[k] = a[i].b;
    if(arr[k]==-1){
      arr[k] = 2;
    }
    k++;
  }


  int i;
  unsigned char c;
#if PACK_DEG > (PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  int j;
#endif

  for(i=0; i<PACK_DEG/5; i++)
  {
    c =        arr[5*i+4] & 255;
    c = (3*c + arr[5*i+3]) & 255;
    c = (3*c + arr[5*i+2]) & 255;
    c = (3*c + arr[5*i+1]) & 255;
    c = (3*c + arr[5*i+0]) & 255;

    
    msg[i] = c;
  }
#if PACK_DEG > (PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  i = PACK_DEG/5;
  c = 0;
  for(j = PACK_DEG - (5*i) - 1; j>=0; j--)
    c = (3*c + arr[5*i+j]) & 255;
  msg[i] = c;
#endif
}

void poly_S3m_frombytes(Term *r, const unsigned char msg[PPKE_MESSAGEBYTES])
{
  int arr[2*N3];
  int i;
  unsigned char c;
#if PACK_DEG > (PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  int j;
#endif

  for(i=0; i<PACK_DEG/5; i++)
  {
    c = msg[i];
    arr[5*i+0] = c;
    arr[5*i+1] = c * 171 >> 9;  // this is division by 3
    arr[5*i+2] = c * 57 >> 9;  // division by 3^2
    arr[5*i+3] = c * 19 >> 9;  // division by 3^3
    arr[5*i+4] = c * 203 >> 14;  // etc.
  }
#if PACK_DEG > (PACK_DEG / 5) * 5  // if 5 does not divide NTRU_N-1
  i = PACK_DEG/5;
  c = msg[i];
  for(j=0; (5*i+j)<PACK_DEG; j++)
  {
    arr[5*i+j] = c;
    c = c * 171 >> 9;
  }
#endif
  // arr[2*N3-1] = 0;
  // poly_mod_3_Phi_n(r);

  // for(int i = 0;i<2*N3;i++){
  //   printf("%d ",arr[i]%3);
  // }
  // printf("\n");

  for(int i = 0;i<2*N3;i++){
    arr[i] = mod3(arr[i]);
    if(arr[i]==2){
      arr[i] = -1;
    }
  }

  int k = 0;

  for(int i = 0;i<N3;i++){
    r[i].a = arr[k++];
    r[i].b = arr[k++];
  }

}