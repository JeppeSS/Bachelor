#ifndef PLAINTEXT_H
#define PLAINTEXT_H



struct Plaintext {

    char *msg;

    int *bin;
    int size;

};

typedef struct Plaintext Plaintext;

int plaintext_init(Plaintext *plain, char *msg);
int toBinary(Plaintext *plain);


int plaintext_clean(Plaintext *plain);

#endif