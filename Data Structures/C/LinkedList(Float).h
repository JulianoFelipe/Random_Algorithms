#ifndef LINKEDLIST_FLOAT_H
#define LINKEDLIST_FLOAT_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "FloatNode.h"
#include "Macros.h"

#define LinkedListFloat SLLFloat
typedef struct fnode SLLFloat;
///SLLFloat_Float - Singly Linked List cujo "info" é um float
SLLFloat* SLLFloatdestroi (SLLFloat* lista);
SLLFloat* SLLFloatinsert(SLLFloat* lista, float val);
SLLFloat* SLLFloatremoveIndex (SLLFloat* lista, int index);
float SLLFloatsearch(SLLFloat* lista, float P);
float SLLFloatgetFromIndex (SLLFloat* lista, int index);
int SLLFloatgetSize (SLLFloat* lista);
SLLFloat* SLLFloatgetTail (SLLFloat* head);
void SLLFloatprint (SLLFloat* lista);
/// Exercicio 1
SLLFloat* SLLFloatsplit (SLLFloat* lista, float token);
/// Exercicio 2
SLLFloat* SLLFloatAppend (SLLFloat* lista1, SLLFloat* lista2);
/// Exercicio 3
SLLFloat* SLLFloatSublist (SLLFloat* lista, unsigned int terms);



/**
* Dada uma lista e um inteiro "token", separa-se
* a lista na ocorrência do token. Retorna o resultado
* do split, o resto da lista mantêm-se no ponteiro inicial.
*/
SLLFloat* SLLFloatsplit (SLLFloat* lista, float token){
    SLLFloat* p = lista;

    //Percorre a lista até encontrar o token
    //Quando encontra, sai do look
    while (p->info != token){
        p = p->next;
    }
    //P é o nodo cujo "info" é o token
    //Split no próximo nodo.

    SLLFloat* aux = p->next;
    p->next = NULL;

    return aux;
}

/**
* Concatena duas listas. De modo que os ponteiros permanecam inalterados, ou seja,
* ptr para lista1 aponta para o inicio da lista concatenada e ptr da lista2 aponta
* para alguma parte no meio da lista.
* Retorna ptr igual a lista1, ou seja, para o inicio da lista concatenada.
*/
SLLFloat* SLLFloatAppend (SLLFloat* lista1, SLLFloat* lista2){
    if (lista1 == NULL){
        if (DISPLAY_INFO) printf ("  -- A primeira lista e nula. Retorna-se a segunda em sua totalidade...\n");
        return lista2;
    }

    if (lista2 == NULL){
        if (DISPLAY_INFO) printf ("  -- A segunda lista e nula. Retorna-se a primeira em sua totalidade...\n");
        return lista1;
    }

    SLLFloat* tail = SLLFloatgetTail(lista1);
    tail->next = lista2;
    return lista1;
}

/**
* Retira os "terms" primeiros elementos de uma lista.
* Retorna ponteiro para a mesma lista.
*/
SLLFloat* SLLFloatSublist (SLLFloat* lista, unsigned int terms){
    if (lista == NULL){
        if (DISPLAY_INFO) printf ("  -- Lista nula. Nao ha como retirar elementos.\n");
        return NULL;
    }

    while ((lista->next != NULL) && terms>0){
        lista = SLLFloatremoveIndex(lista, 0);

        if ((lista == NULL) && (terms > 0)){
            if (DISPLAY_INFO) printf ("  -- Retirados todos os termos da lista, pois \"n\" era maior que a mesma.\n");
            return NULL;
        }

        terms--;
    }

    return lista;
}



///Funcoes auxiliares e implementadas anteriormente


/**
* Destroi a lista e libera toda a memoria.
* Retorna NULL para substituir o ponteiro.
*/
SLLFloat* SLLFloatdestroi (SLLFloat* lista){
    if (lista==NULL){
        if (DISPLAY_INFO) printf("  -- Lista nula. Retorna-se NULL\n");
        return NULL;
    }

    if (lista->next == NULL){
        SLLFloat* aux = lista->next;
        free(aux);
        if (DISPLAY_INFO) printf("  -- Lista destruida. Apenas um elemento.\n");
        return NULL;
    }

    SLLFloat* aux;
    SLLFloat* p = lista;
    while (p->next != NULL){
        aux = p->next;
        free (p);
        p = aux;
    }

    if (DISPLAY_INFO) printf("  -- Lista destruida.\n");

    return NULL;
}

/**
* Insere SLLFloats na lista
* Retorna lista com o elemento adicionado.
*/
SLLFloat* SLLFloatinsert(SLLFloat* lista, float val){
    //SLLFloat* novo=(SLLFloat*) m(sizeof(SLLFloat));
    SLLFloat* novo = NEWFNODE; //ALLOC_STRUCT(SLLFloat);
    novo->info=val;
    novo->next=lista;

    if (DISPLAY_INFO) printf("  -- Elemento %.3f inserido.\n", val);

    return novo;
}

/**
* Remove elemento da lista.
* Retorna a lista com o elemento removido.
* Se o elemento nao foi encontrado, a mesma
* lista e retornada.
*/
SLLFloat* SLLFloatremoveElement (SLLFloat* lista, float R){
    if (lista->info == R){
        SLLFloat* tmp = lista;
        lista = tmp->next;
        free(tmp);
        if (DISPLAY_INFO) printf("  -- Elemento %.3f removido da head.\n", R);
        return lista;
    }
    short found_flag=0;
    SLLFloat* p;
    SLLFloat* aux;
    for (p=lista;p->next!=NULL;p=p->next){
        aux=p->next;
        if (aux->info==R){
            p->next=aux->next;
            free(aux);
            if (DISPLAY_INFO) printf("  -- Elemento %.3f removido.\n", R);
            found_flag++;
            break;
        }
    }

    if (DISPLAY_INFO==1 && found_flag==0) printf("  -- Elemento %.3f nao encontrado.\n", R);

    return lista;
}

/**
* Remove elemento da lista em um determinado indice.
* (1º elemento -> indice = 0.)
* Retorna a lista com o elemento removido.
* Se o indice for invalido, a mesma
* lista e retornada.
*/
SLLFloat* SLLFloatremoveIndex (SLLFloat* lista, int index){
    if (lista == NULL) return NULL;

    if (index == 0){
        SLLFloat* tmp = lista;
        if (DISPLAY_INFO) printf("  -- Elemento na posicao %d (head) removido: %.3f\n", index, tmp->info);
        lista = tmp->next;
        free(tmp);
        return lista;
    }

    SLLFloat* p = lista;
    SLLFloat* aux;
    int i=1;
    p = p->next;
    for (p=lista;p->next!=NULL;p=p->next){
        aux=p->next;
        if (i==index){
            if (DISPLAY_INFO) printf("  -- Elemento %.3f removido.\n", aux->info);
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
float SLLFloatsearch(SLLFloat* lista, float P){
    if (lista == NULL){
        if(DISPLAY_INFO)
            printf("  -- Lista nula. Nao existem elementos.\n");
        return -1;
    }

    int cont=0;
    SLLFloat* p;
    for (p=lista;p!=NULL;p=p->next){
        if(p->info==P){
            if (DISPLAY_INFO)
                printf("  -- Encontrado em  %.3f -> Index(%d).\n", P, cont);
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
float SLLFloatgetFromIndex (SLLFloat* lista, int index){
    if (lista == NULL) {
        if (DISPLAY_INFO) printf("  -- Lista nula.\n");
        return INT_MAX;
    }


    if (index == 0) return lista->info;

    SLLFloat* p = lista;
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
int SLLFloatgetSize (SLLFloat* lista){
    if (lista == NULL){
        if (DISPLAY_INFO) printf("  -- Lista nula.\n");
        return INT_MIN;
    }

    SLLFloat* p;
    int i=0;
    for (p=lista; p!=NULL; p=p->next){
        i++;
    }
    return i;
}

/**
* Retorna o ponteiro para a cauda a head.
*/
SLLFloat* SLLFloatgetTail (SLLFloat* head){
    if (head==NULL){
        if (DISPLAY_INFO)
            printf("  -- Lista vazia. Nao existe cauda.\n");
        return NULL;
    }

    if (head->next == NULL) {
        return head;
    }

    SLLFloat* p = head;
    while (p->next != NULL)
        p = p->next;

    return p;
}

/**
* Imprime lista
* Formato: [x, y, z] - Size: l
*/
void SLLFloatprint (SLLFloat* lista){
    if (lista == NULL){
        printf("  -- [NULL] - Size: -1.\n");
        return;
    }

    SLLFloat* p = lista;
    int i=0;
    printf("  -- [ %.3f", p->info);
    p = p->next;
    for (;p!=NULL;p=p->next){
        printf(", %.3f", p->info);
        i++;
    }
    printf("] - Size: %d.\n", i+1);
}

#endif
