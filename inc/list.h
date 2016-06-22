#ifndef LIST_H
    #define LIST_H
    #include "loc.h"

	typedef struct list
	{
		GAME *g;
		struct list *prox;
	}LIST;

	LIST *cria_lista(GAME *g); // Função que cria a lista;
	int insere_comeco(LIST *comeco, GAME *g); // Função para inserir um nó no começo;
	void exclui_lista(LIST *comeco); // Função que exclui a lista passado o começo dela;
    void imp_lista(LIST *comeco); // Função para imprimir todos os nós da lista;
	void insere_fim(LIST *comeco, GAME *g); // Função para inserir um nó no fim;
#endif
