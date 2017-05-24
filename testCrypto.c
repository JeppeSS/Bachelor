#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>

#include "keyGen.h"
#include "DGHV.h"
#include "random.h"

int main(void){
    printf("STARTING -> encryption/decryption test SUIT\n");

    unsigned int num_trials = 50;
    unsigned int sum_errors = 0;

    Param param;
    SK sk;
    PK pk;


    mpz_t chiper;
    param_init(&param, 5);

    mpz_init(chiper);
    keyGen(&sk, &pk, &param);
    printf("keygen done\n");

    srand(time(NULL));
    for(int i=0; i < num_trials; i++){
        int r = rand() % 2;
        printf("Test %d -> parameter: %d\n", i, r);
        encrypt(chiper, &param, &pk, r);
        decrypt(&sk, chiper);
        if(mpz_get_ui(chiper) != r){
            sum_errors ++;
            printf("--------------ERROR--------------\n");
        }
    }


    keyClean(&sk, &pk, &param);


    return 0;
}
