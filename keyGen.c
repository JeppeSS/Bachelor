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
    
    // Allocate (tau * byte size of int) size.
    // The PK array contains a array of pointers to mpz_t values.
    pk->PK = malloc(param->tau * sizeof(int));

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

    // ranNum = 0
    mpz_init(randNum);

    // Init randState for a Mersenne Twister algorithm.
    gmp_randinit_mt(randState);
    
    // Set an initial seed value into randState
    gmp_randseed_ui(randState, seed);

    // Generate a random integer. The random number will be in the range
    // 2^{eta-1} - 2^{n}-1 inclusive.
    mpz_rrandomb(randNum, randState, param->eta);

    // set SK to be the next prime greather than randNum
    // Uses a probabilistic algorithm to identity primes.
    mpz_nextprime(sk->SK, randNum);

    // Clear allocated memory
    mpz_clear(randNum);
    gmp_randclear(randState);
}

void genPK(mpz_t pk, mpz_t sk, int gamma, int rho){

    mpz_t q;
    mpz_t r;
    mpz_t pow;
    mpz_t divide;
    mpz_t tmp;

    mpz_init(q);
    mpz_init(r);
    mpz_init(pow);
    mpz_init(divide);
    mpz_init(tmp);

    mpz_ui_pow_ui(pow, 2, gamma);
    mpz_tdiv_q(divide, pow, sk);
    mpz_add_ui(divide, divide, 1);

    randomUniform(q, divide);
    randomRange(r, rho);


    mpz_mul(tmp, sk, q);
    mpz_add(pk, tmp, r);

}

/*
void keyGen(mpz_t sk, mpz_t pk[], int lambda, int rho, int eta, int gamma, int tau){
    
    genSK(sk, eta);

    
    for(int i = 0; i < tau; i++){
        mpz_init(pk[i]);
        genPK(pk[i], sk, gamma, rho);
    }


    mpz_t tmp; 
    mpz_init(tmp);

    for(int i = 0; i < tau; i++){
        if(mpz_cmp(pk[i], tmp) > 0){
            mpz_set(tmp, pk[i]);
        }
    }
    

    mpz_t res;
    mpz_init(res);

    rp(res, sk, pk[0]);


    while(mpz_odd_p(res) || mpz_even_p(pk[0])){
        for(int i = 0; i < tau; i++){
            mpz_clear(pk[i]);
            mpz_init(pk[i]);
            genPK(pk[i], sk, gamma, rho);
         }
        
        mpz_clear(tmp);
        mpz_init(tmp);

        for(int i = 0; i < tau; i++){
            if(mpz_cmp(pk[i], tmp) > 0){
                mpz_set(tmp, pk[i]);
            } 
        }
        
        mpz_clear(res);
        mpz_init(res);
        rp(res, sk, pk[0]);
    }
    


}
*/
void rp(mpz_t res, mpz_t sk, mpz_t z){
    
    mpz_t qpRes;
    mpz_t tmp;

    mpz_init(tmp);
    mpz_init(qpRes);
    
    qp(qpRes, sk, z);
    mpz_mul(tmp, qpRes, sk);
    mpz_sub(res, z, tmp);



}


void qp(mpz_t res, mpz_t sk, mpz_t z){

    mpz_tdiv_q(res, z, sk);

}

