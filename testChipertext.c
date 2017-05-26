#include <stdio.h>
#include <stdlib.h>

#include "keyGen.h"
#include "DGHV.h"
#include "random.h"
#include "Filemanager.h"
#include "Plaintext.h"
#include "Chipertext.h"


int main(void){
    Plaintext plain;
    Plaintext plain2;
    plaintext_init(&plain, "Hej");

    Chipertext chiper;

    Param param;
    SK sk;
    PK pk;

    param_init(&param, 8);
    keyGen(&sk, &pk, &param);

    for(unsigned int i = 0; i < plain.size; ++i){
        printf("%d\n", plain.bin[i]);
    }


    printf("Encrypting msg: %s\n", plain.msg);

    encrypt(&chiper, &param, &pk, &plain);
    
    decrypt(&plain2, &sk, &chiper);
    
    for(unsigned int i = 0; i < plain.size; ++i){
        printf("%d\n", plain2.bin[i]);
    }
    

    


    plaintext_clean(&plain);

}
