#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "keyGen.h"
#include "random.h"




Param param_init(Param *param, int lambda, int rho, int eta, int gamma, int tau){

    param->lambda = lambda;
    param->rho    = rho;
    param->eta    = eta;
    param->gamma  = gamma;
    param->tau    = tau;
}



void genSK(mpz_t sk, int eta){

    mpz_t randNum;
    gmp_randstate_t randState;
    
    unsigned long seed = genSeed();

    mpz_init(randNum);

    gmp_randinit_mt(randState);
    gmp_randseed_ui(randState, seed);

    mpz_rrandomb(randNum, randState, eta);

    mpz_nextprime(sk, randNum);
}

void genPK(mpz_t pk, mpz_t sk, int gamma, int rho){

    mpz_t q;
    mpz_t r;
    mpz_t pow;
    mpz_t divide;
    mpz_t tmp;

    mpz_init(q);
    mpz_init(r);
    mpz_init(pow);
    mpz_init(divide);
    mpz_init(tmp);

    mpz_ui_pow_ui(pow, 2, gamma);
    mpz_tdiv_q(divide, pow, sk);
    mpz_add_ui(divide, divide, 1);

    randomUniform(q, divide);
    randomRange(r, rho);


    mpz_mul(tmp, sk, q);
    mpz_add(pk, tmp, r);

}

void keyGen(mpz_t sk, mpz_t pk[], int lambda, int rho, int eta, int gamma, int tau){
    
    genSK(sk, eta);

    
    for(int i = 0; i < tau; i++){
        mpz_init(pk[i]);
        genPK(pk[i], sk, gamma, rho);
    }


    mpz_t tmp; 
    mpz_init(tmp);

    for(int i = 0; i < tau; i++){
        if(mpz_cmp(pk[i], tmp) > 0){
            mpz_set(tmp, pk[i]);
        }
    }
    

    mpz_t res;
    mpz_init(res);

    rp(res, sk, pk[0]);


    while(mpz_odd_p(res) || mpz_even_p(pk[0])){
        for(int i = 0; i < tau; i++){
            mpz_clear(pk[i]);
            mpz_init(pk[i]);
            genPK(pk[i], sk, gamma, rho);
         }
        
        mpz_clear(tmp);
        mpz_init(tmp);

        for(int i = 0; i < tau; i++){
            if(mpz_cmp(pk[i], tmp) > 0){
                mpz_set(tmp, pk[i]);
            } 
        }
        
        mpz_clear(res);
        mpz_init(res);
        rp(res, sk, pk[0]);
    }
    


}

void rp(mpz_t res, mpz_t sk, mpz_t z){
    
    mpz_t qpRes;
    mpz_t tmp;

    mpz_init(tmp);
    mpz_init(qpRes);
    
    qp(qpRes, sk, z);
    mpz_mul(tmp, qpRes, sk);
    mpz_sub(res, z, tmp);



}


void qp(mpz_t res, mpz_t sk, mpz_t z){

    mpz_tdiv_q(res, z, sk);

}

