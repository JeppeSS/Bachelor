#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tools.h"
#include "keyGen.h"


int test_param_init(unsigned int lambda){

    Param p;
    param_init(&p, lambda);

    if(p.lambda != lambda){
        return 1;
    }
    if(p.eta != pow(lambda, 2)){
        return 1;
    }
    if(p.gamma != pow(lambda, 5)){
        return 1;
    }
    if(p.rho != lambda){
        return 1;
    }
    if(p.rhoM != (2 * lambda)){
        return 1;
    }
    if(p.tau != (p.gamma + lambda + 1)){
        return 1;
    }
    return 0;
}

int test_sk_init(Param p){
    mpz_t tmp_val;
    SK sk;
    mpz_inits(sk.sk, tmp_val, NULL);
    if(sk_init(&p, &sk) != EXIT_SUCCESS){
        printf("Function sk_init fail\n");
    }

    mpz_ui_pow_ui(tmp_val, 2, p.eta -1);
    if(mpz_cmp(tmp_val, sk.sk) == 1){
        printf("Secret key too small\n");
        return 1;
    }

    mpz_ui_pow_ui(tmp_val, 2, p.eta);
    if(mpz_cmp(tmp_val, sk.sk) == -1){
        printf("Secret key too large\n");
        return 1;
    }

    mpz_mod_ui(tmp_val, sk.sk, 2);
    if(mpz_cmp_ui(tmp_val, 0) == 0){
        printf("Secret key even number");
        return 1;
    }

    mpz_clears(tmp_val, sk.sk, NULL);
    return 0;
}

int test_pk_init(Param *p, SK *sk){
    mpz_t comp_val;
    mpz_inits(comp_val, NULL);
    PK pk;
    if(pk_init(&pk, p, sk) != EXIT_SUCCESS){
        printf("Function pk_init_fail\n");
        return 1;
    }

    mpz_set(comp_val, pk.PK[0]);
    for(int i=0; i < p->tau; i++){
        if(mpz_cmp(comp_val, pk.PK[i]) == -1){
            mpz_set(comp_val, pk.PK[i]);
        }
    }
    if(mpz_cmp(comp_val, pk.PK[0]) != 0){
        printf("PK list [0] was not the greatest value!\n");
        return 1;
    }

    mpz_mod_ui(comp_val, pk.PK[0], 2);
    if(mpz_cmp_ui(comp_val, 0) == 0){
        printf("PK[0] is not an odd value!\n");
        return 1;
    }

    mpz_mod(comp_val, pk.PK[0], sk->sk);
    mpz_mod_ui(comp_val, comp_val, 2);
    if(mpz_cmp_ui(comp_val, 0) != 0){
        printf("Remainder of pk[0]/sk was not even!\n");
        return 1;
    }
    mpz_clear(comp_val);
    return 0;
}