#include <stdio.h>
#include <gmp.h>

#include "keyGen.h"
#include "DGHV.h"

int main(void){
    printf("STARTING -> encryption/decryption test SUIT\n");
    Param param;
    SK sk;
    PK pk;



    printf("generating key\n");
    param_init(&param, 42, 26, 988, 147456, 158); 
    keyGen(&sk, &pk, &param);
    printf("keygen done\n");

    mpz_t chiper1;
    mpz_init(chiper1);
    int test_param1 = 1;
    printf("Test 1 -> parameter: %i", test_param1);
    encrypt(chiper1, &param, &pk, test_param1);
    decrypt(&sk, chiper1);
    printf("return value: %Z", chiper1);

    mpz_t chiper2;
    mpz_init(chiper2);
    int test_param2 = 2;
    printf("Test 2 -> parameter: %i", test_param2);
    encrypt(chiper1, &param, &pk, test_param2);
    decrypt(&sk, chiper2);
    printf("return value: %Z", chiper2);

    mpz_t chiper3;
    mpz_init(chiper3);
    int test_param3 = 3;
    printf("Test 3 -> parameter: %i", test_param3);
    encrypt(chiper3, &param, &pk, test_param3);
    decrypt(&sk, chiper3);
    printf("return value: %Z", chiper3);

    mpz_t chiper4;
    mpz_init(chiper4);
    int test_param4 = 4;
    printf("Test 4 -> parameter: %i", test_param4);
    encrypt(chiper4, &param, &pk, test_param4);
    decrypt(&sk, chiper4);
    printf("return value: %Z", chiper4);

    mpz_t chiper5;
    mpz_init(chiper5);
    int test_param5 = 5;
    printf("Test 5 -> parameter: %i", test_param5);
    encrypt(chiper5, &param, &pk, test_param5);
    decrypt(&sk, chiper5);
    printf("return value: %Z", chiper5);




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





    return 0;
}
