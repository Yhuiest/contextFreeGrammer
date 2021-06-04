#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "removeE.cpp"
#include "contextFreeGrammer.h"

int findInN(char *N, char c)
{
	for (int i = 0; N[i]; i++)
	{
		if (c == N[i])
		{
			return i;
		}
	}
	return -1;
}

Node * newGeneration(Node *lastestNode, char *str, bool *generateE, int loc, char *N)
{
	int len = strlen(str);
	int i;
	int locInN;
	for (i = loc; i < len; i++)
	{
		if ((locInN = findInN(N, str[i])) != -1 && generateE[locInN])
		{
			break;
		}
	}
	if (i >= len)
	{
		lastestNode->next = (Node *)malloc(sizeof(Node));
		Node * tmp = lastestNode->next;
		tmp->str = (char *)malloc((len + 1) * sizeof(char));
		memcpy(tmp->str, str, len + 1);
		tmp->next = NULL;
		return tmp;
	}
	else
	{
		Node *newestNode = newGeneration(lastestNode, str, generateE, i + 1, N);/*
		newestNode->next = (Node *)malloc(sizeof(Node));
		newestNode = newestNode->next;
		newestNode->str = (char *)malloc((len + 1) * sizeof(char));
		newestNode->next = NULL;
		memcpy(newestNode->str, str, len + 1);*/

		char *str2 = strdup(str);
		int k = i;
		for (int j = k++; j < len; j++, k++)
		{
			str2[j] = str[k];
		}
		newestNode = newGeneration(newestNode, str2, generateE, i, N);
		/*newestNode->next = (Node *)malloc(sizeof(Node));
		newestNode = newestNode->next;
		newestNode->str = (char *)malloc((len) * sizeof(char));
		newestNode->next = NULL;
		memcpy(newestNode->str, str2, len);*/
		return newestNode;
	}
}

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