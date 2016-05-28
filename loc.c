#include "inc/loc.h"

#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls");
#endif

#ifdef __linux__
    #define CLEAR_SCREEN() system("clear");
#endif

int create_database(char *nome_arquivo) // Cria o arquivo
{
    FILE *arq = fopen(nome_arquivo, "a+b");
    if(arq != NULL)
    {
        fclose(arq);
        return 0;
    }
    else
    {
        printf("NAO FOI POSSIVEL CRIAR O ARQUIVO DE DADOS\n");
        return -1;
    }
}

FILE *abrir_arquivo(char *nome_arquivo, char *modo) // Abre o arquivo
{
    FILE *arq = fopen(nome_arquivo, "rb"); // Abre o arquivo em modo leitura somente, para verificar se o arquivo existe.
    if(arq != NULL) // Se o arquivo existir
    {
        fclose(arq); // Fecha o arquivo no modo somente leitura
        arq = fopen(nome_arquivo, modo); // Abri novamente o arquivo para o modo especificado na função
    }
    else // Senão
    {
        if(create_database(nome_arquivo)) // Checa se o arquivo foi criado
            abrir_arquivo(nome_arquivo, modo); // E abre ele com o modo especificado na função
        else // Se não foi criado ele retornará NULL
            arq = NULL;
    }
    return arq;
}

void menu()
{
    int escolha = 0;
    while(escolha >= 0)
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
                printf("edit game\n");
                // edit_game();
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

void insert_game()
{
    FILE *arquivo = abrir_arquivo("locadora.dtb", "a+b");
    GAME jogo, tmp_jogo;
    jogo.id = return_last_id() + 1;
    CLEAR_SCREEN();
    printf("\nDigite o nome do jogo: ");
    scanf(" %[^\n]s", jogo.nome);
    printf("\nDigite o genero do jogo: ");
    scanf(" %[^\n]s", jogo.genero);
}

void show_games()
{
    int times = 0, i = 0;
    GAME *jogo = load_into_mem(-1, &times);
    printf("%d\n", times);
    printf("%-5s %-30s %-15s\n","ID:","NOME:","GENERO:");
    for(i = 0; i < times; i++)
    {
        printf("%-5d", jogo[i].id);
        printf("%-30s", jogo[i].nome);
        printf("%-15s\n", jogo[i].genero);
    }
    free(jogo);

    printf("\nDeseja voltar ao menu? [s/n]: ");
    scanf("%s", escolha);

    if( (strcmp(escolha, "s") == 0) || (strcmp(escolha, "S") == 0) )
    {
        menu();
    }
}

GAME *load_into_mem(int amount, int *times_req)
{
    FILE *arquivo = abrir_arquivo("locadora.dtb", "rb");
    void *tmp_ptr = NULL;
    GAME *buffer_mem = NULL;
    if(amount > 0)
    {
        buffer_mem = (GAME *) malloc(sizeof(GAME) * amount);
        fread(buffer_mem, sizeof(GAME), amount, arquivo);
    }
    else
    {
        fseek(arquivo, 0, SEEK_END);
        long f_siz = ftell(arquivo);
        tmp_ptr = malloc(f_siz);
        rewind(arquivo);
        *times_req = f_siz / (sizeof(GAME));
        buffer_mem = (GAME *) tmp_ptr;
        fread(tmp_ptr, f_siz, 1, arquivo);
    }
    fclose(arquivo);
    return buffer_mem;
}
