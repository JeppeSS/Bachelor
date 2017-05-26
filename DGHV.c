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

    fromBinary(plain);

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


void evaluateBit(mpz_t chiper, mpz_t chiper1, mpz_t chiper2){
    mpz_add(chiper, chiper1, chiper2);
}


void evaluate(Chipertext *res, Chipertext *chiper1, Chipertext *chiper2){

    if(chiper1->size != chiper2->size){
        fprintf(stderr, "[ERROR] Not same size\n");
    }

    chipertext_init(res, chiper1->size);

    for(unsigned int i = 0; i < chiper1->size; i++){
        evaluateBit(res->chiper[i], chiper1->chiper[i], chiper2->chiper[i]);
    }


}


int evaluateID(Chipertext *chiper1, Chipertext *chiper2, SK *sk){


    if(chiper1->size != chiper2->size){
        return EXIT_FAILURE;
    }

    mpz_t bit; 
    mpz_init(bit);

    int bits;

    for(unsigned int i = 0; i < chiper1->size; i++){
        evaluateBit(bit, chiper1->chiper[i], chiper2->chiper[i]);
        bits = decryptBit(sk, bit);

        if(bits == 1){
            mpz_clear(bit);
            return EXIT_FAILURE;
        }
    }
    
    mpz_clear(bit);

    return EXIT_SUCCESS;

}
