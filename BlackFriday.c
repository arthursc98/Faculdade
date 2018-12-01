/*
 * BlackFriday.c
 *
 * Sistema que armazena cadastros de produtos,lojas e preços de determinado produto em uma determinada loja
 *
 * Rodrigo Suarez Moreira (Ciência da Computação)
 * Beatriz Jonas Justino (Sistema da Informação)
 * Arthur Silveira Chaves (Sistema da Informação)
 *
 * Disciplina: Introdução a Computação-II
 *
 * 29/11/2018
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição dos Nomes dos Arquivos
#define ARQ_PROD "produtos.bin"
#define ARQ_LOJA "lojas.bin"
#define ARQ_PRECO "precos.bin"

// Definição das Estruturas
typedef struct
{
    int cod;
    char descricao[51];
} tproduto;

typedef struct
{
    int cod;
    char nome[41];
    char site[81];
} tloja;

typedef struct
{
    int cod_produto;
    int cod_loja;
    float preco;
} tpreco;

// Definição das funções
void ordena_prod(tproduto *, int);
void cadastrar_prod(void);
void alterar_prod(void);
void lista_prod(void);
void ordena_loja(tloja *, int);
void cadastrar_loja(void);
void lista_loja(void);
void cadastrar_preco(void);
void ordena_preco(tpreco *, int, tloja *);
void cadastrar_preco(void);
void lista_preco(void);
void consulta_prod(void);
void conta_loja(tloja *,int *,int *,int *,int *,int *,int *,int);
void imprime_espaco(int, int);
void conta_preco(tloja *,tproduto *,tpreco *,int *,int *,int *,int *,int *,int *, int, int, int);
void conta_produto(tproduto *,int *,int *,int *,int *,int );
void imprime_titulo(char *, int);
void imprime_linha(int);
int conta_num(float);
void conta_consulta(int, int *,int *);
void clean_stdin(void);
void pause(void);
void clearscr(void);
void imprime_erro(char *);
void imprime_saida(void);

int main()
{
    int n;
    while(1)
    {
        clearscr();
        fprintf(stdout, "+===================================+\n");
        fprintf(stdout, "| mmm   mmm  eeee  nnn   nn  uu  uu |\n");
        fprintf(stdout, "| mm m m mm  ee    nnnn  nn  uu  uu |\n");
        fprintf(stdout, "| mm  m  mm  eeee  nn nn nn  uu  uu |\n");
        fprintf(stdout, "| mm     mm  ee    nn  nnnn  uu  uu |\n");
        fprintf(stdout, "| mm     mm  eeee  nn   nnn  uuuuuu |\n");
        fprintf(stdout, "+===================================+\n");
        fprintf(stdout, "|               opcoes              |\n");
        fprintf(stdout, "+===================================+\n");
        fprintf(stdout, "| 1 - Cadastrar produtos            |\n");
        fprintf(stdout, "| 2 - Alterar produto               |\n");
        fprintf(stdout, "| 3 - Listar todos os produtos      |\n");
        fprintf(stdout, "| 4 - Cadastrar loja                |\n");
        fprintf(stdout, "| 5 - Listar todas as lojas         |\n");
        fprintf(stdout, "| 6 - Cadastrar preco               |\n");
        fprintf(stdout, "| 7 - Listar todos os precos        |\n");
        fprintf(stdout, "| 8 - Consultar precos de um produto|\n");
        fprintf(stdout, "| 0 - Sair                          |\n");
        fprintf(stdout, "+===================================+\n>>>> ");
        fscanf(stdin, " %d", &n);
        clearscr();
        switch(n)
        {
        case 0:
            imprime_saida();
            return 0;
        case 1:
            cadastrar_prod();
            break;
        case 2:
            alterar_prod();
            break;
        case 3:
            lista_prod();
            break;
        case 4:
            cadastrar_loja();
            break;
        case 5:
            lista_loja();
            break;
        case 6:
            cadastrar_preco();
            break;
        case 7:
            lista_preco();
            break;
        case 8:
            consulta_prod();
            break;

        default:
            imprime_erro("Erro: Opcao invalida");
            pause();
        }
    }
}

/* Função imprime mensagem de saida */
void imprime_saida()
{
    fprintf(stdout, "+======================================+\n");
    fprintf(stdout, "| BB      YY     YY  EEEEEE       ))   |\n");
    fprintf(stdout, "| BB       YY   YY   EE  EE        ))  |\n");
    fprintf(stdout, "| BB        YY YY    EE  EE   00    )) |\n");
    fprintf(stdout, "| BBBBBB     yy      EEEEEE   00    )) |\n");
    fprintf(stdout, "| BB  BB    yy       EE            ))  |\n");
    fprintf(stdout, "| BBBBBB   yy        EEEEEE       ))   |\n");
    fprintf(stdout, "+======================================+\n");
}

// Vai imprimir uma linha com "+" nas pontas e no meio "="
void imprime_linha(int tam)
{
    fprintf(stdout, "+");
    tam-=2;
    while(tam--)
        fprintf(stdout, "=");
    fprintf(stdout, "+\n");
}

/* Funçao imprime uma mensagem de erro*/
void imprime_erro(char *str)
{
    int tam = strlen(str);
    imprime_linha(tam+4);
    fprintf(stderr, "| %s |\n", str);
    imprime_linha(tam+4);
}


/* Função que limpa a tela */
void clearscr()
{
    #ifdef _WIN32
        system("cls");
    #elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
        system("clear");
    #else
        #error "OS not supported."
    #endif
}

/* Função que limpa o buffer da entrada padrao */
void clean_stdin()
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

/* Função que pausa o sistema */
void pause()
{
    fprintf(stdout, "Pressione qualquer tecla para continuar...");
    clean_stdin();
    getchar();
}

/* Função ordena um vetor da struct tproduto usando o algoritmo de ordenação bubblesort */
void ordena_prod(tproduto * prod, int tam)
{
    int i, j;
    tproduto aux;
    for(i = 0; i < tam; i++)
    {
        for(j = i + 1; j < tam; j++)
        {
            // A função strcmp devolve um numero > 0, caso encontre um caractere na string1 maior que na string2, assim ordenando de forma alfabetica
            if(strcmp(prod[i].descricao, prod[j].descricao) > 0)
            {
                aux = prod[i];
                prod[i] = prod[j];
                prod[j] = aux;
            }
        }
    }
}

/* Função que cadastra um ou mais produto no arquivo "produtos.bin" */
void cadastrar_prod()
{
    char ch;
    FILE *p;
    tproduto prod;
    if((p = fopen(ARQ_PROD, "ab")) == NULL)
    {
        char erro[100] = "Erro: Nao foi possivel abrir o arquivo ";
        strcat(erro, ARQ_PROD);
        imprime_erro(erro);
    }
    else
    {
        do
        {
            // Coloca o ponteiro p no final do arquivo
            fseek(p, 0, SEEK_END);
            // Determina  o codigo do produto de forma sequencial, dividindo o valor atual do ponteiro pelo tamanho da struct tproduto + 1
            prod.cod = ftell(p) / sizeof(tproduto) + 1;
            fprintf(stdout, "+====================+\n");
            fprintf(stdout, "| Informe o produto: |\n");
            fprintf(stdout, "+====================+\n>>>> ");
            fscanf(stdin, " %[^\n]", prod.descricao);
            fwrite(&prod, sizeof(tproduto), 1, p);
            clearscr();
            fprintf(stdout, "+=========================================+\n");
            fprintf(stdout, "| Deseja cadastrar outro produto? (s | n) |\n");
            fprintf(stdout, "+=========================================+\n>>>> ");
            fscanf(stdin, " %c", &ch);
            clearscr();
        } while(ch == 's');
        fclose(p);
    }
}

/* Função altera um ou mais produto(s) cadastrado(s) no arquivo "produtos.bin" */
void alterar_prod()
{
    FILE *p;
    if((p = fopen(ARQ_PROD, "r+b")) == NULL)
    {
        char erro[100] = "Erro: Nao foi possivel abrir o arquivo ";
        strcat(erro, ARQ_PROD);
        imprime_erro(erro);
    }
    else
    {
        // Coloca o ponteiro p no final do arquivo
        fseek(p, 0, SEEK_END);
        // Determina o ultimo codigo do produto de forma sequencial, dividindo o valor atual do ponteiro pelo tamanho da struct tproduto + 1
        int id_max = ftell(p) / sizeof(tproduto) + 1;
        char ch;
        tproduto prod;
        do
        {
            clearscr();
            fprintf(stdout, "+=============================================+\n");
            fprintf(stdout, "| Informe o codigo do produto a ser alterado: |\n");
            fprintf(stdout, "+=============================================+\n>>>> ");
            fscanf(stdin, " %d", &prod.cod);
            clearscr();
            // Caso o codigo informado seja menor ou igual que o id_max que armazena o ultimo codigo do produto, ele é valido
            if(prod.cod > id_max)
            {
                char erro [100];
                sprintf(erro, "Erro: Nao existe produto com o codigo %d", prod.cod);
                imprime_erro(erro);
            }
            else
            {
                fprintf(stdout, "+=========================+\n");
                fprintf(stdout, "| Informe o novo produto: |\n");
                fprintf(stdout, "+=========================+\n>>>> ");
                fscanf(stdin, " %[^\n]", prod.descricao);
                clearscr();
                /* Coloca o ponteiro p aonde a estrutura do codigo está armazenado */
                fseek(p, (prod.cod - 1) * sizeof(tproduto), SEEK_SET);
                fwrite(&prod, sizeof(tproduto), 1, p);
            }
            fprintf(stdout, "+=======================================+\n");
            fprintf(stdout, "| Deseja fazer outra alteracao? (s | n) |\n");
            fprintf(stdout, "+=======================================+\n>>>> ");
            fscanf(stdin," %c", &ch);
            clearscr();
        } while(ch == 's');
        fclose(p);
    }
}

/* Função que lista todos os produtos cadastrados do arquivo "produtos.bin" */
void lista_prod()
{
    FILE *p;
    if((p = fopen(ARQ_PROD, "rb")) == NULL)
    {
        char erro[100];
        sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_PROD);
        imprime_erro(erro);
    }
    else
    {
        // Coloca o ponteiro p no final do arquivo
        fseek(p, 0, SEEK_END);
        // Determina o tamanho do vetor a ser criado com base no ultimo codigo do produto de forma sequencial, dividindo o valor atual do ponteiro pelo tamanho da struct tproduto + 1
        int i, tam = (ftell(p) / sizeof(tproduto) + 1) - 1;
        // Cria um vetor de struct tproduto com a quantidade de elementos igual a quantidade de structs no arquivo
        tproduto prod[tam];
        // Coloca o ponteiro no inicio
        fseek(p, 0, SEEK_SET);
        // Lê as structs do tproduto do arquivo
        fread(prod, sizeof(tproduto), tam, p);
        fclose(p);
        // Ordena o vetor utilizando bubblesort
        ordena_prod(prod, tam);
        // Declaracao das variaveis que vao conter o numero maximo de caracteres de cada variavel a ser imprimida
        int tam_max_cod = 0, tam_max_descricao = 0;
        // Declaracao do vetor de variaveis que vai conter o numero de caracteres de cada variavel a ser imprimida
        int tam_cod[tam], tam_descricao[tam];
        // Vai contar o numero de caracteres das variaveis a ser imprimida
        conta_produto(prod, &tam_max_cod, &tam_max_descricao, tam_cod, tam_descricao, tam);
        // Vai verificar se as variaveis tem o tamanho minimo de caracteres a ser imprimido, caso nao tenho vai atribuir a elas o valor minimo
        if(tam_max_cod < 4)
            tam_max_cod = 4;
        if(tam_max_descricao < 5)
            tam_max_descricao = 5;
        // Declaracao da variavel que vai conter o numero de caracteres de cada linha a ser impressa
        int tam_max_linha = tam_max_cod + tam_max_descricao + 7;
        // Impressao do cabeçalho da funçao
        imprime_linha(tam_max_linha);
        imprime_titulo("Produtos", tam_max_linha);
        imprime_linha(tam_max_linha);
        fprintf(stdout, "| Cod");
        // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
        imprime_espaco(3, tam_max_cod);
        fprintf(stdout, "| Prod");
        // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
        imprime_espaco(4, tam_max_descricao);
        fprintf(stdout, "|\n");
        for(i = 0; i < tam; i++)
        {
            // Impressao das linhas
            fprintf(stdout, "| %d", prod[i].cod);
            // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
            imprime_espaco(tam_cod[i], tam_max_cod);
            fprintf(stdout, "| %s", prod[i].descricao);
            // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
            imprime_espaco(tam_descricao[i], tam_max_descricao);
            fprintf(stdout, "|\n");
        }
        imprime_linha(tam_max_linha);
    }
    pause();
}

/* Funçao que vai contar o numero de caracteres de cada variavel a ser impressao na funçao lista_prod */
void conta_produto(tproduto *prod,int *tam_max_cod,int *tam_max_descricao,int *tam_cod,int *tam_descricao,int tam)
{
     int i, num;
     for(i = 0; i < tam; i++)
     {
         tam_descricao[i] = strlen(prod[i].descricao);
         if(tam_descricao[i] > *tam_max_descricao)
            *tam_max_descricao = tam_descricao[i];
         num = prod[i].cod;
         tam_cod[i] = 0;
         while(num > 0)
         {
             num /= 10;
             tam_cod[i]++;
         }
         if(tam_cod[i] > *tam_max_cod)
            *tam_max_cod = tam_cod[i];
     }
}

/* Função ordena um vetor da struct tproduto usando o algoritmo de ordenação bubblesort */
void ordena_loja(tloja *loja, int tam)
{
    int i, j;
    tloja aux;
    for(i = 1; i < tam; i++)
    {
        for(j = i + 1; j < tam; j++)
        {
            // A função strcmp devolve um numero > 0, caso encontre um caractere na string1 maior que na string2, assim ordenando de forma alfabetica
            if(strcmp(loja[i].nome, loja[j].nome) > 0)
            {
                aux = loja[i];
                loja[i] = loja[j];
                loja[j] = aux;
            }
        }
    }
}

/* Função que cadastra uma ou mais lojas no arquivo "lojas.bin" */
void cadastrar_loja()
{
    FILE *p;
    if((p = fopen(ARQ_LOJA, "ab")) == NULL)
    {
        char erro[100];
        sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_LOJA);
        imprime_erro(erro);
    }
    else
    {
        tloja loja;
        char ch;
        do
        {
            // Coloca o ponteiro p no final do arquivo
            fseek(p, 0, SEEK_END);
            // Determina o ultimo codigo da loja de forma sequencial, dividindo o valor atual do ponteiro pelo tamanho da struct tloja + 1
            loja.cod = ftell(p) / sizeof(tloja) + 1;
            fprintf(stdout, "+=========================+\n");
            fprintf(stdout, "| Informe o nome da loja: |\n");
            fprintf(stdout, "+=========================+\n>>>> ");
            fscanf(stdin, " %[^\n]", loja.nome);
            clearscr();
            fprintf(stdout, "+=========================+\n");
            fprintf(stdout, "| Informe o nome do site: |\n");
            fprintf(stdout, "+=========================+\n>>>> ");
            fscanf(stdin, " %[^\n]", loja.site);
            clearscr();
            fwrite(&loja, sizeof(tloja), 1, p);
            fprintf(stdout, "+======================================+\n");
            fprintf(stdout, "| Deseja cadastrar outra loja? (s | n) |\n");
            fprintf(stdout, "+======================================+\n>>>> ");
            fscanf(stdin, " %c", &ch);
            clearscr();
        } while(ch == 's');
        fclose(p);
    }
}

/* Função que lista todas as lojas cadastradas no arquivo "lojas.bin" */
void lista_loja()
{
    FILE *p;
    if((p = fopen(ARQ_LOJA, "rb")) == NULL)
    {
        char erro[100];
        sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_LOJA);
        imprime_erro(erro);
    }
    else
    {
        // Coloca o ponteiro p no final do arquivo
        fseek(p, 0, SEEK_END);
        // Determina o tamanho do vetor a ser criado com base no ultimo codigo da loja de forma sequencial, dividindo o valor atual do ponteiro pelo tamanho da struct tloja + 1
        int tam = (ftell(p) / sizeof(tloja) + 1) - 1, i;
        // Coloca o ponteiro p no inicio do arquivo
        fseek(p, 0, SEEK_SET);
        // Cria o vetor struct com a quantidade de elemntos igual a quantidade de structs tloja no arquivo "lojas.bin"
        tloja loja[tam];
        // Lê todas as structs armazenadas no arquivo "lojas.bin"
        fread(&loja, sizeof(tloja), tam, p);
        fclose(p);
        // Ordena o vetor de struct tloja utilizando BubbleSort
        ordena_loja(loja, tam);
        // Declaracao das variaveis que vao conter o numero maximo de caracteres de cada variavel a ser imprimida
        int tam_max_cod = 0, tam_max_nome = 0, tam_max_site = 0;
        // Declaracao do vetor de variaveis que vai conter o numero de caracteres de cada variavel a ser imprimida
        int tam_cod[tam], tam_nome[tam], tam_site[tam];
        // Vai contar o numero de caracteres das variaveis a ser imprimida
        conta_loja(loja, tam_cod, tam_nome, tam_site, &tam_max_cod, &tam_max_nome, &tam_max_site, tam);
        // Vai verificar se as variaveis tem o tamanho minimo de caracteres a ser imprimido, caso nao tenho vai atribuir a elas o valor minimo
        if(tam_max_cod < 4)
            tam_max_cod = 4;
        if(tam_max_nome < 5)
            tam_max_nome = 5;
        if(tam_max_site < 5)
            tam_max_site = 5;
        // Declaracao da variavel que vai conter o numero de caracteres de cada linha a ser impressa
        int tam_max_linha = tam_max_cod + tam_max_nome + tam_max_site + 10;
        fprintf(stdout, "\n");
        // Impressao do cabeçalho da funçao
        imprime_linha(tam_max_linha);
        imprime_titulo("Lojas", tam_max_linha);
        imprime_linha(tam_max_linha);
        fprintf(stdout, "| Cod");
        // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
        imprime_espaco(3, tam_max_cod);
        fprintf(stdout, "| Loja");
        // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
        imprime_espaco(4, tam_max_nome);
        fprintf(stdout, "| Site");
        // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
        imprime_espaco(4, tam_max_site);
        fprintf(stdout, "|\n");
        for(i = 0; i < tam; i++)
        {
            // Impressao das linhas
            fprintf(stdout, "| %d", loja[i].cod);
            // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
            imprime_espaco(tam_cod[i], tam_max_cod);
            fprintf(stdout, "| %s", loja[i].nome);
            // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
            imprime_espaco(tam_nome[i], tam_max_nome);
            fprintf(stdout, "| %s", loja[i].site);
            // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
            imprime_espaco(tam_site[i], tam_max_site);
            fprintf(stdout, "|\n");
        }
        imprime_linha(tam_max_linha);
        char ch;
    }
    pause();
}

// Vai imprimir o texto centralizado com base no tamanho maximo de caracteres da linha
void imprime_titulo(char * str, int tam_max)
{
    fprintf(stdout, "|");
    tam_max -= strlen(str) + 2;
    int tam_max_antes = tam_max / 2, tam_max_depois = tam_max / 2;
    // Caso tamanho de caracteres da linha seja impar vai atribuir +1 a variavel que vai conter a quantidade de espacos a ser imprimida depois
    if(tam_max % 2 == 1)
        tam_max_depois += 1;
    while(tam_max_antes--)
        fprintf(stdout, " ");
    fprintf(stdout, "%s", str);
    while(tam_max_depois--)
        fprintf(stdout, " ");
    fprintf(stdout, "|\n");
}


/* Funçao que vai contar o numero de caracteres de cada variavel a ser impressao na funçao lista_loja */
void conta_loja(tloja *loja,int *tam_cod,int *tam_nome,int *tam_site,int *tam_max_cod,int *tam_max_nome,int *tam_max_site,int tam)
{
    int i, num;
    for(i = 0; i < tam; i++)
    {
        tam_cod[i] = 0;
        num = loja[i].cod;
        while(num > 0)
        {
            num /= 10;
            tam_cod[i]++;
        }
        if(tam_cod[i] > *tam_max_cod)
        {
            *tam_max_cod = tam_cod[i];
        }
        tam_nome[i] = strlen(loja[i].nome);
        if(tam_nome[i] > *tam_max_nome)
            *tam_max_nome = tam_nome[i];
        tam_site[i] = strlen(loja[i].site);
        if(tam_site[i] > *tam_max_site)
            *tam_max_site = tam_site[i];
    }
}

// Vai imprimir espaco ate que o espaco ocupado pelo campo seja o mesmo que o tamanho maximo de caracteres
void imprime_espaco(int tam_cod, int tam_max_cod)
{
    for(; tam_cod <= tam_max_cod; tam_cod++)
        fprintf(stdout, " ");
}

/* Função que cadastra preço de um produto em uma determinada loja no arquivo "precos.bin", nao aceitando preços repetidos de produtos em uma mesma loja */
void cadastrar_preco()
{
    tpreco preco;
    char ch;
    int cod_max;
    FILE *p;
    do {
        fprintf(stdout, "+==============================+\n");
        fprintf(stdout, "| Informe o codigo do produto: |\n");
        fprintf(stdout, "+==============================+\n>>>> ");
        fscanf(stdin, " %d", &preco.cod_produto);
        clearscr();
        if((p = fopen(ARQ_PROD, "rb")) == NULL)
        {
            char erro[100];
            sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_PROD);
            imprime_erro(erro);
            pause();

        }
        else
        {
            // Coloca o ponteiro p no final do arquivo "produtos.bin"
            fseek(p, 0, SEEK_END);
            // Determina o ultimo codigo sequencial do arquivo "produtos.bin", dividindo o atual valor do ponteiro p pelo tamanho da struct tproduto + 1
            cod_max = ftell(p) / sizeof(tproduto) + 1;
            // Caso  o codigo do produto informado seja menor ou igual ao ultimo codigo do produto, o codigo informado é valido
            if(preco.cod_produto > cod_max)
            {
                char erro[100];
                sprintf(erro, "Erro: Nao existe nenhuma produto com o codigo %d", preco.cod_produto);
                imprime_erro(erro);
                pause();
            }
            else
            {
                fclose(p);
                fprintf(stdout, "+===========================+\n");
                fprintf(stdout, "| Informe o codigo da loja: |\n");
                fprintf(stdout, "+===========================+\n>>>> ");
                fscanf(stdin, " %d", &preco.cod_loja);
                clearscr();
                if((p = fopen(ARQ_LOJA, "rb")) == NULL)
                {
                    char erro[100];
                    sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_LOJA);
                    imprime_erro(erro);
                    pause();
                }
                else
                {
                    // Coloca o ponteiro p no final do arquivo "lojas.bin"
                    fseek(p, 0, SEEK_END);
                    // Determina o ultimo codigo sequencial do arquivo "lojas.bin", dividindo o atual valor do ponteiro p pelo tamanho da struct tloja + 1
                    cod_max = ftell(p) / sizeof(tloja) + 1;
                    // Caso  o codigo da loja informado seja menor ou igual ao ultimo codigo da loja, o codigo informado é valido
                    if(preco.cod_loja > cod_max)
                    {
                        char erro[100];
                        sprintf(erro, "Erro: Nao existe nenhuma loja com o codigo %d", preco.cod_loja);
                        imprime_erro(erro);
                        pause();
                    }
                    else
                    {
                        fclose(p);
                        if((p = fopen(ARQ_PRECO, "a+b")) == NULL)
                        {
                            char erro[100];
                            sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_PRECO);
                            imprime_erro(erro);
                            pause();
                        }
                        else
                        {
                            int r = 0;
                            tpreco verifica;
                            // Verifica se ja existe um preço para o produto informado na loja informada
                            while(fread(&verifica, sizeof(tpreco), 1, p) > 0)
                            {
                                if(verifica.cod_produto == preco.cod_produto && verifica.cod_loja == preco.cod_loja)
                                    r = 1;
                            }
                            if(r)
                            {
                                char erro[100] = "Erro: Preco ja foi cadastrado";
                                imprime_erro(erro);
                                fclose(p);
                                pause();
                            }
                            else
                            {
                                fprintf(stdout, "+=============================+\n");
                                fprintf(stdout, "| Informe o preco do produto: |\n");
                                fprintf(stdout, "+=============================+\n>>>> ");
                                fscanf(stdin, " %f", &preco.preco);
                                fwrite(&preco, sizeof(tpreco), 1, p);
                                fclose(p);
                            }
                        }
                    }
                }
            }
        }
        clearscr();
        fprintf(stdout, "+=====================================+\n");
        fprintf(stdout, "| Quer cadastrar outro preco? (s | n) |\n");
        fprintf(stdout, "+=====================================+\n>>>> ");
        fscanf(stdin, " %c", &ch);
        clearscr();
    } while(ch == 's');
}

/* Função que lista todos os preços do arquivo "preços.bin" */
void lista_preco()
{
    FILE *p;
    if((p = fopen(ARQ_PROD, "rb")) == NULL)
    {
        char erro[100];
        sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_PROD);
        imprime_erro(erro);
    }
    else
    {
        // Coloca o ponteiro p no final do arquivo "produtos.bin"
        fseek(p, 0, SEEK_END);
        // Determina o tamanho do vetor prod a ser criado com base no ultimo codigo do produto de forma sequencial, dividindo o valor atual do ponteiro pelo tamanho da struct tproduto + 1
        int tam_prod = (ftell(p) / sizeof(tproduto) + 1) - 1;
        // Cria um vetor prod de struct tproduto com a quantidade de elementos igual a quantidade de structs no arquivo
        tproduto prod[tam_prod];
        // Coloca o ponteiro p no inicio do arquivo
        fseek(p, 0, SEEK_SET);
        // Lê todos as structs tproduto armazenado no arquivo "produtos.bin"
        fread(prod, sizeof(tproduto), tam_prod, p);
        fclose(p);
        if((p = fopen(ARQ_LOJA, "rb")) == NULL)
        {
            char erro[100];
            sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_LOJA);
            imprime_erro(erro);
        }
        else
        {
            // Coloca o ponteiro p no final do arquivo "lojas.bin"
            fseek(p, 0, SEEK_END);
            // Determina o tamanho do vetor loja a ser criado com base no ultimo codigo da loja de forma sequencial, dividindo o valor atual do ponteiro pelo tamanho da struct tloja + 1
            int tam_loja = (ftell(p) / sizeof(tloja) + 1) - 1;
            // Cria um vetor loja de struct tloja com a quantidade de elementos igual a quantidade de structs no arquivo
            tloja loja[tam_loja];
            // Coloca o ponteiro p no inicio do arquivo
            fseek(p, 0, SEEK_SET);
            // Lê todos as structs tloja armazenado no arquivo "lojas.bin"
            fread(loja, sizeof(tloja), tam_loja, p);
            fclose(p);
            if((p = fopen(ARQ_PRECO, "rb")) == NULL)
            {
                char erro[100];
                sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_PRECO);
                imprime_erro(erro);
            }
            else
            {
                // Coloca o ponteiro p no final do arquivo "precos.bin"
                fseek(p, 0, SEEK_END);
                // Determina o tamanho do vetor preco a ser criado com base no ultimo codigo do preco de forma sequencial, dividindo o valor atual do ponteiro pelo tamanho da struct tpreco + 1
                int i, tam_preco = (ftell(p) / sizeof(tpreco) + 1) - 1;
                // Cria um vetor preco de struct tpreco com a quantidade de elementos igual a quantidade de structs no arquivo
                tpreco preco[tam_preco];
                // Coloca o ponteiro p no inicio do arquivo "precos.bin"
                fseek(p, 0, SEEK_SET);
                // Lê todos as structs tpreco armazenado no arquivo "preco.bin"
                fread(preco, sizeof(tpreco), tam_preco, p);
                fclose(p);
                // Ordena o vetor preco de struct tpreco utilizando BubbleSort, ordenando pelo nome da loja de forma ascendente e pelo preço de forma descendente
                ordena_preco(preco, tam_preco, loja);
                // Declaracao das variaveis que vao conter o numero maximo de caracteres de cada variavel a ser imprimida
                int tam_descricao[tam_prod], tam_nome[tam_loja], tam_valor[tam_preco];
                // Declaracao do vetor de variaveis que vai conter o numero de caracteres de cada variavel a ser imprimida
                int tam_max_descricao = 0, tam_max_nome = 0, tam_max_valor = 0;
                // Vai contar o numero de caracteres das variaveis a ser imprimida
                conta_preco(loja, prod, preco, tam_descricao, tam_nome, tam_valor, &tam_max_descricao, &tam_max_nome, &tam_max_valor, tam_loja, tam_preco, tam_prod);
                // Vai verificar se as variaveis tem o tamanho minimo de caracteres a ser imprimido, caso nao tenho vai atribuir a elas o valor minimo
                if(tam_max_descricao < 8)
                    tam_max_descricao = 8;
                if(tam_max_nome < 5)
                    tam_max_nome = 5;
                if(tam_max_valor < 6)
                    tam_max_valor = 6;
                // Declaracao da variavel que vai conter o numero de caracteres de cada linha a ser impressa
                int tam_max_linha = tam_max_descricao + tam_max_nome + tam_max_valor + 10;
                // Impressao do cabeçalho da funçao
                imprime_linha(tam_max_linha);
                imprime_titulo("Precos",tam_max_linha);
                imprime_linha(tam_max_linha);
                fprintf(stdout, "| Produto");
                // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                imprime_espaco(7, tam_max_descricao);
                fprintf(stdout, "| Loja");
                // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                imprime_espaco(4, tam_max_nome);
                fprintf(stdout, "| Preco");
                // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                imprime_espaco(5, tam_max_valor);
                fprintf(stdout, "|\n");
                for(i = 0; i < tam_preco; i++)
                {
                    // Impressao das linhas
                    fprintf(stdout, "| %s", prod[preco[i].cod_produto-1].descricao);
                    // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                    imprime_espaco(tam_descricao[preco[i].cod_produto-1], tam_max_descricao);
                    fprintf(stdout, "| %s", loja[preco[i].cod_loja-1].nome);
                    // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                    imprime_espaco(tam_nome[preco[i].cod_loja-1], tam_max_nome);
                    fprintf(stdout, "| %.2f R$", preco[i].preco);
                    // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                    imprime_espaco(tam_valor[i], tam_max_valor);
                    fprintf(stdout, "|\n");
                }
                imprime_linha(tam_max_linha);
            }
        }
    }
    pause();
}

/* Funçao que vai contar o numero de caracteres de cada variavel a ser impressao na funçao lista_preco */
void conta_preco(tloja *loja,tproduto *prod,tpreco *preco,int *tam_descricao,int *tam_nome,int *tam_valor,int *tam_max_descricao,int *tam_max_nome,int *tam_max_valor, int tam_loja, int tam_preco, int tam_prod)
{
    int i;
    float num;
    for(i = 0; i < tam_loja; i++)
    {
        tam_nome[i] = strlen(loja[i].nome);
        if(tam_nome[i] > *tam_max_nome)
            *tam_max_nome = tam_nome[i];
    }
    for(i = 0; i < tam_prod; i++)
    {
        tam_descricao[i] = strlen(prod[i].descricao);
        if(tam_descricao[i] > *tam_max_descricao)
            *tam_max_descricao = tam_descricao[i];
    }
    for(i = 0; i < tam_preco; i++)
    {
        tam_valor[i] = conta_num(preco[i].preco);
        if(*tam_max_valor < tam_valor[i])
            *tam_max_valor = tam_valor[i];
    }
}

/* Função que ordena o vetor preco de struct tpreco utilizando BubbleSort,  ordenando pelo nome da loja de forma ascendente e pelo preco de forma descendente */
void ordena_preco(tpreco *preco, int tam_preco, tloja *loja)
{
    int i, j;
    tpreco aux;
    // Ordena pelo nome da loja de forma ascedente
    for(i = 1; i < tam_preco; i++)
    {
        for(j = i + 1; j < tam_preco; j++)
        {
            if(strcmp(loja[preco[i].cod_loja-1].nome, loja[preco[j].cod_loja-1].nome) > 0)
            {
                aux = preco[i];
                preco[i] = preco[j];
                preco[j] = aux;
            }
        }
    }
    // Ordena o vetor pelo preco de forma descendente mas os precos sao ordenados sendo da mesma loja
    for(i = 0; i < tam_preco; i++)
    {
        for(j = i + 1; j < tam_preco; j++)
        {
            // Caso os dois precos sejam da mesma loja, ele é ordenado
            if(preco[i].cod_loja == preco[j].cod_loja && preco[i].preco < preco[j].preco)
            {
                aux = preco[i];
                preco[i] = preco[j];
                preco[j] = aux;
            }
        }
    }

}

/* Função que consulta os precos de um determinado produtos em todas as lojas */
void consulta_prod()
{
    FILE *p_preco, *p_loja, *p_prod;
    if((p_prod = fopen(ARQ_PROD, "rb")) == NULL)
    {
        char erro[100];
        sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_PROD);
        imprime_erro(erro);
    }
    else
    {

        if((p_preco = fopen(ARQ_PRECO, "rb")) == NULL)
        {
            char erro[100];
            sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_PRECO);
            imprime_erro(erro);
            fclose(p_prod);
        }
        else
        {
            if((p_loja = fopen(ARQ_LOJA, "rb")) == NULL)
            {
                char erro[100];
                sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_LOJA);
                imprime_erro(erro);
                fclose(p_preco);
                fclose(p_prod);
            }
            else
            {
                int id_cod, id_max;
                fprintf(stdout, "+==============================+\n");
                fprintf(stdout, "| Informe o codigo do produto: |\n");
                fprintf(stdout, "+==============================+\n>>>> ");
                fscanf(stdin, " %d", &id_cod);
                clearscr();
                tproduto prod;
                // Coloca o ponteiro p no final do arquivo "produtos.bin"
                fseek(p_prod, 0, SEEK_END);
                // Determina o ultimo codigo sequencial do arquivo "produtos.bin", dividindo o atual valor do ponteiro p pelo tamanho da struct tproduto + 1
                id_max = ftell(p_prod) / sizeof(tproduto) + 1;
                // Caso  o codigo do produto informado seja menor ou igual ao ultimo codigo do produto, o codigo informado é valido
                if(id_cod > id_max)
                {
                    char erro[100];
                    sprintf(erro, "Erro: Nao existe nenhum produto com o codigo %d", id_cod);
                    imprime_erro(erro);
                    fclose(p_preco);
                    fclose(p_prod);
                    fclose(p_loja);
                }
                else
                {
                    // Coloca o ponteiro aonde esta armazena a struct tproduto, do codigo informado
                    fseek(p_prod, (id_cod - 1) * sizeof(tproduto), SEEK_SET);
                    fread(&prod, sizeof(tproduto), 1, p_prod);
                    fclose(p_prod);
                    tpreco preco;
                    tloja loja;
                    // Declaracao das variaveis que vao conter o numero maximo de caracteres de cada variavel a ser imprimida
                    int tam_max_nome = 0, tam_max_valor = 0, tam;
                    // Vai contar o numero de caracteres das variaveis a ser imprimida
                    conta_consulta(id_cod, &tam_max_nome, &tam_max_valor);
                    // Vai verificar se as variaveis tem o tamanho minimo de caracteres a ser imprimido, caso nao tenho vai atribuir a elas o valor minimo
                    if(tam_max_nome < 5)
                        tam_max_nome = 5;
                    if(tam_max_valor < 6)
                        tam_max_valor = 6;
                    // Declaracao da variavel que vai conter o numero de caracteres de cada linha a ser impressa
                    int tam_max_linha = tam_max_nome + tam_max_valor + 7;
                    // Impressao do cabeçalho da funçao
                    imprime_linha(tam_max_linha);
                    char aux[51] = "Produto ";
                    strcat(aux, prod.descricao);
                    imprime_titulo(aux, tam_max_linha);
                    imprime_linha(tam_max_linha);
                    fprintf(stdout, "| Loja");
                    // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                    imprime_espaco(4, tam_max_nome);
                    fprintf(stdout, "| Preco");
                    // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                    imprime_espaco(5, tam_max_valor);
                    fprintf(stdout, "|\n");
                    // Lê todos os precos do arquivo "precos.bin" um por um
                    while(fread(&preco, sizeof(tpreco), 1, p_preco) > 0)
                    {
                        // Caso o produto lido seja o mesmo que o informado, ele vai imprimir a loja e o preco do produto na tela
                        if(preco.cod_produto == id_cod)
                        {
                            // Impressao das linhas
                            fseek(p_loja, (preco.cod_loja - 1) * sizeof(tloja), SEEK_SET);
                            fread(&loja, sizeof(loja), 1, p_loja);
                            fprintf(stdout, "| %s", loja.nome);
                            tam = strlen(loja.nome); // Determina a quantidade de caracteres a ser impressa
                            // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                            imprime_espaco(tam, tam_max_nome);
                            fprintf(stdout, "| %.2f R$", preco.preco);
                            tam = conta_num(preco.preco); // Determina a quantidade de caracteres a ser impressa
                            // Vai imprimir espaco para que cada campo da coluna tenha o mesmo tamanho
                            imprime_espaco(tam, tam_max_valor);
                            fprintf(stdout, "|\n");
                        }
                    }
                    imprime_linha(tam_max_linha);
                }
            }
        }
    }
    pause();
}

/* Conta a quantidade de caracteres de um numero */
int conta_num(float num)
{
    int c = 2;
    num *= 10000;
    do
    {
        c++;
        num /= 10;
    }while(num >= 1);
    return c;
}

/* Funçao que vai contar o numero de caracteres de cada variavel a ser impressao na funçao consulta_prod */
void conta_consulta(int id_cod, int *tam_max_nome,int *tam_max_valor)
{
    FILE *p_preco, *p_loja;
    if((p_loja = fopen(ARQ_LOJA, "rb")) == NULL)
    {
        char erro[100];
        sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_LOJA);
        imprime_erro(erro);
    }
    else
    {
        if((p_preco = fopen(ARQ_PRECO, "rb")) == NULL)
        {
            char erro[100];
            sprintf(erro, "Erro: Nao foi possivel abrir o arquivo %s", ARQ_PRECO);
            imprime_erro(erro);
            fclose(p_loja);
        }
        else
        {
            tloja loja;
            int tam;
            tpreco preco;
            while(fread(&preco, sizeof(tpreco), 1, p_preco) > 0)
            {
                if(preco.cod_produto == id_cod)
                {
                    fseek(p_loja, (preco.cod_loja - 1) * sizeof(tloja), SEEK_SET);
                    fread(&loja, sizeof(loja), 1, p_loja);
                    tam = strlen(loja.nome);
                    if(tam > *tam_max_nome)
                        *tam_max_nome = tam;
                    tam = conta_num(preco.preco);
                    if(tam > *tam_max_valor)
                        *tam_max_valor = tam;
                }
            }
        }
    }
}
