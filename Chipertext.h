#ifndef CHIPERTEXT_H
#define CHIPERTEXT_H

#include <gmp.h>

struct Chipertext{
    
    mpz_t *chiper;

    unsigned int size;


};


typedef struct Chipertext Chipertext;


int chipertext_init(Chipertext *chiper, unsigned int size);

#endif
