/* Caixa.c
 *
 * Programa que informa um saque e duas cedulas e ele imprime o troco
 *
 * Rodrigo Suarez Moreira (Ciência da Computação)
 * Arthur Silveira Chaves (Sistema da informação)
 * Nicholas Meirinho Perez (Sistema da informação)
 *
 * Disciplina: Matematica Discreta-II
 *
 * 06/10/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Textos

// Imprime a logo "CAIXA"
void logo();
// Imprime o menu inicial
void menu();
//Imprime um alerta caso a opcao escolhida seja invalida
void erroMenu();
// Imprime texto do saque
void textSaque();
// Imprime o texto cedula
void textCed(int i, int c1);
// Imprime  um alerta caso a cedula seja invalida
void textCedInvalida();
// Imprime um alerta caso a cedula ja foi escolhida
void textCedRepetida();
// Imprime um alerta caso o saque seja invalido
void textSaqInvalido();

/* Funcoes */

/* A função retorna o valor do saque */
int saque();
/* Recebe o vetor v que contem as cedulas validas e as escolhidas e o inteiro i que representa o numero da cedula escolhida
 * e devolve o valor da cedula */
int ced(int *v, int i, int c1);
/* Ordena c1 e c2 de forma descrecente */
void orderna(int *c1,int *c2);
/* Imprime e determina a quantidade de cedulas */
void imprimiQntdCed(int qtd_c1,int qtd_c2,int c1,int c2,int saque);
/* Verifica se o numero informada e valido ou nao */
void apuraErro(char * numStr, int * numDec);

int main()
{
    int v[101] = {0}, c1, c2, saq, qtd_c1, qtd_c2, opcDec, tam;
    char opcStr[100];
    do
    {
        system ("cls");
        // Vai atribuir 1 as cedulas validas
        v[2] = 1;
        v[5] = 1;
        v[10] = 1;
        v[20] = 1;
        v[50] = 1;
        v[100] = 1;
        logo();
        menu();
        scanf(" %99[^\n]", &opcStr);
        // Verifica se a opcao e valida ou nao
        tam = strlen(opcStr);
        if(tam == 1 && opcStr[0] == '1')
            opcDec = 1;
        else if(tam == 1 && opcStr[0] == '0')
            opcDec = 0;
        else
            opcDec = -1;
        switch(opcDec)
        {
        case 0:
            break;
        case 1:
            saq = saque();
            c1 = ced(v, 1, c1);
            c2 = ced(v, 2, c1);
            orderna( &c1, &c2);
            imprimiQntdCed( qtd_c1, qtd_c2, c1, c2, saq);
            break;
        default:
            system ("cls");
            logo();
            erroMenu();
        }
    }
    while(opcDec);
    return 0;
}

void logo()
{
    printf("+--------------------------------------------+\n");
    printf("|    $$$$$$  $$$$$$  $$  $$    $$  $$$$$$    |\n");
    printf("|    $$      $$  $$  $$   $$  $$   $$  $$    |\n");
    printf("|    $$      $$  $$  $$    $$$$    $$  $$    |\n");
    printf("|    $$      $$$$$$  $$     $$     $$$$$$    |\n");
    printf("|    $$      $$  $$  $$    $$$$    $$  $$    |\n");
    printf("|    $$      $$  $$  $$   $$  $$   $$  $$    |\n");
    printf("|    $$$$$$  $$  $$  $$  $$    $$  $$  $$    |\n");
    printf("+--------------------------------------------+\n");
}
void menu()
{
    printf("|                Bem Vindo!!!                |\n");
    printf("+--------------------------------------------+\n");
    printf("| Menu:                                      |\n");
    printf("|  1 - Saque                                 |\n");
    printf("|  0 - Sair                                  |\n");
    printf("+--------------------------------------------+\n");
    printf(">>>> ");
}

void erroMenu()
{
    printf("|            Erro: Opcao invalida            |\n");
    printf("+--------------------------------------------+\n");
    system("pause");
    system("cls");

}

void textSaque()
{
    printf("| Saque minimo = 7 $                         |\n");
    printf("+--------------------------------------------+\n");
    printf("| Informe o saque:                           |\n");
    printf("+--------------------------------------------+\n");
    printf(">>>> ");
}

void textSaqInvalido()
{
    printf("|            Erro: Saque invalido            |\n");
    printf("+--------------------------------------------+\n");
    system("pause");
    system("cls");
}

int saque()
{
    system ("cls");
    char saqStr[50];
    int saqDec;
    do
    {
        system ("cls");
        logo();
        textSaque();
        scanf(" %49[^\n]", saqStr);
        apuraErro(saqStr, &saqDec);
        if(saqDec < 7)
        {
            system ("cls");
            logo();
            textSaqInvalido();
        }
    }
    while(saqDec < 7);
    system ("cls");
    return saqDec;
}


void textCed(int i, int ced)
{
    printf("| Cedulas = ");
    // Vai Colocar espaços o suficiente para nao extrapolar a borda da caixa
    if(i == 2)
    {
        if(ced != 2)
            printf("|2");
        if(ced != 5)
            printf("|5");
        if(ced != 10)
            printf("|10");
        if(ced != 25)
            printf("|20");
        if(ced != 50)
            printf("|50");
        if(ced != 100)
            printf("|100");
        printf("|                ");
        switch(ced)
        {
        case 100:
            printf(" ");
        case 50:
        case 20:
        case 10:
            printf(" ");
        case 5:
        case 2:
            printf(" ");
        }
        printf("|\n");
    }
    else
        printf("|2|5|10|20|50|100|               |\n");
    printf("+--------------------------------------------+\n");
    printf("| Escolha a %d cedula:                        |\n", i);
    printf("+--------------------------------------------+\n");
    printf(">>>> ");
}

void textCedInvalida()
{
    printf("|            Erro: Cedula invalida           |\n");
    printf("+--------------------------------------------+\n");
    system("pause");
    system("cls");
}

void textCedRepetida()
{
    printf("|            Erro: Cedula ja informada       |\n");
    printf("+--------------------------------------------+\n");
    system("pause");
    system("cls");
}

int ced(int *v, int i, int ced)
{
    char cedStr[50];
    int cedDec;
    do
    {
        system ("cls");
        logo();
        textCed(i, ced);
        scanf(" %49[^\n]", cedStr);
        apuraErro(cedStr, &cedDec);
        // Verifica se a cedula e valida
        if(cedDec > 100)
        {
            system ("cls");
            logo();
            textCedInvalida();
        }
        else
        {
            if(v[cedDec] == -1)
            {
                system ("cls");
                logo();
                textCedRepetida();
            }
            else if( cedDec == -1 || v[cedDec] != 1 )
            {
                system ("cls");
                logo();
                textCedInvalida();
            }
        }
        // Verifica se a cedula e valida
    }
    while(v[cedDec] != 1);
    v[cedDec] = -1;
    system ("cls");
    return cedDec;
}

void orderna(int *c1, int *c2)
{
    int aux;
    if(*c1 < *c2)
    {
        aux = *c1;
        *c1 = *c2;
        *c2 = aux;
    }
}

void imprimiQntdCed(int qtd_c1, int qtd_c2, int c1, int c2, int saque)
{
    int r = 1,i,j, saqOri = saque;
    // Vai determinar a menor quantidade de cedulas, tendo em vista que a quantidade de cedulas 2 vai ser 0
    qtd_c1 = saque / c1;
    saque %= c1;
    system("cls");
    logo();
    if (saque == 0)
    {
        printf("| Quantidade de cedulas de %d = %d", c1, qtd_c1);
        //Vai imprimir a quantidade de espaços para nao extrapolar a caixa
        j = 0;
        for(i = 1; i <= c1; i*=10, j++);
        for(i = 1; i <= qtd_c1; i*=10, j++);
        for(; j < 15; j++)
        {
            printf(" ");
        }
        printf("|");
        printf("\n| Quantidade de cedulas de %d = 0", c2);
        //Vai imprimir a quantidade de espaços para nao extrapolar a caixa
        j = 1;
        for(i = 1; i <= c2; i*=10, j++);
        for(; j < 15; j++)
        {
            printf(" ");
        }
        printf("|\n");
        r = 0;
        // Vai determinar a menor quantidade de cedulas, tendo em vista que a quantidade minima para cada cedula é 1
        saque += c1;
        qtd_c1--;
        while(saque % c2 != 0 && saqOri > saque )
        {
            saque += c1;
            qtd_c1--;
        }
    }
    // Vai determinar a menor quantidade de cedulas, tendo em vista que a quantidade minima para cada cedula é 1
    qtd_c2 = saque / c2;
    saque %= c2;
    if(qtd_c1 > 0 && saque == 0)
    {
        if(r == 0)
            printf("+------------------- OU ---------------------+\n");
        printf("| Quantidade de cedulas de %d = %d", c1, qtd_c1);
        //Vai imprimir a quantidade de espaços para nao extrapolar a caixa
        j = 0;
        // Vai Colocar espaços o suficiente para nao extrapolar a borda da caixa
        for(i = 1; i <= c1; i*=10, j++);
        for(i = 1; i <= qtd_c1; i*=10, j++);
        for(; j < 15; j++)
        {
            printf(" ");
        }
        printf("|");
        printf("\n| Quantidade de cedulas de %d = %d", c2, qtd_c2);
        //Vai imprimir a quantidade de espaços para nao extrapolar a caixa
        j = 0;
        // Vai Colocar espaços o suficiente para nao extrapolar a borda da caixa
        for(i = 1; i <= c2; i*=10, j++);
        for(i = 1; i <= qtd_c2; i*=10, j++);
        for(; j < 15; j++)
        {
            printf(" ");
        }
        printf("|\n");
    }
    else if(r)
    {
        printf("|            Erro: Saque invalido            |\n");
    }
    printf("+--------------------------------------------+\n");
    system("pause");
    system("cls");
}

void  apuraErro(char * numStr, int * numDec)
{
    * numDec = 0;
    int  i, j, dec, tam = strlen(numStr);
    //J vai obter a quantidade de casas decimais da numStr
    j = pow(10, tam) / 10;
    // Vai corrigir os numeros que funçao pow arrendondar para baixo
    if(j % 10 != 0 && tam != 1)
        j++;
    // Vai transformar numStr em inteiro e armazenar em numDec
    for(i = 0; numStr[i] != '\0'; i++, j /= 10)
    {
        if(numStr[i] >= '0' && numStr[i] <= '9')
        {
            * numDec += (numStr[i] - '0') * j;
        }
        else
        {
            * numDec = -1;
            break;
        }
    }
}
