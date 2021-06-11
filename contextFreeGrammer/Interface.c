#include"Interface.h"

Grammer * grammers=NULL ;

Grammer * Input(){
	printf("------------------------欢迎使用C语言版简化CFG小程序-----------------------------\n");
	printf("**操作流程如下:                                                                **\n");
	printf("**                                                                             **\n");
	printf("**             符号'φ'代表空集                                                **\n");
	printf("**             已经确定使用S作为起始符，请直接输入剩余非终结符                 **\n");
	printf("**                                                                             **\n");
	int i;
	grammers = (Grammer *)malloc(sizeof(Grammer));
	grammers->N = (char *)malloc(sizeof(char));
	grammers->T = (char *)malloc(sizeof(char));
	grammers->delta = (Node **)malloc(sizeof(Node*));
	grammers->delta[0] = (Node *)malloc(sizeof(Node));
	printf("**    请输入除起始符外剩余非终结符的个数                                       **\n");
	printf("**    ");
	scanf("%d", &grammers->numN);
	grammers->numN++;
	printf("**    请依次输入剩余非终结符:                                                  **\n");
	printf("**    ");
	grammers->N[0] = 'S';
	for (i = 1; i < grammers->numN;) {
		char ch = getchar();
		if (ch != '\n'&&ch != ' ') {
			grammers->N[i] = ch;
			i++;
		}
	}
	printf("**    请输入终结符的个数:                                                      **\n");
	printf("**    ");
	scanf("%d", &grammers->numT);
	printf("**    请依次输入终结符:                                                        **\n");
	printf("**    ");
	for (i = 0; i < grammers->numT; ) {
		char ch = getchar();
		if (ch != '\n'&&ch != ' ') {
			grammers->T[i] = ch;
			i++;
		}
	}
	printf("**    请以如下格式依次输入每个非终结符产生式规则:                              **\n");
	printf("**    S-->|α |β |…,S∈N且α,β∈(N∪T)                                      **\n");
	printf("**    (注意：每个输入的生成式最后要加空格)                                     **\n");
	char ch = getchar();
	while (ch != grammers->N[0]) {
		ch = getchar();
	}
	for (i = 0; i < grammers->numN; i++) {
		if (ch == grammers->N[i]) {
			while (ch != '>') {
				ch = getchar();
			}
			ch = getchar();
			//ch = '|'	
			grammers->delta[i] = NULL;
			Node *p = NULL, *r = NULL;
			while (ch == '|') {
				p = (Node *)malloc(sizeof(Node));
				p->str = (char *)malloc(sizeof(char));
				p->next = NULL;
				scanf("%s", p->str);
				if (r == NULL) {
					grammers->delta[i] = p;
					r = p;
				}
				else {
					r->next = p;
					r = p;
				}
				ch = getchar();
				while (i< grammers->numN-1 && ch != grammers->N[i + 1]) {
					ch = getchar();
				}

			}
	/*		while (grammers->delta[i] != NULL) {
				printf("%s ", grammers->delta[i]->str);
				grammers->delta[i] = grammers->delta[i]->next;
			}
	*/	}
		else
				grammers->delta[i] = NULL;
	}
	return grammers;
	printf("**                                                                               **\n");
}

/*void Put_out(Grammer *g) {
	printf("**    以下是简化以后的CFG：                                                      **\n");

	printf("**    CFG M={N,T,P,S},其中                                                       **\n");
	printf("**    N={ ");
	int i = 0;
	while (i < g->numN)
		printf("%ch ", g->N[i]);
	printf("}\n");
	printf("**    T={ ");
	i = 0;
	while (i < g->numT)
		printf("%ch ", g->T[i]);
	printf("}\n");
	printf("**    T={ ");
	i = 0;
	while (i < g->numT)
		printf("%ch ", g->T[i]);
	printf("}\n");
	printf("**    生成式P如下：                                                              **\n");
	i = 0;
	while (g->delta[i] != NULL) {
		printf("**    ");
		printf("%c-->", g->N[i]);
		Node *node = g->delta[i];
		while (node != NULL) {
			printf("%s", node->str);
			node->next == NULL ? printf("\n") : printf("|");
			node = node->next;
		}
		i++;
	}
	printf("---------------------------------------------------------------------------------\n");
}*/
int main() {
	Input();
}