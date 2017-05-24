#include <stdio.h>
#include <gmp.h>

#include "DGHV.h"
#include "keyGen.h"
#include "random.h"


void encrypt(mpz_t chiper, Param *param, PK *pk, int c){

    mpz_t sum;
    mpz_t tau;
    mpz_t rand;
    mpz_t r;
    mpz_inits(r, sum, tau, rand, NULL);

    mpz_set_ui(tau, param->tau);

    unsigned int subStart = 0;
    unsigned int subEnd   = 0;

    while((subEnd < subStart) || (subStart == 0 || subEnd == 0)){
        subStart = genSeed() % param->tau;
        subEnd = genSeed() % param->tau;
    }

    randomRange(rand, param->rhoM);

    for(int i = subStart; i < subEnd; i++){
        mpz_add(sum, sum, pk->PK[i]);
    }

    
    mpz_mul_si(rand, rand, 2);
    
    mpz_add_ui(sum, sum, c);
    mpz_add(rand, rand, sum);

    mpz_mod(chiper, rand, pk->PK[0]);


    mpz_set_ui(sum, 0);
    mpz_set_ui(tau, 0);
    mpz_set_ui(rand, 0);
    mpz_set_ui(r, 0);

    mpz_clear(sum);
    mpz_clear(tau);
    mpz_clear(rand);
    mpz_clear(r);

}

void decrypt(SK *sk, mpz_t chiper){
    
    mpz_t plain;

    mpz_init(plain);


    mpz_mod(plain, chiper, sk->SK);
    mpz_mod_ui(plain, plain, 2);

    gmp_printf("%Zd\n", plain);

}


void evaluate(mpz_t chiper, mpz_t chiper1, mpz_t chiper2){
    mpz_add(chiper, chiper1, chiper2);
}
