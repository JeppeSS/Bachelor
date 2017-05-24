#include <stdio.h>
#include <gmp.h>

#include "keyGen.h"
#include "DGHV.h"
#include "random.h"
#include "Filemanager.h"

int main(void){
    
    SK sk;


    sk_init(&sk);


    readSK(&sk, "key.txt");

    skClean(&sk);


    return 0;
}
