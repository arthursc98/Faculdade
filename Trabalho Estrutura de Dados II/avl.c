/*
 * avl.h
 * Implementação das operações realizadas sobre o TAD que r
 * representa uma árvore AVL.
 *
 * Arthur Silveira Chaves (Sistemas de Informação)
 * Beatriz Jonas Justino (Sistemas de Informação)
 * Nicholas Meirinho Perez (Sistemas de Informação)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 14/10/2019
 */

#include "avl.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tree(avl_tree t)
{
    if (t != NULL)
    {
        print_tree(t->esq);
        printf("Usuario -> %s\n", t->dado.usuario);
        printf("Nome completo -> %s\n", t->dado.nome_completo);
        printf("Sexo -> %c\n\n", t->dado.sexo);
        print_tree(t->dir);
    }
}

void avl_search(avl_tree * t, avl_info x, bool * h, bool * inseriu)
{
    if (*t == NULL)
    {
        if ((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL)
        {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        *h = true;
        *inseriu=true;
        strcpy((*t)->dado.usuario,x.usuario);
        strcpy((*t)->dado.nome_completo,x.nome_completo);
        (*t)->dado.sexo=x.sexo;
        (*t)->dado.amigos=x.amigos;
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
    }
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) < 0)   // Inserir a esquerda
    {
        avl_search(&(*t)->esq, x, h,inseriu);
        if (*h)   // O ramo esquerdo cresceu
        {
            switch ((*t)->bal)
            {
            case 1:
                (*t)->bal = 0;
                *h = false;
                break;
            case 0:
                (*t)->bal = -1;
                break;
            case -1:
                // Rebalanceamento
                if ((*t)->esq->bal == -1)   //Rotação simples p/ direita
                {
                    rotacao_dir(t);
                    (*t)->dir->bal = 0; //Ajusta o fator de balanceamento
                }
                else   // Rotação dupla para direita
                {
                    rotacao_esq(&(*t)->esq);
                    rotacao_dir(t);
                    // Ajusta o fator de balanceamento
                    if ((*t)->bal == -1)
                        (*t)->dir->bal = 1;
                    else (*t)->dir->bal = 0;
                    if ((*t)->bal == 1)
                        (*t)->esq->bal = -1;
                    else (*t)->esq->bal = 0;
                }
                *h = false;
                (*t)->bal = 0;
                break;
            } // fim do switch
        }
    } // fim do if
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) > 0)   // Inserir a direita
    {
        avl_search(&(*t)->dir, x, h,inseriu);
        if (*h)   // O ramo direito cresceu
        {
            switch ((*t)->bal)
            {
            case -1:
                (*t)->bal = 0;
                *h = false;
                break;
            case 0 :
                (*t)->bal = 1;
                break;
            case 1: // Rebalanceamento
                if ((*t)->dir->bal == 1)   // Rotação simples p/ esquerda
                {
                    rotacao_esq(t);
                    // Ajusta o fator de balanceamento
                    (*t)->esq->bal = 0;
                }
                else   // Rotação dupla para esquerda
                {
                    rotacao_dir(&(*t)->dir);
                    rotacao_esq(t);
                    // Ajusta o fator de balanceamento
                    if ((*t)->bal == 1)
                        (*t)->esq->bal = -1;
                    else (*t)->esq->bal = 0;
                    if ((*t)->bal == -1)
                        (*t)->dir->bal = 1;
                    else (*t)->dir->bal = 0;
                } // fim do else
                *h = false;
                (*t)->bal = 0;
                break;
            } // fim do switch
        }
    } // fim do if
    else // a chave já está na árvore
        *inseriu=false;
} // fim de avl_search

// Rotaçao para a esquerda
void rotacao_esq(avl_tree * t)
{
    avl_tree p;
    p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}

// Rotação para a direita
void rotacao_dir(avl_tree * t)
{
    avl_tree p;
    p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}


bool delete(avl_tree * t, avl_info x, bool * h)
{
    avl_tree p;
    bool result;
    if (*t == NULL) // A chave não se encontra na árvore
        return false;
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) == 0)   // a chave está neste nó
    {
        p = *t;
        if ((*t)->esq == NULL)   // nó folha ou somente com subárvore direita
        {
            *t = p->dir;
            *h = true;
        }
        else if ((*t)->dir == NULL)   // nó com uma única subárvore esquerda
        {
            *t = p->esq;
            *h = true;
        }
        else   // nó com duas subávores
        {
            p = get_min(&(*t)->dir, h);
            (*t)->dado = p->dado;
            if(*h)
                balance_dir(t, h);
        }
        free(p);
        return true;
    }
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) < 0)
    {
        result = delete(&(*t)->esq, x, h);
        if (*h)
            balance_esq(t, h);
        return result;
    }
    else
    {
        result = delete(&(*t)->dir, x, h);
        if (*h)
            balance_dir(t, h);
        return result;
    }
} // fim do delete

void balance_dir(avl_tree * t, bool * h)
{
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal)
    {
    case 1:
        (*t)->bal = 0;
        break;
    case 0:
        (*t)->bal = -1;
        *h = false;
        break;
    case -1: // rebalanceamento
        p1 = (*t)->esq;
        b1 = p1->bal;
        if (b1 <= 0)   // rotação simples
        {
            (*t)->esq = p1->dir;
            p1->dir = *t;
            if (b1 == 0)
            {
                (*t)->bal = -1;
                p1->bal = 1;
                *h = false;
            }
            else
            {
                (*t)->bal = 0;
                p1->bal = 0;
            }
            *t = p1;
        }
        else   // rotação dupla
        {
            p2 = p1->dir;
            b2 = p2->bal;
            p1->dir = p2->esq;
            p2->esq = p1;
            p1->esq = p2->dir;
            p2->dir = *t;
            if(b2 == -1)
                (*t)->bal = 1;
            else (*t)->bal = 0;
            if(b2 == 1)
                p1->bal = -1;
            else
                p1->bal = 0;
            *t = p2;
            p2->bal = 0;
        }
    } // fim do switch
}

void balance_esq(avl_tree * t, bool * h)
{
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal)
    {
    case -1:
        (*t)->bal = 0;
        break;
    case 0:
        (*t)->bal = 1;
        *h = false;
        break;
    case 1: // rebalanceamento
        p1 = (*t)->dir;
        b1 = p1->bal;
        if (b1 >= 0)   // rotação simples
        {
            (*t)->dir = p1->esq;
            p1->esq = *t;
            if (b1 == 0)
            {
                (*t)->bal = 1;
                p1->bal = -1;
                *h = false;
            }
            else
            {
                (*t)->bal = 0;
                p1->bal = 0;
            }
            *t = p1;
        }
        else   // rotação dupla
        {
            p2 = p1->esq;
            b2 = p2->bal;
            p1->esq = p2->dir;
            p2->dir = p1;
            p1->dir = p2->esq;
            p2->esq = *t;
            if (b2 == 1)
                (*t)->bal = -1;
            else (*t)->bal = 0;
            if (b2 == -1)
                p1->bal = 1;
            else
                p1->bal = 0;
            *t = p2;
            p2->bal = 0;
        }
    } // fim do switch
}

avl_tree get_min(avl_tree * t, bool * h)
{
    avl_tree q;
    if ((*t)->esq != NULL)
    {
        q = get_min(&((*t)->esq),h);
        if (*h)
            balance_esq(t, h);
        return q;
    }
    else
    {
        *h = true;
        q = *t;
        *t = (*t)->dir;
        return q;
    }
}

void search_friendlist(avl_tree t,char * username, bool * h)
{
    if(t!=NULL)
    {
        search_friendlist(t->esq,username,h);
        if(strcasecmp(t->dado.usuario,username)==0) // Procura o usuário e imprime a lista de amigos
        {
            lst_print(t->dado.amigos);
            *h=true;
        }
        search_friendlist(t->dir,username,h);
    }
}

void avl_addfriend(avl_tree t, char * username, char * friendname, bool *h)
{
    if(t!=NULL)
    {
        avl_addfriend(t->esq,username,friendname,h);
        if(strcasecmp(t->dado.usuario,username)==0) // Verifica o usuário e copia
        {
            // o amigo para a lista do usuário
            lst_info x;
            strcpy(x.usuario,friendname);
            lst_ins(&(t)->dado.amigos,x);
            *h=true;
        }
        avl_addfriend(t->dir,username,friendname,h);
    }
}

void verify_avl(avl_tree t,char * friendname, bool * is)
{
    if(t!=NULL)
    {
        verify_avl(t->esq,friendname,is); // Verifica se o amigo existe como usuário
        if(strcasecmp(t->dado.usuario,friendname)==0)
            *is=true;
        verify_avl(t->dir,friendname,is);
    }
}

void rem_list(avl_tree * t, char * username)
{
    if ((*t) != NULL)
    {
        lst_info x;
        bool h;
        strcpy(x.usuario,username);
        rem_list(&(*t)->esq,username);
        lst_rem(&(*t)->dado.amigos,x,&h);
        rem_list(&(*t)->dir,username);
    }
}

void saving(avl_tree t, FILE * p)
{
    if (t != NULL) // Grava os usuários e seus amigos de forma ordenada
    {
        saving(t->esq,p);
        fprintf(p,"%s;%s;%c\n",t->dado.usuario,t->dado.nome_completo,t->dado.sexo);
        if(t->dado.amigos==NULL)
            fprintf(p,"\n");
        else
        {
            while(t->dado.amigos != NULL)
            {
                if(t->dado.amigos->prox!=NULL)
                {
                    fprintf(p,"%s; ", t->dado.amigos->dado.usuario);
                    t->dado.amigos = t->dado.amigos->prox;
                }
                else
                {
                    fprintf(p,"%s\n",t->dado.amigos->dado.usuario);
                    t->dado.amigos = t->dado.amigos->prox;
                }
            }
        }
        saving(t->dir,p);
    }
}
