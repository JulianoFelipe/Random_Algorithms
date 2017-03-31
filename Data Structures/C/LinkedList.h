#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Node.h"
#include "Macros.h"

#define LinkedList SLL
typedef struct node SLL;
///SLL - Singly Linked List
SLL* SLLdestroi (SLL* lista);
SLL* SLLinsert(SLL* lista, int val);
SLL* SLLremoveElement (SLL* lista, int R);
SLL* SLLremoveIndex (SLL* lista, int index);
int SLLsearch(SLL* lista, int P);
int SLLgetFromIndex (SLL* lista, int index);
int SLLgetSize (SLL* lista);
SLL* SLLgetTail(SLL* head);
void SLLprint (SLL* lista);
/// Exercício 1
SLL* SLLsplit (SLL* lista, int token);


/**
* Dada uma lista e um inteiro "token", separa-se
* a lista na ocorrência do token. Retorna o resultado
* do split, o resto da lista mantêm-se no ponteiro inicial.
*/
SLL* SLLsplit (SLL* lista, int token){
    if (lista == NULL){
        if (DISPLAY_INFO) printf ("  -- Lista nula. Nao ha o que separar.\n");
        return NULL;
    }

    SLL* p = lista;

    //Percorre a lista até encontrar o token
    //Quando encontra, sai do look
    while (p->info != token){
        p = p->next;

        if (p == NULL){
            if (DISPLAY_INFO) printf ("  -- Elemento nao encontrado. Nao e possivel separar. Lista permanece inalterada.\n");
            return lista;
        }

    }
    //P é o nodo cujo "info" é o token
    //Split no próximo nodo.

    SLL* aux = p->next;
    p->next = NULL;

    return aux;
}



///Funcoes auxiliares e implementadas anteriormente


/**
* Destroi a lista e libera toda a memoria.
* Retorna NULL para substituir o ponteiro.
*/
SLL* SLLdestroi (SLL* lista){
    if (lista==NULL){
        if (DISPLAY_INFO) printf("  -- Lista nula. Retorna-se NULL\n");
        return NULL;
    }

    if (lista->next == NULL){
        SLL* aux = lista->next;
        free(aux);
        if (DISPLAY_INFO) printf("  -- Lista destruida. Apenas um elemento.\n");
        return NULL;
    }

    SLL* aux;
    SLL* p = lista;
    while (p->next != NULL){
        aux = p->next;
        free (p);
        p = aux;
    }

    if (DISPLAY_INFO) printf("  -- Lista destruida.\n");

    return NULL;
}

/**
* Insere SLLs na lista
* Retorna lista com o elemento adicionado.
*/
SLL* SLLinsert(SLL* lista, int val){
    //SLL* novo=(SLL*) m(sizeof(SLL));
    SLL* novo = NEWNODE; //ALLOC_STRUCT(SLL);
    novo->info=val;
    novo->next=lista;

    if (DISPLAY_INFO) printf("  -- Elemento %d inserido.\n", val);

    return novo;
}

/**
* Remove elemento da lista.
* Retorna a lista com o elemento removido.
* Se o elemento nao foi encontrado, a mesma
* lista e retornada.
*/
SLL* SLLremoveElement (SLL* lista, int R){
    if (lista->info == R){
        SLL* tmp = lista;
        lista = tmp->next;
        free(tmp);
        if (DISPLAY_INFO) printf("  -- Elemento %d removido da head.\n", R);
        return lista;
    }
    short found_flag=0;
    SLL* p;
    SLL* aux;
    for (p=lista;p->next!=NULL;p=p->next){
        aux=p->next;
        if (aux->info==R){
            p->next=aux->next;
            free(aux);
            if (DISPLAY_INFO) printf("  -- Elemento %d removido.\n", R);
            found_flag++;
            break;
        }
    }

    if (DISPLAY_INFO==1 && found_flag==0) printf("  -- Elemento %d nao encontrado.\n", R);

    return lista;
}

/**
* Remove elemento da lista em um determinado indice.
* (1º elemento -> indice = 0.)
* Retorna a lista com o elemento removido.
* Se o indice for invalido, a mesma
* lista e retornada.
*/
SLL* SLLremoveIndex (SLL* lista, int index){
    if (lista == NULL) return NULL;

    if (index == 0){
        SLL* tmp = lista;
        if (DISPLAY_INFO) printf("  -- Elemento na posicao %d (head) removido: %d\n", index, tmp->info);
        lista = tmp->next;
        free(tmp);
        return lista;
    }

    SLL* p = lista;
    SLL* aux;
    int i=1;
    p = p->next;
    for (p=lista;p->next!=NULL;p=p->next){
        aux=p->next;
        if (i==index){
            if (DISPLAY_INFO) printf("  -- Elemento %d removido.\n", aux->info);
            p->next=aux->next;
            free(aux);
            return lista;
        }
        i++;
    }

    if (DISPLAY_INFO==1) printf("  -- Posicao %d invalida.\n", index);

    return lista;
}

/**
* Busca node na lista.
* Retorna o index (index >= 0) se encontrou;
* E -1 se não encontrou.
*/
int SLLsearch(SLL* lista, int P){
    if (lista == NULL){
        if(DISPLAY_INFO)
            printf("  -- Lista nula. Nao existem elementos.\n");
        return -1;
    }

    int cont=0;
    SLL* p;
    for (p=lista;p!=NULL;p=p->next){
        if(p->info==P){
            if (DISPLAY_INFO)
                printf("  -- Encontrado em  %d -> Index(%d).\n", P, cont);
            return cont;
        }
        cont++;
    }

    if (DISPLAY_INFO)
        printf("  -- Elemento nao encontrado. Inspecionados %d elemento(s).\n", cont);

    return -1;
}

/**
* Retorna o inteiro em um indice da lista.
* Se lista NULL, retorna INT_MAX.
* Se indice invalido, retorna INT_MIN.
*/
int SLLgetFromIndex (SLL* lista, int index){
    if (lista == NULL) {
        if (DISPLAY_INFO) printf("  -- Lista nula.\n");
        return INT_MAX;
    }


    if (index == 0) return lista->info;

    SLL* p = lista;
    int i=1;
    p = p->next;
    for (;p!=NULL;p=p->next){
        if (i == index) return p->info;
        i++;
    }

    if (DISPLAY_INFO) printf("  -- Posicao invalida.\n");

    return INT_MIN;
}

/**
* Retorna o tamanho da lista.
* Lista com um elemento Size=1.
* Lista nula, retorna INT_MIN.
*/
int SLLgetSize (SLL* lista){
    if (lista == NULL){
        if (DISPLAY_INFO) printf("  -- Lista nula.\n");
        return INT_MIN;
    }

    SLL* p;
    int i=0;
    for (p=lista; p!=NULL; p=p->next){
        i++;
    }
    return i;
}

/**
* Retorna o ponteiro para a cauda a head.
*/
SLL* SLLgetTail (SLL* head){
    if (head==NULL){
        if (DISPLAY_INFO)
            printf("  -- Lista vazia. Nao existe cauda.\n");
        return NULL;
    }

    if (head->next == NULL) {
        return head;
    }

    SLL* p = head;
    while (p->next != NULL)
        p = p->next;

    return p;
}

/**
* Imprime lista
* Formato: [x, y, z] - Size: l
*/
void SLLprint (SLL* lista){
    if (lista == NULL){
        printf("  -- [NULL] - Size: -1.\n");
        return;
    }

    SLL* p = lista;
    int i=0;
    printf("  -- [ %d", p->info);
    p = p->next;
    for (;p!=NULL;p=p->next){
        printf(", %d", p->info);
        i++;
    }
    printf("] - Size: %d.\n", i+1);
}

#endif
