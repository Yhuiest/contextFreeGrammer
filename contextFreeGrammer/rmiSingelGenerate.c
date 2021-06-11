#include "rmSingelGenerate.h"

Grammer * rmSingelGenerate(Grammer * g)
{
	bool * sg = (bool *)malloc(sizeof(bool) * g->numN);
	for (int i = 0; i < g->numN; i++)
	{
		Node * addToD = g->delta[i];
		while (addToD->next)
		{
			addToD = addToD->next;
		}
		int add = 0;
		memset(sg, 0, g->numN * sizeof(bool));
		add = addSg(g, i, sg);
		for (int j = 0; j < g->numN; j++)
		{
			if (sg[j])
			{
				Node * tmp = g->delta[j];
				while (tmp)
				{
					if (strlen(tmp->str) > 1 || findInN(g->N, tmp->str[0]) == -1)
					{
						addToD->next = (Node *)malloc(sizeof(Node));
						addToD = addToD->next;
						addToD->str = strdup(tmp->str);
						addToD->next = NULL;
					}
					tmp = tmp->next;
				}
			}
		}
	}
}

int addSg(Grammer * g,int loc, bool * sg)
{
	int ret = 0;
	Node * tmp = g->delta[loc];
	int locInN;
	while (tmp)
	{
		if (strlen(tmp->str) == 1 && (locInN = findInN(g->N,tmp->str[0])) != -1)
		{
			ret ++;
			sg[locInN] = true;
			addSg(g, locInN, sg);
		}
		tmp = tmp->next;
	}
	return ret;
}