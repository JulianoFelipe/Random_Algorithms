#include "Macros.h"

#ifndef PRIORITYNODE_H
#define PRIORITYNODE_H

#define NEWPRIORITYNODE ALLOC_STRUCT(PriorityNode)

typedef struct prioritynode PriorityNode;

/**
* Define a estrutura basica de
* um nodo.
*/
struct prioritynode{
    int priority;
    int info;
    float extraInfo;
    PriorityNode* next;
    PriorityNode* prev;
};

/**
* Cria um nodo vazio
*/
PriorityNode* createPNode(void){
    return NULL;
}

#endif



