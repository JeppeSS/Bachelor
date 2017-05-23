#ifndef DGHV_H
#define DGHV_H

#include <gmp.h>
#include "keyGen.h"


typedef struct {
    unsigned int list_length;
    mpz_t *arguments;
} C_List ;

void encrypt(mpz_t chiper, Param *param, PK *pk, int c);
void evaluate(mpz_t sum, C_List *list);
void decrypt(SK *sk, mpz_t chiper);



#endif
