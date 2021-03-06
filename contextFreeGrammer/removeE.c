#pragma once
#include "contextFreeGrammer.h"
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
		Node *newestNode = newGeneration(lastestNode, str, generateE, i + 1, N);
		char *str2 = strdup(str);
		int k = i;
		for (int j = k++; j < len; j++, k++)
		{
			str2[j] = str[k];
		}
		newestNode = newGeneration(newestNode, str2, generateE, i, N);
		return newestNode;
	}
}

Grammer * removeE(Grammer * g)
{
	bool *generateE = (bool *)malloc(sizeof(bool) * g->numN);
	memset(generateE, 0, g->numN);
	for (int i = 0; i < g->numN; i++)
	{
		Node *tmp = g->delta[i];
		while (tmp)
		{
			if ((*tmp).str[0] == EPSILON)
			{
				generateE[i] = true;
				break;
			}
			tmp = tmp->next;
		}
	}
	Grammer *newG = (Grammer *)malloc(sizeof(Grammer));
	newG->numN = g->numN;
	newG->numT = g->numT;
	newG->N = (char *)malloc(sizeof(char) * (newG->numN + 1));
	newG->T = (char *)malloc(sizeof(char) * (newG->numT + 1));
	memcpy(newG->N, g->N, g->numN + 1);
	memcpy(newG->T, g->T, g->numT + 1);
	newG->delta = (Node **)malloc(newG->numN * sizeof(Node *));
	for (int i = 0; i < g->numN; i++)
	{
		Node *tmp = g->delta[i];
		Node *forNext = (Node *)malloc(sizeof(Node));
		Node *newNode = forNext;
		while (tmp)
		{
			newNode->next = NULL;
			newNode = newGeneration(newNode, tmp->str, generateE, 0, g->N);
			tmp = tmp->next;
		}
		newG->delta[i] = forNext->next;
	}
	Node *tmp = newG->delta[0];
	while (tmp)
	{
		if (memcmp(tmp->str, "&", 1) == 0)
		{
			newG->numN += 1;
			char * newN = (char *)malloc((newG->numN + 1) * sizeof(char));
			newN[0] = 'S';
			memcpy(&(newN[1]), newG->N, newG->numN);
			free(newG->N);
			newG->N = newN;
			Node ** newDelta = (char *)malloc((newG->numN) * sizeof(Node *));
			newDelta[0] = (Node *)malloc(sizeof(Node));
			newDelta[0]->str = strdup("S");
			newDelta[0]->next = (Node *)malloc(sizeof(Node));
			newDelta[0]->next->str = strdup("&");
			newDelta[0]->next->next = NULL;
			memcpy(&(newDelta[1]), newG->delta, (newG->numN - 1) * sizeof(Node *));
			free(newG->delta);
			newG->delta = newDelta;
			break;
		}
		tmp = tmp->next;
	}
	for (int i = 1; i < newG->numN; i++)
	{
		Node *tmp = newG->delta[i];
		if (memcmp(tmp->str, "&", 1) == 0)
		{
			newG->delta[i] = tmp->next;
			free(tmp->str);
			free(tmp);
		}
		else
		{
			while (tmp->next)
			{
				Node * nextNode = tmp->next;
				if (memcmp(nextNode->str, "&", 1) == 0)
				{
					tmp->next = nextNode->next;
					free(nextNode->str);
					free(nextNode);
					break;
				}
				tmp = tmp->next;
			}
		}
	}
	return newG;
}