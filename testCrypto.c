#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>

#include "tools.h"
#include "keyGen.h"
#include "test_keyGen.h"
#include "partial_enc.h"

int main(void){
    printf("STARTING -> encryption/decryption test SUIT\n");
    srand(time(NULL));

    unsigned int num_trials = 1000;
    unsigned int sum_errors = 0;
    unsigned int lambda = 11;

    Param param;

    SK sk;
    PK pk;
    //mpz_init(sk.sk);

    /*
    if(test_param_init(lambda) != 0){
        printf("Parameters initiated wrong\n");
        return 0;
    }
    param_init(&param, lambda);

    printf("made it past param init\n");
    //gmp_printf("upper-----------%Zd\n", upper);
    //gmp_printf("lower-----------%Zd\n", lower);

    if(test_sk_init(param) != 0){
        return 0;
    }
    sk_init(&param, &sk);
    printf("made it past sk init\n");

    //if(test_pk_init(&param, &sk) != 0){
    //    printf("Public keys generated wrong\n");
    //    return 0;
    //}
    pk_init(&pk, &param, &sk);
    printf("made it past pk init\n");
    */

    mpz_t cipher;
    mpz_init(cipher);
    for(int i=0; i < num_trials; i++){
        printf("------------------------yolo-----------------\n");
        param_init(&param, lambda);
        sk_init(&param, &sk);
        pk_init(&pk, &param, &sk);

        int trial_val = rand() % 2;

        char trial_char = trial_val + '0';
        partial_enc(&pk, &param, trial_char, &cipher);
        char res = partial_dec(&sk, &cipher);

        if(trial_char != res){
            sum_errors += 1;
            printf("FUCK - there's an error#############################\n");
        }

        keyClean(&sk, &pk, &param);

        if((i % 100) == 0){
            printf("-----------i currently is: %d\"-----------\n", i);
        }
    }
    printf("-----------------------------------------\n");
    printf("tot error: %d\n", sum_errors);

    //keyClean(&sk, &pk, &param);


    return 0;
}
