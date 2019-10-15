/*
 * redesocial.c
 * Implementação de uma rede social com árvores avl e listas ordenadas
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 14/10/2019
 */

#include "redesocial.h"
#include "lista.h"
#include "avl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_users(avl_tree * t, char * filename)
{
    FILE * arq;
    char linha[100];
    if ((arq = fopen(filename, "r")) == NULL)
    {
        clearscr();
        error();
        fprintf(stderr, "Erro na abertura do arquivo %s\n", filename);
        exit(1);
    }
    bool h,inseriu;
    avl_info x;
    while(fscanf(arq, " %[^\n]", linha) != EOF)
    {
        char * token=strtok(linha,";");
        // Adiciona o username
        strcpy(x.usuario,token);
        // Adiciona o nome inteiro
        token = strtok(NULL, ";");
        strcpy(x.nome_completo,token);
        // Adiciona o sexo
        token = strtok(NULL, ";");
        x.sexo = token[0];
        // Inicia a lista de amigos e adiciona todos
        lst_init(&x.amigos);
        lst_info entrada;
        fscanf(arq, " %[^\n]", linha); // Pega a próxima linha
        token=strtok(linha,"; ");
        while(token!=NULL)
        {
            strcpy(entrada.usuario,token);
            lst_ins(&x.amigos,entrada);
            token = strtok(NULL, "; ");
        }
        avl_search(t,x,&h,&inseriu);
    }
    fclose(arq);
}

bool add_new_user(avl_tree * t, avl_info x)
{
    bool h,inseriu;
    avl_search(t,x,&h,&inseriu); // Adiciona usuário novo de forma ordenada
    return inseriu;
}

bool add_friend(avl_tree t, char * username, char * friendname)
{
    bool h=false,is=false;
    verify_avl(t,friendname,&is); // Verifica se o amigo está na árvore
    if(is==true)
        avl_addfriend(t,username,friendname,&h); // Adiciona o amigo a lista
    return h;
}

bool list_friends(avl_tree t, char * username)
{
    bool h;
    search_friendlist(t,username,&h); // Busca todos os amigos do usuário
    return h;
}

void list_users(avl_tree t)
{
    print_tree(t); // Mostra todos usuários
}

bool remove_user(avl_tree * t, char * username)
{
    avl_info x;
    lst_info y;
    bool h=false;
    strcpy(x.usuario,username);
    strcpy(y.usuario,username);
    if(!delete(t,x,&h)) // Irá remover o usuário caso exista e caso contrário retornará falso
        return false;
    else
    {
        rem_list(&(*t),username);
        return true;
    }
}

void save_users(avl_tree t)
{
    FILE * p;
    char * filename="arvore_salva.txt";
    if ((p = fopen(filename, "w")) == NULL)
    {
        fprintf(stderr, "Erro na abertura do arquivo %s\n", filename);
        exit(1);
    }
    saving(t,p);
    fclose(p);
}

void menu()
{
    printf("+===========================+\n");
    printf("|                           |\n");
    printf("|           menu            |\n");
    printf("|                           |\n");
    printf("+===========================+\n");
    printf("|1-Carregar usuários        |\n");
    printf("|2-Inserir usuários         |\n");
    printf("|3-Inserir amigo            |\n");
    printf("|4-Listar usuários          |\n");
    printf("|5-Listar amigos            |\n");
    printf("|6-Remover usuário          |\n");
    printf("|7-Salvar e sair do programa|\n");
    printf("+===========================+\n");
}

void salvo()
{
    printf("+=================================+\n");
    printf("|    Arquivo salvo com sucesso    |\n");
    printf("+=================================+\n");
}

void users_logo()
{
    printf("+=================================+\n");
    printf("|             Usuários            |\n");
    printf("+=================================+\n");
}

void friendslist_logo()
{
    printf("+==================================+\n");
    printf("|    Amigos do usuário desejado    |\n");
    printf("+==================================+\n");
}

void adduser_logo()
{
    printf("+==================================+\n");
    printf("|     Adicionando usuário novo     |\n");
    printf("+==================================+\n");
}

void addfriend_logo()
{
    printf("+==================================+\n");
    printf("|   Adicionando amigo ao usuário   |\n");
    printf("+==================================+\n");
}

void rem_logo()
{
    printf("+==================================+\n");
    printf("|         Removendo usuário        |\n");
    printf("+==================================+\n");
}

void read_logo()
{
    printf("+==================================+\n");
    printf("|       Ler arquivo desejado       |\n");
    printf("+==================================+\n");
}

void clearscr()
{
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
#else
#error "OS not supported."
#endif
}

void pause()
{
    printf("Pressione enter para continuar...");
    getchar();
    scanf("c\n");
}

void error()
{
    printf("+==================================+\n");
    printf("|               ERROR              |\n");
    printf("+==================================+\n");
}
