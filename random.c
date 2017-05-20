#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "random.h"

#define RANDOM_PATH "/dev/urandom"



/* 
 * === Function ===============================================================
 *         Name: genSeed
 *
 *  Description: Generates a random number. The code to the genSeed function
 *  has been obtained from: https://rosettacode.org/wiki/Random_number_generator_(device)
 *
 *  The function generates a random 32-bit number, from /dev/urandom.
 * ============================================================================
 */
unsigned long genSeed(void){
    
    unsigned char buf[4];
    unsigned long seed;
    FILE *fp;


    if((fp = fopen(RANDOM_PATH, "r")) == NULL){
        fprintf(stderr, "[Error] Unable to open file %s\n", RANDOM_PATH);
        return EXIT_FAILURE;
    }

    if (fread(buf, 1, sizeof buf, fp) != sizeof buf){
        fprintf(stderr, "[Error] Not enough bytes (expected %u)\n", RANDOM_PATH, (unsigned) sizeof buf);
        return EXIT_FAILURE;
    }

    fclose(fp);

    seed = buf[0] | buf[1] << 8UL | buf[2] << 16UL | buf[3] << 24UL;

    return seed;

}

/* 
 * === Function ===============================================================
 *         Name: randomUniform
 *
 *  Description: Generates a uniform random integer in the range [0, n],
 *  inclusive.
 * ============================================================================
 */
void randomUniform(mpz_t rand, mpz_t size){
        
    // Contains the algorithm selection and current state.
    gmp_randstate_t randState;
    
    // Random seed pulled from /dev/urandom
    unsigned long seed = genSeed();

    // The mpz_urandomm generates a uniform random number [0, n-1]
    // so to obtain [0, n] we add one to the n.
    mpz_add_ui(size, size, 1);

    // Init randState for a Mersenne Twister algorithm.
    gmp_randinit_mt(randState);
    
    // Set an initial seed value into randState.
    gmp_randseed_ui(randState, seed);

    // Generates the random integer.
    mpz_urandomm(rand, randState, size);

    // Free allocated memory for randState.
    gmp_randclear(randState);

}


/* 
 * === Function ===============================================================
 *         Name: randomRange
 *
 *  Description: Generate a uniformly distributed random integer in the
 *  the [-2^{n}, 2^{n}-1], inclusive.
 * ============================================================================
 */
void randomRange(mpz_t rand, int rho){
    
    /*
     * Because GMP library does not contain any random functions
     * to generate negative numbers. We custom made our own.
     */

    // The posNeg variable, is used to determine if the random number,
    // should be positive or negative.
    mpz_t posNeg;

    // posNeg = 0
    mpz_init(posNeg);
    
    // Contains the algorithm selection and current state.
    gmp_randstate_t randState;

    // Random seed pulled from /dev/urandom
    unsigned long seed = genSeed();

    // Init randState for a Mersenne Twister algorithm.
    gmp_randinit_mt(randState);
    
    // Set an initial seed value into randState
    gmp_randseed_ui(randState, seed);

    // Generates a random number 0 or 1.
    mpz_urandomb(posNeg, randState, 1);


    // If 0, generate negative number
    // else generate positive number
    if(mpz_cmp_ui(posNeg, 0)){
        mpz_urandomb(rand, randState, rho+1);
        mpz_neg(rand, rand);
    } else {
        mpz_urandomb(rand, randState, rho+1);
    }
    
    // Clear allocated memory
    mpz_clear(posNeg);
    gmp_randclear(randState);
}
