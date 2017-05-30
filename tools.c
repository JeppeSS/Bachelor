#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include "tools.h"
#include "keyGen.h"

int rand_num(mpz_t *buf, mpz_t *lower, mpz_t *upper){
    mpz_t max_possible, min_possible, tmp_val1, tmp_val2;
    mpz_inits(max_possible, min_possible, tmp_val1, tmp_val2, NULL);

    // calculate max & range for the number that sizeof(upper) can possibly result in
    mpz_set_ui(tmp_val1, 2);
    mpz_pow_ui(max_possible, tmp_val1, sizeof(upper) * 8);
    mpz_div_ui(max_possible, max_possible, 2);
    mpz_neg(min_possible, max_possible);
    mpz_sub_ui(max_possible, max_possible, 1);

    ll_int tmp_buf = NULL;
    unsigned int flags = 0;
    int r = syscall(SYS_getrandom, &tmp_buf, sizeof(upper), flags);

    // Adapt(scale) the resulting integer to the range we have dictated in lower - upper
    mpz_sub(tmp_val1, upper, lower);
    mpz_set_si(tmp_val2, tmp_buf);
    mpz_sub(tmp_val2, tmp_val2, min_possible);
    mpz_mul(tmp_val1, tmp_val1, tmp_val2);
    mpz_sub(tmp_val2, max_possible, min_possible);
    mpz_div(tmp_val1, tmp_val1, tmp_val2);
    mpz_add(tmp_val1,tmp_val1, lower);
    // ll_int res = llroundl(((upper - lower) * (tmp_buf - min_possible) / (max_possible - min_possible)) + lower);
    mpz_set(*buf, tmp_val1);

    mpz_clears(max_possible, min_possible, tmp_val1, tmp_val2, NULL);
    return r;
}


void sort_pk_list(PK *pk, unsigned int list_len){
    mpz_t placeholder;
    mpz_init(placeholder);
    mpz_set(placeholder, pk->PK[0]);
    for(int i=0; i < list_len; i++){
        if(mpz_cmp(pk->PK[i], pk->PK[0]) == 1){
            mpz_set(placeholder, pk->PK[0]);
            mpz_set(pk->PK[0], pk->PK[i]);
            mpz_set(pk->PK[i], placeholder);
        }
    }
    mpz_clear(placeholder);
}

