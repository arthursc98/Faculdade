/*
 * hashmap.c
 * Implementação das funções do HashMap
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void map_init(hash_map m)
{
	int i;
	for (i = 0; i < M; i++) {
		lst_init(&m[i]);
	}
}

bool map_isempty(hash_map m)
{
	int i;
	for (i = 0; i < M; i++)
		if (!lst_isempty(m[i]))
			return false;
	return true;
}

map_value * map_get(hash_map m, map_key key)
{
	return lst_find(m[h(key)], key);
}

void map_put(hash_map m, map_key key, map_value val)
{
	lst_ins(&m[h(key)], key, val);
}

/* método do meio do quadrado para chaves alfanuméricas */
int h(map_key key)
{
	int soma = 0;

	// meio do quadrado
	soma *= soma;
	int x = log10(M) / log10(2);
	int desl = (NUM_BITS - x) / 2;
	soma >>= desl;
	return soma & ((int) pow(2, x) - 1);
}
