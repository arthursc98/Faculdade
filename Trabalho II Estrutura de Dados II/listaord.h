/*
 * listaord.h
 * Protótipos das funções da lista ordenada.
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 13/11/2019
 */

#ifndef _LISTAORD_H
#define _LISTAORD_H

#include "hashmap.h"
#include <stdbool.h>

/* função que inicializa a lista encadeada ordenada */
void lst_init(map_ptr *);

/* função que devolve verdadeiro se a lista estiver vazia */
bool lst_isempty(map_ptr);

/* função que insere um novo par (chave, valor) na lista */
void lst_ins(map_ptr *, map_key, map_value);

/* função que remove a entrada (chave, valor) e devolve o
   endereço do valor, caso sua chave esteja na lista, ou NULL,
   caso contrário */
map_value * lst_rem(map_ptr *, map_key);

/* função que e devolve o endereço do valor, caso sua chave
   esteja na lista, ou NULL, caso contrário */
map_value * lst_find(map_ptr, map_key);

#endif
