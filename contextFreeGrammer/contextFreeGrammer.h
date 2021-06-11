#pragma once
#include <stdbool.h>
#include <stdlib.h>

//д╛хо
#define START 'S'
#define EPSILON '&'

typedef struct linkNode
{
	char *str;
	struct linkNode *next;
}Node;

typedef struct grammer
{
	char *N;
	char *T;
	int numN;
	int numT;
	Node **delta;
}Grammer;

int findInN(const char *N, char c);