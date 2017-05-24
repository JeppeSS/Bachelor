#include <stdio.h>
#include <gmp.h>

#include "keyGen.h"
#include "DGHV.h"
#include "random.h"

int main(void){
    
    Param param;
    SK sk;
    PK pk;

    mpz_t chiper1;
    mpz_t chiper2;
    mpz_t chiper3;
    mpz_t chiper4;
    mpz_t chiper5;
    mpz_t chiper6;

    mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);

    param_init(&param, 8); 
    keyGen(&sk, &pk, &param);

    encrypt(chiper1, &param, &pk, 1);
    encrypt(chiper2, &param, &pk, 0);
    encrypt(chiper3, &param, &pk, 1);
    encrypt(chiper4, &param, &pk, 1);
    encrypt(chiper5, &param, &pk, 0);
    encrypt(chiper6, &param, &pk, 1);

    decrypt(&sk, chiper1);
    decrypt(&sk, chiper2);
    decrypt(&sk, chiper3);
    decrypt(&sk, chiper4);
    decrypt(&sk, chiper5);
    decrypt(&sk, chiper6);



    keyClean(&sk, &pk, &param);


    return 0;
}
