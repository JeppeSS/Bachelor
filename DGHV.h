#ifndef DGHV_H
#define DGHV_H

#include <gmp.h>
#include "keyGen.h"
#include "Plaintext.h"
#include "Chipertext.h"

void encryptBit(mpz_t chiper, Param *param, PK *pk, int c);
void encrypt(Chipertext *chiper, Param *param, PK *pk, Plaintext *plain); 
int decryptBit(SK *sk, mpz_t chiper);
void decrypt(Plaintext *plain, SK *sk, Chipertext *chiper);
void evaluate(mpz_t chiper, mpz_t chiper1, mpz_t chiper2);



#endif
