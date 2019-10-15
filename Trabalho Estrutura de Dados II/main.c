/*
 * main.c
 * Implementa��o de uma rede social com �rvores avl e listas ordenadas
 *
 * Arthur Silveira Chaves (Sistemas de Informa��o)
 * Beatriz Jonas Justino (Sistemas de Informa��o)
 * Nicholas Meirinho Perez (Sistemas de Informa��o)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 10/10/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "redesocial.h"

int main()
{
    char filename[61]; // Nome do arquivo
    char username[21];
    char friendname[21];
    avl_info x;
    int op;
    avl_tree t = NULL; // Ponteiro para a raiz da �rvore
    while(true)
    {
        menu();
        scanf(" %d",&op);
        clearscr();
        switch(op)
        {
        case 1:
            read_logo();
            printf("Entre com o nome do arquivo(Sem extens�o): ");
            scanf(" %60[^\n]", filename);
            strcat(filename,".txt");
            load_users(&t,filename);
            clearscr();
            break;
        case 2:
            adduser_logo();
            lst_init(&x.amigos);
            printf("Digite o usu�rio: ");
            scanf(" %20[^\n]",x.usuario);
            printf("Digite o nome completo: ");
            scanf(" %50[^\n]",x.nome_completo);
            printf("Digite o sexo: ");
            scanf(" %c",&x.sexo);
            if(add_new_user(&t,x))
                printf("Usu�rio inserido com sucesso\n");
            else
                printf("Imposs�vel inserir o usu�rio requerido talvez j� esteja na rede social\n");
            pause();
            clearscr();
            break;
        case 3:
            addfriend_logo();
            printf("Entre com o nome do usu�rio: ");
            scanf(" %20[^\n]",username);
            printf("Nome do amigo a ser adicionado: ");
            scanf(" %20[^\n]",friendname);
            if(!add_friend(t,&username,&friendname))
                printf("Verifique se usu�rio existe e/ou se o amigo tamb�m existe\n");
            else
                printf("Opera��o feita com sucesso\n");
            pause();
            clearscr();
            break;
        case 4:
            users_logo();
            list_users(t);
            pause();
            clearscr();
            break;
        case 5:
            friendslist_logo();
            printf("Digite o nome do usu�rio: ");
            scanf(" %20[^\n]",username);
            if(!list_friends(t,&username))
                printf("Usu�rio n�o est� na rede social\n");
            pause();
            clearscr();
            break;
        case 6:
            rem_logo();
            printf("Digite o nome do usu�rio: ");
            scanf(" %20[^\n]",username);
            if(!remove_user(&t,&username))
                printf("Usu�rio n�o est� na rede social\n");
            else
                printf("Usu�rio removido com sucesso\n");
            pause();
            clearscr();
            break;
        case 7:
            save_users(t);
            salvo();
            return 0;
        default:
            error();
            printf("Escolha inv�lida por favor digite uma op��o do menu\n");
            pause();
            clearscr();
            break;
        }
    }
}
