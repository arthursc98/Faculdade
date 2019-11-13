/*
 * cobertura.h
 * Protótipos das funções utilizadas no arquvio main.c
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 13/11/2019
 */

#ifndef COBERTURA_H_INCLUDED
#define COBERTURA_H_INCLUDED

#include "hashmap.h"
#include "avl.h"

// Função para consultar uma chave no HashMap
void consult(hash_map m);

// Função para mostrar as n menores coberturas vacinais
void print_inorder(avl_tree t, int n, int * i);

// Função para mostrar as n maiores coberturas vacinais
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
