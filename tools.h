#ifndef BACHELOR_TOOLS_H
#define BACHELOR_TOOLS_H

#include <gmp.h>
#include <limits.h>
#include "tools.h"

typedef long int l_int;
typedef long long int ll_int;
typedef unsigned long int ul_int;
typedef unsigned long long int ull_int;
typedef double d_int;
typedef long double dl_int;


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
typedef struct {

    // Security parameter.
    ull_int lambda;

    // Bit-length of noise.
    ull_int rho;
    ull_int rhoM;

    // Bit-length of the secret key.
    ull_int eta;

    // Bit-length of the integers in the public key
    ull_int gamma;

    // Number of integers in the public key
    ull_int tau;

} Param;

/*
 * === Structure ==============================================================
 *         Name:  Secret key (SK)
 *
 *  Description: The secret key is an odd eta-bit integer:
 *
 *      SK <-- (2Z + 1) ∩ [2^{eta - 1}, 2^{eta})
 * ============================================================================
 */
typedef struct {
    // Secret key
    mpz_t sk;
} SK;

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
typedef struct {
    // Public key vector
    mpz_t *PK;
} PK;

int rand_num(mpz_t *buf, mpz_t *lower, mpz_t *upper);
void sort_pk_list(PK *pk, unsigned int list_len);
#endif //BACHELOR_TOOLS_H
