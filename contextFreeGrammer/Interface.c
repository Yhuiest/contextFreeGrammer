#include"Interface.h"

Grammer * grammers=NULL ;

Grammer * Input(){
	printf("------------------------��ӭʹ��C���԰��CFGС����-----------------------------\n");
	printf("**������������:                                                                **\n");
	printf("**                                                                             **\n");
	printf("**             ����'��'�����ռ�                                                **\n");
	printf("**             �Ѿ�ȷ��ʹ��S��Ϊ��ʼ������ֱ������ʣ����ս��                 **\n");
	printf("**                                                                             **\n");
	int i;
	grammers = (Grammer *)malloc(sizeof(Grammer));
	grammers->N = (char *)malloc(sizeof(char));
	grammers->T = (char *)malloc(sizeof(char));
	grammers->delta = (Node **)malloc(sizeof(Node*));
	grammers->delta[0] = (Node *)malloc(sizeof(Node));
	printf("**    ���������ʼ����ʣ����ս���ĸ���                                       **\n");
	printf("**    ");
	scanf("%d", &grammers->numN);
	grammers->numN++;
	printf("**    ����������ʣ����ս��:                                                  **\n");
	printf("**    ");
	grammers->N[0] = 'S';
	for (i = 1; i < grammers->numN;) {
		char ch = getchar();
		if (ch != '\n'&&ch != ' ') {
			grammers->N[i] = ch;
			i++;
		}
	}
	printf("**    �������ս���ĸ���:                                                      **\n");
	printf("**    ");
	scanf("%d", &grammers->numT);
	printf("**    �����������ս��:                                                        **\n");
	printf("**    ");
	for (i = 0; i < grammers->numT; ) {
		char ch = getchar();
		if (ch != '\n'&&ch != ' ') {
			grammers->T[i] = ch;
			i++;
		}
	}
	printf("**    �������¸�ʽ��������ÿ�����ս������ʽ����:                              **\n");
	printf("**    S-->|�� |�� |��,S��N�Ҧ�,�¡�(N��T)                                      **\n");
	printf("**    (ע�⣺ÿ�����������ʽ���Ҫ�ӿո�)                                     **\n");
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
	printf("**    �����Ǽ��Ժ��CFG��                                                      **\n");

	printf("**    CFG M={N,T,P,S},����                                                       **\n");
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
	printf("**    ����ʽP���£�                                                              **\n");
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