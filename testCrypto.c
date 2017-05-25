#include <stdio.h>
#include <gmp.h>

#include "keyGen.h"
#include "DGHV.h"
#include "random.h"
#include "Filemanager.h"

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

    param_init(&param,10); 
    keyGen(&sk, &pk, &param);

    encryptBit(chiper1, &param, &pk, 1);
    encryptBit(chiper2, &param, &pk, 0);
    encryptBit(chiper3, &param, &pk, 1);
    encryptBit(chiper4, &param, &pk, 1);
    encryptBit(chiper5, &param, &pk, 0);
    encryptBit(chiper6, &param, &pk, 1);

    decryptBit(&sk, chiper1);
    decryptBit(&sk, chiper2);
    decryptBit(&sk, chiper3);
    decryptBit(&sk, chiper4);
    decryptBit(&sk, chiper5);
    decryptBit(&sk, chiper6);



    keyClean(&sk, &pk, &param);


    return 0;
}
