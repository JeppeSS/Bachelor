#include <stdio.h>
#include <gmp.h>
#include "tools.h"


char partial_enc(PK *pk, Param *param, char m, mpz_t *cipher){
    mpz_t upper_s, upper_r, lower_s, lower_r, r, sum, tmp_val;
    mpz_inits(upper_s, upper_r, lower_s, lower_r, r, sum, tmp_val, NULL);
    mpz_set_ui(lower_s, 1);
    mpz_set_ui(upper_s, param->tau -1);
    mpz_set_ui(sum, 0);

    ull_int subset[param->tau];
    for(int i=0; i < param->tau; i++){
        rand_num(&tmp_val, &lower_s, &upper_s);
        mpz_add(sum, sum, pk->PK[mpz_get_ui(tmp_val)]);
    }

    mpz_ui_pow_ui(upper_r, 2, param->rhoM);
    mpz_neg(lower_r, upper_r);
    rand_num(&r, &lower_r, &upper_r);
    mpz_mul_ui(r, r, 2);
    unsigned short bit = m - '0';

    mpz_add_ui(r, r, bit);
    mpz_add(sum, sum, r);
    mpz_mod(sum, sum, pk->PK[0]);
    //gmp_printf("sum-----------%Zd\n", sum);
    mpz_set(cipher, sum);
    mpz_clears(upper_s, upper_r, lower_s, lower_r, r, sum, tmp_val, NULL);
    return 'c';
}

char partial_dec(SK *sk, mpz_t cipher){
    mpz_t tmp;
    mpz_init(tmp);
    mpz_mod(tmp, cipher, sk->sk);
    mpz_mod_ui(tmp, tmp, 2);
    char c = mpz_get_ui(tmp) + '0';
    return c;
}