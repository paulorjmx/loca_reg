#include "inc/list.h"

HEAD_LIST *cria_lista(char *genero)
{
	HEAD_LIST *cabeca = NULL;
	cabeca = (HEAD_LIST *) malloc(sizeof(HEAD_LIST));
	if(cabeca == NULL)
	{
		printf("NAO FOI POSSIVEL ALOCA A CABECA DA LISTA!\n");
		return NULL;
	}
	cabeca->genero = (*genero);
	cabeca->ptr_list = NULL;
	return cabeca;
}

int insere_comeco(HEAD_LIST *comeco, GAME *g)
{
	LIST *new_node = NULL;
	new_node = (LIST *) malloc(sizeof(LIST));
	if(new_node == NULL)
	{
		printf("NAO FOI POSSIVEL ALOCAR UM NO!\n");
		return -1;
	}
	new_node->prox = comeco->ptr_list;
	comeco->ptr_list = new_node;
	return 0;
}

void exclui_lista(HEAD_LIST *comeco)
{
	LIST *aux = NULL, *aux2 = NULL;
	for(aux = comeco->ptr_list; aux != NULL; )
	{
		aux2 = aux->prox;
		free(aux);
		aux = aux2;
	}
	free(comeco);
}

void insere_fim(HEAD_LIST *comeco)
{
	
}