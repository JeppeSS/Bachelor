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
    mpz_t           size;
    mpz_t           minSize;
    mpz_t           maxSize;

    // Contains the algorithm selection and current state.
    gmp_randstate_t randState;
    
    // Random seed pulled from /dev/urandom
    unsigned long seed = genSeed();

    // ranNum = 0, addOne = 0
    mpz_inits(randNum, minSize, maxSize, size, NULL);
    
    mpz_set_ui(minSize, 2);
    mpz_set_ui(maxSize, 2);
    mpz_pow_ui(minSize, minSize, param->eta-1);
    mpz_pow_ui(maxSize, maxSize, param->eta);

    // Make a boolean random 0 or 1
    mpz_set_ui(size, 1);

    // Init randState for a Mersenne Twister algorithm.
    gmp_randinit_mt(randState);
    
    // Set an initial seed value into randState
    gmp_randseed_ui(randState, seed);


    // Keep generating random number until its an odd integer
    while(mpz_even_p(randNum)){
        
        mpz_clear(randNum);
        mpz_init(randNum);
        
        // Generate a random integer. The random number will be in the range
        // 2^{eta-1} - 2^{eta}-1 inclusive.
        while((mpz_cmp(randNum, minSize) < 0) || mpz_cmp(randNum, maxSize) > 0){
            randomUniform(randNum, maxSize);
        }
        
    }

    // set SK to be the next random odd-integer
    mpz_set(sk->SK, randNum);

    // To prevent attacker to find the secret key in memory.
    // Override before freeing.
    mpz_set_ui(randNum, 0);
    mpz_set_ui(maxSize, 0);
    mpz_set_ui(minSize, 0);

    // Clear allocated memory
    mpz_clear(randNum);
    mpz_clear(maxSize);
    mpz_clear(minSize);
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
void pkSample(mpz_t sample, SK *sk, Param *param){
    
    // q <-- [0, 2^{gamma} % SK).
    // r <-- [-2^{rho}, 2^{rho}]. 
    mpz_t q, r;

    // qEnd = (2^{gamma}/SK) tmp container.
    mpz_t qEnd; 
    mpz_t qEnd2;

    // Set all = 0
    mpz_inits(q, r, qEnd, qEnd2, NULL);

    // qEnd = (2^{gamma} % SK).
    mpz_ui_pow_ui(qEnd, 2, param->gamma);
    mpz_mod(qEnd2, qEnd, sk->SK);
    mpz_sub(qEnd, qEnd, qEnd2);
    mpz_fdiv_q(qEnd, qEnd, sk->SK);
    
    // Select random in the defined range
    randomUniform(q, qEnd);
    randomRange(r, param->rho);

    // sample = sk*q + r
    mpz_mul(sample, sk->SK, q);
    mpz_mul_si(r, r, 2);
    mpz_add(sample, sample, r);
    
    // Set values to 0 and free memory.
    mpz_set_ui(q, 0);
    mpz_set_ui(r, 0);
    mpz_set_ui(qEnd, 0);

    mpz_clear(q);
    mpz_clear(r);
    mpz_clear(qEnd);
    

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


    mpz_t res;
    mpz_init(res);


    // Generate public key vector. Relabel so that x_{0} is the largest.
    // Restart unless x_{0} is odd and rp(x_{0}) is even.
    while(mpz_odd_p(res) || mpz_even_p(pk->PK[0])){
        
        // Create sample for all integers in the public key vector
        for(int i = 0; i < param->tau; i++){
            pkSample(pk->PK[i], sk, param);
        }

        // Find the largest element and set it to x_{0}
        mpz_t tmp; 
        mpz_init(tmp);
        int index;

        // Only swap if needed
        int swap = 0;

        mpz_set(tmp, pk->PK[0]);

        for(int i = 0; i < param->tau; i++){
            if(mpz_cmp(tmp, pk->PK[i]) < 0){
                mpz_set(tmp, pk->PK[i]);
                index = i;

                swap = 1;
            }
        }
        
        if(swap){
            // Swap the elements
            mpz_set(pk->PK[index], pk->PK[0]);
            mpz_set(pk->PK[0], tmp);
        }
        
        // Clear the tmp variable
        mpz_set_ui(tmp, 0);
        mpz_clear(tmp);
      
        // Remainder of x_{0} with respect to SK.
        mpz_mod(res, pk->PK[0], sk->SK);
    }


    // Free memory    
    mpz_set_ui(res, 0);
    mpz_clear(res);

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


/* 
 * === Function ===============================================================
 *         Name: skClean
 *
 *  Description: Free sk memory
 * ============================================================================
 */
void skClean(SK *sk){

    // Set SK = 0, to prevent attacker reading memory after clear.
    mpz_set_ui(sk->SK, 0);
    mpz_clear(sk->SK);
}

/* 
 * === Function ===============================================================
 *         Name: pkClean
 *
 *  Description: Free pk memory
 * ============================================================================
 */
void pkClean(PK *pk, Param *param){

    // Set all PK values = 0, and free.
    for(int i = 0; i < param->tau; i++){
        mpz_set_ui(pk->PK[i], 0);
        mpz_clear(pk->PK[i]);
    }
}

/* 
 * === Function ===============================================================
 *         Name: keyClean
 *
 *  Description: Free sk and pk memory
 * ============================================================================
 */
void keyClean(SK *sk, PK *pk, Param *param){

    skClean(sk);
    pkClean(pk, param);
}



