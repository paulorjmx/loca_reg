#include "inc/list.h"

LIST *cria_lista(GAME *game)
{
	LIST *cabeca = NULL;
	cabeca = (LIST *) malloc(sizeof(LIST));
	if(cabeca == NULL)
	{
		printf("NAO FOI POSSIVEL ALOCAR A LISTA!\n");
		return NULL;
	}
	cabeca->g = game;
	cabeca->prox = NULL;
	return cabeca;
}

int insere_comeco(LIST *comeco, GAME *g)
{
	LIST *new_node = NULL;
	new_node = (LIST *) malloc(sizeof(LIST));
	if(new_node == NULL)
	{
		printf("NAO FOI POSSIVEL ALOCAR UM NO!\n");
		return -1;
	}
	new_node->g = g;
	new_node->prox = comeco->prox;
	comeco->prox = new_node;
	return 0;
}

void imp_lista(LIST *comeco)
{
	char esc;
	LIST *pt_list = NULL;
	for(pt_list = comeco; pt_list != NULL; pt_list = pt_list->prox)
	{
		printf("%-5d", pt_list->g->id);
        printf("%-30s", pt_list->g->nome);
        printf("%-15s\n", pt_list->g->genero);
	}
}

void exclui_lista(LIST *comeco)
{
	LIST *pt_slow = NULL, *pt_fast = NULL;
	for(pt_slow = comeco, pt_fast = comeco->prox; pt_fast != NULL; pt_slow = pt_fast, pt_fast = pt_fast->prox)
	{
		free(pt_slow);
	}
	free(pt_fast);
}

void insere_fim(LIST *comeco, GAME *g)
{
	LIST *ptr_list;
	for(ptr_list = comeco; ptr_list->prox != NULL; ptr_list = ptr_list->prox);
	ptr_list->prox = (LIST *) malloc(sizeof(LIST));
	ptr_list->prox->g = g;
	ptr_list->prox->prox = NULL;
}
