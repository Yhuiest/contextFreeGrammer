#pragma once
#include "contextFreeGrammer.h"

int findInN(const char *N, char c);
Node * newGeneration(Node *lastestNode, const char *str, const bool *generateE, int loc, const char *N);
Grammer * removeE(Grammer * g);

