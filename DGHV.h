#ifndef DGHV_H
#define DGHV_H

#include <gmp.h>
#include "keyGen.h"


void encrypt(mpz_t chiper, Param *param, PK *pk, int c);
void decrypt(SK *sk, mpz_t chiper);
void evaluate(mpz_t chiper, mpz_t chiper1, mpz_t chiper2);



#endif
