#ifndef LOC_H
    #define LOC_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    typedef struct game
    {
        int id;
        char nome[71], genero[31];
        char deletable[1]; // Será deletável se este campo está com o valor < 0, caso contrário ainda existirá.
    } GAME;


	VETOR_LISTA **generos; // ponteiro que irá apontar para os genêros dos jogos seguindo a ordem:
	/*
		0 = FPS;
		1 = HACK N SLASH;
		2 = ACAO;
		.
		.
		.
		.
		n = GENERO
	*/

	// pesquisa sera feita por genero ou por nome;
	// implementar uma lista contendo jogos do gênero escolhido e nome em ordem alfabética ( de acordo pela letra inicial);
	// algoritmo desfragmentador; (merge sort, ou quick sort)


    // Variáveis globais
    char escolha[2];
    GAME *g_mem = NULL;
    int qt_games = 0;

    void insert_game();
    void show_games();
    int return_last_id(); // Retorna o último id do último jogo cadastrado
    GAME *load_into_mem(int amount, int *times_req); // Recupera um quantidade 'amount' de dados do arquivo apontado por 'arq'. Se 'amount' for < 0, então será lido o arquivo inteiro.
    FILE *abrir_arquivo(char *nome_arquivo, char *modo); // Abre o arquivo com o nome 'nome_arquivo' em modo 'modo'
    int create_database(char *nome_arquivo); // Cria o arquivo com o nome 'nome_arquivo' e o modo 'modo' como abrirá este arquivo
#endif
