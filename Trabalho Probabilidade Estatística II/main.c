/*
 * main.c
 * Implementação criação de tabelas normais
 * com desvio padrão eprecisão desejada pelo
 * usuário (max precisão: 1e-10).
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 18/11/2019
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Protótipos das funções
void pause();
void clearscr();
void input_precision(int * precision);
void input_std(float * std);
void input_operation(int * op);
void print_table(float std, float * index_col, int precision);
void savefile(float std,float * index_col, int precision);
void savecsv(float std,float * index_col, int precision);
void savemenu();
void menu();
float * create_index_col(float std);
double f(double x, int precision);
double higher_precision(double n, double i);

// Pausa da tela do usuário
void pause()
{
    printf("\nPressione enter para continuar...\n");
    getchar();
    scanf("c\n");
}

// Limpa tela
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

// Input de precisão
void input_precision(int * precision)
{
    printf("Digite quantos números após a vírgula mostrará a tabela:\n");
    scanf(" %d",&(*precision));
}


// Input de desvios-padrões
void input_std(float * std)
{
    printf("Digite quantos desvio-padrão(ões) deseja ter a tabela:\n");
    scanf(" %f",&(*std));
}

// Input operação desejada do usuário
void input_operation(int * op)
{
    printf("Digite a operação desejada:\n");
    scanf(" %d",&(*op));
}

// Printa a tabela
void print_table(float std, float * index_col,int precision)
{
    int k,i,j;
    for(k=0; k<20+5*precision; k++)
        printf(" ");
    printf("Tabela Z com mu=0 e sigma=%.2f\n\n",std);
    for(i=0; i<10; i++)
    {
        if(i==0)
            printf("|z  |   ");
        int spaces=precision/2;
        if(precision%2==0)
        {
            printf("|");
            for(k=0; k<spaces; k++)
                printf(" ");
            printf("%d",i);
            for(k=0; k<spaces; k++)
                printf(" ");
            printf(" |\t");
        }
        else
        {
            printf("|");
            for(k=0; k<spaces; k++)
                printf(" ");
            printf("%d",i);
            for(k=0; k<spaces; k++)
                printf(" ");
            printf("  |\t");
        }
    }
    for(j=0; j<(std/.1); j++)
    {
        printf("\n|%.1f|\t",index_col[j]);
        double c;
        for(c=0; c<10; c++)
        {
            if(c!=9)
                printf("|%.*lf|\t",precision,f(index_col[j]+(c/100),precision));
            else
                printf("|%.*lf|",precision,f(index_col[j]+(c/100),precision));
        }
    }
    pause();
    savefile(std,index_col,precision);
}

// Função para verificar se o usuário deseja salvar a tabela criada
void savefile(float std,float * index_col, int precision)
{
    clearscr();
    savemenu();
    char op[2];
    scanf(" %s",op);
    if(strcasecmp(op,"S")==0)
        savecsv(std,index_col,precision);
    else
        clearscr();
}

// Salva a tabela em formato csv
void savecsv(float std, float * index_col, int precision)
{
    FILE * p;
    char FILENAME[81];
    printf("Por favor digite o nome do arquivo o qual quer salvar: ");
    scanf(" %s",FILENAME);
    if ((p = fopen(strcat(FILENAME,".csv"), "w")) == NULL)
    {
        fprintf(stderr, "Erro na criação do arquivo %s!\n", FILENAME);
        exit(1);
    }
    int k,i,j;
    fprintf(p,"Tabela Z com mu=0 e sigma=%.2f,\n",std);
    for(i=0; i<10; i++)
    {
        if(i==0)
            fprintf(p,"z,");
        if(i==9)
            fprintf(p,"%d\n",i);
        else
            fprintf(p,"%d,",i);
    }
    for(j=0; j<(std/.1); j++)
    {
        fprintf(p,"%.1f,",index_col[j]);
        double c;
        for(c=0; c<10; c++)
        {
            if(c!=9)
                fprintf(p,"%.*lf,",precision,f(index_col[j]+(c/100),precision));
            else
                fprintf(p,"%.*lf\n",precision,f(index_col[j]+(c/100),precision));
        }
    }
    printf("Arquivo salvo com sucesso!! Está no mesmo diretório do arquivo do programa");
    pause();
    clearscr();
}

// Alerta para salvar o arquivo
void savemenu()
{
    printf("++================================================++\n");
    printf("||                   Atenção!!                    ||\n");
    printf("++================================================++\n");
    printf("||                                                ||\n");
    printf("||  Deseja salvar a tabela em formato .csv?(S/N)  ||\n");
    printf("||                                                ||\n");
    printf("++================================================++\n");
}
// Interface de menu
void menu()
{
    printf("++================================================++\n");
    printf("||   Trabalho de Probabilidade e Estatística II   ||\n");
    printf("||================================================||\n");
    printf("||                                                ||\n");
    printf("||              Objetivo do Trabalho:             ||\n");
    printf("||  Criar tabelas Z com número de desvios padrões ||\n");
    printf("||  desejados pelo usuário.                       ||\n");
    printf("||                                                ||\n");
    printf("||================================================||\n");
    printf("|| 1 - Gerar tabela                               ||\n");
    printf("|| 2 - Sair                                       ||\n");
    printf("++================================================++\n");
    printf("|| Obs: Para deixar a tabela de forma harmoniosa  ||\n");
    printf("|| coloque em fullscreen.                         ||\n");
    printf("++================================================++\n");
}

// Cria o index da coluna de z
float * create_index_col(float std)
{
    int index_qtd=(std/.1)+1,i;
    float resto=(std-(std/.1*.1))+1;
    float * index_col=malloc((index_qtd+1+resto)*sizeof(float));
    for(i=0; i<index_qtd; i++)
    {
        if (i==0)
            index_col[i]=.0;
        else
            index_col[i]=index_col[i-1]+.1;
    }
    return index_col;
}

// Retorna a função de probabilidade cumulativa - 0.5
double f(double x,int precision)
{
    return higher_precision(.5*erfc(x*-M_SQRT1_2)-.5,precision);
}

// Delimita e valida a precisão
double higher_precision(double n, double i)
{
    return floor(pow(10,i)*n)/pow(10,i);
}

int main()
{
    int op,precision;
    float std;
    float * index_col;
    while(true)
    {
        menu();
        input_operation(&op);
        switch(op)
        {
        case 1:
            input_std(&std);
            input_precision(&precision);
            clearscr();
            index_col=create_index_col(std);
            print_table(std,&(*index_col),precision);
            break;
        case 2:
            return 0;
        default:
            fprintf(stderr,"Operação inválida, tente novamente\n");
            pause();
            clearscr();
        }
    }
}
