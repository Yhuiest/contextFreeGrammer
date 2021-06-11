#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "contextFreeGrammer.h"
#include "removeE.h"
#include "rmSingelGenerate.h"
#include "Interface.h"
#include "Del_useless.h"

void test()
{
	Grammer * g = (Grammer *)malloc(sizeof(Grammer));
	g->N = "SABCD";
	g->numN = 5;
	g->T = "01";
	g->numT = 2;
	g->delta = (Node **)malloc(g->numN * sizeof(Node *));
	g->delta[0] = (Node *)malloc(sizeof(Node));
	g->delta[0]->str = (char *)malloc(2 * sizeof(char));
	Node *next = g->delta[0];
	memcpy(next->str, "A", 2);
	next->next = NULL;
	next = (Node *)malloc(sizeof(Node));
	g->delta[1] = next;
	next->str = (char *)malloc(5 * sizeof(char));
	memcpy(next->str, "0BD", 4);
	next->next = NULL;
	next = (Node *)malloc(sizeof(Node));
	g->delta[2] = next;
	next->str = (char *)malloc(4 * sizeof(char));
	memcpy(next->str, "0BC", 4);
	next->next = (Node *)malloc(sizeof(Node));
	next = next->next;
	next->str = (char *)malloc(2 * sizeof(char));
	memcpy(next->str, "1", 2);
	next->next = (Node *)malloc(sizeof(Node));
	next = next->next;
	next->str = (char *)malloc(2 * sizeof(char));
	memcpy(next->str, "&", 2);
	next->next = NULL;
	next = (Node *)malloc(sizeof(Node));
	g->delta[3] = next;
	next->str = (char *)malloc(2 * sizeof(char));
	memcpy(next->str, "1", 2);
	next->next = NULL;
	next = (Node *)malloc(sizeof(Node));
	g->delta[4] = next;
	next->str = (char *)malloc(2 * sizeof(char));
	memcpy(next->str, "&", 2);
	next->next = NULL;
	Grammer * new = removeE(g);
	Node * n1 = new->delta[1];
	Node * n2 = new->delta[2];
	Node * n3 = new->delta[3];
	Node * n4 = new->delta[4];
	return;
}

void test2()
{
	Grammer * g = (Grammer *)malloc(sizeof(Grammer));
	g->N = "S";
	g->numN = 1;
	g->T = "ab";
	g->numT = 2;
	g->delta = (Node **)malloc(sizeof(Node *));
	g->delta[0] = (Node *)malloc(sizeof(Node));
	Node *tmp = g->delta[0];
	tmp->str = "aSbS";
	tmp->next = (Node *)malloc(sizeof(Node));
	tmp = tmp->next;
	tmp->str = "bSaS";
	tmp->next = (Node *)malloc(sizeof(Node));
	tmp = tmp->next;
	tmp->str = "&";
	tmp->next = NULL;
	Grammer * new = removeE(g);
	Node * n1 = new->delta[1];
	return;
}

void test3()
{
	Grammer * g = (Grammer *)malloc(sizeof(Grammer));
	g->N = "SAB";
	g->numN = 3;
	g->T = "()+*a";
	g->numT = 5;
	g->delta = (Node **)malloc(g->numN * sizeof(Node *));
	g->delta[0] = (Node *)malloc(sizeof(Node));
	Node * tmp = g->delta[0];
	tmp->str = "S+A";
	tmp->next = (Node *)malloc(sizeof(Node));
	tmp = tmp->next;
	tmp->str = "A";
	tmp->next = NULL;
	g->delta[1] = (Node *)malloc(sizeof(Node));
	tmp = g->delta[1];
	tmp->str = "A*B";
	tmp->next = (Node *)malloc(sizeof(Node));
	tmp = tmp->next;
	tmp->str = "B";
	tmp->next = NULL;
	g->delta[2] = (Node *)malloc(sizeof(Node));
	tmp = g->delta[2];
	tmp->str = "(S)";
	tmp->next = (Node *)malloc(sizeof(Node));
	tmp = tmp->next;
	tmp->str = "a";
	tmp->next = NULL;
	Node * n1 = g->delta[1];
	Node * n2 = g->delta[2];
	rmSingelGenerate(g);
}
int main()
{
	//test3();
	Grammer * g =Input();
	g = removeE(g);
	Put_out(g);
	g = Useful_grammer(g);
	Put_out(g);
	rmSingelGenerate(g);
	Put_out(g);
	return 0;
}