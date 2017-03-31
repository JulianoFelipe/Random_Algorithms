#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "ExtendedNode.h"
#include "Node.h"

#define Queue Queue
typedef struct extnode Queue;

Queue* QueueCreate(int maxSize);
Queue* QueueDestroi (Queue* fila);
Queue* QueueCreateFirst (Queue* fila, int val);
Queue* EnQueue (Queue* fila, int val);
int DeQueue (Queue* fila);
int QueueSearch(Queue* fila, int P);
int QueueNumElements (Queue* fila);
int QueueGetMaxSize (Queue* fila);
void QueuePrint (Queue* fila);

/**
* Cria uma fila com no maximo "maxSize" elementos.
*/
Queue* QueueCreate(int maxSize){
    Queue* t = extCreate(maxSize);
    t->impN->current=0;
    return t;
}

/**
* Destroi a fila e libera toda a memoria.
* Retorna NULL para substituir o ponteiro.
*/
Queue* QueueDestroi (Queue* fila){
    if (fila == NULL){
        if (DISPLAY_INFO) printf("  -- Fila nula. Retorna-se NULL.\n");
        return fila;
    }

    if (fila->impN->current == 0){
        if (DISPLAY_INFO) printf("  -- Fila vazia. Destroi-se estrutura.\n");
        free(fila);
        return NULL;
    }

    Node* aux;
    Node* p = fila->impN->node;
    while (p->next != NULL){
        aux = p;
        p = p->next;
        free(aux);
    }
    free(p);
    free(fila);
    if (DISPLAY_INFO) printf("  -- Fila destruida.\n");

    return NULL;
}

/**
* Insere primeiro nodo na fila
* Retorna fila com o elemento adicionado.
*/
Queue* QueueCreateFirst (Queue* fila, int val){
    Node* first = NEWNODE;
    first->info = val;
    first->next = NULL;

    fila->impN->node = first;
    fila->tail = first;
    fila->impN->current=1;

    if (DISPLAY_INFO) printf("  -- Inserido primeiro elemento: %d.\n", val);
    return fila;
}

/**
* Insere Nodes na fila (tail, ja que e uma fila).
* Retorna fila com o elemento adicionado.
*/
Queue* EnQueue(Queue* fila, int val){
    if (fila->impN->current == -1){
        if (DISPLAY_INFO) printf("  -- Fila nao inicializada.\n");
        return fila;
    }

    if (fila->impN->current == 0) return QueueCreateFirst (fila, val);
    if (fila->impN->current == fila->impN->MAXSIZE){
        if (DISPLAY_INFO) printf("  -- Fila cheia. %d/%d elemento(s).\n", fila->impN->current, fila->impN->MAXSIZE);
        return fila;
    }

    Node* novo = NEWNODE;
    novo->info=val;
    novo->next=NULL;

    Node* prevTail = fila->tail;
    prevTail->next = novo;
    fila->tail = prevTail->next; //Avanca a cauda.

    fila->impN->current++;
    if (DISPLAY_INFO) printf("  -- Inserido elemento: %d. Fila: %d/%d elemento(s).\n", val, fila->impN->current, fila->impN->MAXSIZE);
    return fila;
}

/**
* Retira o primeiro node da fila.
* Retorna o elemento retirado (0 em caso de erro).
* Obs.: Se retirar o elemento  0, retornara 0. Assim,
* 0 nao deve ser usado como deteccao de erro.
*/
int DeQueue (Queue* fila){
    if (fila==NULL){
        if (DISPLAY_INFO) printf("  -- Fila nula.\n");
        return 0;
    }

    if (fila->impN->current == 0){
        if (DISPLAY_INFO) printf("  -- Fila vazia. %d/%d elemento(s).\n", fila->impN->current, fila->impN->MAXSIZE);
        return 0;
    }
    int val=0;
    Node* tmp = fila->impN->node;

    if (tmp->next == NULL){
        val = tmp->info;
        if (DISPLAY_INFO) printf("  -- Removido elemento: %d. Fila: %d/%d elemento(s).\n", tmp->info, fila->impN->current-1, fila->impN->MAXSIZE);
        free(tmp); ///Maybe the next line is a mistake...
        //fila->impN->node=NULL;
        fila->impN->current=0;
        return val;
    }
    val = tmp->info;
    if (DISPLAY_INFO) printf("  -- Removido elemento: %d. Fila: %d/%d elemento(s).\n", tmp->info, fila->impN->current-1, fila->impN->MAXSIZE);

    fila->impN->node = fila->impN->node->next; //Avanca a cabeca
    free(tmp);
    fila->impN->current--;

    return val;
}

///IMPLEMENT THIS?
/**
* Busca Node na fila.
* Retorna o index (index >= 0) se encontrou;
* E -1 se não encontrou.
*/
int QueueSearch(Queue* fila, int P){
    if (fila == NULL){
        if (DISPLAY_INFO)
            printf("  -- Fila nula. Nao existem elementos.\n");
        return -1;
    }

    if (fila->tail->info == P){ //Hooray, esta na cauda.
        int index = fila->impN->current - 1;
        if (DISPLAY_INFO)
                printf("  -- Encontrado %d em -> Index(%d). Cauda.\n", P, index);
        return index;
    }

    Node* p = fila->impN->node;
    int i=0;
    while (p->next != NULL){
        if (p->info == P){
            if (DISPLAY_INFO)
                printf("  -- Encontrado %d em -> Index(%d).\n", P, i);
            return i;
        }
        p = p->next;
        i++;
    }

    if (p->info == P){
            if (DISPLAY_INFO)
                printf("  -- Encontrado %d em -> Index(%d).\n", P, i);
            return i;
        }

    if (DISPLAY_INFO)
        printf("  -- Elemento %d nao encontrado. Inspecionado(s) %d elemento(s).\n", P, i+1);

    return -1;
}

/**
* Retorna o numero de elementos inseridos.
* e.g.: fila->impN->current
*/
int QueueNumElements (Queue* fila){
    return (fila->impN->current);
}

/**
* Retorna o tamanho maximo da fila.
* fila nula, retorna INT_MIN.
*/
int QueueGetMaxSize (Queue* fila){
    if (fila == NULL){
        if (DISPLAY_INFO) printf("  -- Fila nula.\n");
        return INT_MIN;
    }

    return fila->impN->MAXSIZE;
}

/**
* Imprime fila. Esquerda = topo.
* Formato: Topo->[x, y, z] - Size: l
*/
void QueuePrint (Queue* fila){
    if (fila == NULL){
        printf("  -- Queue: Topo->[NULL] - Size: -1\n");
        return;
    }

    if (fila->impN->current == 0){
        printf("  -- Fila vazia. %d/%d elemento(s). Size: 0\n", fila->impN->current, fila->impN->MAXSIZE);
        return;
    }

    Node* head = fila->impN->node;
    if (head->next == NULL) {
        printf("  -- Queue: Topo->[%d] - Size: 1\n", head->info);
        return;
    }

    Node* p = head;
    int i=0;
    printf("  -- Queue: Topo->[");
    while (p->next != NULL){
        printf ("%d, ", p->info);
        p = p->next;
        i++;
    }
    printf("%d] - Size: %d.\n",p->info, i+1);
}

#endif
