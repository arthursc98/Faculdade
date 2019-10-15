/*
 * avl.c
 * Definição da TAD para implementação das operações realizadas sobre o TAD que r
 * representa uma árvore AVL.
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
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

// Definição da estrutura de dados
typedef struct {
 char usuario[21]; // nome de usuário
 char nome_completo[51]; // nome completo
 char sexo;
 lista amigos; // lista encadeada ordenada dos amigos
} avl_info;

typedef struct avl_no * avl_tree;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do nó
};

/*
 * Imprime a árvore AVL t através de um percurso em ordem.
 */
void print_tree(avl_tree t);


/*
 * Verifica se o usuário x já ocorreu na árvore AVL t;
 * caso contrário ele insere na árvore
 */
void avl_search(avl_tree * t, avl_info x, bool * h, bool * inseriu);


/*
 * Faz uma rotação para a direita na árvore AVL t.
 */
void rotacao_dir(avl_tree * t);


/*
 * Faz uma rotação para a esquerda na árvore AVL t.
 */
void rotacao_esq(avl_tree *);

/*
 * Verifica se o usuário existe, remove ele e retorna verdadeiro
 * caso contrário retorna falso
 */
bool delete(avl_tree * t, avl_info x, bool * h);


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


/*
 * Devolve um ponteiro para o nó que contém o menor
 * valor na árvore AVL t e sinaliza através de h se
 * houve uma diminuição da altura de t.
 */
avl_tree get_min(avl_tree * t, bool * h);


/*
 * Irá procurar o usuário e imprimir a lista de amigos
 */
void search_friendlist(avl_tree t, char * username, bool * h);


/*
 * Irá verificar se o amigo está na árvore como usuário
 */
void verify_avl(avl_tree t,char * friendname, bool * is);


/*
 * Adiciona um novo amigo a lista de um usuário da árvore
 */
void avl_addfriend(avl_tree t, char * username, char * friendname, bool *h);


/*
 * Remove o usuário da lista de amigos
 */
void rem_list(avl_tree * t, char * username);


/*
 * Salva a árvore em arquivo do tipo texto
 */
void saving(avl_tree t, FILE * p);
#endif
