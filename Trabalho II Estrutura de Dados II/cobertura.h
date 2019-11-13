/*
 * cobertura.h
 * Prot�tipos das fun��es utilizadas no arquvio main.c
 *
 * Arthur Silveira Chaves (Sistemas de Informa��o)
 * Beatriz Jonas Justino (Sistemas de Informa��o)
 * Nicholas Meirinho Perez (Sistemas de Informa��o)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 13/11/2019
 */

#ifndef COBERTURA_H_INCLUDED
#define COBERTURA_H_INCLUDED

#include "hashmap.h"
#include "avl.h"

// Fun��o para consultar uma chave no HashMap
void consult(hash_map m);

// Fun��o para mostrar as n menores coberturas vacinais
void print_inorder(avl_tree t, int n, int * i);

// Fun��o para mostrar as n maiores coberturas vacinais
void print_inorder_desc(avl_tree t, int n, int * i);

// Interface menu
void menu();

// Limpar a tela
void clearscr();

// Pausar a tela
void pause();

// Pular linha
void line();

// Armazenar a quantidade de n
void input_n(int * n);
#endif // COBERTURA_H_INCLUDED
