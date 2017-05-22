#include <stdio.h>
#include <gmp.h>

#include "keyGen.h"
#include "DGHV.h"

int main(void){
    
    Param param;
    SK sk;
    PK pk;

    mpz_t chiper;
    mpz_init(chiper);


    param_init(&param, 52, 41, 1558, 843033, 572); 
    keyGen(&sk, &pk, &param);

    encrypt(chiper, &param, &pk, 1);
    decrypt(&sk, chiper);




    return 0;
}
