#include <stdio.h>
#include <stdlib.h>

#include "Plaintext.h"


int main(void){
    Plaintext plain;

    plaintext_init(&plain, "Hej med dig");

    for(unsigned int i = 0; i < plain.size; ++i){
        printf("%d\n", plain.bin[i]);
    }


    plaintext_clean(&plain);

}
