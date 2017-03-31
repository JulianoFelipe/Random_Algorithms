#ifndef STATICDEQUE_H
#define STATICDEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h> //memmove para mover inteiros... Yeah...
#include "Macros.h"

#define MAXSIZESD 10

struct staticdeque{
    int data[MAXSIZESD];
    int current; //Lado direito current
    short isCheio;
};
typedef struct staticdeque StaticDeque;

short SDequeEstado (StaticDeque* estrutura);
void SDEnqueue(StaticDeque* estrutura, short lado, int val);
int SDDequeue(StaticDeque* estrutura, short lado);
void SDequePrint (StaticDeque* estrutura);
void SDequeExtendedPrint (StaticDeque* estrutura);
StaticDeque* createStaticDeque (short forceInit);
void destroiStaticDeque( StaticDeque* estrutura);

/**
* Dada um deque, verifica se esta cheio ou vazio. Params.:
* - estrutura: Ponteiro para o deque.
*
* Retorna 0 se vazio; 1 cheio; 2 se parcialmente cheio.
*/
short SDequeEstado (StaticDeque* estrutura){
    if (estrutura->isCheio) return 1;

    if (estrutura->current == 0) return 0;

    return 2;
}

/**
* Insere elementos em uma pilha, caso o vetor nao esteja cheio. Params.:
* - estrutura: Ponteiro para a struct.
* - pilha: 1 para primeira pilha e 2 para a segunda. Outro numero nao acontecera nada.
*/
void SDEnqueue(StaticDeque* estrutura, short lado, int val){
    if (estrutura->isCheio == 1){
        if (DISPLAY_INFO) printf ("  -- Erro. Deque cheio.\n");
        return;
    }

    if (lado == 1){
        //Shift todo o array para a direita em uma posicao
        memmove(&estrutura->data[1], &estrutura->data[0], sizeof(estrutura->data) - sizeof(*estrutura->data));
        estrutura->data[0] = val;
        if (DISPLAY_INFO) printf ("  -- Adicionado no lado esquerdo: %d. Estado: %d/%d.\n", val, estrutura->current+1, MAXSIZESD);
    } else if (lado == 2) {
        estrutura->data[ estrutura->current ] = val;
        if (DISPLAY_INFO) printf ("  -- Adicionado no lado direito: %d. Estado: %d/%d.\n", val, estrutura->current+1, MAXSIZESD);
    } else {
        if (DISPLAY_INFO) printf ("  -- Erro. Lado invalida. 1 para esquerda, 2 para direita.\n");
    }
    estrutura->current++;

    if (estrutura->current >= MAXSIZESD){
        estrutura->isCheio = 1;
    }

    return;
}

/**
* Remocao de elementos de um dos lados do Deque. Params.:
* - estrutura: Ponteiro para a struct.
* - lado: 1 para esquerda, 2 para a direita. Outro numero nao acontecera nada.
*
* Retorna o inteiro removido da posicao.
*
* Obs.: A remocao direita nao remove os elementos propriamente, apenas reduz a
* current; para que o valor "removido" possa ser, eventualmente, sobreescrito.
* A remocao esquerda e feita com memmove, entao o removido eh sobreescrito.
* Note que a func. "SDequeExtendedPrint" mostrara valores deletados, ja que
* nao se baseia em current e eh usada para debug.
*/
int SDDequeue(StaticDeque* estrutura, short lado){
    if (SDequeEstado(estrutura) == 0){
        if (DISPLAY_INFO) printf ("  -- Erro. Deque vazio.\n");
        return 0;
    }

    int val;

    estrutura->current--; //Dec. antes para mostrar elemento "removido" do array. E current atual na impressao.
    if (lado == 1){
        val = estrutura->data[0];
        memmove(&estrutura->data[0], &estrutura->data[1], sizeof(estrutura->data) - sizeof(*estrutura->data)); //Shift left, one pos.
        if (DISPLAY_INFO) printf ("  -- Removido do lado esquerdo: %d. Estado: %d/%d.\n", val, estrutura->current, MAXSIZESD);
    } else if (lado == 2) {
        val = estrutura->data[ estrutura->current ];
        if (DISPLAY_INFO) printf ("  -- Removido do lado direito: %d. Estado: %d/%d.\n", val, estrutura->current, MAXSIZESD);
    } else {
        if (DISPLAY_INFO) printf ("  -- Erro. Lado invalida. 1 para esquerda, 2 para direita.\n");
    }

    if (estrutura->current < MAXSIZESD)
        estrutura->isCheio = 0;

    return val;
}

/**
* Imprime o deque (apenas os elementos validos).
* Formato: Deque: [%d, %d, %d ...] - %d/%d elemento(s).\n
*/
void SDequePrint (StaticDeque* estrutura){
    if (estrutura->current == 0){
        printf ("  -- Deque: [ ] - 0/%d elemento(s).\n", MAXSIZESD);
        return;
    }

    printf ("  -- Deque: [ ");
    int i;
    int curr = estrutura->current;
    for (i=0; i<curr-1; i++){
        printf ("%d, ", estrutura->data[i]);
    }
    printf("%d] - %d/%d elemento(s).\n", estrutura->data[i], estrutura->current, MAXSIZESD);
    return;
}

/**
* Imprime o vetor de dados em sua totalidade. Usado para verificacao de erros.
* Note que ele pode imprimir "dados que nao mais existem", devido a estrutura do SDequeDequeue.
* Formato: Data: %d %d %d (<-C) %d ...   Obs.: C de Current.
*/
void SDequeExtendedPrint (StaticDeque* estrutura){
    int i;
    short flag=0;
    printf ("  -- Data: ");
    for (i=0; i<MAXSIZESD; i++){
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
StaticDeque* createStaticDeque (short forceInit){
    StaticDeque* newPtr = ALLOC_STRUCT(StaticDeque);
    newPtr->isCheio=0;
    newPtr->current = 0;

    if (forceInit){
        int i;
        for (i=0; i<MAXSIZESD; i++){
            newPtr->data[i]=0;
        }
    }

    return newPtr;
}

void destroiStaticDeque( StaticDeque* estrutura){
    free(estrutura);
}

#endif
