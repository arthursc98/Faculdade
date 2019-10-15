/*
 * lista.c
 * Implementa��o das opera��es sobre o TAD lista ordenada.
 *
 * Arthur Silveira Chaves (Sistemas de Informa��o)
 * Beatriz Jonas Justino (Sistemas de Informa��o)
 * Nicholas Meirinho Perez (Sistemas de Informa��o)
 *
 * Disciplina: Estrutura de Dados-II
 *
 * 10/10/2019
 */

#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lst_init(lista * l)
{
    *l = NULL;
}

void lst_ins(lista * l, lst_info val)
{
    lista n;
    if ((n = (lista) malloc(sizeof(struct lst_no))) == NULL)
    {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(1);
    }
    strcpy(n->dado.usuario,val.usuario);
    if (*l == NULL || strcasecmp(val.usuario,(*l)->dado.usuario)<=0)
    {
        n->prox = *l;
        *l = n;
    }
    else
    {
        lista p = *l;
        while (p->prox != NULL && strcasecmp(val.usuario,p->prox->dado.usuario)>0)
        {
            p = p->prox;
        }
        n->prox = p->prox;
        p->prox = n;
    }
}

void lst_rem(lista * l, lst_info x, bool * h)
{
    if (*l == NULL || strcasecmp(x.usuario,(*l)->dado.usuario)<0)
    {
        *h=false;
    }
    else
    {
        lista p = *l;
        if (strcasecmp(x.usuario,(*l)->dado.usuario)==0)
        {
            *l = p->prox;
            free(p);
            *h=true;
        }
        else
        {
            while (p->prox != NULL && strcasecmp(x.usuario,p->prox->dado.usuario)>0)
            {
                p = p->prox;
            }
            if (p->prox != NULL && strcasecmp(x.usuario,p->prox->dado.usuario)==0)
            {
                lista n = p->prox;
                p->prox = n->prox;
                free(n);
                *h=true;
            }
        }
        *h=false;
    }
}

void lst_print(lista l)
{
    printf("\n\n");
    if(l==NULL)
        printf("Este usu�rio n�o possui amigos\n");
    while (l != NULL)
    {
        if(l->prox!=NULL)
        {
            printf("%s,", l->dado.usuario);
            l = l->prox;
        }
        else
        {
            printf("%s", l->dado.usuario);
            l = l->prox;
        }
    }
    printf("\n\n");
}

