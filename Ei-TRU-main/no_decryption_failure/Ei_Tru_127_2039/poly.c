#include "poly.h"
#include <stdio.h>
#include <stdbool.h>

Term Zw_add(Term a, Term b)
    /*
    adding two terms in Zw
    */
    {
        Term c;

        c.a= a.a+b.a;
        c.b = a.b+b.b;
        return c;

    }


void poly_Zw_add(const Term* a, const Term *b, Term* r){

   

    for(int i = 0;i<N;i++){
        r[i].a = a[i].a + b[i].a;
        r[i].b = a[i].b + b[i].b;
    }

    
}
void ZwCnC3_add(const Term* a, const Term *b, Term* r){

   

    for(int i = 0;i<N3;i++){
        r[i].a = a[i].a + b[i].a;
        r[i].b = a[i].b + b[i].b;
    }


    
}



void poly_Zw_add3(const Term* a, const Term *b,const Term* c, Term* r){

    Term q = {Q,0};

    for(int i = 0;i<N;i++){
        r[i].a = a[i].a + b[i].a + c[i].a;
        r[i].b = a[i].b + b[i].b + c[i].b;
    }

    poly_Zw_mod_q(r,q,r);

    

    
}


Term q = {Q,0};

int poly_Zw_cmp(const Term* a, const Term *b,int len){
    for(int i = 0;i<len;i++){
        if(a[i].a!=b[i].a || a[i].b!=b[i].b){
            return 0;
        }
    }

    return 1;
}


Term poly_div_rat(Term A, Term q){ // q is of form (c + 0 w) where c is prime
    
    Term rem;
    Term REM;
    
   
    // int x = (A.a%(q.a) + q.a)%(q.a);
    // int y = (A.b%(q.a) + q.a)%(q.a);


    int x = int_mod_uint14(A.a,q.a);
    int y = int_mod_uint14(A.b,q.a);

    if(q.a==2){
        if(x==1 && y==1){
            rem.a = -1;
            rem.b = -1;
        }
        else{
            rem.a = x;
            rem.b = y;
        }

        return rem;
    }

    int X = 2 * x;
    int Y = 2 * y;


    bool t1 = (x+y)>(q.a) && X>y && Y>=x;
    bool t2 = (X-y)>q.a && Y<x;
    bool t3 = (Y-x)>=q.a && X<=y;

    rem.a = x - (int)((t1 || t2) && !(t3))*q.a;
    rem.b = y - (int)((t1 || t3) && !(t2))*q.a;

    

    // printf("rem: (%d + %dw)\n",rem.a,rem.b);
    return rem;

}

void poly_Zw_mod_q(const Term* a, Term q, Term* r){
    
    for(int i = 0;i<N;i++){
        r[i] = poly_div_rat(a[i],q);
    }
}
void ZwCnC3_mod_q(const Term* a, Term q, Term* r){
    
    for(int i = 0;i<N3;i++){
        r[i] = poly_div_rat(a[i],q);
    }
}

void poly_Zw_mul_p(Term *r, Term P,int len){
    int p = P.a;

    for(int i = 0;i<len;i++){
        r[i].a = p*r[i].a;
        r[i].b = p*r[i].b;
    }
}

int isSame(Term A,Term B){
    if(A.a==B.a && A.b==B.b){
        return 1;
    }

    return 0;
}

Term Zw_multiply(Term t1, Term t2){ // assuming the two terms are (a+bw) and (c+dw)
    Term result;

    int ac = t1.a * t2.a;
    int bd = t1.b * t2.b;

    int ab_dc = (t1.a - t1.b) * (t2.b - t2.a);

    result.a = ac - bd;
    result.b = ac + ab_dc;

    return result;

}


Term multiply_terms(Term t1, Term t2){ // assuming the two terms are (a+bw) and (c+dw)
    Term result;

    int ac = t1.a * t2.a;
    int bd = t1.b * t2.b;

    int ab_dc = (t1.a - t1.b) * (t2.b - t2.a);

    result.a = ac - bd;
    result.b = ac + ab_dc;

    return result;

}

void poly_Zw_mul(const Term *f, const Term *g, Term *r){
    
    int k,i;
    Term temp;

    for(k=0; k<N; k++)
    {
        r[k].a = 0;
        r[k].b = 0;
        for(i=1; i<N-k; i++){
            // temp = multiply_terms(f[k+i],g[N-i]);
            int ac = f[k+i].a * g[N-i].a;
            int bd = f[k+i].b * g[N-i].b;

            int ab_dc = (f[k+i].a - f[k+i].b) * (g[N-i].b - g[N-i].a);

            temp.a = ac - bd;
            temp.b = ac + ab_dc;
            // r->coeffs[k] += a->coeffs[k+i] * b->coeffs[NTRU_N-i];
            r[k].a += temp.a;
            r[k].b += temp.b;
        }
        for(i=0; i<k+1; i++){
            // r->coeffs[k] += a->coeffs[k-i] * b->coeffs[i];
            // temp = multiply_terms(f[k-i],g[i]);
            int ac = f[k-i].a * g[i].a;
            int bd = f[k-i].b * g[i].b;

            int ab_dc = (f[k-i].a - f[k-i].b) * (g[i].b - g[i].a);

            temp.a = ac - bd;
            temp.b = ac + ab_dc;
            r[k].a += temp.a;
            r[k].b += temp.b;
        }

    }
}

void poly_Zw_mul_mod_q(const Term *f, const Term *g,Term q, Term *r){
    
    int k,i;
    Term temp;

    for(k=0; k<N; k++)
    {
        r[k].a = 0;
        r[k].b = 0;
        for(i=1; i<N-k; i++){
            // temp = multiply_terms(f[k+i],g[N-i]);
            int ac = f[k+i].a * g[N-i].a;
            int bd = f[k+i].b * g[N-i].b;

            int ab_dc = (f[k+i].a - f[k+i].b) * (g[N-i].b - g[N-i].a);

            temp.a = ac - bd;
            temp.b = ac + ab_dc;
            // r->coeffs[k] += a->coeffs[k+i] * b->coeffs[NTRU_N-i];
            r[k].a += temp.a;
            r[k].b += temp.b;
        }
        for(i=0; i<k+1; i++){
            // r->coeffs[k] += a->coeffs[k-i] * b->coeffs[i];
            // temp = multiply_terms(f[k-i],g[i]);
            int ac = f[k-i].a * g[i].a;
            int bd = f[k-i].b * g[i].b;

            int ab_dc = (f[k-i].a - f[k-i].b) * (g[i].b - g[i].a);

            temp.a = ac - bd;
            temp.b = ac + ab_dc;
            r[k].a += temp.a;
            r[k].b += temp.b;
        }

    }
    poly_Zw_mod_q(r,q,r);
}

void poly_Zw_print(Term *p,int len){
    for(int i = 0;i<len;i++){
        printf("(%d + %dw)x^%d",p[i].a,p[i].b,i);
        if(i<len-1){
            printf("+ ");
        }
    }

    printf("\n");
}


void poly_Zw_shift_t(const Term *f ,int t, Term* r){

    for(int i = 0;i<N;i++){
        r[(i*t)%N] = f[i];
    }

}


Term Zw_sub(Term a, Term b)
{
    Term c;
    c.a = a.a - b.a;
    c.b = a.b - b.b;

    return c;
}



void poly_Zw_sub(const Term* a, const Term *b, Term* r){

    

    for(int i = 0;i<N;i++){
        r[i].a = a[i].a - b[i].a;
        r[i].b = a[i].b - b[i].b;
    }

    
}

void Zw_CnC3_multiply(Term *f, Term *g, Term *r){
    int t = T;
    int t2 = t*t;
    Term q = {Q,0};

    Term f0[N];
    Term f1[N];
    Term f2[N];

    for(int i = 0;i<N;i++){
        f0[i] = f[i];
    }
    for(int i = N;i<2*N;i++){
        f1[i-N] = f[i];
    }
    for(int i = 2*N ;i < 3*N;i++){
        f2[i-2*N] = f[i]; 
    }

    Term g0[N];
    Term g1[N];
    Term g2[N];

    for(int i = 0;i<N;i++){
        g0[i] = g[i];
    }
    for(int i = N;i<2*N;i++){
        g1[i-N] = g[i];
    }
    for(int i = 2*N ;i < 3*N;i++){
        g2[i-2*N] = g[i]; 
    }

    Term f0t[N];
    Term f0t2[N];
    Term f1t[N];
    Term f1t2[N];
    Term f2t[N];
    Term f2t2[N];

    poly_Zw_shift_t(f0,t,f0t);
    poly_Zw_shift_t(f0,t2,f0t2);
    poly_Zw_shift_t(f1,t,f1t);
    poly_Zw_shift_t(f1,t2,f1t2);
    poly_Zw_shift_t(f2,t,f2t);
    poly_Zw_shift_t(f2,t2,f2t2);

    Term f0g0[N];
    Term f2tg1[N];
    Term f1t2g2[N];

    poly_Zw_mul(f0,g0,f0g0);
    poly_Zw_mul(f2t,g1,f2tg1);
    poly_Zw_mul(f1t2,g2,f1t2g2);

    Term f1g0[N];
    Term f0tg1[N];
    Term f2t2g2[N];

    poly_Zw_mul(f1,g0,f1g0);
    poly_Zw_mul(f0t,g1,f0tg1);
    poly_Zw_mul(f2t2,g2,f2t2g2);

    Term f2g0[N];
    Term f1tg1[N];
    Term f0t2g2[N];

    poly_Zw_mul(f2,g0,f2g0);
    poly_Zw_mul(f1t,g1,f1tg1);
    poly_Zw_mul(f0t2,g2,f0t2g2);

    Term X[N];
    Term Y[N];
    Term Y2[N];

    poly_Zw_add3(f0g0,f2tg1,f1t2g2,X);
    poly_Zw_add3(f1g0,f0tg1,f2t2g2,Y);
    poly_Zw_add3(f2g0,f1tg1,f0t2g2,Y2);

    for(int i = 0;i<N;i++){
        r[i] = X[i];
        r[i+N] = Y[i];
        r[i+2*N] = Y2[i];
    }

    


}

