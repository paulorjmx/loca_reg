#include "inc/loc.h"

#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls");
#endif

#ifdef __linux__
    #define CLEAR_SCREEN() system("clear");
#endif

void init_game(GAME *j_emp)
{
    j_emp->id = 0;
    j_emp->deletable = false;
}

void init_header(HEADER *h_empty)
{
    h_empty->signature = 0x445442;
    h_empty->version = 0x001;
}

bool file_exists(char *nome_arquivo)
{
    FILE *arquivo = abrir_arquivo(nome_arquivo, "rb");
    if(arquivo == NULL)
    {
        fclose(arquivo);
        return false;
    }
    else
    {
        fclose(arquivo);
        return true;
    }
}

FILE *abrir_arquivo(char *nome_arquivo, char *modo)
{
    FILE *arq = fopen(nome_arquivo, modo);
    if(arq == NULL)
    {
        printf("\nNAO FOI POSSIVEL ABRIR O ARQUIVO!\n");
        return NULL;
    }
    else
    {
        return arq;
    }
}

void menu()
{
    int escolha = 0;

    CLEAR_SCREEN();
    printf("####################################################\n");
    printf("####################################################\n");
    printf("# \t\t\t\t\t\t   #");
    printf("\n#\t\tEscolha uma opcao \t\t   #\n# \t\t\t\t\t\t   #\n");
    printf("####################################################\n");
    printf("####################################################\n");

    printf("\n[1] Inserir Game");
    printf("\n[2] Editar Game");
    printf("\n[3] Deletar Game");
    printf("\n[4] Consultar Estoque");
    printf("\n[5] Sair");

    printf("\n\n->");
    scanf("%d", &escolha);

    if(escolha == 1)
    {
        inserir_game();
    }
    else
    {
        if(escolha == 2)
        {
            editar_game();
        }
        else
        {
            if(escolha == 3)
            {
                deletar_game();
            }
            else
            {
                if(escolha == 4)
                {
                    mostra_dados();
                }
                else
                {
                    if(escolha == 5)
                    {
                        printf("Adiós!");
                        return;
                    }
                    else
                    {
                        printf("\nEscolha uma opcao valida!");
                        menu();
                    }
                }
            }
        }
    }
}

void inserir_game() // INSERE DADOS NO ARQUIVO BINÁRIO.
{
    FILE *arquivo = NULL;
    GAME jogo, tmp_jogo;

    init_game(&jogo);
    init_game(&tmp_jogo);
    arquivo = abrir_arquivo("locadora.dtb", "a+b");

    rewind(arquivo);
    fseek(arquivo, (-1 * sizeof(GAME)), SEEK_END); // ANDA ATÉ A POSIÇÃO N-1 BYTES
    fread(&jogo, sizeof(GAME), 1, arquivo); // PEGA O ÚLTIMO BLOCO DO TAMANHO DE "GAME"
    rewind(arquivo); // VOLTA O INDICADOR DA POSIÇÃO DO ARQUIVO NO COMEÇO

    // FUNCAO AUTO INCREMENT
    if(jogo.id == 0)
    {
        jogo.id = 1; // SE NÃO HOUVER UM "GAME" CADASTRADO ADICIONA O PRIMEIRO ID COM O VALOR DE "1"
    }
    else
    {
        jogo.id += 1; // CASO CONTRÁRIO ADICIONA +1 NO ID DO "GAME" QUE SERÁ CADASTRADO
    }

    CLEAR_SCREEN();
    printf("\nDigite o nome do jogo: ");
    scanf(" %[^\n]s", jogo.nome);
    printf("\nDigite o genero do jogo: ");
    scanf(" %[^\n]s", jogo.genero);

    while(1)
    {
        fread(&tmp_jogo, sizeof(GAME), 1, arquivo);
        if(feof(arquivo) != 0)
        {
            rewind(arquivo);
            fclose(arquivo);
            arquivo = abrir_arquivo("locadora.dtb", "a+b");
            break;
        }
        else
        {
            if(tmp_jogo.deletable == true)
            {
                fclose(arquivo);
                arquivo = abrir_arquivo("locadora.dtb", "r+b");
                jogo.id = tmp_jogo.id;
                fseek(arquivo, (-1 * sizeof(GAME)), SEEK_CUR);
                break;
            }
            else
            {
                continue;
            }
        }
    }

    size_t result = fwrite(&jogo, sizeof(GAME), 1, arquivo);
    if(result == 1)
    {
        CLEAR_SCREEN();
        printf("\nDADOS INSERIDOS COM SUCESSO!");
        printf("\nDeseja inserir mais dados? [s/n]: ");
        scanf("%s", escolha);

        if( (strcmp(escolha, "s") == 0) || (strcmp(escolha, "S") == 0) )
        {
            fclose(arquivo);
            CLEAR_SCREEN();
            inserir_game();
        }
        else
        {
            fclose(arquivo);
            CLEAR_SCREEN();
            menu();
        }
    }
    else
    {
        fclose(arquivo);
        CLEAR_SCREEN();
        printf("\nOCORREU UM ERRO AO TENTAR INSERIR OS DADOS!\n");
        menu();
    }
}

void editar_game()
{
    int escolha_id = 0;
    GAME jogo, tmp_jogo;
    FILE *arquivo = NULL;

    if(file_exists("locadora.dtb") == false)
    {
        printf("\nO ARQUIVO NAO EXISTE!\n");
        printf("\nDESEJA CRIAR O ARQUIVO? [s/n]: \n");
        scanf("%s", escolha);
        if( (strcmp(escolha, "s") == 0) || (strcmp(escolha, "S") == 0) )
        {
            arquivo = abrir_arquivo("locadora.dtb", "r+b");
            fclose(arquivo);
            menu();
        }
        return;
    }
    else
    {
        arquivo = abrir_arquivo("locadora.dtb", "r+b");
    }

    mostra_dados();

    rewind(arquivo);
    printf("\nDigite o ID que deseja editar: ");
    scanf("%d", &escolha_id);

    while(1)
    {
        fread(&jogo, sizeof(GAME), 1, arquivo);
        if(feof(arquivo) == 0)
        {
            if(escolha_id == jogo.id )
            {
                tmp_jogo = jogo;
                fseek(arquivo, (-1 * sizeof(GAME)), SEEK_CUR); // ANDA ATE A POSICAO INICIAL DO DADO ESCOLHIDO
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            printf("\nO ID NAO FOI ENCONTRADO!\n");
            printf("\nDESEJA VOLTAR AO MENU PRINCIPAL? [s/n]: \n");
            scanf("%s", escolha);

            if( (strcmp(escolha, "s") == 0) || (strcmp(escolha, "S") == 0) )
            {
                menu();
            }
            else
            {
                return;
            }
        }
    }

    CLEAR_SCREEN();
    printf("####################################################\n");
    printf("####################################################\n");
    printf("# \t\t\t\t\t\t   #");
    printf("\n#\t\tDADOS DO ID ESCOLHIDO \t\t   #\n# \t\t\t\t\t\t   #\n");
    printf("####################################################\n");
    printf("####################################################\n");

    printf("\n[1] NOME: %s", tmp_jogo.nome);
    printf("\n[2] GENERO: %s", tmp_jogo.genero);
    printf("\nQUAL DADO DESEJA EDITAR?\n");
    printf("-> ");
    scanf("%d", &escolha_id);

    if(escolha_id == 1)
    {
        CLEAR_SCREEN();
        printf("\nDigite o novo nome do jogo: ");
        scanf(" %[^\n]s", tmp_jogo.nome);
        fwrite(&tmp_jogo, sizeof(GAME), 1, arquivo);
    }
    else
    {
        CLEAR_SCREEN();
        printf("\nDigite o novo genero do jogo: ");
        scanf(" %[^\n]s", tmp_jogo.genero);
        fwrite(&tmp_jogo, sizeof(GAME), 1, arquivo);
    }

    fclose(arquivo);
    printf("\nDESEJA EDITAR MAIS ALGUM REGISTRO? [s/n]: \n");
    scanf("%s", escolha);

    if( (strcmp(escolha, "s") == 0) || (strcmp(escolha, "S") == 0) )
    {
        CLEAR_SCREEN();
        editar_game();
    }
    else
    {
        menu();
    }
}

void mostra_dados()
{
    FILE *arquivo;
    GAME jogo;
    arquivo = abrir_arquivo("locadora.dtb", "rb");
    printf("%-5s %-30s %-15s\n","ID:","NOME:","GENERO:");
    while(1)
    {
        fread(&jogo, sizeof(GAME), 1, arquivo);
        if(feof(arquivo) != 0)
        {
            break;
        }
        else
        {
            if(jogo.deletable == false)
            {
                printf("%-5d", jogo.id);
                printf("%-30s", jogo.nome);
                printf("%-15s\n", jogo.genero);
            }
            else
            {
                continue;
            }
        }
    }
    fclose(arquivo);
}

void deletar_game()
{
    int escolha_id = 0;
    FILE *arquivo;
    GAME jogo;
    if(file_exists("locadora.dtb") == false)
    {
        printf("\nO ARQUIVO NAO EXISTE!\n");
        printf("\nDESEJA CRIAR O ARQUIVO? [s/n]: \n");
        scanf("%s", escolha);
        if( (strcmp(escolha, "s") == 0) || (strcmp(escolha, "S") == 0) )
        {
            arquivo = abrir_arquivo("locadora.dtb", "r+b");
            fclose(arquivo);
            menu();
        }
        return;
    }
    else
    {
        arquivo = abrir_arquivo("locadora.dtb", "r+b");
        init_game(&jogo);
        mostra_dados();

        rewind(arquivo);
        printf("\nDigite o ID que deseja deletar: ");
        scanf("%d", &escolha_id);

        while(1)
        {
            fread(&jogo, sizeof(GAME), 1, arquivo);
            if(feof(arquivo) == 0)
            {
                if(jogo.id == escolha_id)
                {
                    jogo.deletable = true;
                    break;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                printf("\nO ID NAO FOI ENCONTRADO!\n");
                printf("\nDESEJA VOLTAR AO MENU PRINCIPAL? [s/n]: \n");
                scanf("%s", escolha);

                if( (strcmp(escolha, "s") == 0) || (strcmp(escolha, "S") == 0) )
                {
                    menu();
                }
                else
                {
                    return;
                }
            }
        }

        fseek(arquivo, (-1 * sizeof(GAME)), SEEK_CUR);
        size_t result = fwrite(&jogo, sizeof(GAME), 1, arquivo);
        if(result == 1)
        {
            CLEAR_SCREEN();
            printf("\nJOGO DELETADO COM SUCESSO!");
            printf("\nDeseja deletar mais algum jogo? [s/n]: ");
            scanf("%s", escolha);

            if( (strcmp(escolha, "s") == 0) || (strcmp(escolha, "S") == 0) )
            {
                fclose(arquivo);
                CLEAR_SCREEN();
                deletar_game();
            }
            else
            {
                fclose(arquivo);
                CLEAR_SCREEN();
                menu();
            }
        }
        else
        {
            fclose(arquivo);
            CLEAR_SCREEN();
            printf("\nOCORREU UM ERRO AO TENTAR DELETAR O JOGO!\n");
            menu();
        }
    }
}
