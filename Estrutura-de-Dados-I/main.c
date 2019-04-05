/*
 * main.c
 * Implementação das operações realizadas sobre um set (Conjunto)
 * de números inteiros.
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 * Disciplina: Estrutura de Dados-I
 *
 * 02/04/2019
 */
#include "set.h"
#include <stdio.h>
int main()
{
    set s1, s2, s3;
    int op;
    set_info val;
    set_init(&s1);
    set_init(&s2);
    do
    {
        printf("+=============================+\n");
        printf("|          CONJUNTOS          |\n");
        printf("+=============================+\n");
        printf("|            Opções           |\n");
        printf("+=============================+\n");
        printf("|  <1> Inserir no 1o conjunto |\n");
        printf("|  <2> Inserir no 2o conjunto |\n");
        printf("|  <3> Remover do 1o conjunto |\n");
        printf("|  <4> Remover do 2o conjunto |\n");
        printf("|  <5> Imprimir o 1o conjunto |\n");
        printf("|  <6> Imprimir o 2o conjunto |\n");
        printf("|   <7> União dos conjuntos   |\n");
        printf("|<8> Interseccao dos conjuntos|\n");
        printf("| <9> Diferenca dos conjuntos |\n");
        printf("|     <0> Sair do programa    |\n");
        printf("+=============================+\n");
        printf("Opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("+============================+\n");
            printf("|   Inserir no 1o conjunto   |\n");
            printf("+============================+\n");
            printf("Valor: ");
            scanf("%d", &val);
            if (set_insert(&s1, val))
            {
                printf("+=======================================+\n");
                printf("|%d inserido com sucesso no 1o conjunto!|\n",val);
                printf("+=======================================+\n");
            }
            else
            {
                printf("+==========================================+\n");
                printf("|Erro: conjunto cheio ou elemento repetido!|\n");
                printf("+==========================================+\n");
            }
            pause();
            clearscr();
            break;
        case 2:
            printf("+============================+\n");
            printf("|   Inserir no 2o conjunto   |\n");
            printf("+============================+\n");
            printf("Valor: ");
            scanf("%d", &val);
            if (set_insert(&s2, val))
            {
                printf("+=======================================+\n");
                printf("|%d inserido com sucesso no 2o conjunto!|\n",val);
                printf("+=======================================+\n");
            }
            else
            {
                printf("+==========================================+\n");
                printf("|Erro: conjunto cheio ou elemento repetido!|\n");
                printf("+==========================================+\n");
            }
            pause();
            clearscr();
            break;
        case 3:
            printf("+============================+\n");
            printf("|   Remover do 1o conjunto   |\n");
            printf("+============================+\n");
            printf("Valor: ");
            scanf("%d", &val);
            if (set_remove(&s1, val))
            {
                printf("+=======================================+\n");
                printf("|%d removido com sucesso no 1o conjunto!|\n",val);
                printf("+=======================================+\n");
            }
            else
            {
                printf("+=============================================+\n");
                printf("| Erro: %d nao esta' contido no 1o. conjunto! |\n", val);
                printf("+=============================================+\n");
            }
            pause();
            clearscr();
            break;
        case 4:
            printf("+============================+\n");
            printf("|   Remover do 2o conjunto   |\n");
            printf("+============================+\n");
            printf("Valor: ");
            scanf("%d", &val);
            if (set_remove(&s2, val))
            {
                printf("+=======================================+\n");
                printf("|%d removido com sucesso no 2o conjunto!|\n",val);
                printf("+=======================================+\n");
            }
            else
            {
                printf("+=============================================+\n");
                printf("| Erro: %d nao esta' contido no 2o. conjunto! |\n", val);
                printf("+=============================================+\n");
            }
            pause();
            clearscr();
            break;
        case 5:
            printf("+====================+\n");
            printf("|     1o conjunto:   |\n");
            printf("+====================+\n");
            set_print(s1);
            pause();
            clearscr();
            break;
        case 6:
            printf("+====================+\n");
            printf("|     2o conjunto:   |\n");
            printf("+====================+\n");
            set_print(s2);
            pause();
            clearscr();
            break;
        case 7:
            if (set_union(s1, s2, &s3))
            {
                printf("+==========================+\n");
                printf("|  Uniao dos 2 conjuntos:  |\n");
                printf("+==========================+\n");
               set_print(s3);
            }
            else
            {
                printf("+=======================================================+\n");
                printf("|  Erro: não ha' espaco suficiente para essa operacao!  |\n");
                printf("+=======================================================+\n");
            }
            pause();
            clearscr();
            break;
        case 8:
            printf("+================================+\n");
            printf("|  Interseccao dos 2 conjuntos:  |\n");
            printf("+================================+\n");
            set_intersection(s1, s2, &s3);
            set_print(s3);
            pause();
            clearscr();
            break;
        case 9:
            if(set_difference(s1, s2, &s3)){
                printf("+==============================+\n");
                printf("|  Diferenca dos 2 conjuntos:  |\n");
                printf("+==============================+\n");
                set_print(s3);
            }
            else
            {
                printf("+=======================================================+\n");
                printf("|  Erro: não ha' espaco suficiente para essa operacao!  |\n");
                printf("+=======================================================+\n");
            }
            pause();
            clearscr();
            break;
        case 0:
            break;
        default:
            printf("+=========================+\n");
            printf("|  Erro: opcao invalida!  |\n");
            printf("+=========================+\n");
            pause();
            clearscr();
        }
    }
    while (op != 0);
    clearscr();
    printf("+==============================+\n");
    printf("|            Tchau!!           |\n");
    printf("+==============================+\n");
    return 0;
}
