#ifndef LOC_H
    #define LOC_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    typedef struct game
    {
        int id;
        char nome[71], genero[31];
        bool deletable;
    } GAME;
    typedef struct header
    {
        long signature;
        unsigned int version;

    } HEADER;
    char escolha[2];
    void menu();
    void init_game(GAME *g_emp);
    void init_header(HEADER *h_empty);
    void inserir_game();
    void editar_game();
    void deletar_game();
    void mostra_dados();
    FILE *abrir_arquivo(char *nome_arquivo, char *modo);
#endif
