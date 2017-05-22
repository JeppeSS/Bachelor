#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "keyGen.h"
#include "random.h"


/* 
 * === Function ===============================================================
 *         Name: param_init
 *
 *  Description: Initialize all the parameters
 * ============================================================================
 */
int param_init(Param *param, int lambda, int rho, int eta, int gamma, int tau){

    param->lambda = lambda;
    param->rho    = rho;
    param->eta    = eta;
    param->gamma  = gamma;
    param->tau    = tau;

    return EXIT_SUCCESS;
}

/* 
 * === Function ===============================================================
 *         Name: sk_init
 *
 *  Description: Initialize the secret key
 * ============================================================================
 */
int sk_init(SK *sk){

    // Set SK = 0
    mpz_init(sk->SK);

    return EXIT_SUCCESS;
}

/* 
 * === Function ===============================================================
 *         Name: pk_init
 *
 *  Description: Initialize the public key vector, according to tau.
 * ============================================================================
 */
int pk_init(PK *pk, Param *param){
    
    // Set x0 = 0
    mpz_init(pk->x0);


    // Allocate (tau * byte size of mpz_t struct) size.
    // The PK array contains a array of pointers to mpz_t values.
    pk->PK = malloc(param->tau * sizeof(mpz_t));

    if(!pk->PK){
        fprintf(stderr, "[Error] Public key memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Set all values in PK to 0
    for(int i = 0; i < param->tau; i++){
        mpz_init(pk->PK[i]);
    }


    return EXIT_SUCCESS;

}

/* 
 * === Function ===============================================================
 *         Name: genSK
 *
 *  Description: Generates a secret key, according to the parameters set.
 * ============================================================================
 */
void genSK(SK *sk, Param *param){


    fprintf(stdout, "[OK] Generating Secret key of %d bits\n", param->eta);
    fprintf(stdout, "[OK] Please wait..\n");

    // Initialize the secret key
    int ret = sk_init(sk);

    if(ret){
        fprintf(stderr, "[Error] The secret key could not be initialized\n");
    }

    // Pseudo-random number placeholder.
    mpz_t           randNum;

    // Contains the algorithm selection and current state.
    gmp_randstate_t randState;
    
    // Random seed pulled from /dev/urandom
    unsigned long seed = genSeed();

    // randNum = 0
    mpz_init(randNum);
    
    // Init randState for a Mersenne Twister algorithm.
    gmp_randinit_mt(randState);
    
    // Set an initial seed value into randState
    gmp_randseed_ui(randState, seed);
        
    // Generate a random integer. The random number will be in the range
    // 2^{eta-1} - 2^{eta}-1 inclusive.
    mpz_rrandomb(randNum, randState, param->eta);
        
    // set SK to be the next random odd-integer
    mpz_nextprime(sk->SK, randNum);

    // To prevent attacker to find the secret key in memory.
    // Override before freeing.
    mpz_set_ui(randNum, 0);

    // Clear allocated memory
    mpz_clear(randNum);
    gmp_randclear(randState);
    
    fprintf(stdout, "[OK] Secret key generated\n");
}

/* 
 * === Function ===============================================================
 *         Name: pkSample
 *
 *  Description: For a specific (eta-bit) odd positive integer SK, the
 *  following distribution over gamma-bit integers, generates a sample.
 * ============================================================================
 */
void pkSample(PK *pk, SK *sk, mpz_t sample, Param *param){

    
    mpz_t ri;
    mpz_t Xi;
    mpz_t xi;

    mpz_inits(xi, Xi, ri, NULL);

    randomRange(ri, param->rho);


    randomBitSeed(xi, pk->seed, param->gamma);
    randomBitSeed(Xi, pk->seed, param->lambda + param->eta);
    
    mpz_fdiv_q(Xi, Xi, sk->SK);
    mpz_mod(xi, xi, sk->SK);

    mpz_mul(Xi, Xi, sk->SK);
    mpz_add(xi, xi, Xi);
    mpz_sub(sample, xi, ri);


}

/* 
 * === Function ===============================================================
 *         Name: genPK
 *
 *  Description: Generates a public key vector 
 *  pk = (x_{0}, x_{1}, ..., x_{tau})
 * ============================================================================
 */
void genPK(PK *pk, SK *sk, Param *param){
    
    fprintf(stdout, "[OK] Generating Public key vector\n");
    fprintf(stdout, "[OK] Number of elements in vector: %d\n", param->tau);
    fprintf(stdout, "[OK] Bit size of each element: %d\n", param->gamma);
    fprintf(stdout, "[OK] Please wait..\n");
    
    // Initialize the public key
    int ret = pk_init(pk, param);

    if(ret){
        fprintf(stderr, "[Error] The public key could not be initialized\n");
    }

    mpz_t q0;
    mpz_t tmp;

    mpz_inits(q0, tmp, NULL);
    
    mpz_ui_pow_ui(q0, 2, param->gamma);
    mpz_mod(q0, q0, sk->SK);
    
    randomUniform(tmp, q0);

    mpz_mul(pk->x0, tmp, sk->SK);

    pk->seed = genSeed();


    for(int i = 0; i < param->tau; i++){
        pkSample(pk, sk, pk->PK[i], param);
    }


    fprintf(stdout, "[OK] Public key generated\n");

}
/* 
 * === Function ===============================================================
 *         Name: keyGen
 *
 *  Description: Generates the private key and public key with respect
 *  to the parameters.
 * ============================================================================
 */

void keyGen(SK *sk, PK *pk, Param *param){
    
    genSK(sk, param);
    genPK(pk, sk, param);
}
