#ifndef RANDOM
#define RANDOM

#include <gmp.h>

// Seed generator.
unsigned long genSeed(void);

// Random functions
void randomUniform(mpz_t rand, mpz_t size);
void randomRange(mpz_t rand, int rho);


#endif
