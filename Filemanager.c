#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Filemanager.h"
#include "keyGen.h"

int countLines(char *filename){
    
    FILE *fp = fopen(filename, "r");
    
    int count = 0;
    char c;


    if(fp){

        for(c = getc(fp); c != EOF; c = getc(fp)){
            if(c == '\n'){
                count++;
            }
        }

        fclose(fp);

    } else{
        fprintf(stderr, "[ERROR] Could not read file: %s\n", filename);
        return EXIT_FAILURE;
    }



    return count;
}

int readSK(SK *sk, char *filename){
    
    FILE *fp = fopen(filename, "rb");
    
    char *source;

    if(!fp){
        fprintf(stderr, "[ERROR] Could not write public key to file\n");
        return EXIT_FAILURE;
    }

    long bufsize;
    
    /*Go to the end of the file */
    if(fseek(fp, 0L, SEEK_END) == 0){

        bufsize = ftell(fp);

        if(bufsize == -1){
            fprintf(stderr, "[ERROR] Could not read file\n");
        }

        /* Allocate our buffer to that size.  */
        source = malloc(sizeof(char) * (bufsize + 1));

        /*  Go back to the start of the file. */
        if(fseek(fp, 0L, SEEK_SET) != 0){
            fprintf(stderr, "[ERROR] Could not read file\n");
        }

        /* Read the entire file into memory. */
        size_t newLen = fread(source, sizeof(char), bufsize, fp);

        if(ferror(fp) != 0){
            fprintf(stderr, "[ERROR] Could not read file\n"); 
        } else {
            /* Just to be sure that the file has an ending. */
            source[newLen++] = '\0';
        }

        fclose(fp);
    }

    char *skVal = malloc(sizeof(char) * (bufsize));

    int x = 0;
    for(int i = 0; source[i] != '\0'; i++){
        if(source[i] != '-'  && source[i] != 'B' && source[i] != 'E' &&
           source[i] != 'G'  && source[i] != 'I' && source[i] != 'N' &&
           source[i] != '\n' && source[i] != 'D' && source[i] != 'H' && 
           source[i] != 'V'  && source[i] != 'S' && source[i] != 'C' &&
           source[i] != 'R'  && source[i] != 'T' && source[i] != 'K' &&
           source[i] != 'Y'  && source[i] != 'D' && source[i] != ' '){

           skVal[x] = source[i];
           x++;   
        }
    }

    int z = mpz_set_str(sk->SK, skVal, 16);

    if(z < 0){
        fprintf(stderr, "[ERROR] Could not import secret key\n");
    }



    free(skVal);
    free(source);




    return EXIT_SUCCESS;
}


int writePK(PK *pk, Param *param, char *filename){
    
    FILE *fp = fopen(filename, "wb");
    
    if(!fp){
        fprintf(stderr, "[ERROR] Could not write public key to file\n");
        return EXIT_FAILURE;
    }

    const char *BEGINPAR = "-----BEGIN DGHV PARAMATERS-----";
    const char *ENDPAR   = "-----END DGHV PARAMATERS-----";

    const char *BEGINPK = "-----BEGIN DGHV PUBLIC KEY-----";
    const char *ENDPK   = "-----END DGHV PUBLIC KEY-----";
    

    unsigned int rhoM = param->rhoM;
    unsigned int tau  = param->tau;

    fprintf(fp, "%s\n", BEGINPAR);
    
    fprintf(fp, "%X\n", rhoM);
    fprintf(fp, "%X", tau);
    fprintf(fp, "\n%s\n\n", ENDPAR);

    fprintf(fp, "%s\n", BEGINPK);
    
    size_t data;
    
    for(unsigned int i = 0; i < param->tau; i++){
        data = mpz_out_str(fp, 16, pk->PK[i]);

        if(!data){
            fprintf(stderr, "[ERROR] Could not write public key\n");
            return EXIT_FAILURE;
        }

        fprintf(fp, "\n");
    }

    fprintf(fp, "%s\n", ENDPK);
    
    fclose(fp);

    
    return EXIT_SUCCESS;
}

int writeSK(SK *sk, char *filename){

    FILE *fp = fopen(filename, "wb");
    
    if(!fp){
        fprintf(stderr, "[ERROR] Could not write secret key to file\n");
        return EXIT_FAILURE;
    }

    const char *BEGIN = "-----BEGIN DGHV SECRET KEY-----";
    const char *END   = "-----END DGHV SECRET KEY-----";

    fprintf(fp, "%s\n", BEGIN);

    size_t data = mpz_out_str(fp, 16, sk->SK);

    if(!data){
        fprintf(stderr, "[ERROR] Could not write secret key\n");
        return EXIT_FAILURE;
    }

    fprintf(fp, "\n%s\n", END);

    
    fclose(fp);

    return EXIT_SUCCESS;

}

char *readTestData(char *filename){
    
    FILE *fp = fopen(filename, "r");

    char *source;

    if(fp){

        /*Go to the end of the file */
        if(fseek(fp, 0L, SEEK_END) == 0){

            long bufsize = ftell(fp);

            if(bufsize == -1){
                fprintf(stderr, "[ERROR] Could not read file\n");
            }

            /* Allocate our buffer to that size.  */
            source = malloc(sizeof(char) * (bufsize + 1));

            /*  Go back to the start of the file. */
            if(fseek(fp, 0L, SEEK_SET) != 0){
                fprintf(stderr, "[ERROR] Could not read file\n");
            }

            /* Read the entire file into memory. */
            size_t newLen = fread(source, sizeof(char), bufsize, fp);

            if(ferror(fp) != 0){
                fprintf(stderr, "[ERROR] Could not read file\n"); 
            } else {
                /* Just to be sure that the file has an ending. */
                source[newLen++] = '\0';
            }

            fclose(fp);
        }
    } else{
        fprintf(stderr, "[ERROR] Could not read file: %s\n", filename);
    }

    return source;
}
