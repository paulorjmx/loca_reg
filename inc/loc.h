#ifndef LOC_H
    #define LOC_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <limits.h>
    typedef struct game
    {
        unsigned int id;
        char nome[71], genero[31];
    } GAME;

    // Variáveis globais
    GAME *g_mem;
    int qt_games;

    void menu(); // Menu do programa
    void insert_game(); // Função para inserir um jogo na estrutura g_mem;
    void edit_game(); // Função que edita um jogo na estrutura g_mem;
    void delete_game(); // Função que delete um jogo da estrutura g_mem;
    void show_games(int orderby); // Função para mostrar todos os jogos na estrutura 'g_mem' ordenando, se estiver em 1, segundo seu parâmetro 'orderby';
    int print_question(char *question); // Função que imprime uma pergunta para serem utilizadas no final de cada função;
    int return_last_id(); // Retorna o último id do último jogo cadastrado;
    GAME *load_into_mem(int amount, int *times_req); // Recupera um quantidade 'amount' de dados do arquivo apontado por 'arq'. Se 'amount' for < 0, então será lido o arquivo inteiro;
    FILE *abrir_arquivo(const char *nome_arquivo, char *modo); // Abre o arquivo com o nome 'nome_arquivo' em modo 'modo';
    int salva_alteracoes(const char *nome_arquivo, GAME *data_tob_write); // Função que salva as alterações;
    int binary_search(unsigned int id); // Retorna o índice do vetor g_mem correspondente a 'id';
	void mergesort(GAME *vetor_game, int left, int right, void (*merge_func)(GAME *v, int p, int q, int r)); // Função mergesort para ordenação dos generos e nome em ordem alfabética;
	void merge_byid(GAME *vetor_game, int left, int middle, int right); // Função que compõe os subvetores particionados pelo 'mergesort' de acordo com o id;
    void merge_bygen(GAME *v, int p, int q, int r); // Função que compões os subvetores particionados pelo 'mergesort' de acordo com o gênero;
    void merge_byname(GAME *v, int p, int q, int r); // Função que compões os subvetores particionados pelo 'mergesort' de acordo com o nome;
#endif
