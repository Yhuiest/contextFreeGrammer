#include"Interface.h"

Grammer * grammers=NULL ;

Grammer * Input() {
	printf("------------------------��ӭʹ��C���԰��CFGС����-----------------------------\n");
	printf("**������������:                                                                \n");
	printf("**                                                                             \n");
	printf("**             ����'��'����ռ�                                                \n");
	printf("**             �Ѿ�ȷ��ʹ��S��Ϊ��ʼ������ֱ������ʣ����ս��                 \n");
	printf("**                                                                             \n");
	int i;
	grammers = (Grammer *)malloc(sizeof(Grammer));
	grammers->N = (char *)malloc(sizeof(char));
	grammers->T = (char *)malloc(sizeof(char));
	grammers->delta = (Node **)malloc(sizeof(Node*));
	grammers->delta[0] = (Node *)malloc(sizeof(Node));
	printf("**    ���������ʼ����ʣ����ս���ĸ���                                       \n");
	printf("**    ");
	scanf("%d", &grammers->numN);
	grammers->delta = (Node **)malloc(grammers->numN * sizeof(Node*));
	grammers->N = (char *)malloc(grammers->numN * sizeof(char));
	grammers->numN++;
	printf("**    ����������ʣ����ս��:                                                  \n");
	printf("**    ");
	grammers->N[0] = 'S';
	for (i = 1; i < grammers->numN;) {
		char ch = getchar();
		if (ch != '\n'&&ch != ' ') {
			grammers->N[i] = ch;
			i++;
		}
	}
	printf("**    �������ս���ĸ���:                                                      \n");
	printf("**    ");
	scanf("%d", &grammers->numT);
	grammers->T = (char *)malloc(grammers->numT * sizeof(char));
	printf("**    �����������ս��:                                                        \n");
	printf("**    ");
	for (i = 0; i < grammers->numT; ) {
		char ch = getchar();
		if (ch != '\n'&&ch != ' ') {
			grammers->T[i] = ch;
			i++;
		}
	}
	printf("**    ����������ÿ�����ս������ʽ:                                            \n");
	int number;
	for (i = 0; i < grammers->numN; i++) {
		grammers->delta[i] = NULL;
		Node *p = NULL, *r = NULL;
		printf("**    ��������ս��%c����ʽ����:    ", grammers->N[i]);
		scanf("%d", &number);
		for (int j = 0; j < number; j++) {
			printf("**    ��%d������ʽ(�س�����):        ", j+1);
			p = (Node *)malloc(sizeof(Node));
			p->str = (char *)malloc(sizeof(char));
			p->next = NULL;
			char tmp[10];
			scanf("%s", tmp);
			p->str = strdup(tmp);
			if (r == NULL) {
				grammers->delta[i] = p;
				r = p;
			}
			else {
				r->next = p;
				r = p;
			}
		}
	}
	grammers->delta[i] = NULL;
	printf("**    ���������                                                               \n\n");
	i = 0;
	return grammers;
}


void Put_out(Grammer *g) {
	printf("**    �����Ǽ��Ժ��CFG��                                                      \n");

	printf("**    CFG M={N,T,P,S},����                                                       \n");


	printf("**    N={ ");

	int i = 0;
	while (i < g->numN) {
		if (i == 0) {
			g->N[1] == 'S' ? printf("%c1 ", g->N[0]) : printf("%c ", g->N[0]);
		}
		else {
			printf("%c ", g->N[i]);
		}
		i++;
	}

	printf("}\n");
	printf("**    T={ ");
	i = 0;
	while (i < g->numT) {
		printf("%c ", g->T[i]);
		i++;
	}
	printf("}\n");
	printf("**    ����ʽP����:\n");
	i = 0;
	while (i < g->numN) {
		printf("**    ");
		if (i == 0) {
			g->N[1] == 'S' ? printf("%c1-->", g->N[0]) : printf("%c-->", g->N[0]);
		}
		else {
			printf("%c-->", g->N[i]);
		}
		Node *node = g->delta[i];

		while (node != NULL) {
			printf("%s", node->str);
			node->next == NULL ? printf("\n") : printf("|");
			node = node->next;
		}
		i++;
	}
	printf("---------------------------------------------------------------------------------\n");
}
