#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h> //memmove para mover inteiros... Yeah...
#include "Macros.h"

#define MAXSIZESQ 10

struct staticqueue{
    int data[MAXSIZESQ];
    int current; //Lado direito current
    short isCheio;
};
typedef struct staticqueue StaticQueue;

short SQueue (StaticQueue* estrutura);
void SQEnqueue(StaticQueue* estrutura, int val);
int SQDequeue(StaticQueue* estrutura);
void SQueuePrint (StaticQueue* estrutura);
void SQueueExtendedPrint (StaticQueue* estrutura);
StaticQueue* createStaticQueue (short forceInit);
void destroiStaticQueue( StaticQueue* estrutura);

/**
* Dada um queue, verifica se esta cheio ou vazio. Params.:
* - estrutura: Ponteiro para o queue.
*
* Retorna 0 se vazio; 1 cheio; 2 se parcialmente cheio.
*/
short SQueueEstado (StaticQueue* estrutura){
    if (estrutura->isCheio) return 1;

    if (estrutura->current == 0) return 0;

    return 2;
}

/**
* Insere elementos em uma pilha, caso o vetor nao esteja cheio. Params.:
* - estrutura: Ponteiro para a struct.
* - pilha: 1 para primeira pilha e 2 para a segunda. Outro numero nao acontecera nada.
*/
void SQEnqueue(StaticQueue* estrutura, int val){
    if (estrutura->isCheio == 1){
        if (DISPLAY_INFO) printf ("  -- Erro. Pilha cheia.\n");
        return;
    }

    //Shift todo o array para a direita em uma posicao
    memmove(&estrutura->data[1], &estrutura->data[0], sizeof(estrutura->data) - sizeof(*estrutura->data));
    estrutura->data[0] = val;
    if (DISPLAY_INFO) printf ("  -- Enfileirado(Enqueued): %d. Estado: %d/%d.\n", val, estrutura->current+1, MAXSIZESQ);

    estrutura->current++;

    if (estrutura->current >= MAXSIZESQ){
        estrutura->isCheio = 1;
    }

    return;
}

/**
* Remocao de elementos de um dos lados do queue. Params.:
* - estrutura: Ponteiro para a struct.
* - lado: 1 para esquerda, 2 para a direita. Outro numero nao acontecera nada.
*
* Retorna o inteiro removido da posicao.
*
* Obs.: A remocao direita nao remove os elementos propriamente, apenas reduz a
* current; para que o valor "removido" possa ser, eventualmente, sobreescrito.
* A remocao esquerda e feita com memmove, entao o removido eh sobreescrito.
* Note que a func. "SQueueExtendedPrint" mostrara valores deletados, ja que
* nao se baseia em current e eh usada para debug.
*/
int SQDequeue(StaticQueue* estrutura){
    if (SQueueEstado(estrutura) == 0){
        if (DISPLAY_INFO) printf ("  -- Erro. Queue vazia.\n");
        return 0;
    }

    int val;

    estrutura->current--; //Dec. antes para mostrar elemento "removido" do array. E current atual na impressao.
    val = estrutura->data[ estrutura->current ];
    if (DISPLAY_INFO) printf ("  -- Removido do lado direito: %d. Current: %d.\n", val, estrutura->current);

    if (estrutura->current < MAXSIZESQ)
        estrutura->isCheio = 0;

    return val;
}

/**
* Imprime o queue (apenas os elementos validos).
* Formato: Queue: [%d, %d, %d ...] - %d/%d elemento(s).\n
*/
void SQueuePrint (StaticQueue* estrutura){
    if (estrutura->current == 0){
        printf ("  --  Queue: [ ] - 0/%d elemento(s).\n", MAXSIZESQ);
        return;
    }

    printf ("  -- Queue: [ ");
    int i;
    int curr = estrutura->current;
    for (i=0; i<curr-1; i++){
        printf ("%d, ", estrutura->data[i]);
    }
    printf("%d] <-Topo - %d/%d elemento(s).\n", estrutura->data[i], estrutura->current, MAXSIZESQ);
    return;
}

/**
* Imprime o vetor de dados em sua totalidade. Usado para verificacao de erros.
* Note que ele pode imprimir "dados que nao mais existem", devido a estrutura do SQueue.
* Formato: Data: %d %d %d (<-C) %d ...   Obs.: C de Current.
*/
void SQueueExtendedPrint (StaticQueue* estrutura){
    int i;
    short flag=0;
    printf ("  -- Data: ");
    for (i=0; i<MAXSIZESQ; i++){
        printf ("%d ", estrutura->data[i]);
        if (i == estrutura->current){
                flag++;
                printf ("(<-C) ");
        }
    }
    if (flag==0) printf ("(MAX<-C)");
    printf ("\n");
}

/**
* Inicializador de componentes. Param.:
* - forceInit: Se !=0, inicializa todos os elementos
* de data em 0. Nao muda funcionalidade, apenas visualizacao.
*
* Retorna ponteiro para uma pilha sequencial (estatica).
*/
StaticQueue* createStaticQueue (short forceInit){
    StaticQueue* newPtr = ALLOC_STRUCT(StaticQueue);
    newPtr->isCheio=0;
    newPtr->current = 0;

    if (forceInit){
        int i;
        for (i=0; i<MAXSIZESQ; i++){
            newPtr->data[i]=0;
        }
    }

    return newPtr;
}

void destroiStaticQueue( StaticQueue* estrutura){
    free(estrutura);
}

#endif
