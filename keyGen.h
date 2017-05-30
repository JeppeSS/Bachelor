#ifndef KEYGEN_H
#define KEYGEN_H

#include <gmp.h>
#include "tools.h"


// Initializers
void param_init(Param *param, ull_int lambda);
int sk_init(Param *p, SK *sk);
int pk_init(PK *pk, Param *param, SK *sk);
void keyClean(SK *sk, PK *pk, Param *param);
#endif
