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


    mpz_t out1;
    mpz_t out2;
    mpz_t out3;
    

    mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, out1, out2, out3, NULL);

    param_init(&param,8); 
    keyGen(&sk, &pk, &param);

    encryptBit(chiper1, &param, &pk, 1);
    encryptBit(chiper2, &param, &pk, 0);
    encryptBit(chiper3, &param, &pk, 1);

    encryptBit(chiper4, &param, &pk, 1);
    encryptBit(chiper5, &param, &pk, 1);
    encryptBit(chiper6, &param, &pk, 1);


    evaluateBit(out1, chiper1, chiper4);
    evaluateBit(out2, chiper2, chiper5);
    evaluateBit(out3, chiper3, chiper6);


    int bit1 = decryptBit(&sk, out1);
    int bit2 = decryptBit(&sk, out2);
    int bit3 = decryptBit(&sk, out3);

    printf("Eval1: %d\n", bit1);
    printf("Eval2: %d\n", bit2);
    printf("Eval3: %d\n", bit3);



    keyClean(&sk, &pk, &param);


    return 0;
}
