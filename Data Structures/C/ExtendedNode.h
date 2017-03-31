#ifndef EXTENDEDNODE_H
#define EXTENDEDNODE_H

#include "Macros.h"
#include "ImprovedNode.h"

#define NEWEXTNODE ALLOC_STRUCT(ExtNode)

typedef struct extnode ExtNode;

/**
* Define a estrutura basica de
* um nodo.
*/
struct extnode{
    ImpNode* impN;
    Node* tail;
};

/**
* Cria um nodo melhorado vazio
*/
ExtNode* extCreate(int maxSize){
    ExtNode* novo = NEWEXTNODE;
    novo->impN = impCreate(maxSize);
    return novo;
}

#endif



