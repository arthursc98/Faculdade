/*
 * redesocial.h
 * Defini��o das fun��es para implementa��o de uma rede social com �rvores avl e listas ordenadas
 *
 * Arthur Silveira Chaves (Sistemas de Informa��o)
 * Beatriz Jonas Justino (Sistemas de Informa��o)
 * Nicholas Meirinho Perez (Sistemas de Informa��o)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 14/10/2019
 */


#ifndef REDESOCIAL_H_INCLUDED
#define REDESOCIAL_H_INCLUDED
#include "avl.h"
#include <stdbool.h>

// Carregar usu�rios e seus respectivos amigos
void load_users(avl_tree * t, char * filename);
// Adicionar um novo usu�rio na �rvore avl
bool add_new_user(avl_tree * t, avl_info x);
// Adicionar um amigo a lista de um usu�rio
bool add_friend(avl_tree t, char * username, char * friendname);
// Listar usu�rios da �rvore avl
void list_users(avl_tree t);
// Listar amigos de um usu�rio
bool list_friends(avl_tree t, char * username);
// Remover usu�rio da �rvore avl
bool remove_user(avl_tree * t, char * username);
// Finalizar o programa salvando a rede social
void save_users(avl_tree t);
// Mostra menu
void menu();
// Mostra que o arquivo foi salvo
void salvo();
// Letreiro de usu�rio
void users_logo();
// Letreiro de lista de amigos do usu�rio
void friendslist_logo();
// Letreiro de adicionar novo usu�rio
void adduser_logo();
// Letreiro de adicionar novo amigo na lista de algum usu�rio
void addfriend_logo();
// Letreiro de removendo usu�rio
void rem_logo();
// Letreiro para ler o arquivo
void read_logo();
// Fun��o que pausa o sistema
void pause();
// Fun��o que limpa a tela
void clearscr();
// Letreiro que algo do programa deu errado
void error();
#endif // REDESOCIAL_H_INCLUDED
