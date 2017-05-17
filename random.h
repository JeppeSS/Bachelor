#ifndef RANDOM
#define RANDOM

#include <gmp.h>

unsigned long genSeed(void);
void randomUniform(mpz_t rand, mpz_t size);
void randomRange(mpz_t rand, int rho);


#endif
