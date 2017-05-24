
#include <stdio.h>
#include <gmp.h>

#include "keyGen.h"
#include "DGHV.h"
#include "random.h"
#include "Filemanager.h"

int main(void){
    
    Param param;
    SK sk;
    PK pk;


    param_init(&param,5); 

    keyGen(&sk, &pk, &param);


    writeSK(&sk, "key.txt");
    writePK(&pk, &param, "public.key");


    skClean(&sk);


    return 0;
}
