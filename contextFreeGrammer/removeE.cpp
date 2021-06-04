#pragma once
#include "contextFreeGrammer.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int findInN(const char *N, char c)
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

Node * newGeneration(Node *lastestNode, const char *str, const bool *generateE, int loc, const char *N)
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
	if (i == len)
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
		Node *newestNode = newGeneration(lastestNode, str, generateE, i + 1, N);
		newestNode->next = (Node *)malloc(sizeof(Node));
		newestNode = newestNode->next;
		newestNode->str = (char *)malloc((len + 1) * sizeof(char));
		newestNode->next = NULL;
		memcpy(newestNode->str, str, len + 1);

		char *str2 = strdup(str);
		for (int j = i++; j < len; j++)
		{
			str2[j] = str[i];
		}
		newestNode = newGeneration(newestNode, str2, generateE, loc + 1, N);
		newestNode->next = (Node *)malloc(sizeof(Node));
		newestNode = newestNode->next;
		newestNode->str = (char *)malloc((len) * sizeof(char));
		newestNode->next = NULL;
		memcpy(newestNode->str, str2, len);
		return newestNode;
	}
}

void removeE(Grammer * g)
{
	bool *generateE = (bool *)malloc(sizeof(bool) * g->numN);
	for (int i = 0; i < g->numN; i++)
	{
		Node *tmp = g->delta[i];
		while (tmp)
		{
			if ((*tmp).str[0] == '&')
			{
				generateE[i] = true;
				break;
			}
			tmp = tmp->next;
		}
	}
	Grammer *newG = (Grammer *)malloc(sizeof(Grammer));

	for (int i = 0; i < g->numN; i++)
	{
		Node *tmp = g->delta[i];
		Node *forNext = (Node *)malloc(sizeof(Node));
		Node *newNode = forNext;
		while (tmp)
		{
			newNode->next = NULL;
			newNode = newGeneration(newNode, tmp->str, generateE, 0, g->N);
		}
	}
}