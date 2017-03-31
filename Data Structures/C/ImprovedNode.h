#ifndef IMPROVEDNODE_H
#define IMPROVEDNODE_H

#include "Macros.h"

#define NEWIMPNODE ALLOC_STRUCT(ImpNode)

typedef struct impnode ImpNode;

/**
* Define a estrutura basica de
* um nodo.
*/
struct impnode{
    int MAXSIZE; //Nao da pra usar CONST, nenhum metodo "pode" acessar, entao
    int current;
    Node* node;
};

/**
* Cria um nodo melhorado vazio
*/
ImpNode* impCreate(int maxSize){
    ImpNode* novo = NEWIMPNODE;
    novo->MAXSIZE = maxSize;
    novo->current = -1;
    return novo;
}

#endif



