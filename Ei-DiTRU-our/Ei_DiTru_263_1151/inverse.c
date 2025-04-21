

#include "inverse.h"
#include "int16.h"
#include <stdlib.h>

Term zero = {0,0};


/* return -1 if x!=0; else return 0 */
static int int16_nonzero_mask(int16 x)
{
  uint16 u = x; /* 0, else 1...65535 */
  uint32 v = u; /* 0, else 1...65535 */
  v = -v; /* 0, else 2^32-65535...2^32-1 */
  v >>= 31; /* 0, else 1 */
  return -v; /* 0, else -1 */
}

/* return -1 if the term is not zero otherwise returns 0 */

static int term_nonzero_mask(Term t)
{
    int16 a = t.a;
    int16 b = t.b;

    uint16 u1 = a;
    uint16 u2 = b;

    uint32 v1 = u1;
    uint32 v2 = u2;

    v1 = -v1;
    v2 = -v2;

    v1>>=31;
    v2>>=31;

    return -1*(v1|v2);
}



/* return -1 if x<0; otherwise return 0 */
static int int16_negative_mask(int16 x)
{
  uint16 u = x;
  u >>= 15;
  return -(int) u;
  /* alternative with gcc -fwrapv: */
  /* x>>15 compiles to CPU's arithmetic right shift */
}

int deg(Term *a,int len){
    int n = len;

    

    for(int i = n - 1;i>=0;i--){
        if(isSame(a[i],zero)==0){
            return i;
        }
    }
}

int is_degree_one(Term* a,int len){
    for(int i = 1;i<len;i++){
        if(isSame(a[i],zero)==0){
            return 0;
        }
    }

    if(isSame(a[0],zero)==0){
        return 1;
    }

    return 0;

}


void division_by_x(Term* a, int len){
    for(int i = 0;i<len-1;i++){
        a[i] = a[i+1];
    }

    a[len-1] = zero;
    
}

void multiply_by_x(Term* a, int len){
    for(int i = len-1;i>0;i--){
        a[i] = a[i-1];
    }

    a[0] = zero;
}

Term unit(Term u){
    Term res;
    if(u.a==1 && u.b==0){
        res.a = 1;
        res.b = 0;
    }
    if(u.a==-1 && u.b==0){
        res.a = -1;
        res.b = 0;
    }
    if(u.a==0 && u.b==1){
        res.a = -1;
        res.b = -1;
    }
    if(u.a==0 && u.b==-1){
        res.a = 1;
        res.b = 1;
    }
    if(u.a==1 && u.b==1){
        res.a = 0;
        res.b = -1;
    }
    if(u.a==-1 && u.b==-1){
        res.a = 0;
        res.b = 1;
    }
    
    return res;
}

Term minus(Term A, Term B){
    Term res;

    res.a = A.a - B.a;
    res.b = A.b - B.b;

    return res;
}

void minus_Zw(Term* a, Term *b, Term mod, Term* res,int len){
    for(int i = 0;i<len;i++){
        res[i] = poly_div_rat(minus(a[i],b[i]),mod);
    }
}



void minus_single_Zwpoly(Term* a, Term* res, Term mod, int len)
    /*
        Input:  - Term*a 
        Output: minus(a)
    */
  {   
    Term Zero = {0,0};
      for(int i=0;i<len;i++)
         {
            res[i] = poly_div_rat(minus(Zero, a[i]), mod);
         }
    
  }

int round1(int c,int d){
    int c1 = c%d;
    if(c1>d/2){
        c1 = c1 - d;
    }
    int res = (c-c1)/d;

    return res;
}

int norm_Zw(Term element){
    int a = element.a;
    int b = element.b;

    int d = a*a + b*b - a*b;

    return d;
}


void red_q_etru(Term element,Term q, Term *res){
    int m = element.a;
    int n = element.b;
    int a = q.a;
    int b = q.b;

    int Q_ = norm_Zw(q);

    int d = 2 * Q_;

    int s = m*(2*a-b)+n*(2*b-a);
    int t = n*a-m*b;

    int re = s/d;
    int im = t/d;

    int x0 = round1(s,d);
    int x1 = round1(t,d);

    Term r1 = {x0+x1,2*x1};

    int s1 = s+Q_;
    int t1 = t-Q_;

    int y0 = round1(s1,d);
    int y1 = round1(t1,d);

    Term r2 = {y0+y1,2*y1+1};

    Term b1 = minus(element,multiply_terms(q,r1));
    Term b2 = minus(element,multiply_terms(q,r2));

    int d1 = norm_Zw(b1);
    int d2 = norm_Zw(b2);

    if(d1<d2){
        res[0] = r1;
        res[1] = b1;
    }
    else if(d1>d2){
        res[0] = r2;
        res[1] = b2;
    }
    else if(x0<y0){
        res[0] = r1;
        res[1] = b1;
    }
    else{
        res[0] = r2;
        res[1] = b2;
    }

}





int inverse_zq(int x, int q)
    /*

    Input: x,q ; x is an input and q is a modulo
    Output: x^{q-2} mod q
    The inverse is x^{q-2},
    The caller should take care of the input that needs to be positive

    */

    {
        int res = 1; 
        int qm2 = q-2;
        while(qm2>0)
            {
                if(qm2 & 1)
                  {
                    res = uint32_mod_uint14(res*x,q);
                  }
                x = uint32_mod_uint14(x*x,q);
                qm2 = qm2>>1;
            }

        return res;
        
    }




Term inverse_zw(Term A, Term q){

    /*
    Input: term A = a+bw
    Output: the inverse of the term calculated as 1/(a^2+b^2-ab)*(a-b - bw)
    
    */
    int a = A.a;
    int b = A.b;

    int temp = a * a + b * b - a * b;

    temp =  uint32_mod_uint14(temp,q.a);
    int inv =  inverse_zq(temp,q.a);

    // printf("The inverse inside %d: ", inv);

    

    Term res_temp;

    res_temp.a = (a - b)*inv;
    res_temp.b = (-b)*inv;

   
    Term res;
    
    res = poly_div_rat(res_temp,q);

    // printf("\nInverse in zw:\n");

    // printf("\n(%d + %d w)\n",res.a,res.b);

    return res;



}

void egcd_etru(Term A,Term q,Term* r){
    Term one = {1,0};

    Term r2 = A;
    Term r1 = q;

    if(isSame(A,zero) && isSame(q,zero)){
        r[0] = zero;
        r[1] = zero;
        r[2] = zero;
        return;
    }

    Term u0 = zero;
    Term u1 = zero;
    Term u2 = one;

    while(isSame(r1,zero)==0){
        Term res[2];
        red_q_etru(r2,r1,res);

        Term q0 = res[0];
        Term r0 = res[1];

        r2 = r1;
        r1 = r0;
        u0 = minus(u2,multiply_terms(q0,u1));

        u2 = u1;
        u1 = u0;
    }

    Term u = u2;
    Term v;

    if(isSame(q,zero)){
        v = zero;
    }
    else{
        Term res[2];
        red_q_etru(minus(r2,multiply_terms(u,A)),q,res);
        v = res[0];
    }

    Term res[2];

    red_q_etru(r2,q,res);
    
    Term d = res[1];

    Term inv_d = unit(d);

    red_q_etru(multiply_terms(u,inv_d),q,res);

    u = res[1];

    r[0] = u;
    r[1] = v;
    r[2] = d;
}

Term find_inverse(Term A,Term mod){
    Term res;

    res = inverse_zw(A, mod);

    // egcd_etru(A,mod,res);

    // printf("find_inverse : (%d + %d w) (%d + %d w) + (%d + %d w)\n",res[0].a,res[0].b,res[1].a,res[1].b, res[2].a,res[2].b);
    // printf("find_inverse : (%d + %d w)\n",res[0].a,res[0].b);

    return res;
}

void multiply_by_constant(Term constant, Term* a,Term *res,int len,Term q){
    for(int i = 0;i<len;i++){
        res[i] = poly_div_rat(multiply_terms(a[i],constant),q);
    }
}


void reverse(int i,int j,Term* a){
    while(i<=j){
        Term temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i++;
        j--;
    }
}

void shiftRight_k(Term *arr, int k,int len){
    
    k = (k%len + len)%len;
    reverse(0,len-1,arr);
    reverse(0,k-1,arr);
    reverse(k,len-1,arr);

    // if(isSame(arr[len-1],zero)==0){
    //     arr[0] = arr[0] + arr[len-1];
    //     arr[len-1] = zero;
    // }
}

void swapArrays(Term* a,Term* b,int len){
    for(int i = 0;i<len;i++){
        Term temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}



int Almost_inverse_ZpwCn(Term *a, int mod,Term* a_inv,int n){
    Term q = {mod,0};

    int allZero = 1;

    for(int i = 0;i<n;i++){
        if(a[i].a!=0 || a[i].b!=0){
            allZero = 0;
            break;
        }
    }

    if(allZero){
        printf("Inverse do not exists\n");

        return 0;
    }

    int upper_bound = n + deg(a,n);

    // printf("%d\n",upper_bound);
    // printf("%d\n",deg(a,N3));



    int counter = 0;

    Term f[n+1];

    for(int i = 0;i<n;i++){
        f[i] = a[i];
    }

    f[n] = zero;

    // poly_Zw_print(f,N3+1);

    int k = 0;

    Term b[n+1];

    b[0].a = 1;
    b[0].b = 0;

    for(int i = 1;i<=n;i++){
        b[i] = zero;
    }

    // poly_Zw_print(b,N3+1);

    Term c[n+1];

    for(int i = 0;i<=n;i++){
        c[i] = zero;
    }

    // poly_Zw_print(c,N3+1);

    Term g[n+1];

    for(int i = 0;i<=n;i++){
        g[i] = zero;
    }

    g[0].a = -1; g[0].b = 0;
    g[n].a = 1 ; g[n].b = 0;



    // poly_Zw_print(g,N3+1);

    int flag = 1;

    

    while(flag){

        printf("Result of check: %d\n",isSame(poly_div_rat(f[0],q),zero));
        while(isSame(poly_div_rat(f[0],q),zero)){
           
            printf("Inside almost inverse loop\n");
            // poly_Zw_print(f,N3+1);
            division_by_x(f,n+1);
            
            counter++;
        
            if(counter==upper_bound){
                printf("Inverse does not exists.\n");

                return 0;
            }
            multiply_by_x(c,n+1);
            k++;
            
        }

        

        if(is_degree_one(f,n+1)){
            flag = 0;
            Term f0_inv = find_inverse(f[0],q);

            
            multiply_by_constant(f0_inv,b,b,n+1,q);
           
            for(int i = 0;i<n;i++){
                a_inv[i] = b[i];
            }

           

            shiftRight_k(a_inv,n-k,n);// change the a_inv size to N3 from N3+1

            return 1;
        }

        // printf("%d\n",deg(f,N3+1)<deg(g,N3+1));

        if(deg(f,n+1)<deg(g,n+1)){
            swapArrays(f,g,n+1);//swap can be optimized using pointers
            swapArrays(b,c,n+1);
        }

        Term g0_inv = find_inverse(g[0],q);
        Term u = poly_div_rat(multiply_terms(f[0],g0_inv),q);


        Term ug[n+1];

        multiply_by_constant(u,g,ug,n+1,q);
        minus_Zw(f,ug,q,f,n+1);

        Term uc[n+1];

        multiply_by_constant(u,c,uc,n+1,q);
        minus_Zw(b,uc,q,b,n+1);


    }
    
}


int Almost_inverse_ZpwCn_constant(Term *in, int mod,Term* a_inv,int n)
{
 /*
Input:  Term *in: a pointer to the term to be inverted
        mod: the modulo
        n: the length of the input
Output: the inverse of the input in ZpwCn
 */



//  poly_Zw_print(in, N);
 Term q = {mod,0};
 Term f[n+1], g[n+1], v[n+1], r[n+1];
 int i, loop, delta;
 int swap, t1, t2;
 Term f0, g0;
 Term scale;

 Term aux1,aux2, aux3;

 for (i=0;i<n+1;++i) {v[i].a =0;  v[i].b = 0;}
 for (i=0;i<n+1;++i) {r[i].a =0 ; r[i].b = 0;}
 r[0].a = 1;

 for (i=0; i<n;++i) {f[i].a =0; f[i].b = 0;}
 f[0].a = 1; f[n].a = -1; f[n].b=0;

 for (i=0;i<n;++i) g[n-1-i] = in[i];
 g[n].a = 0;
 g[n].b = 0;

 delta = 1;
 for(loop=0; loop<2*n-1;++loop)
 {
    for (i=n; i>0; --i) v[i] = v[i-1];
    v[0].a = 0;
    v[0].b = 0;

    swap = int16_negative_mask(-delta) & term_nonzero_mask(g[0]);
    delta ^= swap&(delta^-delta);
    delta +=1;


    for (i=0; i<n+1; ++i)
    {
        t1 = swap&(f[i].a^g[i].a); f[i].a ^=t1; g[i].a ^=t1;
        t2 = swap&(f[i].b^g[i].b); f[i].b ^=t2; g[i].b ^=t2;

        t1 = swap&(v[i].a^r[i].a); v[i].a ^=t1; r[i].a ^=t1;
        t2 = swap&(v[i].b^r[i].b); v[i].b ^=t2; r[i].b ^=t2;
    }

    f0 = f[0];
    g0 = g[0];


  
    for (i=0;i<n+1; ++i)
    {
        aux1 = multiply_terms(f0, g[i]);
        aux2 = multiply_terms(g0, f[i]);
        aux3 = minus(aux1, aux2);
        g[i] = poly_div_rat(aux3, q);
    }


    for (i=0;i<n+1; ++i)
    {
        
    aux1 = multiply_terms(f0, r[i]);
    aux2 = multiply_terms(g0, v[i]);
    aux3 = minus(aux1, aux2);
    r[i] = poly_div_rat(aux3, q);}


    for(i=0;i<n;++i) g[i] = g[i+1];
    g[n].a = 0;
    g[n].b = 0;

   

 }

  scale = find_inverse(f[0],q);

  for (i=0;i<n;++i) a_inv[i] = poly_div_rat(multiply_terms(scale, v[n-1-i]),q);
  return int16_nonzero_mask(delta);

}



int Almost_inverse_ZpwDN(Term *f,int mod,Term *res){

    


    // printf("Input f: \n");
    // print_element(f, N2);
    Term q = {mod,0};

    group_ring F;

    F.a = (Term*)malloc(N*sizeof(Term));
    F.b = (Term*)malloc(N*sizeof(Term));

    poly_to_DN(f,&F);

    Term u[N];
    Term v[N];

    for(int i = 0;i<N;i++){
        u[i] = F.a[i];
        v[i] = F.b[i];
    }

    // printf("Element u \n");
    // print_element(u,N);

    // printf("Element v \n");
    // print_element(v,N);

    Term u1[N]; //ubar
    Term v1[N]; //vbar
    Term uu1[N]; //
    Term vv1[N];

    Term final_inv[N];

    rotinv(u, u1);
    rotinv(v, v1);

    // printf("u1 is ");
    // print_element(u1, N);
    // printf("\n");

    // printf("v1 is ");
    // print_element(v1, N);
    // printf("\n");
    
    poly_Zw_mul_mod_q(u,u1,q,uu1);
    poly_Zw_mul_mod_q(v,v1,q,vv1);
    minus_single_Zwpoly(vv1,vv1,q,N); //vv1 = -vv1 change added for twisted dihedral group

    // printf("uu1: ");
    // print_element(uu1, N);
    // printf("\n");

    // printf("vv1");
    // print_element(vv1, N);
    // printf("\n");

    Term check[N];
    
    minus_Zw(vv1, uu1, q,check,N);
    
    // printf("check element: \n");
    // print_element(check, N);

    
    int found =0;
    found = Almost_inverse_ZpwCn_constant(check,q.a,final_inv,N);

    // printf("found value: %d", found);

    if(found!=0){
        printf("Inverse does not exists in CnC3\n");
        return 0;
    }

    Term a[N];
    Term b[N];
    Term minusu1[N];
    minus_single_Zwpoly(u1,minusu1,q,N);

    poly_Zw_mul_mod_q(minusu1,final_inv,q,a);
    poly_Zw_mul_mod_q(v,final_inv,q,b);


    for(int i = 0;i<N;i++){
        res[i] = a[i];
    }

    for(int i = N;i<2*N;i++){
        res[i] = b[i-N];
    }
    
    return 1;

}