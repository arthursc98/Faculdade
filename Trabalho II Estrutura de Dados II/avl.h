/*
 * avl.h
 * Protótipos das funções de AVL e adaptação
 * TAD para AVL.
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 13/11/2019
 */

#ifndef _AVL_H
#define _AVL_H

#include <stdbool.h>

// Definição da estrutura de dados
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
    int bal; // balanceamento do nó
};


/*
 * Verifica se a chave x já ocorreu na árvore AVL t;
 * caso afirmativo, produz uma mensagem de erro; caso contrário,
 * x é inserida em t e h sinaliza que houve um aumento da
 * altura de t.
 */
void avl_search(avl_tree * t, int key, double cobertura, char nome_muni[256], bool * h);


/*
 * Faz uma rotação para a direita na árvore AVL t.
 */
void rotacao_dir(avl_tree * t);


/*
 * Faz uma rotação para a esquerda na árvore AVL t.
 */
void rotacao_esq(avl_tree *);


/*
 * Faz o balanceamento da árvore AVL t após uma remoção
 * em sua subárvore esquerda e sinaliza se houve uma
 * dimuição da altura dessa subárvore através de h.
 */
void balance_esq(avl_tree * t, bool * h);


/*
 * Faz o balanceamento da árvore AVL t após uma remoção
 * em sua subárvore direita e sinaliza se houve uma
 * dimuição da altura dessa subárvore através de h.
 */
void balance_dir(avl_tree *, bool *);


#endif
