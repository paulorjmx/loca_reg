#ifndef LOC_H
    #define LOC_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    typedef struct game
    {
        unsigned int id;
        char nome[71], genero[31];
    } GAME;


	// ponteiro que irá apontar para os genêros dos jogos seguindo a ordem:
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
    GAME *g_mem;
    int qt_games;

    void menu(); // Menu do programa
    void insert_game(); // Função para inserir um jogo na estrutura g_mem;
    void edit_game(); // Função que edita um jogo na estrutura g_mem;
    void delete_game();
    void show_games(); // Função para mostrar todos os jogos na estrutura g_mem;
    int print_question(char *question);
    int return_last_id(); // Retorna o último id do último jogo cadastrado
    GAME *load_into_mem(int amount, int *times_req); // Recupera um quantidade 'amount' de dados do arquivo apontado por 'arq'. Se 'amount' for < 0, então será lido o arquivo inteiro.
    FILE *abrir_arquivo(const char *nome_arquivo, char *modo); // Abre o arquivo com o nome 'nome_arquivo' em modo 'modo'
    int salva_alteracoes(const char *nome_arquivo, GAME *data_tob_write);
    int binary_search(unsigned int id); // Retorna o índice do vetor g_mem correspondente a 'id'
#endif
