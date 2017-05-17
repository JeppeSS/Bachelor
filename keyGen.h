#ifndef KEYGEN
#define KEYGEN

#include <gmp.h>

void genSK(mpz_t sk, int eta);
void genPK(mpz_t pk, mpz_t sk, int gamma, int rho); 
void keyGen(mpz_t sk, mpz_t pk[], int lambda, int rho, int eta, int gamma, int tau); 

void qp(mpz_t res, mpz_t sk, mpz_t z);
void rp(mpz_t res, mpz_t sk, mpz_t z);

#endif
