#ifndef STATICDOUBLESTACK_H
#define STATICDOUBLESTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Macros.h"

#ifndef MAXSIZESDSSDS
    #define MAXSIZESDS 20
#endif

struct staticdoublestack{
    int data[MAXSIZESDS];
    int pilha1Current; //Lado esquerdo
    int pilha2Current; //Lado direito
    short isCheia;
};
typedef struct staticdoublestack StaticDoubleStack;

void SDStackPush(StaticDoubleStack* estrutura, short pilha, int val);
int SDStackPop(StaticDoubleStack* estrutura, short pilha);
void SDStackPrint (StaticDoubleStack* estrutura);
void SDStackExtendedPrint (StaticDoubleStack* estrutura);

/**
* Dada uma estrutura, verifica se estao cheias ou vazias as pilhas. Params.:
* - estrutura: Ponteiro para a pilha.
*
* Retorna 0 se ambas estao vazias; 1 se a primeira e nao vazia; 2 se a
* segunda e nao vazia; 3 se as duas sao nao vazias e 4 se o vetor esta cheio.
*/
short SDStackEstado (StaticDoubleStack* estrutura){
    short vazia=0;

    if (estrutura->isCheia) return 4;

    if (estrutura->pilha1Current>0) vazia=1;
    if (estrutura->pilha2Current>0 && vazia==0) vazia=2;
    if (estrutura->pilha2Current>0 && vazia==1) vazia=3;

    return vazia;
}

/**
* Insere elementos em uma pilha, caso o vetor nao esteja cheio. Params.:
* - estrutura: Ponteiro para a struct.
* - pilha: 1 para primeira pilha e 2 para a segunda. Outro numero nao acontecera nada.
*/
void SDStackPush(StaticDoubleStack* estrutura, short pilha, int val){
    if (estrutura->isCheia == 1){
        if (DISPLAY_INFO) printf ("  -- Erro. Ambas pilhas cheias.\n");
        return;
    }

    if (pilha == 1){
        estrutura->data[estrutura->pilha1Current] = val;
        estrutura->pilha1Current++;
        if (DISPLAY_INFO) printf ("  -- Adicionado na pilha1: %d. Current1: %d.\n", val, estrutura->pilha1Current);
    } else if (pilha == 2) {
        estrutura->data[MAXSIZESDS - estrutura->pilha2Current - 1] = val;
        estrutura->pilha2Current++;
        if (DISPLAY_INFO) printf ("  -- Adicionado na pilha2: %d. Current2: %d.\n", val, estrutura->pilha2Current);
    } else {
        if (DISPLAY_INFO) printf ("  -- Erro. Pilha invalida.\n");
    }

    if (estrutura->pilha1Current + estrutura->pilha2Current >= MAXSIZESDS){
        estrutura->isCheia = 1;
        return;
    }

    return;
}

/**
* Remocao de elementos de uma das pilhas. Params.:
* - estrutura: Ponteiro para a struct.
* - pilha: 1 para primeira pilha e 2 para a segunda. Outro numero nao acontecera nada.
*
* Retorna o inteiro removido da posicao.
*
* Obs.: A remocao nao remove os elementos propriamente, apenas reduz a posicao atual de
* uma das pilhas; para que o valor "removido" possa ser, eventualmente, sobreescrito.
* Note que a func. "SDStackExtendedPrint" mostrara valores deletados, ja que nao se baseia
* nas posicoes e eh usada para debug.
*/
int SDStackPop(StaticDoubleStack* estrutura, short pilha){
    if (SDStackEstado(estrutura) == 0){
        if (DISPLAY_INFO) printf ("  -- Erro. Ambas pilhas vazias.\n");
        return 0;
    }

    int val;

    if (pilha == 1){

        if (estrutura->pilha1Current > 0){ //Protecao para nao remover elementos em "posicao negativa"
            val = estrutura->data[estrutura->pilha1Current-1];
            estrutura->pilha1Current--;
            if (DISPLAY_INFO) printf ("  -- Removido da pilha1: %d. Current1: %d.\n", val, estrutura->pilha1Current);
        } else {
            if (DISPLAY_INFO) printf ("  -- Pilha 1 vazia. Impossivel remover elemento.\n");
        }

    } else if (pilha == 2) {

        if (estrutura->pilha2Current > 0){ //Protecao para nao remover elementos em "posicao negativa"
            val = estrutura->data[estrutura->pilha2Current-1];
            estrutura->pilha2Current--;
            if (DISPLAY_INFO) printf ("  -- Removido da pilha2: %d. Current2: %d.\n", val, estrutura->pilha2Current);
        } else {
            if (DISPLAY_INFO) printf ("  -- Pilha 2 vazia. Impossivel remover elemento.\n");
        }

    } else {
        if (DISPLAY_INFO) printf ("  -- Erro. Pilha invalida.\n");
    }

    if (estrutura->pilha1Current + estrutura->pilha2Current < MAXSIZESDS)
        estrutura->isCheia = 0;

    return val;
}

/**
* Imprime as duas pilhas (apenas os elementos validos).
* Formato: Pilha1:  ...   \n
*          Pilha2:  ...   \n
*/
void SDStackPrint (StaticDoubleStack* estrutura){
    printf ("  -- Pilha1: ");
    int i;
    for (i=0; i<estrutura->pilha1Current; i++){
        printf ("%d ", estrutura->data[i]);
    }
    printf ("  <-Topo \n");
    printf ("     Pilha2: ");
    for (i=MAXSIZESDS-1; i > ( MAXSIZESDS - estrutura->pilha2Current-1); i--){
        printf ("%d ", estrutura->data[i]);
    }
    printf ("  <-Topo \n");
    return;
}

/**
* Imprime o vetor de dados em sua totalidade. Usado para verificacao de erros.
* Note que ele pode imprimir "dados que nao mais existem", devido a estrutura do SDStackPop.
*/
void SDStackExtendedPrint (StaticDoubleStack* estrutura){
    int i;
    printf ("  -- Data: ");
    for (i=0; i<MAXSIZESDS; i++){
        printf ("%d ", estrutura->data[i]);
    }
    printf ("  <-Topo \n");
}

/**
* Inicializador de componentes.
* Retorna ponteiro para uma pilha sequencial (estatica).
*/
StaticDoubleStack* createStaticStack (){
    StaticDoubleStack* newPtr = ALLOC_STRUCT(StaticDoubleStack);
    newPtr->isCheia=0;
    newPtr->pilha1Current=0;
    newPtr->pilha2Current=0;
    return newPtr;
}

void destroiStatickDoubleStack( StaticDoubleStack* estrutura){
    free(estrutura);
}

#endif
