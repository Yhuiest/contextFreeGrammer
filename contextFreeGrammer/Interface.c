#include"Interface.h"

Grammer * grammers=NULL ;

Grammer * Input() {
	printf("------------------------欢迎使用C语言版简化CFG小程序-----------------------------\n");
	printf("**操作流程如下:                                                                \n");
	printf("**                                                                             \n");
	printf("**             符号'φ'代表空集                                                \n");
	printf("**             已经确定使用S作为起始符，请直接输入剩余非终结符                 \n");
	printf("**                                                                             \n");
	int i;
	grammers = (Grammer *)malloc(sizeof(Grammer));
	grammers->N = (char *)malloc(sizeof(char));
	grammers->T = (char *)malloc(sizeof(char));
	grammers->delta = (Node **)malloc(sizeof(Node*));
	grammers->delta[0] = (Node *)malloc(sizeof(Node));
	printf("**    请输入除起始符外剩余非终结符的个数                                       \n");
	printf("**    ");
	scanf("%d", &grammers->numN);
	grammers->delta = (Node **)malloc(grammers->numN * sizeof(Node*));
	grammers->N = (char *)malloc(grammers->numN * sizeof(char));
	grammers->numN++;
	printf("**    请依次输入剩余非终结符:                                                  \n");
	printf("**    ");
	grammers->N[0] = 'S';
	for (i = 1; i < grammers->numN;) {
		char ch = getchar();
		if (ch != '\n'&&ch != ' ') {
			grammers->N[i] = ch;
			i++;
		}
	}
	printf("**    请输入终结符的个数:                                                      \n");
	printf("**    ");
	scanf("%d", &grammers->numT);
	grammers->T = (char *)malloc(grammers->numT * sizeof(char));
	printf("**    请依次输入终结符:                                                        \n");
	printf("**    ");
	for (i = 0; i < grammers->numT; ) {
		char ch = getchar();
		if (ch != '\n'&&ch != ' ') {
			grammers->T[i] = ch;
			i++;
		}
	}
	printf("**    请依次输入每个非终结符产生式:                                            \n");
	int number;
	for (i = 0; i < grammers->numN; i++) {
		grammers->delta[i] = NULL;
		Node *p = NULL, *r = NULL;
		printf("**    请输入非终结符%c产生式个数:    ", grammers->N[i]);
		scanf("%d", &number);
		for (int j = 0; j < number; j++) {
			printf("**    第%d个产生式(回车结束):        ", j+1);
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
	printf("**    输入结束！                                                               \n\n");
	i = 0;
	return grammers;
}


void Put_out(Grammer *g) {
	printf("**    以下是简化以后的CFG：                                                      \n");

	printf("**    CFG M={N,T,P,S},其中                                                       \n");


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
	printf("**    生成式P如下:\n");
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
