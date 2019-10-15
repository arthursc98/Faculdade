/*
 * avl.c
 * Defini��o da TAD para implementa��o das opera��es realizadas sobre o TAD que r
 * representa uma �rvore AVL.
 *
 * Arthur Silveira Chaves (Sistemas de Informa��o)
 * Beatriz Jonas Justino (Sistemas de Informa��o)
 * Nicholas Meirinho Perez (Sistemas de Informa��o)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 14/10/2019
 */

#ifndef _AVL_H
#define _AVL_H
#include "lista.h"
#include <stdbool.h>
#include <stdio.h>

// Defini��o da estrutura de dados
typedef struct {
 char usuario[21]; // nome de usu�rio
 char nome_completo[51]; // nome completo
 char sexo;
 lista amigos; // lista encadeada ordenada dos amigos
} avl_info;

typedef struct avl_no * avl_tree;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do n�
};

/*
 * Imprime a �rvore AVL t atrav�s de um percurso em ordem.
 */
void print_tree(avl_tree t);


/*
 * Verifica se o usu�rio x j� ocorreu na �rvore AVL t;
 * caso contr�rio ele insere na �rvore
 */
void avl_search(avl_tree * t, avl_info x, bool * h, bool * inseriu);


/*
 * Faz uma rota��o para a direita na �rvore AVL t.
 */
void rotacao_dir(avl_tree * t);


/*
 * Faz uma rota��o para a esquerda na �rvore AVL t.
 */
void rotacao_esq(avl_tree *);

/*
 * Verifica se o usu�rio existe, remove ele e retorna verdadeiro
 * caso contr�rio retorna falso
 */
bool delete(avl_tree * t, avl_info x, bool * h);


/*
 * Faz o balanceamento da �rvore AVL t ap�s uma remo��o
 * em sua sub�rvore esquerda e sinaliza se houve uma
 * dimui��o da altura dessa sub�rvore atrav�s de h.
 */
void balance_esq(avl_tree * t, bool * h);


/*
 * Faz o balanceamento da �rvore AVL t ap�s uma remo��o
 * em sua sub�rvore direita e sinaliza se houve uma
 * dimui��o da altura dessa sub�rvore atrav�s de h.
 */
void balance_dir(avl_tree *, bool *);


/*
 * Devolve um ponteiro para o n� que cont�m o menor
 * valor na �rvore AVL t e sinaliza atrav�s de h se
 * houve uma diminui��o da altura de t.
 */
avl_tree get_min(avl_tree * t, bool * h);


/*
 * Ir� procurar o usu�rio e imprimir a lista de amigos
 */
void search_friendlist(avl_tree t, char * username, bool * h);


/*
 * Ir� verificar se o amigo est� na �rvore como usu�rio
 */
void verify_avl(avl_tree t,char * friendname, bool * is);


/*
 * Adiciona um novo amigo a lista de um usu�rio da �rvore
 */
void avl_addfriend(avl_tree t, char * username, char * friendname, bool *h);


/*
 * Remove o usu�rio da lista de amigos
 */
void rem_list(avl_tree * t, char * username);


/*
 * Salva a �rvore em arquivo do tipo texto
 */
void saving(avl_tree t, FILE * p);
#endif
