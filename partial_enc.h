#ifndef BACHELOR_PARTIAL_ENC_H
#define BACHELOR_PARTIAL_ENC_H

#include "tools.h"

char partial_enc(PK *pk, Param *param, char m, mpz_t cipher);
char partial_dec(SK *sk, mpz_t cipher);
#endif //BACHELOR_PARTIAL_ENC_H
