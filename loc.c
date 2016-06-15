#include "inc/loc.h"
#include "inc/list.h"

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
		printf("\n\t\t[5] Testar MergeSortByID");
        printf("\n\t\t[6] Sair");
        printf("\n\t\t-> ");
        scanf("%d", &escolha);

        switch(escolha)
        {
            case 1:
                insert_game();
                while(print_question("Deseja inserir mais algum jogo? [s/n]: ") == 0)
                {
                    insert_game();
                }
                break;

            case 2:
                edit_game();
				while(print_question("Deseja editar mais algum jogo? [s/n]: ") == 0)
				{
					edit_game();
				}
                break;

            case 3:
                delete_game();
                while(print_question("Deseja deletar mais algum jogo? [s/n]: ") == 0)
                {
                    delete_game();
                }
                break;

            case 4:
                show_games();
                while(print_question("Deseja mostrar os jogos cadastrados novamente? [s/n]: ") == 0)
                {
                    show_games();
                }
                break;

			case 5:

				break;

            case 6:
                mergesort(g_mem, 0, (qt_games-1), &merge_byid); // Ordena o vetor g_mem levando em consideração o campo id;
                if(salva_alteracoes("locadora.dtb", g_mem) != 0) // Tenta salvar as alterações no arquivo;
                    printf("NAO FOI POSSIVEL SALVAR AS ALTERACOES\n");
                free(g_mem); // libera o vetor para a estrutura GAME;
                escolha = -1;
                break;

            default:
                printf("Digite uma opcao valida!\n");
                break;
        }
    }
}

int print_question(char *question)
{
    char escolha;
    int answer;
    printf("\n%s", question);
    scanf(" %c", &escolha);
    if(escolha == 's' || escolha == 'S')
    {
        answer = 0;
    }
    else
    {
        answer = 1;
    }
    return answer;
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
	char decision;
	unsigned int choice, indice;
    CLEAR_SCREEN();
    show_games();
    printf("\nDigite ID do jogo que deseja editar: ");
    scanf("%u", &choice);
    indice = binary_search(choice);
    printf("%u\t%s\t%s\n", g_mem[indice].id, g_mem[indice].nome, g_mem[indice].genero);
	printf("Tem certeza que voce quer editar esse jogo? [s/n]: ");
    scanf(" %c", &decision);
    if(decision == 's' || decision == 'S')
	{
        printf("\nDigite o novo nome do jogo: ");
        scanf(" %[^\n]s", g_mem[indice].nome);
        printf("\nDigite o novo genero do jogo: ");
        scanf(" %[^\n]s", g_mem[indice].genero);
    }
}

void delete_game()
{
    GAME *g_new = NULL;
    int indice = 0, i = 0;
    unsigned int escolha;
    CLEAR_SCREEN();
    show_games();
    printf("\nDigite o ID do jogo que voce deseja deletar: ");
    scanf("%u", &escolha);
    indice = binary_search(escolha);
    if(indice < 0)
    {
        printf("\nO jogo nao foi encontrado!\n");
    }
    else
    {
        CLEAR_SCREEN();
        printf("####################################################\n");
        printf("####################################################\n");
        printf("# \t\t\t\t\t\t   #");
        printf("\n#\t\tDados do jogo encontrado \t   #\n# \t\t\t\t\t\t   #\n");
        printf("####################################################\n");
        printf("####################################################\n");
        printf("%-5s %-30s %-15s\n","ID:","NOME:","GENERO:");
        printf("%-5d", g_mem[indice].id);
        printf("%-30s", g_mem[indice].nome);
        printf("%-15s\n", g_mem[indice].genero);
        if(print_question("Tem certeza que deseja deletar o jogo? [s/n]: ") == 0)
        {
            if(escolha == qt_games)
            {
                g_mem = (GAME *) realloc(g_mem, sizeof(GAME) * (qt_games - 1));
            }
            else
            {
                g_new =  (GAME *) malloc(sizeof(GAME) * (qt_games - 1));
                if(g_new != NULL)
                {
                    for(i = 0; i < (qt_games - 1); i++)
                    {
                        if(i >= indice)
                        {
							g_new[i] = g_mem[i+1];
                        }
                        else
                        {
                            g_new[i] = g_mem[i];
                        }
                    }
                    free(g_mem);
                    g_mem = g_new;
                }
                else
                {
                    printf("NAO FOI POSSIVEL ALOCAR MEMORIA\n");
                }
            }
			qt_games -= 1;
        }
    }
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
}

void show_games()
{
    int i = 0;
    // mergesort(g_mem, 0, (qt_games - 1), &merge_bygen);
    printf("%-5s %-30s %-15s\n","ID:","NOME:","GENERO:");
    for(i = 0; i < qt_games; i++)
    {
        printf("%-5d", g_mem[i].id);
        printf("%-30s", g_mem[i].nome);
        printf("%-15s\n", g_mem[i].genero);
    }
}

GAME *load_into_mem(int amount, int *times_req)
{
    FILE *arquivo = abrir_arquivo("locadora.dtb", "r+b");
    void *tmp_ptr = NULL;
    GAME *buffer_mem = NULL;
    fseek(arquivo, 0, SEEK_END);
    long f_siz = ftell(arquivo);
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

int binary_search(unsigned int id)
{
    int limite_superior = qt_games-1, limite_inferior = 0, meio = 0, indice = -1;
    while(limite_inferior <= limite_superior)
    {
        meio = (limite_superior + limite_inferior) / 2;
        if(g_mem[meio].id == id)
        {
            indice = meio;
            break;
        }
        else
        {
            if(g_mem[meio].id > id)
            {
                limite_superior = meio - 1;
            }
            else
            {
                if(g_mem[meio].id < id)
                {
                    limite_inferior = meio + 1;
                }
            }
        }
    }
    return indice;
}

void mergesort(GAME *vetor_game, int left, int right, void (*merge_func)(GAME *v, int p, int q, int r)){//breaks the ids into 3 arrays
  //g_mem = all IDs, qt_games = amount of ids
  int middle;

  if(left < right){
    middle = (left+right)/2; //finds the halfway point
    mergesort(vetor_game, left, middle, merge_func);//partitions the left side
    mergesort(vetor_game, middle+1, right, merge_func);//does it with the right
    merge_func(vetor_game, left, middle, right);//merger
  }
}

void merge_bygen(GAME *v, int p, int q, int r)
{
    GAME *w = NULL;
    int n1, n2, i, j, k;
    n1 = (q - p) + 1;
    n2 = r - q;
    w = (GAME *) malloc(sizeof(GAME) * ((n1 + 1) + (n2 + 1)));
    for(i = p, j = 0; i <= q; i++, j++)
    {
        w[j] = v[i];
    }
    for(i = q + 1, j = n1 + 1; i <= r; i++, j++)
    {
        w[j] = v[i];
    }
    w[n1].genero[0] = SCHAR_MAX;
    w[n1+n2+1].genero[0] = SCHAR_MAX;
    for(k = p, i = 0, j = (n1 +1); k <= r; k++)
    {
        if(strcmp(w[i].genero, w[j].genero) <= 0)
        {
            v[k] = w[i++];
        }
        else
        {
            v[k] = w[j++];
        }
    }
    free(w);
}

void merge_byid(GAME *vetor_game, int left, int middle, int right){
  int l, r;
  int i, j, k; //indexes

  l = middle-left+1; //size of left subarray;
  r = right-middle; //size of right array;
  GAME left_arr[l+1], right_arr[r+1];

  for(i = left, j = 0; i <= middle; i++, j++)  left_arr[j] = vetor_game[i];//subarray copies main arr
  for(i = middle + 1, j = 0; i <= right; i++, j++) right_arr[j] = vetor_game[i];

  left_arr[l].id = INT_MAX;
  right_arr[r].id = INT_MAX;

  for(k = left, i = 0, j = 0; k <= right; k++){//main array takes sorted values
      if(left_arr[i].id <= right_arr[j].id){
          vetor_game[k] = left_arr[i];
          i++;
      }else{
          vetor_game[k] = right_arr[j];
          j++;
      }
  }
}
