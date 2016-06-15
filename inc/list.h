#ifndef LIST_H
    #define LIST_H
    #include "loc.h"

	typedef struct list
	{
		GAME *g;
		struct list *prox;
	}LIST;

    typedef struct head_list
    {
		char *genero;
        LIST *ptr_list;
    } HEAD_LIST;


	HEAD_LIST *cria_lista(char *genero); // Função que cria a lista;
	int insere_comeco(HEAD_LIST *comeco, GAME *g); // Função para inserir um nó no começo;
	void exclui_lista(HEAD_LIST *comeco); // Função que exclui a lista passado o começo dela;
    void imp_lista(HEAD_LIST *comeco); // Função para imprimir todos os nós da lista
	void insere_fim(HEAD_LIST *comeco); // Função para inserir um nó no começo;
#endif
