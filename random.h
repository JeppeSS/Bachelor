#ifndef RANDOM
#define RANDOM

#include <gmp.h>

// Seed generator.
unsigned long genSeed(void);

// Random functions
void randomBitSeed(mpz_t rand, unsigned int seed, int size);
void randomUniform(mpz_t rand, mpz_t size);
void randomRange(mpz_t rand, int rho);


#endif
