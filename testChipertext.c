#include <stdio.h>
#include <stdlib.h>

#include "keyGen.h"
#include "DGHV.h"
#include "Plaintext.h"
#include "Chipertext.h"

int main(void){
    Plaintext plain;
    Chipertext chiper;

    Param param;
    SK sk;
    PK pk;

    param_init(&param,8); 
    keyGen(&sk, &pk, &param);


    plaintext_init(&plain, "Hej med dig");

    encrypt(&chiper, &param, &pk, &plain);


    for(unsigned int i = 0; i < plain.size; ++i){
        gmp_printf("%Zx\n", chiper.chiper[i]);
    }


    keyClean(&sk, &pk, &param);
    plaintext_clean(&plain);

}
