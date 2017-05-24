#include <stdio.h>
#include <gmp.h>

#include "DGHV.h"
#include "keyGen.h"
#include "random.h"


void encrypt(mpz_t chiper, Param *param, PK *pk, int c){

    mpz_t sum;
    mpz_t subset;
    mpz_t tau;
    mpz_t rand;
    mpz_t r;
    mpz_inits(r, sum, subset, tau, rand, NULL);

    mpz_set_ui(tau, param->tau);

    randomRange(rand, param->rhoM);
    randomUniform(subset, tau);

    for(int i = 1; mpz_cmp_ui(subset, i); i++){
        mpz_add(sum, sum, pk->PK[i]);
    }

    
    mpz_mul_si(rand, rand, 2);
    
    mpz_add_ui(sum, sum, c);
    mpz_add(rand, rand, sum);

    mpz_mod(chiper, rand, pk->PK[0]);

}

void decrypt(SK *sk, mpz_t chiper){
    
    mpz_t plain;

    mpz_init(plain);


    mpz_mod(plain, chiper, sk->SK);
    mpz_mod_ui(plain, plain, 2);

    gmp_printf("%Zd\n", plain);

}
