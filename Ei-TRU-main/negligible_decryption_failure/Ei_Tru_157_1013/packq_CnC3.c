#include "packq_CnC3.h"

#if Q==701

void poly_pack_Sq_tobytes(unsigned char *r, Term *a)
{

    Term q = {Q,0};
   
  int i,j;
  int16_t t[8];


  int k = 0;

  for(i=0;i<PACK_DEG/8;i++)
  {
    for(j=0;j<8;j+=2){
        Term temp = a[k++];
        
       
      t[j] = temp.a;
      if(t[j]<0){
        t[j] = -t[j];
        t[j] = t[j] | (1<<9);
      }
      t[j+1] = temp.b;
      if(t[j+1]<0){
        t[j+1] = -t[j+1];
        t[j+1] = t[j+1] | (1<<9);
      }
    }
    

    r[10 * i + 0] = (t[0] & 0xff);
    r[10 * i + 1] = (t[0]>>8)&0x03 | (t[1] & 0x3f)<<2;
    r[10 * i + 2] = (t[1]>>6)&0x0f | (t[2] & 0x0f)<<4;
    r[10 * i + 3] = (t[2]>>4)&0x3f | (t[3] & 0x03)<<6;
    r[10 * i + 4] = (t[3]>>2)&0xff;
    r[10 * i + 5] = (t[4] & 0xff);
    r[10 * i + 6] = (t[4]>>8)&0x03 | (t[5] & 0x3f)<<2;
    r[10 * i + 7] = (t[5]>>6)&0x0f | (t[6] & 0x0f)<<4;
    r[10 * i + 8] = (t[6]>>4)&0x3f | (t[7] & 0x03)<<6;
    r[10 * i + 9] = (t[7]>>2)&0xff;
  }

  for(j=0;j<PACK_DEG-8*i;j+=2){

    Term temp = a[k++];
        
      t[j] = temp.a;
      if(t[j]<0){
        t[j] = -t[j];
        t[j] = t[j] | (1<<9);
      }
      t[j+1] = temp.b;
      if(t[j+1]<0){
        t[j+1] = -t[j+1];
        t[j+1] = t[j+1] | (1<<9);
      }
  }
  for(; j<8; j++)
    t[j] = 0;

  switch(PACK_DEG&0x07)
  {
    
    case 6:
    r[10 * i + 0] = (t[0] & 0xff);
    r[10 * i + 1] = (t[0]>>8)&0x03 | (t[1] & 0x3f)<<2;
    r[10 * i + 2] = (t[1]>>6)&0x0f | (t[2] & 0x0f)<<4;
    r[10 * i + 3] = (t[2]>>4)&0x3f | (t[3] & 0x03)<<6;
    r[10 * i + 4] = (t[3]>>2)&0xff;
    r[10 * i + 5] = (t[4] & 0xff);
    r[10 * i + 6] = (t[4]>>8)&0x03 | (t[5] & 0x3f)<<2;
    r[10 * i + 7] = (t[5]>>6)&0x0f | (t[6] & 0x0f)<<4;
    r[10 * i + 8] = (t[6]>>4)&0x3f | (t[7] & 0x03)<<6;
    break;
    
    case 2:
      r[11 * i + 0] = (unsigned char) (t[0]        & 0xff);
      r[11 * i + 1] = (unsigned char) (t[0] >>  8) | ((t[1] & 0x1f) << 3);
      r[11 * i + 2] = (unsigned char) (t[1] >>  5) | ((t[2] & 0x03) << 6);
      break;
  }
}

void poly_unpack_Sq_frombytes(Term *r, const unsigned char *a)
{
    int16_t arr[2*N3];
  int i;
  for(i=0;i<PACK_DEG/8;i++)
  {
    arr[8 * i + 0] = (a[10 * i + 0] & 0xff) | (a[10 * i + 1] & 0x03)<<8;
    arr[8 * i + 1] = (a[10 * i + 1]>>2)&0x3f | (a[10 * i + 2]&0x0f)<<6;
    arr[8 * i + 2] = (a[10 * i + 2]>>4)&0x0f | (a[10 * i + 3] & 0x3f)<<4;
    arr[8 * i + 3] = (a[10 * i + 3]>>6)&0x03 | (a[10 * i + 4] & 0xff)<<2;
    arr[8 * i + 4] = (a[10 * i + 5] & 0xff) | (a[10 * i + 6] & 0x03)<<8;
    arr[8 * i + 5] = (a[10 * i + 6]>>2)&0x3f | (a[10 * i + 7]&0x0f)<<6;
    arr[8 * i + 6] = (a[10 * i + 7]>>4)&0x0f | (a[10 * i + 8] & 0x3f)<<4;
    arr[8 * i + 7] = (a[10 * i + 8]>>6)&0x03 | (a[10 * i + 9] & 0xff)<<2;
  }


  switch(PACK_DEG&0x07)
  {
    
    case 6:
     arr[8 * i + 0] = (a[10 * i + 0] & 0xff) | (a[10 * i + 1] & 0x03)<<8;
    arr[8 * i + 1] = (a[10 * i + 1]>>2)&0x3f | (a[10 * i + 2]&0x0f)<<6;
    arr[8 * i + 2] = (a[10 * i + 2]>>4)&0x0f | (a[10 * i + 3] & 0x3f)<<4;
    arr[8 * i + 3] = (a[10 * i + 3]>>6)&0x03 | (a[10 * i + 4] & 0xff)<<2;
    arr[8 * i + 4] = (a[10 * i + 5] & 0xff) | (a[10 * i + 6] & 0x03)<<8;
    arr[8 * i + 5] = (a[10 * i + 6]>>2)&0x3f | (a[10 * i + 7]&0x0f)<<6;
    break;
    

    case 2:
      arr[8*i+0] = (a[11*i+ 0] >> 0) | (((uint16_t)a[11*i+ 1] & 0x07) << 8);
      arr[8*i+1] = (a[11*i+ 1] >> 3) | (((uint16_t)a[11*i+ 2] & 0x3f) << 5);
      break;
  }
  int k = 0;

  
  for(int i = 0;i<N3*2;i++){
        int sign = (arr[i]&(1<<9))!=0;
       
        arr[i] = arr[i]&0x1ff;
        if(sign){
            
            arr[i] = -arr[i];
        }
  }

  for(int i = 0;i<N3;i++){
    r[i].a = arr[k++];
    r[i].b = arr[k++];
  }
  
}

#elif Q==1361 || Q==1013
void poly_pack_Sq_tobytes(unsigned char *r, Term *a)
{

    Term q = {Q,0};

    
  int i,j;
  int16_t t[8];


  int k = 0;

  for(i=0;i<PACK_DEG/8;i++)
  {
    for(j=0;j<8;j+=2){
        Term temp = a[k++];
        
        
      t[j] = temp.a;
      if(t[j]<0){
        t[j] = -t[j];
        t[j] = t[j] | (1<<10);
      }
      t[j+1] = temp.b;
      if(t[j+1]<0){
        t[j+1] = -t[j+1];
        t[j+1] = t[j+1] | (1<<10);
      }
    }
    
    r[11 * i + 0] = (unsigned char) ( t[0]        & 0xff);
    r[11 * i + 1] = (unsigned char) ((t[0] >>  8) | ((t[1] & 0x1f) << 3));
    r[11 * i + 2] = (unsigned char) ((t[1] >>  5) | ((t[2] & 0x03) << 6));
    r[11 * i + 3] = (unsigned char) ((t[2] >>  2) & 0xff);
    r[11 * i + 4] = (unsigned char) ((t[2] >> 10) | ((t[3] & 0x7f) << 1));
    r[11 * i + 5] = (unsigned char) ((t[3] >>  7) | ((t[4] & 0x0f) << 4));
    r[11 * i + 6] = (unsigned char) ((t[4] >>  4) | ((t[5] & 0x01) << 7));
    r[11 * i + 7] = (unsigned char) ((t[5] >>  1) & 0xff);
    r[11 * i + 8] = (unsigned char) ((t[5] >>  9) | ((t[6] & 0x3f) << 2));
    r[11 * i + 9] = (unsigned char) ((t[6] >>  6) | ((t[7] & 0x07) << 5));
    r[11 * i + 10] = (unsigned char) ((t[7] >>  3));
  }

  for(j=0;j<PACK_DEG-8*i;j+=2){

    Term temp = a[k++];
        
      t[j] = temp.a;
      if(t[j]<0){
        t[j] = -t[j];
        t[j] = t[j] | (1<<10);
      }
      t[j+1] = temp.b;
      if(t[j+1]<0){
        t[j+1] = -t[j+1];
        t[j+1] = t[j+1] | (1<<10);
      }
  }
  for(; j<8; j++)
    t[j] = 0;

  switch(PACK_DEG&0x07)
  {
    // cases 0 and 6 are impossible since 2 generates (Z/n)* and
    // p mod 8 in {1, 7} implies that 2 is a quadratic residue.
    case 6:
    r[11 * i + 0] = (unsigned char) ( t[0]        & 0xff);
    r[11 * i + 1] = (unsigned char) ((t[0] >>  8) | ((t[1] & 0x1f) << 3));
    r[11 * i + 2] = (unsigned char) ((t[1] >>  5) | ((t[2] & 0x03) << 6));
    r[11 * i + 3] = (unsigned char) ((t[2] >>  2) & 0xff);
    r[11 * i + 4] = (unsigned char) ((t[2] >> 10) | ((t[3] & 0x7f) << 1));
    r[11 * i + 5] = (unsigned char) ((t[3] >>  7) | ((t[4] & 0x0f) << 4));
    r[11 * i + 6] = (unsigned char) ((t[4] >>  4) | ((t[5] & 0x01) << 7));
    r[11 * i + 7] = (unsigned char) ((t[5] >>  1) & 0xff);
    r[11 * i + 8] = (unsigned char) ((t[5] >>  9) | ((t[6] & 0x3f) << 2));
    r[11 * i + 9] = (unsigned char) ((t[6] >>  6) );
    break;
    
    case 2:
      r[11 * i + 0] = (unsigned char) (t[0]        & 0xff);
      r[11 * i + 1] = (unsigned char) (t[0] >>  8) | ((t[1] & 0x1f) << 3);
      r[11 * i + 2] = (unsigned char) (t[1] >>  5);
      break;
  }
}

void poly_unpack_Sq_frombytes(Term *r, const unsigned char *a)
{
    int16_t arr[2*N3];
  int i;
  for(i=0;i<PACK_DEG/8;i++)
  {
    arr[8*i+0] = (a[11*i+ 0] >> 0) | (((uint16_t)a[11*i+ 1] & 0x07) << 8);
    arr[8*i+1] = (a[11*i+ 1] >> 3) | (((uint16_t)a[11*i+ 2] & 0x3f) << 5);
    arr[8*i+2] = (a[11*i+ 2] >> 6) | (((uint16_t)a[11*i+ 3] & 0xff) << 2) | (((uint16_t)a[11*i+ 4] & 0x01) << 10);
    arr[8*i+3] = (a[11*i+ 4] >> 1) | (((uint16_t)a[11*i+ 5] & 0x0f) << 7);
    arr[8*i+4] = (a[11*i+ 5] >> 4) | (((uint16_t)a[11*i+ 6] & 0x7f) << 4);
    arr[8*i+5] = (a[11*i+ 6] >> 7) | (((uint16_t)a[11*i+ 7] & 0xff) << 1) | (((uint16_t)a[11*i+ 8] & 0x03) <<  9);
    arr[8*i+6] = (a[11*i+ 8] >> 2) | (((uint16_t)a[11*i+ 9] & 0x1f) << 6);
    arr[8*i+7] = (a[11*i+ 9] >> 5) | (((uint16_t)a[11*i+10] & 0xff) << 3);
  }


  switch(PACK_DEG&0x07)
  {
    // cases 0 and 6 are impossible since 2 generates (Z/n)* and
    // p mod 8 in {1, 7} implies that 2 is a quadratic residue.
    case 6:
    arr[8*i+0] = (a[11*i+ 0] >> 0) | (((uint16_t)a[11*i+ 1] & 0x07) << 8);
    arr[8*i+1] = (a[11*i+ 1] >> 3) | (((uint16_t)a[11*i+ 2] & 0x3f) << 5);
    arr[8*i+2] = (a[11*i+ 2] >> 6) | (((uint16_t)a[11*i+ 3] & 0xff) << 2) | (((uint16_t)a[11*i+ 4] & 0x01) << 10);
    arr[8*i+3] = (a[11*i+ 4] >> 1) | (((uint16_t)a[11*i+ 5] & 0x0f) << 7);
    arr[8*i+4] = (a[11*i+ 5] >> 4) | (((uint16_t)a[11*i+ 6] & 0x7f) << 4);
    arr[8*i+5] = (a[11*i+ 6] >> 7) | (((uint16_t)a[11*i+ 7] & 0xff) << 1) | (((uint16_t)a[11*i+ 8] & 0x03) <<  9);
    // arr[8*i+6] = (a[11*i+ 8] >> 2) | (((uint16_t)a[11*i+ 9] & 0x1f) << 6);
    break;
    
    case 2:
      arr[8*i+0] = (a[11*i+ 0] >> 0) | (((uint16_t)a[11*i+ 1] & 0x07) << 8);
      arr[8*i+1] = (a[11*i+ 1] >> 3) | (((uint16_t)a[11*i+ 2] & 0x3f) << 5);
      break;
  }
  int k = 0;

 
  for(int i = 0;i<N3*2;i++){
        int sign = (arr[i]&(1<<10))!=0;
        
        arr[i] = arr[i]&0x3ff;
        if(sign){

            arr[i] = -arr[i];
        }
  }

  for(int i = 0;i<N3;i++){
    r[i].a = arr[k++];
    r[i].b = arr[k++];
  }
 
}

#elif Q==2039 || Q==2903
void poly_pack_Sq_tobytes(unsigned char *r, Term *a)
{

    Term q = {Q,0};

  int i,j;
  int16_t t[8];


  int k = 0;

  for(i=0;i<PACK_DEG/8;i++)
  {
    for(j=0;j<8;j+=2){
        Term temp = a[k++];
       
      t[j] = temp.a;
      if(t[j]<0){
        t[j] = -t[j];
        t[j] = t[j] | (1<<11);
      }
      t[j+1] = temp.b;
      if(t[j+1]<0){
        t[j+1] = -t[j+1];
        t[j+1] = t[j+1] | (1<<11);
      }
    }
   

    r[12 * i + 0] = (unsigned char) ( t[0]        & 0xff);
    r[12 * i + 1] = (unsigned char) ((t[0] >>  8) | ((t[1] & 0x0f) << 4));
    r[12 * i + 2] = (unsigned char) ((t[1] >>  4) & 0xff);

    r[12 * i + 3] = (unsigned char) (t[2]         & 0xff);
    r[12 * i + 4] = (unsigned char) ((t[2] >>  8) | ((t[3] & 0x0f) << 4));
    r[12 * i + 5] = (unsigned char) ((t[3] >>  4) & 0xff);
    r[12 * i + 6] = (unsigned char) (t[4]         & 0xff);
    r[12 * i + 7] = (unsigned char) ((t[4] >>  8) | ((t[5] & 0x0f) << 4));
    r[12 * i + 8] = (unsigned char) ((t[5] >>  4) & 0xff);
    r[12 * i + 9] = (unsigned char) ( t[6]        & 0xff);
    r[12 * i + 10] = (unsigned char) ((t[6] >>  8) | ((t[7] & 0x0f) << 4));
    r[12 * i + 11] = (unsigned char) ((t[7] >>  4) & 0xff);
  }

  for(j=0;j<PACK_DEG-8*i;j+=2){

    Term temp = a[k++];
       
      t[j] = temp.a;
      if(t[j]<0){
        t[j] = -t[j];
        t[j] = t[j] | (1<<11);
      }
      t[j+1] = temp.b;
      if(t[j+1]<0){
        t[j+1] = -t[j+1];
        t[j+1] = t[j+1] | (1<<11);
      }
  }
  for(; j<8; j++)
    t[j] = 0;

  switch(PACK_DEG&0x07)
  {
    // cases 0 and 6 are impossible since 2 generates (Z/n)* and
    // p mod 8 in {1, 7} implies that 2 is a quadratic residue.
    case 6:
      r[12 * i + 0] = (unsigned char) ( t[0]        & 0xff);
    r[12 * i + 1] = (unsigned char) ((t[0] >>  8) | ((t[1] & 0x0f) << 4));
    r[12 * i + 2] = (unsigned char) ((t[1] >>  4) & 0xff);

    r[12 * i + 3] = (unsigned char) (t[2]         & 0xff);
    r[12 * i + 4] = (unsigned char) ((t[2] >>  8) | ((t[3] & 0x0f) << 4));
    r[12 * i + 5] = (unsigned char) ((t[3] >>  4) & 0xff);
    r[12 * i + 6] = (unsigned char) (t[4]         & 0xff);
    r[12 * i + 7] = (unsigned char) ((t[4] >>  8) | ((t[5] & 0x0f) << 4));
    r[12 * i + 8] = (unsigned char) ((t[5] >>  4) & 0xff);
    r[12 * i + 9] = (unsigned char) ( t[6]        & 0xff);
    r[12 * i + 10] = (unsigned char) ((t[6] >>  8) | ((t[7] & 0x0f) << 4));
      break;
    

    case 2:
      r[12 * i + 0] = (unsigned char) ( t[0]        & 0xff);
    r[12 * i + 1] = (unsigned char) ((t[0] >>  8) | ((t[1] & 0x0f) << 4));
    r[12 * i + 2] = (unsigned char) ((t[1] >>  4) & 0xff);
      break;
  }
}

void poly_unpack_Sq_frombytes(Term *r, const unsigned char *a)
{
    int16_t arr[2*N3];
  int i;
  for(i=0;i<PACK_DEG/8;i++)
  {
    arr[8*i+0] = (a[12*i+ 0] >> 0) | (((uint16_t)a[12*i+ 1] & 0x0f) << 8);
    arr[8*i+1] = (a[12*i+ 1] >> 4) | (((uint16_t)a[12*i+ 2] & 0xff) << 4);
    arr[8*i+2] = (a[12*i+ 3] >> 0) | (((uint16_t)a[12*i+ 4] & 0x0f) << 8);
    arr[8*i+3] = (a[12*i+ 4] >> 4) | (((uint16_t)a[12*i+ 5] & 0xff) << 4);
    arr[8*i+4] = (a[12*i+ 6] >> 0) | (((uint16_t)a[12*i+ 7] & 0x0f) << 8);
    arr[8*i+5] = (a[12*i+ 7] >> 4) | (((uint16_t)a[12*i+ 8] & 0xff) << 4);
    arr[8*i+6] = (a[12*i+ 9] >> 0) | (((uint16_t)a[12*i+ 10] & 0x0f) << 8);
    arr[8*i+7] = (a[12*i+ 10] >> 4) | (((uint16_t)a[12*i+ 11] & 0xff) << 4);
  }


  switch(PACK_DEG&0x07)
  {
    // cases 0 and 6 are impossible since 2 generates (Z/n)* and
    // p mod 8 in {1, 7} implies that 2 is a quadratic residue.
    case 6:
      arr[8*i+0] = (a[12*i+ 0] >> 0) | (((uint16_t)a[12*i+ 1] & 0x0f) << 8);
    arr[8*i+1] = (a[12*i+ 1] >> 4) | (((uint16_t)a[12*i+ 2] & 0xff) << 4);
    arr[8*i+2] = (a[12*i+ 3] >> 0) | (((uint16_t)a[12*i+ 4] & 0x0f) << 8);
    arr[8*i+3] = (a[12*i+ 4] >> 4) | (((uint16_t)a[12*i+ 5] & 0xff) << 4);
    arr[8*i+4] = (a[12*i+ 6] >> 0) | (((uint16_t)a[12*i+ 7] & 0x0f) << 8);
    arr[8*i+5] = (a[12*i+ 7] >> 4) | (((uint16_t)a[12*i+ 8] & 0xff) << 4);
    break;
   
    case 2:
       arr[8*i+0] = (a[12*i+ 0] >> 0) | (((uint16_t)a[12*i+ 1] & 0x0f) << 8);
    arr[8*i+1] = (a[12*i+ 1] >> 4) | (((uint16_t)a[12*i+ 2] & 0xff) << 4);
      break;
  }
  int k = 0;

  for(int i = 0;i<N3*2;i++){
        int sign = (arr[i]&(1<<11))!=0;
        
        arr[i] = arr[i]&0x7ff;
        if(sign){
          
            arr[i] = -arr[i];
        }
  }

  for(int i = 0;i<N3;i++){
    r[i].a = arr[k++];
    r[i].b = arr[k++];
  }
  
}

#elif Q==3863
void poly_pack_Sq_tobytes(unsigned char *r, Term *a)
{

    Term q = {Q,0};

  int i,j;
  int16_t t[8];


  int k = 0;

  for(i=0;i<PACK_DEG/8;i++)
  {
    for(j=0;j<8;j+=2){
        Term temp = a[k++];
       
      t[j] = temp.a;
      if(t[j]<0){
        t[j] = -t[j];
        t[j] = t[j] | (1<<12);
      }
      t[j+1] = temp.b;
      if(t[j+1]<0){
        t[j+1] = -t[j+1];
        t[j+1] = t[j+1] | (1<<12);
      }
    }
    

    r[13*i + 0] = (t[0] & 0xff);
    r[13*i + 1] = ((t[0]>>8)&0x1f) | ((t[1]&0x07)<<5);
    r[13*i + 2] = ((t[1]>>3) & 0xff);
    r[13*i + 3] = ((t[1]>>11 & 0x03) | (t[2] & 0x03f)<<2);
    r[13*i + 4] = ((t[2]>>6)&0x7f) | ((t[3]&0x01)<<7);
    r[13*i + 5] = ((t[3]>>1)&0xff);
    r[13*i + 6] = ((t[3]>>9 &0x0f)) | (t[4]&0x0f)<<4;
    r[13*i + 7] = ((t[4]>>4) &0xff);
    r[13*i + 8] = ((t[4]>>12) & 0x01) | ((t[5]&0x7f)<<1);
    r[13*i + 9] = ((t[5]>>7) & 0x3f)|((t[6]&0x03)<<6);
    r[13*i + 10] = ((t[6]>>2 & 0xff));
    r[13*i + 11] = ((t[6]>>10) & 0x07) | ((t[7]&0x1f)<<3);
    r[13*i + 12] = ((t[7]>>5)&0xff);
  }

  for(j=0;j<PACK_DEG-8*i;j+=2){

    Term temp = a[k++];
        
      t[j] = temp.a;
      if(t[j]<0){
        t[j] = -t[j];
        t[j] = t[j] | (1<<12);
      }
      t[j+1] = temp.b;
      if(t[j+1]<0){
        t[j+1] = -t[j+1];
        t[j+1] = t[j+1] | (1<<12);
      }
  }
  for(; j<8; j++)
    t[j] = 0;

  switch(PACK_DEG&0x07)
  {
    // cases 0 and 6 are impossible since 2 generates (Z/n)* and
    // p mod 8 in {1, 7} implies that 2 is a quadratic residue.
    case 6:
      r[13*i + 0] = (t[0] & 0xff);
    r[13*i + 1] = ((t[0]>>8)&0x1f) | ((t[1]&0x07)<<5);
    r[13*i + 2] = ((t[1]>>3) & 0xff);
    r[13*i + 3] = ((t[1]>>11 & 0x03) | (t[2] & 0x03f)<<2);
    r[13*i + 4] = ((t[2]>>6)&0x7f) | ((t[3]&0x01)<<7);
    r[13*i + 5] = ((t[3]>>1)&0xff);
    r[13*i + 6] = ((t[3]>>9 &0x0f)) | (t[4]&0x0f)<<4;
    r[13*i + 7] = ((t[4]>>4) &0xff);
    r[13*i + 8] = ((t[4]>>12) & 0x01) | ((t[5]&0x7f)<<1);
    r[13*i + 9] = ((t[5]>>7) & 0x3f)|((t[6]&0x03)<<6);
      break;
   

    case 2:
      r[12 * i + 0] = (unsigned char) ( t[0]        & 0xff);
    r[12 * i + 1] = (unsigned char) ((t[0] >>  8) | ((t[1] & 0x0f) << 4));
    r[12 * i + 2] = (unsigned char) ((t[1] >>  4) & 0xff);
      break;
  }
}

void poly_unpack_Sq_frombytes(Term *r, const unsigned char *a)
{
    int16_t arr[2*N3];
  int i;
  for(i=0;i<PACK_DEG/8;i++)
  {
    arr[8*i + 0] = (a[13*i + 0] & 0xff) | (a[13*i + 1] & 0x1f)<<8;
    arr[8*i + 1] = (a[13*i + 1]>>5 & 0x07) | (a[13*i + 2] & 0xff)<<3 | (a[13*i + 3] & 0x03)<<11;
    arr[8*i + 2] = (a[13*i + 3]>>2 & 0x3f) | (a[13*i + 4] & 0x7f)<<6;
    arr[8*i + 3] = (a[13*i + 4]>>7 & 0x01) | (a[13*i + 5] & 0xff)<<1 | (a[13*i + 6] & 0x0f)<<9;
    arr[8*i + 4] = (a[13*i + 6]>>4 & 0x0f) | (a[13*i + 7] & 0xff)<<4 | (a[13*i + 8] & 0x01)<<12;
    arr[8*i + 5] = (a[13*i + 8]>>1 & 0x7f) | (a[13*i + 9] & 0x3f)<<7;
    arr[8*i + 6] = (a[13*i + 9]>>6 & 0x03) | (a[13*i + 10] & 0xff)<<2 | (a[13*i + 11] & 0x07)<<10;
    arr[8*i + 7] = (a[13*i + 11]>>3 & 0x1f) | (a[13*i + 12] & 0xff)<<5;
  }


  switch(PACK_DEG&0x07)
  {
    // cases 0 and 6 are impossible since 2 generates (Z/n)* and
    // p mod 8 in {1, 7} implies that 2 is a quadratic residue.
    case 6:
       arr[8*i + 0] = (a[13*i + 0] & 0xff) | (a[13*i + 1] & 0x1f)<<8;
    arr[8*i + 1] = (a[13*i + 1]>>5 & 0x07) | (a[13*i + 2] & 0xff)<<3 | (a[13*i + 3] & 0x03)<<11;
    arr[8*i + 2] = (a[13*i + 3]>>2 & 0x3f) | (a[13*i + 4] & 0x7f)<<6;
    arr[8*i + 3] = (a[13*i + 4]>>7 & 0x01) | (a[13*i + 5] & 0xff)<<1 | (a[13*i + 6] & 0x0f)<<9;
    arr[8*i + 4] = (a[13*i + 6]>>4 & 0x0f) | (a[13*i + 7] & 0xff)<<4 | (a[13*i + 8] & 0x01)<<12;
    arr[8*i + 5] = (a[13*i + 8]>>1 & 0x7f) | (a[13*i + 9] & 0x3f)<<7;
      break;

    
    case 2:
       arr[8*i+0] = (a[12*i+ 0] >> 0) | (((uint16_t)a[12*i+ 1] & 0x0f) << 8);
    arr[8*i+1] = (a[12*i+ 1] >> 4) | (((uint16_t)a[12*i+ 2] & 0xff) << 4);
      break;
  }
  int k = 0;

  for(int i = 0;i<N3*2;i++){
        int sign = (arr[i]&(1<<12))!=0;
        
        arr[i] = arr[i]&0xfff;
        if(sign){
           
            arr[i] = -arr[i];
        }
  }

  for(int i = 0;i<N3;i++){
    r[i].a = arr[k++];
    r[i].b = arr[k++];
  }
 
}
#endif