#include "poly_r.h"

#include <stdio.h>

void poly_to_CnC3(Term* p,group_ring* result){

    result->a = (Term*)malloc(N*sizeof(Term));
    result->b = (Term*)malloc(N*sizeof(Term));
    result->c = (Term*)malloc(N*sizeof(Term));

    
    for(int i = 0;i<N;i++){
        result->a[i] = p[i];
    }
    for(int i = N;i<2*N;i++){
        result->b[i-N] = p[i];
    }
    for(int i = 2*N;i<3*N;i++){
        result->c[i-2*N] = p[i];
    }

}

void CnC3_to_poly(group_ring* R, Term* a){
    for(int i = 0;i<N;i++){
        a[i] = R->a[i];
        a[i+N] = R->b[i];
        a[i+2*N] = R->c[i]; 
    }
}



void poly_ZwCnC3_add(group_ring* A, group_ring* B,group_ring* E){
    poly_Zw_add(A->a,B->a,E->a);
    poly_Zw_add(A->b,B->b,E->b);
    poly_Zw_add(A->c,B->c,E->c);
}
void poly_ZwCnC3_sub(group_ring* A, group_ring* B,group_ring* E){
    poly_Zw_sub(A->a,B->a,E->a);
    poly_Zw_sub(A->b,B->b,E->b);
    poly_Zw_sub(A->c,B->c,E->c);
}


void poly_ZwCnC3_mod(group_ring* A, Term q, group_ring* r){
    poly_Zw_mod_q(A->a,q,r->a);
    poly_Zw_mod_q(A->b,q,r->b);
    poly_Zw_mod_q(A->c,q,r->c);
}




void poly_ZwCnC3_print(group_ring* r){
    printf("\n(");
    poly_Zw_print(r->a, N);
    printf(")\n + ");
    printf("\n(");
    poly_Zw_print(r->b, N);
    printf(")y\n + ");
    printf("\n(");
    poly_Zw_print(r->c, N);
    printf(")y^2\n");
}


void ZwCnC3_sub(const Term* a, const Term *b, Term* r){

    

    for(int i = 0;i<N3;i++){
        r[i].a = a[i].a - b[i].a;
        r[i].b = a[i].b - b[i].b;
    }

    
}

void poly_ZwCnC3_mul(group_ring* z, group_ring* a,int t,group_ring* result){

    // Term *u = z->a;
    // Term *v = z->b;
    // Term *w = z->c;

    // Term* A = a->a;
    // Term* B = a->b;
    // Term* G = a->c;

    Term u[N];
    Term v[N];
    Term w[N];

    Term A[N];
    Term B[N];
    Term G[N];

    for(int i = 0;i<N;i++){
        u[i] = z->a[i];
        v[i] = z->b[i];
        w[i] = z->c[i];

        A[i] = a->a[i];
        B[i] = a->b[i];
        G[i] = a->c[i];
    }


    int t2 = t*t;

    //1
    Term uA[N];

    poly_Zw_mul(u,A,uA);

    Term wt[N];
    
    poly_Zw_shift_t(w,t,wt);

    Term wtB[N];

    poly_Zw_mul(wt,B,wtB);

    Term vt2[N];
    
    poly_Zw_shift_t(v,t2,vt2);

    Term vt2G[N];

    poly_Zw_mul(vt2,G,vt2G);

    
    poly_Zw_add3(uA,wtB,vt2G,result->a);

    

    //y

    Term vA[N];

    poly_Zw_mul(v,A,vA);

    Term ut[N];

    poly_Zw_shift_t(u,t,ut);

    Term utB[N];

    poly_Zw_mul(ut,B,utB);

    Term wt2[N];

    poly_Zw_shift_t(w,t2,wt2);

    Term wt2G[N];

    poly_Zw_mul(wt2,G,wt2G);

    poly_Zw_add3(vA, utB, wt2G, result->b);

    //y2

    Term wA[N];

    poly_Zw_mul(w,A,wA);

    Term vt[N];

    poly_Zw_shift_t(v,t,vt);

    Term vtB[N];

    poly_Zw_mul(vt,B,vtB);

    Term ut2[N];

    poly_Zw_shift_t(u,t2,ut2);

    Term ut2G[N];

    poly_Zw_mul(ut2,G,ut2G);

    poly_Zw_add3(wA, vtB, ut2G, result->c);
}
