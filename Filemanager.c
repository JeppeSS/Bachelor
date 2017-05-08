#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filemanager.h"

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
