
#include <stdio.h>
#include <gmp.h>

#include "keyGen.h"
#include "DGHV.h"
#include "random.h"
#include "Filemanager.h"

int main(void){
    
    Param param;
    SK sk;


    param_init(&param,42); 

    genSK(&sk, &param);

    writeSK(&sk, "key.txt");


    skClean(&sk);


    return 0;
}
