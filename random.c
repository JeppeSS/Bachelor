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

