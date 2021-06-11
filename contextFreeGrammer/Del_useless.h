#pragma once
#include "contextFreeGrammer.h"
#include <stdbool.h>

bool *JudgeA(bool *b, int numN, Node **n, char *ch,int times);
bool *JudgeB(bool *b, int numN, Node **n, char *ch);
Grammer *Change(Grammer *g, bool *b);
Grammer * Useful_grammer(Grammer * g);
//void test();