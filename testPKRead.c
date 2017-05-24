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
    gmp_printf("%Zx\n", pk.PK[param.tau-1]);

    pkClean(&pk, &param);

    

    return 0;
}
