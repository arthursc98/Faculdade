/*
 * avl.h
 * Prot�tipos das fun��es de AVL e adapta��o
 * TAD para AVL.
 *
 * Arthur Silveira Chaves (Sistemas de Informa��o)
 * Beatriz Jonas Justino (Sistemas de Informa��o)
 * Nicholas Meirinho Perez (Sistemas de Informa��o)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 13/11/2019
 */

#ifndef _AVL_H
#define _AVL_H

#include <stdbool.h>

// Defini��o da estrutura de dados
typedef struct {
	int key;
	double cobertura;
	char nome_muni[256];
} avl_info;

typedef struct avl_no * avl_tree;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do n�
};


/*
 * Verifica se a chave x j� ocorreu na �rvore AVL t;
 * caso afirmativo, produz uma mensagem de erro; caso contr�rio,
 * x � inserida em t e h sinaliza que houve um aumento da
 * altura de t.
 */
void avl_search(avl_tree * t, int key, double cobertura, char nome_muni[256], bool * h);


/*
 * Faz uma rota��o para a direita na �rvore AVL t.
 */
void rotacao_dir(avl_tree * t);


/*
 * Faz uma rota��o para a esquerda na �rvore AVL t.
 */
void rotacao_esq(avl_tree *);


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


#endif
