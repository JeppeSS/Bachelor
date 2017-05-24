#ifndef FILEMANAGER
#define FILEMANAGER

#include "keyGen.h"

char *readTestData(char *filename);
int countLines(char *filename);
int writeSK(SK *sk, char *filename);
int writePK(PK *pk, Param *param, char *filename);

#endif
