#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Plaintext.h"


int plaintext_init(Plaintext *plain, char *msg){

    plain->msg = malloc(strlen(msg));
    strcpy(plain->msg, msg);

    plain->bin = malloc(strlen(msg) * (8 * sizeof(int)));
    plain->size = 0;

    toBinary(plain);

    return EXIT_SUCCESS;

}


int toBinary(Plaintext *plain){

    int index = 0;

    for(int i = 0; plain->msg[i] != '\0'; ++i){
        for(int j = 0; j < 8; ++j){
            plain->bin[index] = ((plain->msg[i] >> j) & 1);
            index++;
            plain->size++;
        }
    }

    return EXIT_SUCCESS;
}

int fromBinary(Plaintext *plain){

    int count = 0;
    int val = 0;
    int index = 0;
    int r = 1;


    for(unsigned int i = 0; i <= plain->size; ++i){
        if(count == 8){
            count = 0;
            plain->msg[index] = val;
            index++;
            val = 0;
            r = 1;
        }


        val += plain->bin[i] * r;
        r *= 2;
        count++;
    }


    return EXIT_SUCCESS;
}


int plaintext_clean(Plaintext *plain){

    free(plain->msg);
    free(plain->bin);

    return EXIT_SUCCESS;
}
