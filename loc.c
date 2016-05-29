#include "inc/loc.h"

#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls");
#endif

#ifdef __linux__
    #define CLEAR_SCREEN() system("clear");
#endif

FILE *abrir_arquivo(const char *nome_arquivo, char *modo) // Abre o arquivo
{
    FILE *arq;
    if(access(nome_arquivo, F_OK) != -1) // Checa se o arquivo existe
    {
        arq = fopen(nome_arquivo, modo); // Abre o arquivo para o modo especificado na função
    }
    else // Senão
    {
        arq = fopen(nome_arquivo, "w+b"); // Cria o arquivo
        fclose(arq);
        arq = fopen(nome_arquivo, modo); // Abre o arquivo para o modo especificado na função
    }
    return arq;
}

void menu()
{
    int escolha = 0;
    while(escolha > -1)
    {
        CLEAR_SCREEN();
        printf("####################################################\n");
        printf("####################################################\n");
        printf("# \t\t\t\t\t\t   #");
        printf("\n#\t\tEscolha uma opcao \t\t   #\n# \t\t\t\t\t\t   #\n");
        printf("####################################################\n");
        printf("####################################################\n");

        printf("\n\t\t[1] Inserir Jogo");
        printf("\n\t\t[2] Editar Jogo");
        printf("\n\t\t[3] Deletar Jogo");
        printf("\n\t\t[4] Consultar Estoque");
        printf("\n\t\t[5] Sair");
        printf("\n\t\t-> ");
        scanf("%d", &escolha);

        switch(escolha)
        {
            case 1:
                insert_game();
                escolha = -1;
                break;

            case 2:
                edit_game();
                escolha = -1;
                break;

            case 3:
                printf("delete game\n");
                // delete_game();
                escolha = -1;
                break;

            case 4:
                show_games();
                escolha = -1;
                break;

            case 5:
                // quick_sort(g_mem);
                if(salva_alteracoes("locadora.dtb", g_mem) != 0)
                    printf("NAO FOI POSSIVEL SALVAR AS ALTERACOES\n");
                free(g_mem);
                escolha = -1;
                break;

            default:
                printf("Digite uma opcao valida!\n");
                break;
        }
    }
}

int return_last_id()
{
    FILE *arquivo = NULL;
    GAME jogo;
    arquivo = abrir_arquivo("locadora.dtb", "rb");
    fseek(arquivo, 0, SEEK_END); // ANDA ATÉ A POSIÇÃO N-1 BYTES
    long size = ftell(arquivo);
    rewind(arquivo);
    if(size > 0)
    {
        fread(&jogo, sizeof(GAME), 1, arquivo); // PEGA O ÚLTIMO BLOCO DO TAMANHO DE "GAME"
    }
    else
    {
        jogo.id = 0;
    }
    fclose(arquivo);
    return jogo.id;
}

void edit_game()
{

}

void insert_game()
{
    CLEAR_SCREEN();
    if(qt_games != 0)
    {
        qt_games += 1;
        g_mem = (GAME *) realloc(g_mem, sizeof(GAME) * qt_games);
        g_mem[qt_games-1].id = qt_games;
        printf("\nDigite o nome do jogo: ");
        scanf(" %[^\n]s", g_mem[qt_games-1].nome);
        printf("\nDigite o genero do jogo: ");
        scanf(" %[^\n]s", g_mem[qt_games-1].genero);
    }
    else
    {
        qt_games += 1;
        g_mem = (GAME *) malloc(sizeof(GAME) * qt_games);
        g_mem[0].id = qt_games;
        printf("\nDigite o nome do jogo: ");
        scanf(" %[^\n]s", g_mem[0].nome);
        printf("\nDigite o genero do jogo: ");
        scanf(" %[^\n]s", g_mem[0].genero);
    }

    printf("\nDeseja inserir mais algum jogo? [s/n]: ");
    scanf(" %c", &escolha);

    if( escolha == 's' || escolha == 'S' )
    {
        CLEAR_SCREEN();
        insert_game();
    }
    else
    {
        menu();
    }
}

void show_games()
{
    int i = 0;
    printf("%-5s %-30s %-15s\n","ID:","NOME:","GENERO:");
    for(i = 0; i < qt_games; i++)
    {
        printf("%-5d", g_mem[i].id);
        printf("%-30s", g_mem[i].nome);
        printf("%-15s\n", g_mem[i].genero);
    }

    printf("\nDeseja voltar ao menu? [s/n]: ");
    scanf(" %c", &escolha);

    if( escolha == 's' || escolha == 'S' )
    {
        menu();
    }
}

GAME *load_into_mem(int amount, int *times_req)
{
    FILE *arquivo = abrir_arquivo("locadora.dtb", "r+b");
    void *tmp_ptr = NULL;
    GAME *buffer_mem = NULL;
    fseek(arquivo, 0, SEEK_END);
    long f_siz = ftell(arquivo);
    printf("Size of file: %li\n", f_siz);
    if(f_siz != 0)
    {
        if(amount > 0)
        {
            rewind(arquivo);
            buffer_mem = (GAME *) malloc(sizeof(GAME) * amount);
            fread(buffer_mem, sizeof(GAME), amount, arquivo);
        }
        else
        {

            tmp_ptr = malloc(f_siz);
            rewind(arquivo);
            (*times_req) = f_siz / (sizeof(GAME));
            buffer_mem = (GAME *) tmp_ptr;
            fread(tmp_ptr, f_siz, 1, arquivo);
        }
    }
    else
    {
        (*times_req) = 0;
    }
    fclose(arquivo);
    return buffer_mem;
}

int salva_alteracoes(const char *nome_arquivo, GAME *data_tob_write)
{
    size_t bytes_writed;
    FILE *arquivo = abrir_arquivo("locadora.dtb", "wb");
    bytes_writed = fwrite(data_tob_write, qt_games, sizeof(GAME), arquivo);
    if(bytes_writed > 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
