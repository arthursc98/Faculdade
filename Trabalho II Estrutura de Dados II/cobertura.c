/*
 * cobertura.c
 * Implementação das funções principais utilizadas
 * no arquivo main.c
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 13/11/2019
 */

#include "hashmap.h"
#include "avl.h"
#include <stdio.h>
#include <stdbool.h>

void consult(hash_map m){
    map_value * pval;
    int key;
    printf("Digite a chave que deseja consultar: ");
    scanf("%d",&key);
    pval=map_get(m,key);        // Consulta o HashMap e devolve o map_value
    if(pval!=NULL)
        printf("\nConsulta com chave: %d\nNome do Município: %s\nCobertura Vacinal: %.3lf\n",key,pval->nome_muni,pval->cobertura);
    else
        printf("Chave não encontrada.\n");
}

void print_inorder(avl_tree t, int n, int * i)
{
    if (n<1 || n>5570)
        fprintf(stderr,"Número desejado menor que 0 ou maior que o máximo do arquivo(5570)\n");
    else{
        if(t!=NULL)
        {
            print_inorder(t->esq,n,i);
            if(++*i<=n)             // Verifica se o contador já printou toda a quantidade requisitada
                printf("Chave: %d\tNome do Município: %s\tCobertura Vacinal: %.3lf\n",t->dado.key,t->dado.nome_muni,t->dado.cobertura);
            print_inorder(t->dir,n,i);
        }
    }
}

void print_inorder_desc(avl_tree t, int n, int * i)
{
    if (n<1 || n>5570)
        fprintf(stderr,"Número desejado menor que 0 ou maior que o máximo do arquivo(5570)\n");
    else{
        if(t!=NULL)
        {
            print_inorder_desc(t->dir,n,i);
            if(++*i<=n)                  // Verifica se o contador já printou toda a quantidade requisitada
                printf("Chave: %d\tNome do Município: %s\tCobertura Vacinal: %.3lf\n",t->dado.key,t->dado.nome_muni,t->dado.cobertura);
            print_inorder_desc(t->esq,n,i);

        }
    }
}

void menu()
{
    printf("+=========================================+\n");
    printf("|                                         |\n");
    printf("|    Trabalho de Estrutura de Dados II    |\n");
    printf("|                                         |\n");
    printf("+=========================================+\n");
    printf("|1-Consultar município por código         |\n");
    printf("|2-Mostrar as menores coberturas vacinais |\n");
    printf("|3-Mostrar as maiores coberturas vacinais |\n");
    printf("|4-Sair                                   |\n");
    printf("+=========================================+\n");
}

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

void pause()
{
    printf("Pressione enter para continuar...");
    getchar();
    scanf("c\n");
}

void line()
{
    printf("\n");
}

void input_n(int * n)
{
    printf("Digite a quantidade que deseja mostrar: ");
    scanf("%d",n);
}
