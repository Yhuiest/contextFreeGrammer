#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "removeE.cpp"
#include "contextFreeGrammer.h"
#include "removeE.h"


int main()
{
	Node * tmp = (Node *)malloc(sizeof(Node));
	tmp->next = NULL;
	char N[10] = "ANXUD";
	bool generateE[6] = { true, false, false, true,true };

	char str[10] = "apAKdsUD";
	newGeneration(tmp, str, generateE, 0, N);
	return 0;
}