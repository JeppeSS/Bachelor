#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "random.h"

#define RANDOM_PATH "/dev/urandom"



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

void randomUniform(mpz_t rand, mpz_t size){
    
    gmp_randstate_t randState;

    unsigned long seed = genSeed();

    gmp_randinit_mt(randState);
    gmp_randseed_ui(randState, seed);

    mpz_urandomm(rand, randState, size);
}


void randomRange(mpz_t rand, int rho){

    mpz_t posNeg;

    mpz_init(posNeg);
    
    gmp_randstate_t randState;

    unsigned long seed = genSeed();

    gmp_randinit_mt(randState);
    gmp_randseed_ui(randState, seed);

    mpz_urandomb(posNeg, randState, 1);


    if(mpz_cmp_ui(posNeg, 0)){
        mpz_urandomb(rand, randState, rho+1);
        mpz_neg(rand, rand);
    } else {
        mpz_urandomb(rand, randState, rho+1);

    }
    

}
