#include "rmSingelGenerate.h"
#include "Interface.h"

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
		sg[i] = true;

		add = addSg(g, i, sg);
		for (int j = 0; j < g->numN; j++)
		{
			if (sg[j] && j != i)
			{
				Node * tmp = g->delta[j];
				while (tmp)
				{
					if ((strlen(tmp->str) > 1 || findInN(g->N, tmp->str[0]) == -1) && findInD(g->delta[i], tmp->str) == 0)
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
		Put_out(g);
	}
	for (int i = 0; i < g->numN; i++)
	{
		Node * to_del = g->delta[i];
		while (to_del && strlen(to_del->str) == 1 && findInN(g->N, to_del->str[0]) != -1)
		{

			g->delta[i] = to_del->next;
			Node * n2 = g->delta[4];
			free(to_del);
			Node * n = g->delta[4];
			to_del = g->delta[i];
            Put_out(g);
		}
		
		while (to_del && to_del->next)
		{
			if (strlen(to_del->next->str) == 1 && findInN(g->N, to_del->next->str[0]) != -1)
			{
				Node *tmp = to_del->next;
				to_del->next = tmp->next;
				free(tmp);
			}
			else
			{
				to_del = to_del->next;
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
		if (strlen(tmp->str) == 1 && (locInN = findInN(g->N,tmp->str[0])) != -1 && !sg[locInN])
		{
			ret ++;
			sg[locInN] = true;
			addSg(g, locInN, sg);
		}
		tmp = tmp->next;
	}
	return ret;
}

int findInD(Node * n, char * str)
{
	while (n)
	{
		int len_str = strlen(str);
		int len_d = strlen(n->str);
		if (strncmp(n->str, str, len_str > len_d ? len_str : len_d) == 0)
		{
			return 1;
		}
		n = n->next;
	}
	return 0;
}