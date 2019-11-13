/*
 * main.c
 * Implementação utilizando HashMap e AVL para
 * ler e consultar arquivo "cobertura_vacinal.csv".
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
#include "cobertura.h"
#include "avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define FILENAME "cobertura_vacinal.csv"

int main()
{
	FILE * f;
	hash_map m;
	char linha[MAX_DEF + 1];
	int chave;
	map_value val;
	avl_tree t=NULL;
    bool h;
	if ((f = fopen(FILENAME, "r")) == NULL) {
		fprintf(stderr, "Erro de abertura do arquivo %s!\n", FILENAME);
		return 1;
	}

	map_init(m);
	while (fscanf(f, " %[^\n]", linha) != EOF) { // Transferindo arquivos para o Map e para AVL
        char * token=strtok(linha,";");
        chave=atoi(token);      // Trocando tipo de dado String para Int
        token=strtok(NULL,";");
        strcpy(val.nome_muni,token);
        token=strtok(NULL,";");
        val.cobertura=atof(token);      //// Trocando tipo de dado String para Double
        map_put(m, chave, val);
        avl_search(&t,chave,val.cobertura,val.nome_muni,&h);
    }
    int op,n;
    while(true){ // Menu para escolha da operação desejada pelo usuário
        int i=0;
        menu();
        printf("Digite a opção desejada: ");
        scanf("%d",&op);
        switch(op){
            case 1:     // Consulta
                consult(m);
                line();
                pause();
                clearscr();
                break;
            case 2:     // Mostrar as n menores coberturas vacinais
                line();
                input_n(&n);
                line();
                print_inorder(t,n,&i);
                line();
                pause();
                clearscr();
                break;
            case 3:     // Mostrar as n maiores coberturas vacinais
                line();
                input_n(&n);
                line();
                print_inorder_desc(t,n,&i);
                line();
                pause();
                clearscr();
                break;
            case 4:     // Sair do programa
                return 0;
            default:
                printf("Opção Inválida\n");
                pause();
                clearscr();
        }
    }
}
