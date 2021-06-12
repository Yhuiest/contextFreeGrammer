#include "contextFreeGrammer.h"
#include"Del_useless.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include"Interface.h"

bool *JudgeA(bool *b, int numN, Node **n, char *ch, int times) {
	int num = 0;//��¼�����ɷ��м�������ʽ
	bool temp = true;
	bool flag = true;
	if (times == numN)
		return b;
	else {
		Node *node = n[times];
		while (node != NULL) {
			int j = 0;
			while (node->str[j] != '\0') {
				for (int k = 0; ch[k] != '\0'; k++) {
					if (node->str[j] == ch[k]) {//��һ�����ս��ָ������һ�����ս��
						flag = false;//flag=0˵����ָ����ս��
						temp = temp && b[k];//ǰ�ߵĿ��������ɺ��߾���
					//	if (k == times) {
					//		if (node->next == NULL) {
					//			node = node->next;
					//			b[times] = false;
					//			goto here;
					//		}
					//	}
					}
				}
				j++;
			}
			if (flag == true) {//˵��û��ָ����ս��
				b[times] = true;
				goto here;
			}
			node = node->next;
			flag = true;//ָ����һ������ʽ
		}
		b[times] = temp;
		here:
		times++;
		return JudgeA(b, numN, n, ch, times);
	}
}
bool *JudgeB(bool *b, int numN, Node **n, char *ch) {
	int i = 0;
	while (i < numN) {
		Node*node = n[i];
		while (node != NULL) {
			int j = 0, k;
			while (node->str[j] != '\0') {
				for (k = 0; k < numN; k++) {
					if (node->str[j] == ch[k] && b[k] != true) {//��һ�����ս����ǰ��ķ��ս��ָ��

						b[k] = b[i];//����ķ��ս����ǰ��ķ��ս���ɴ���һ��
						b[1];
					}
				}
				k = 0;
				j++;
			}
			node = node->next;
		}
		i++;
	}
	return b;
}

Node*New_node(Node *n, bool*b, char*ch, int numN) {

	//һǰһ������ָ�룬nMovePre��nMove��ǰһ���ڵ�
	Node *nMovePre = n;
	Node *nMove = nMovePre->next;
	int i, j;
	if (n == NULL) {
		return NULL;
	}
	while (nMove != NULL) {
		int jump = 0;
		for (i = 0; nMove->str[i] != '\0'; i++) {
			for (j = 0; ch[j] != '\0'; j++) {
				if (nMove->str[i] == ch[j] && b[j] == false) {
					jump = 1;
				}
			}
		}
		i = 0;
		j = 0;
		if (jump == 0) {
			nMovePre->next = nMove;
			nMovePre = nMovePre->next;
			nMove = nMovePre->next;
		}
		else {
			nMove = nMove->next;
			jump = 0;
		}
	}
	return n;
}


Grammer *Change(Grammer *g, bool *b) {
	bool *New_flag = b;
	Grammer *newG = (Grammer *)malloc(sizeof(Grammer));
	newG->numN = 0;
	int i = g->numN;
	while (i > -1) {
		if (New_flag[i] == true) {
			newG->numN++;
		}
		i--;
	}
	newG->numT = g->numT;
	newG->N = (char *)malloc(sizeof(char) * (newG->numN + 1));
	newG->T = (char *)malloc(sizeof(char) * (newG->numT + 1));
	i = 0;
	int New_numN = 0;
	while (i < g->numN) {
		if (New_flag[i] != 0) {
			newG->N[New_numN] = g->N[i];
			New_numN++;
		}
		i++;
	}
	memcpy(newG->T, g->T, g->numT + 1);
	newG->delta = (Node **)malloc(sizeof(Node *) * newG->numN);
	New_numN = 0;
	i = 0;
	while (i < g->numN) {
		if (New_flag[i] != 0) {
			newG->delta[New_numN] = New_node(g->delta[i], b, g->N, g->numN);
			New_numN++;
		}
		i++;
	}
	return newG;
}

Grammer * Useful_grammer(Grammer * g) {
	bool *Flag;
	char *ch;
	Flag = (bool *)malloc(sizeof(bool) * g->numN);
	memset(Flag, 0, g->numN);
	//printf("flag[0]=%d\n", flag[0]);
	ch = g->N;
	bool *Generate_flag = (bool *)malloc(sizeof(bool) * g->numN);
	for (int i = 0; i < g->numN - 1; i++) {
		Generate_flag = JudgeA(Generate_flag, g->numN, g->delta, g->N, 0);
	}
	Grammer *Generate_g = Change(g, Generate_flag);

	Flag = (bool *)malloc(sizeof(bool) * Generate_g->numN);
	memset(Flag, 0, Generate_g->numN);
	Flag[0] = true;
	ch = Generate_g->N;
	bool *Access_flag = (bool *)malloc(sizeof(bool) * Generate_g->numN);
	Access_flag = JudgeB(Flag, Generate_g->numN, Generate_g->delta, Generate_g->N);
//	for (int i = 0; i < Generate_g->numN; i++) {
//		Access_flag[i] == true ? printf("1") : printf("0");
//	}
	Grammer * New_g = Change(Generate_g, Access_flag);
	return New_g;
}

void test5() {
	Grammer * g = (Grammer *)malloc(sizeof(Grammer));
	g->N = "SABCD";
	g->numN = 5;
	g->T = "abcd";
	g->numT = 4;
	g->delta = (Node **)malloc(sizeof(Node *));

	g->delta[0] = (Node *)malloc(sizeof(Node));
	Node *tmp = g->delta[0];
	tmp->str = "a";
	tmp->next = (Node *)malloc(sizeof(Node));
	tmp = tmp->next;
	tmp->str = "bA";
	tmp->next = (Node *)malloc(sizeof(Node));
	tmp = tmp->next;
	tmp->str = "B";
	tmp->next = (Node *)malloc(sizeof(Node));
	tmp = tmp->next;
	tmp->str = "ccD";
	tmp->next = NULL;

	g->delta[1] = (Node *)malloc(sizeof(Node));
	tmp = g->delta[1];
	tmp->str = "abB";
	tmp->next = NULL;

	g->delta[2] = (Node *)malloc(sizeof(Node));
	tmp = g->delta[2];
	tmp->str = "aA";
	tmp->next = (Node *)malloc(sizeof(Node));
	tmp = tmp->next;
	tmp->str = "a";
	tmp->next = NULL;

	g->delta[3] = (Node *)malloc(sizeof(Node));
	tmp = g->delta[3];
	tmp->str = "ddC";
	tmp->next = NULL;

	g->delta[4] = (Node *)malloc(sizeof(Node));
	tmp = g->delta[4];
	tmp->str = "ddd";
	tmp->next = NULL;

	Useful_grammer(g);
}
