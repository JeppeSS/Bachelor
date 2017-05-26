#include <stdio.h>
#include <stdlib.h>


#include "Chipertext.h"



int chipertext_init(Chipertext *chiper, unsigned int size){

    chiper->chiper = malloc(size * sizeof(mpz_t));
    
    for(unsigned int i = 0; i < size; i++){
        mpz_init(chiper->chiper[i]);
    }
    chiper->size = size;

    return EXIT_SUCCESS;
}
