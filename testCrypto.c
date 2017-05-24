#include <stdio.h>
#include <gmp.h>

#include "keyGen.h"
#include "DGHV.h"
#include "random.h"

int main(void){
    printf("STARTING -> encryption/decryption test SUIT\n");
    Param param;
    SK sk;
    PK pk;

    int test_param1 = 1;
    int test_param2 = 0;
    int test_param3 = 1;
    int test_param4 = 0;
    int test_param5 = 0;



    printf("generating key\n");
    param_init(&param, 5);
    mpz_t chiper1;
    mpz_t chiper2;
    mpz_t chiper3;
    mpz_t chiper4;
    mpz_t chiper5;
    mpz_t chiper6;

    mpz_inits(chiper1, chiper2, chiper3, chiper4, chiper5, chiper6, NULL);
    keyGen(&sk, &pk, &param);
    printf("keygen done\n");


    printf("Test 1 -> parameter: %d\n", test_param1);
    encrypt(chiper1, &param, &pk, test_param1);
    decrypt(&sk, chiper1);
    printf("return value: %lu\n", mpz_get_ui(chiper1));

    printf("Test 2 -> parameter: %d\n", test_param2);
    encrypt(chiper1, &param, &pk, test_param2);
    decrypt(&sk, chiper2);
    printf("return value: %lu\n", mpz_get_ui(chiper2));

    printf("Test 3 -> parameter: %d\n", test_param3);
    encrypt(chiper3, &param, &pk, test_param3);
    decrypt(&sk, chiper3);
    printf("return value: %lu\n", mpz_get_ui(chiper3));

    printf("Test 4 -> parameter: %d\n", test_param4);
    encrypt(chiper4, &param, &pk, test_param4);
    decrypt(&sk, chiper4);
    printf("return value: %lu\n", mpz_get_ui(chiper4));

    printf("Test 5 -> parameter: %d\n", test_param5);
    encrypt(chiper5, &param, &pk, test_param5);
    decrypt(&sk, chiper5);
    printf("return value: %lu\n", mpz_get_ui(chiper5));


    /*
    param_init(&param, 52, 10, 10, 10, 10); 
    keyGen(&sk, &pk, &param);
   
    gmp_printf("SK: %Zd\n", sk.SK);

    for(int i = 0; i < param.tau; i++){
        gmp_printf("PK VEC: %Zd\n", pk.PK[i]);
    } 

    
    encrypt(chiper, &param, &pk, 1);
    decrypt(&sk, chiper);
    
    */

    /*
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
    */

    keyClean(&sk, &pk, &param);


    return 0;
}
