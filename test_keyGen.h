#ifndef BACHELOR_TEST_KEYGEN_H
#define BACHELOR_TEST_KEYGEN_H

#include "tools.h"
#include "keyGen.h"

int test_param_init(unsigned int lambda);
int test_sk_init(Param p);
int test_pk_init(Param *p, SK *sk);

#endif //BACHELOR_TEST_KEYGEN_H
