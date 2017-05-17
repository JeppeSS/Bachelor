#ifndef KEYGEN
#define KEYGEN

#include <gmp.h>


/* 
 * === Structure ==============================================================
 *         Name:  Parameters (Param)
 *
 *  Description: The structure has many parameters, controlling the number
 *  of integer in the public key and the bit-length of the various integers.
 *  
 *  (All polynomial in the security parameter Lambda)
 * ============================================================================
 */
struct Param {
    
    // Security parameter.
    int lambda;
    
    // Bit-length of noise.
    int rho;

    // Bit-length of the secret key.
    int eta;

    // Bit-length of the integers in the public key
    int gamma;

    // Number of integers in the public key
    int tau;

};

/* 
 * === Structure ==============================================================
 *         Name:  Secret key (SK)
 *
 *  Description: The secret key is an odd eta-bit integer:
 *
 *      SK <-- (2Z + 1) ∩ [2^{eta - 1}, 2^{eta}) 
 * ============================================================================
 */
struct SK {

    // Secret key
    mpz_t SK;
};

/* 
 * === Structure ==============================================================
 *         Name:  Public key (PK)
 *
 *  Description: The public key contains a vector 
 *
 *  PK = (x_{0}, x_{1}, ..., x_{tau})
 *
 *  Where x_{0} is the largest element.
 * ============================================================================
 */
struct PK {

    // Public key vector
    mpz_t *PK;
};

typedef struct Param Param; 
typedef struct SK SK;
typedef struct PK PK;

// Initializers
int param_init(Param *param, int lambda, int rho, int eta, int gamma, int tau);
int sk_init(SK *sk);
int pk_init(PK *pk, Param *param);

// Generators
void genSK(SK *sk, Param *param);
void genPK(mpz_t pk, mpz_t sk, int gamma, int rho); 
void keyGen(mpz_t sk, mpz_t pk[], int lambda, int rho, int eta, int gamma, int tau); 

void qp(mpz_t res, mpz_t sk, mpz_t z);
void rp(mpz_t res, mpz_t sk, mpz_t z);

#endif
