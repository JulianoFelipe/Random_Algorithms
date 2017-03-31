#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "ExtendedPNode.h"
#include "PriorityNode.h"

#define PPQueue PPQueue
typedef struct extpnode PQueue; //PriorityPQueue

PQueue* PQueueCreate(int maxSize);
PQueue* PQueueDestroi (PQueue* fila);
PQueue* PQueueCreateFirst (PQueue* fila, int info, int priority, float extra);
PQueue* PEnQueue(PQueue* fila, int info, int priority, float extra);
int PDeQueue (PQueue* fila);
int PQueueSearch(PQueue* fila, int P);
int PQueueNumElements (PQueue* fila);
int PQueueGetMaxSize (PQueue* fila);
void PQueuePrint (PQueue* fila);

/**
* Divide uma fila em duas, baseado em um token.
* Retorna uma fila com PNodes com prioridades menores
* ou iguais ao token. A que o ponteiro foi passada, contem
* os elementos restantes. Params.:
* - lista1: Lista para dividir, e, depois, apontar para os nodes
*   restantes (cujas prioridades sao maiores que o token).
* - priorityToken: Prioridade para divisao.
*
* Obs.: Se tratando de operacoes sobre filas, remove-se todos
* os elementos da primeira fila para inspeciona-los e inseri-los
* em suas posicoes adequadas.
*/
PQueue* PQueueSplitPriority(PQueue* lista1, int priorityToken){
    PQueue* ret = PQueueCreate(lista1->MAX);
    PQueue* newL = PQueueCreate(lista1->MAX);

    PriorityNode* p = lista1->head;
    while (lista1->current > 0){
        if (p->priority <= priorityToken){
            PEnQueue(ret, p->info, p->priority, p->extraInfo);
        } else {
            PEnQueue(newL, p->info, p->priority, p->extraInfo);
        }
        PDeQueue(lista1);
        p = p->next;
    }

    lista1->head = newL->head; //Aponta lista1 para os elementos com prioridade maior que o token
    lista1->current = newL->current;
    lista1->tail = newL->tail;

    newL->head=NULL; //Substitui-se ponteiros para nao deletar o que foi passado para lista1
    newL->current=0;
    newL->tail=NULL;
    PQueueDestroi(newL); //Desaloca o que sobra.

    return ret;
}

///Funcs. base

/**
* Cria uma fila com no maximo "maxSize" elementos.
*/
PQueue* PQueueCreate(int maxSize){
    PQueue* t = extPCreate(maxSize);
    return t;
}

/**
* Destroi a fila e libera toda a memoria.
* Retorna NULL para substituir o ponteiro.
*/
PQueue* PQueueDestroi (PQueue* fila){
    if (fila == NULL){
        if (DISPLAY_INFO) printf("  -- Fila nula. Retorna-se NULL.\n");
        return fila;
    }

    if (fila->current == 0){
        if (DISPLAY_INFO) printf("  -- Fila vazia. Destroi-se estrutura.\n");
        free(fila);
        return NULL;
    }

    PriorityNode* aux;
    PriorityNode* p = fila->head;
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
PQueue* PQueueCreateFirst (PQueue* fila, int info, int priority, float extra){
    PriorityNode* first = NEWPRIORITYNODE;
    first->info = info;
    first->extraInfo = extra;
    first->priority = priority;
    first->next = NULL;

    fila->head = first;
    fila->tail = first;
    fila->current=1;

    if (DISPLAY_INFO) printf("  -- Inserido primeiro elemento: %d.\n", info);
    return fila;
}

/**
* Insere Nodes na fila (tail, ja que e uma fila).
* Retorna fila com o elemento adicionado.
*/
PQueue* PEnQueue(PQueue* fila, int info, int priority, float extra){
    if (fila->current == -1){
        if (DISPLAY_INFO) printf("  -- Fila nao inicializada.\n");
        return fila;
    }

    if (fila->current == 0) return PQueueCreateFirst (fila, info, priority, extra);
    if (fila->current == fila->MAX){
        if (DISPLAY_INFO) printf("  -- Fila cheia. %d/%d elemento(s).\n", fila->current, fila->MAX);
        return fila;
    }

    PriorityNode* novo = NEWPRIORITYNODE;
    novo->info=info;
    novo->extraInfo = extra;
    novo->priority = priority;

    novo->next=NULL;

    PriorityNode* prevTail = fila->tail;
    prevTail->next = novo; //Cauda antiga aponta para o novo
    fila->tail = prevTail->next; //Avanca a cauda.

    fila->current++;
    if (DISPLAY_INFO) printf("  -- Inserido elemento: %d. Fila: %d/%d elemento(s).\n", info, fila->current, fila->MAX);
    return fila;
}

/**
* Retira o primeiro node da fila.
* Retorna o elemento retirado (0 em caso de erro).
* Obs.: Se retirar o elemento  0, retornara 0. Assim,
* 0 nao deve ser usado como deteccao de erro.
*/
int PDeQueue (PQueue* fila){
    if (fila==NULL){
        if (DISPLAY_INFO) printf("  -- Fila nula.\n");
        return 0;
    }

    if (fila->current == 0){
        if (DISPLAY_INFO) printf("  -- Fila vazia. %d/%d elemento(s).\n", fila->current, fila->MAX);
        return 0;
    }
    int val=0;
    PriorityNode* tmp = fila->head;

    if (tmp->next == NULL){
        val = tmp->info;
        if (DISPLAY_INFO) printf("  -- Removido elemento: %d. Fila: %d/%d elemento(s).\n", tmp->info, fila->current-1, fila->MAX);
        free(tmp); ///Maybe the next line is a mistake...
        //fila->head=NULL;
        fila->current=0;
        return val;
    }
    val = tmp->info;
    if (DISPLAY_INFO) printf("  -- Removido elemento: %d. Fila: %d/%d elemento(s).\n", tmp->info, fila->current-1, fila->MAX);

    fila->head = fila->head->next; //Avanca a cabeca
    free(tmp);
    fila->current--;

    return val;
}

///IMPLEMENT THIS?
/**
* Busca Node na fila.
* Retorna o index (index >= 0) se encontrou;
* E -1 se não encontrou.
*/
int PQueueSearch(PQueue* fila, int P){
    if (fila == NULL){
        if (DISPLAY_INFO)
            printf("  -- Fila nula. Nao existem elementos.\n");
        return -1;
    }

    if (fila->tail->info == P){ //Hooray, esta na cauda.
        int index = fila->current - 1;
        if (DISPLAY_INFO)
                printf("  -- Encontrado %d em -> Index(%d). Cauda.\n", P, index);
        return index;
    }

    PriorityNode* p = fila->head;
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
* e.g.: fila->current
*/
int PQueueNumElements (PQueue* fila){
    return (fila->current);
}

/**
* Retorna o tamanho maximo da fila.
* fila nula, retorna INT_MIN.
*/
int PQueueGetMaxSize (PQueue* fila){
    if (fila == NULL){
        if (DISPLAY_INFO) printf("  -- Fila nula.\n");
        return INT_MIN;
    }

    return fila->MAX;
}

/**
* Imprime fila. Esquerda = topo.
* Formato: Topo->[x, y, z] - Size: l
*/
void PQueuePrint (PQueue* fila){
    if (fila == NULL){
        printf("  -- PQueue: Topo->[NULL] - Size: -1\n");
        return;
    }

    if (fila->current == 0){
        printf("  -- PQueue vazia. %d/%d elemento(s). Size: 0\n", fila->current, fila->MAX);
        return;
    }

    PriorityNode* head = fila->head;
    if (head->next == NULL) {
        printf("  -- PQueue: Topo->[I:%d P:%d E:%.3f] - Size: 1\n", head->info, head->priority, head->extraInfo);
        return;
    }

    PriorityNode* p = head;
    int i=0;
    printf("  -- PQueue: Topo->[");
    while (p->next != NULL){
        printf ("I:%d P:%d E:%.3f, ", p->info, p->priority, p->extraInfo);
        p = p->next;
        i++;
    }
    printf("I:%d P:%d E:%.3f] - Size: %d.\n", p->info, p->priority, p->extraInfo, i+1);
}

#endif
