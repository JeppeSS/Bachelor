#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include <time.h>
#include "tools.h"



/* 
 * === Function ===============================================================
 *         Name: param_init
 *
 *  Description: Initialize all the parameters
 * ============================================================================
 */
void param_init(Param *param, ull_int lambda){

    param->lambda = lambda;
    param->rho    = lambda;
    param->rhoM   = 2 * lambda;
    param->eta    = (ull_int) pow(lambda, 2);
    param->gamma  = (ull_int) pow(lambda, 5);
    param->tau    = param->gamma + lambda + 1;
}

/*
 * === Function ===============================================================
 *         Name: sk_init
 *
 *  Description: Initialize the secret key
 * ============================================================================
*/

int sk_init(Param *p, SK *sk){
    mpz_t r, upper, lower, tmp_val;
    mpz_inits(sk->sk, r, upper, lower, tmp_val, NULL);
    mpz_ui_pow_ui(upper, 2, p->eta);
    mpz_ui_pow_ui(lower, 2, p->eta - 1);
    rand_num(&r, &lower, &upper);
    mpz_mod_ui(tmp_val, r, 2);
    while(mpz_cmp_ui(tmp_val, 0) == 0){
        rand_num(&r, &lower, &upper);
        mpz_mod_ui(tmp_val, r, 2);
    }

    mpz_set(sk->sk, r);
    mpz_clears(r, upper, lower, tmp_val, NULL);
    return EXIT_SUCCESS;
}

int gen_single_pk(mpz_t *ret, SK *sk, mpz_t *lower_q, mpz_t *lower_r, mpz_t *upper_q, mpz_t *upper_r){
    mpz_t q, r, tmp_pk;
    mpz_inits(q, r, tmp_pk, NULL);
    rand_num(&q, lower_q, upper_q);
    mpz_div(q, q, sk->sk);

    rand_num(&r, lower_r, upper_r);
    mpz_mul_ui(r, r, 2);

    mpz_mul(tmp_pk, sk->sk, q);
    mpz_add(tmp_pk, tmp_pk, r);

    mpz_set(ret, tmp_pk);
    mpz_clears(q, r, tmp_pk, NULL);
    return EXIT_SUCCESS;
}


/*
 * === Function ===============================================================
 *         Name: pk_init
 *
 *  Description: Initialize the public key vector, according to tau.
 * ============================================================================
*/
int pk_init(PK *pk, Param *param, SK *sk){
    // Initiate var's
    mpz_t lower_q, lower_r, upper_q, upper_r, compare1, compare2;
    mpz_inits(lower_q, lower_r, upper_q, upper_r, compare1, compare2, NULL);

    // Set upper / lower bounds for random number q
    mpz_set_ui(lower_q, 0);
    mpz_ui_pow_ui(upper_q, 2, param->gamma);

    // Set upper /lower bounds for random number r
    mpz_ui_pow_ui(upper_r, 2, param->rho);
    mpz_neg(lower_r, upper_r);

    // Generate unsorted list
    pk->PK = malloc(sizeof(mpz_t) * param->tau);
    for(int i=0; i < param->tau; i++){
        mpz_init(pk->PK[i]);
        gen_single_pk(&pk->PK[i], sk, &lower_q, &lower_r, &upper_q, &upper_r);
    }

    // Sort list
    sort_pk_list(pk, param->tau);

    // while pk[0] does not forfill requirements, replace with new random number...
    mpz_mod_ui(compare1, pk->PK[0], 2);

    mpz_mod(compare2, pk->PK[0], sk->sk);
    mpz_mod_ui(compare2, compare2, 2);
    while((mpz_cmp_ui(compare1, 0) == 0) || (mpz_cmp_ui(compare2, 0) == 0)){
        gen_single_pk(&pk->PK[0], sk, &lower_q, &lower_r, &upper_q, &upper_r);

        sort_pk_list(pk, param->tau);
        mpz_mod_ui(compare1, pk->PK[0], 2);
        mpz_mod(compare2, pk->PK[0], sk->sk);
        mpz_mod_ui(compare2, compare2, 2);
    }
    mpz_clears(lower_q, lower_r, upper_q, upper_r, compare1, compare2, NULL);
    return EXIT_SUCCESS;
}

/*
 * === Function ===============================================================
 *         Name: skClean
 *
 *  Description: Free sk memory
 * ============================================================================
*/
void skClean(SK *sk){

    // Set SK = 0, to prevent attacker reading memory after clear.
    mpz_set_ui(sk->sk, 0);
    mpz_clear(sk->sk);
}

/*
 * === Function ===============================================================
 *         Name: pkClean
 *
 *  Description: Free pk memory
 * ============================================================================
*/
void pkClean(PK *pk, Param *param){

    // Set all PK values = 0, and free.
    for(int i = 0; i < param->tau; i++){
        mpz_set_ui(pk->PK[i], 0);
        mpz_clear(pk->PK[i]);
    }
    free(pk->PK);
}

/*
 * === Function ===============================================================
 *         Name: keyClean
 *
 *  Description: Free sk and pk memory
 * ============================================================================
*/
void keyClean(SK *sk, PK *pk, Param *param){
    skClean(sk);
    pkClean(pk, param);
}

