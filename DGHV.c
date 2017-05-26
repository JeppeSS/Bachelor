#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "DGHV.h"
#include "keyGen.h"
#include "random.h"
#include "Plaintext.h"
#include "Chipertext.h"

void encrypt(Chipertext *chiper, Param *param, PK *pk, Plaintext *plain){

    chipertext_init(chiper, plain->size);

    for(unsigned int i = 0; i < plain->size; i++){
        encryptBit(chiper->chiper[i], param, pk, plain->bin[i]);
    }
}


void decrypt(Plaintext *plain, SK *sk, Chipertext *chiper){

    plain->msg = malloc(chiper->size);
    plain->bin = malloc(chiper->size * (8 * sizeof(int)));
    plain->size = chiper->size;

    for(unsigned int i = 0; i < plain->size; i++){
        plain->bin[i] = decryptBit(sk, chiper->chiper[i]);
    }

}

void encryptBit(mpz_t chiper, Param *param, PK *pk, int c){

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

    for(unsigned int i = subStart; i < subEnd; i++){
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

int decryptBit(SK *sk, mpz_t chiper){
    
    mpz_t plain;

    mpz_init(plain);


    mpz_mod(plain, chiper, sk->SK);
    mpz_mod_ui(plain, plain, 2);

    int x = mpz_get_ui(plain);

    return x;
}


void evaluate(mpz_t chiper, mpz_t chiper1, mpz_t chiper2){
    mpz_add(chiper, chiper1, chiper2);
}
