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
    Plaintext res;

    plaintext_init(&plain, "Hej med dig, Dette er en test");
    plaintext_init(&plain2, "Heq med dig, Dette er en test");

    Chipertext chiper;
    Chipertext chiper2;

    Chipertext chiper3;

    Param param;
    SK sk;
    PK pk;



    param_init(&param, 8);
    keyGen(&sk, &pk, &param);

    encrypt(&chiper, &param, &pk, &plain); 
    encrypt(&chiper2, &param, &pk, &plain2); 

    evaluate(&chiper3, &chiper, &chiper2);

    decrypt(&res, &sk, &chiper3);

    printf("Evaluate\n");
    for(unsigned int i = 0; i < res.size; i++){
        printf("%d\n", res.bin[i]);
    }
    

    plaintext_clean(&plain);
    plaintext_clean(&plain2);

}
