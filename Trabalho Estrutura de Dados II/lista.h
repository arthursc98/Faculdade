/*
 * lista.h
 * Defini��o da TAD para implementa��o das opera��es sobre o TAD lista ordenada.
 *
 * Arthur Silveira Chaves (Sistemas de Informa��o)
 * Beatriz Jonas Justino (Sistemas de Informa��o)
 * Nicholas Meirinho Perez (Sistemas de Informa��o)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 10/10/2019
 */

#ifndef _LISTA_H
#define _LISTA_H
#include <stdbool.h>

typedef struct lst_info {
    char usuario[21];
} lst_info;
typedef struct lst_no * lista;
struct lst_no {
    lst_info dado;
    lista prox;
};

/* inicializa a lista ordenada */
void lst_init(lista *);

/* insere um novo elemento na lista ordenada */
void lst_ins(lista *, lst_info);

/* remove um elemento da lista ordenada */
void lst_rem(lista *, lst_info, bool *);

/* imprime os elementos da lista ordenada */
void lst_print(lista);


#endif
