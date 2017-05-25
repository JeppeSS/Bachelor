#include <stdio.h>
#include <gmp.h>

#include "keyGen.h"
#include "DGHV.h"
#include "random.h"
#include "Filemanager.h"

int main(void){
    
    PK pk;
    Param param;


    readPK(&pk, &param, "public.key");



    pkClean(&pk, &param);

    

    return 0;
}
