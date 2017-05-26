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
    plaintext_init(&plain, "Hej med dig, Dette er en test");

    Chipertext chiper;

    Param param;
    SK sk;
    PK pk;

    param_init(&param, 8);
    keyGen(&sk, &pk, &param);


    printf("Encrypting msg: %s\n", plain.msg);

    encrypt(&chiper, &param, &pk, &plain);
    
    decrypt(&plain2, &sk, &chiper);
    
    printf("Decrypting msg: %s\n", plain2.msg);
    

    


    plaintext_clean(&plain);

}
