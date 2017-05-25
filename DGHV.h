#ifndef DGHV_H
#define DGHV_H

#include <gmp.h>
#include "keyGen.h"
#include "Plaintext.h"


void encryptBit(mpz_t chiper, Param *param, PK *pk, int c);
void decryptBit(SK *sk, mpz_t chiper);
void evaluate(mpz_t chiper, mpz_t chiper1, mpz_t chiper2);



#endif
