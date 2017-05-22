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

    param_init(&param, 42, 26, 988, 147456, 158); 
    keyGen(&sk, &pk, &param);
   

    
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
