/*
 * listaord.c
 * Adaptação das funções da lista ordenada
 * utilizada no HashMap.
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
#include "listaord.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lst_init(map_ptr * l)
{
	*l = NULL;
}

bool lst_isempty(map_ptr l)
{
	return l == NULL;
}

void lst_ins(map_ptr * l, map_key key, map_value val)
{
	map_ptr n;
	if (*l == NULL || key < (*l)->key) {
		if ((n = (map_ptr) malloc(sizeof(struct map_node))) == NULL) {
			fprintf(stderr, "Erro de alocacao de memoria!\n");
			exit(1);
		}
		n->key=key;
		if ((n->value = (map_value *) malloc(sizeof(map_value))) == NULL) {
			fprintf(stderr, "Erro de alocacao de memoria!\n");
			exit(1);
		}
		*(n->value) = val;
		n->prox = *l;
		*l = n;
	}
	else {
		map_ptr p = *l;
		while (p->prox != NULL && p->prox->key < key)
			p = p->prox;
		if (p->key != key && (p->prox == NULL || p->prox->key != key)) {
			if ((n = (map_ptr) malloc(sizeof(struct map_node))) == NULL) {
				fprintf(stderr, "Erro de alocacao de memoria!\n");
				exit(1);
			}
			n->key=key;
			if ((n->value = (map_value *) malloc(sizeof(map_value))) == NULL) {
				fprintf(stderr, "Erro de alocacao de memoria!\n");
				exit(1);
			}
			*(n->value) = val;
			n->prox = p->prox;
			p->prox = n;
		}
		else { // já existe na lista, atualiza seu valor
			*((*l)->value) = val;
		}
	}
}

map_value * lst_find(map_ptr l, map_key key)
{
	if (l == NULL || key < l->key) {
		return NULL;
	}
	if (key == l->key) {
		return l->value;
	}
	while (l != NULL && l->key < key) {
		l = l->prox;
	}
	if (l != NULL && l->key == key) {
		return l->value;
	}
	return NULL;
}
