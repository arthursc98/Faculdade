/*
 * main.c
 * Implementa��o cria��o de tabelas normais
 * com desvio padr�o eprecis�o desejada pelo
 * usu�rio (max precis�o: 1e-10).
 *
 * Arthur Silveira Chaves (Sistemas de Informa��o)
 * Beatriz Jonas Justino (Sistemas de Informa��o)
 * Nicholas Meirinho Perez (Sistemas de Informa��o)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 17/11/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Prot�tipos das fun��es
void pause();
void clearscr();
void input_precision(int * precision);
void input_std(float * std);
void input_operation(int * op);
void print_table(float std, float * index_col, int precision);
void menu();
float * create_index_col(float std);
double f(double x, int precision);
double higher_precision(double n, double i);

// Pausa da tela do usu�rio
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

// Input de precis�o
void input_precision(int * precision)
{
    printf("Exemplo: 1e-10=10 (10 n�meros ap�s a virgula)\n");
    printf("Digite a precis�o:\n");
    scanf(" %d",&(*precision));
}


// Input de desvios-padr�es
void input_std(float * std)
{
    printf("Digite quantos desvio-padr�o(�es) deseja utilizar:\n");
    scanf(" %f",&(*std));
}

// Input opera��o desejada do usu�rio
void input_operation(int * op)
{
    printf("Digite a opera��o desejada:\n");
    scanf(" %d",&(*op));
}

// Printa a tabela
void print_table(float std, float * index_col,int precision)
{
    for(int k=0;k<20+5*precision;k++)   printf(" ");
    printf("Tabela Z com mu=0 e sigma=%.2f\n\n",std);
    for(int i=0; i<10; i++)
    {
        if(i==0)    printf("|z  |   ");
	int spaces=precision/2;
	if(precision%2==0){
		printf("|");
		for(int k=0;k<spaces;k++)   printf(" ");
		printf("%d",i);
		for(int k=0;k<spaces;k++)   printf(" ");
		printf(" |\t");
	}
	else{
		printf("|");
		for(int k=0;k<spaces;k++)   printf(" ");
		printf("%d",i);
		for(int k=0;k<spaces;k++)   printf(" ");
		printf("  |\t");
	}
    }
    for(int j=0; j<(std/.1); j++)
    {
        printf("\n|%.1f|\t",index_col[j]);
        for(double k=0;k<10;k++){
            if(k!=9)
                printf("|%.*lf|\t",precision,f(index_col[j]+(k/100),precision));
            else
                printf("|%.*lf|",precision,f(index_col[j]+(k/100),precision));
        }
    }
}

// Interface de menu
void menu()
{
    printf("++================================================++\n");
    printf("||   Trabalho de Probabilidade e Estat�stica II   ||\n");
    printf("||================================================||\n");
    printf("||                                                ||\n");
    printf("||              Objetivo do Trabalho:             ||\n");
    printf("||  Criar tabelas Z com n�mero de desvios padr�es ||\n");
    printf("||  desejados pelo usu�rio.                       ||\n");
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
    int index_qtd=(std/.1)+1;
    float resto=(std-(std/.1*.1))+1;
    float * index_col=malloc((index_qtd+1+resto)*sizeof(float));
    for(int i=0; i<index_qtd; i++)
    {
	if (i==0)
	    index_col[i]=.0;
	else
	    index_col[i]=index_col[i-1]+.1;
    }
    return index_col;
}

// Retorna a fun��o de probabilidade cumulativa - 0.5
double f(double x,int precision)
{
    return higher_precision((.5*erfc(-x*M_SQRT1_2))-.5,precision);
}

// Delimita e valida a precis�o
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
            pause();
            clearscr();
            break;
        case 2:
            return 0;
        default:
            fprintf(stderr,"Opera��o inv�lida, tente novamente\n");
            pause();
            clearscr();
        }
    }
}
