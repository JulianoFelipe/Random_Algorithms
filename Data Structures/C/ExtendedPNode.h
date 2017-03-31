#ifndef EXTENDEDPNODE_H
#define EXTENDEDPNODE_H

#include "Macros.h"
#include "PriorityNode.h"

#define NEWEXTPNODE ALLOC_STRUCT(ExtPNode)

typedef struct extpnode ExtPNode;

/**
* Define a estrutura basica de
* um nodo.
*/
struct extpnode{
    int current;
    int MAX;
    PriorityNode* head;
    PriorityNode* tail;
};

/**
* Cria um nodo melhorado vazio
*/
ExtPNode* extPCreate(int maxSize){
    ExtPNode* novo = NEWEXTPNODE;
    novo->MAX = maxSize;
    novo->current=0;
    novo->head = NULL;
    novo->tail = NULL;
    return novo;
}

#endif



