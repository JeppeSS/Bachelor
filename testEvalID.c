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
    Plaintext plain3;
    Plaintext plain4;
    Plaintext plain5;
    Plaintext plain6;

    plaintext_init(&plain, "Hej med dig, Dette er en test");
    
    plaintext_init(&plain2, "Heq med dig, Dette er en test");
    plaintext_init(&plain3, "Hq med dig, Dette er en test");
    plaintext_init(&plain4, "hej med dig, de1te er en test");
    plaintext_init(&plain5, "Heq m4d dig, Detse er en test");
    plaintext_init(&plain6, "Hej med dig, Dette er en test");

    Chipertext chiper;
    
    Chipertext chiper2;
    Chipertext chiper3;
    Chipertext chiper4;
    Chipertext chiper5;
    Chipertext chiper6;

    Param param;
    SK sk;
    PK pk;

    param_init(&param, 8);
    keyGen(&sk, &pk, &param);

    encrypt(&chiper, &param, &pk, &plain); 
    encrypt(&chiper2, &param, &pk, &plain2); 
    encrypt(&chiper3, &param, &pk, &plain3); 
    encrypt(&chiper4, &param, &pk, &plain4); 
    encrypt(&chiper5, &param, &pk, &plain5); 
    encrypt(&chiper6, &param, &pk, &plain6); 


    int val1 = evaluateID(&chiper, &chiper2, &sk);
    
    if(val1 == EXIT_FAILURE){
        printf("test1: not equal\n");
    }else{
        printf("test1: equal\n");
    }


    int val2 = evaluateID(&chiper, &chiper3, &sk);
    
    if(val2 == EXIT_FAILURE){
        printf("test2: not equal\n");
    }else{
        printf("test2: equal\n");
    }

    int val3 = evaluateID(&chiper, &chiper4, &sk);
    
    if(val3 == EXIT_FAILURE){
        printf("test3: not equal\n");
    }else{
        printf("test3: equal\n");
    }
    int val4 = evaluateID(&chiper, &chiper5, &sk);
    
    if(val4 == EXIT_FAILURE){
        printf("test4: not equal\n");
    }else{
        printf("test4: equal\n");
    }
    int val5 = evaluateID(&chiper, &chiper6, &sk);
    
    if(val5 == EXIT_FAILURE){
        printf("test5: not equal\n");
    }else{
        printf("test5: equal\n");
    }



    plaintext_clean(&plain);
    plaintext_clean(&plain2);
    plaintext_clean(&plain3);
    plaintext_clean(&plain4);
    plaintext_clean(&plain5);
    plaintext_clean(&plain6);

}
