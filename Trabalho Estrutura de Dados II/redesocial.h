/*
 * redesocial.h
 * Definição das funções para implementação de uma rede social com árvores avl e listas ordenadas
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 14/10/2019
 */


#ifndef REDESOCIAL_H_INCLUDED
#define REDESOCIAL_H_INCLUDED
#include "avl.h"
#include <stdbool.h>

// Carregar usuários e seus respectivos amigos
void load_users(avl_tree * t, char * filename);
// Adicionar um novo usuário na árvore avl
bool add_new_user(avl_tree * t, avl_info x);
// Adicionar um amigo a lista de um usuário
bool add_friend(avl_tree t, char * username, char * friendname);
// Listar usuários da árvore avl
void list_users(avl_tree t);
// Listar amigos de um usuário
bool list_friends(avl_tree t, char * username);
// Remover usuário da árvore avl
bool remove_user(avl_tree * t, char * username);
// Finalizar o programa salvando a rede social
void save_users(avl_tree t);
// Mostra menu
void menu();
// Mostra que o arquivo foi salvo
void salvo();
// Letreiro de usuário
void users_logo();
// Letreiro de lista de amigos do usuário
void friendslist_logo();
// Letreiro de adicionar novo usuário
void adduser_logo();
// Letreiro de adicionar novo amigo na lista de algum usuário
void addfriend_logo();
// Letreiro de removendo usuário
void rem_logo();
// Letreiro para ler o arquivo
void read_logo();
// Função que pausa o sistema
void pause();
// Função que limpa a tela
void clearscr();
// Letreiro que algo do programa deu errado
void error();
#endif // REDESOCIAL_H_INCLUDED
