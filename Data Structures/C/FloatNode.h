#include "Macros.h"

#ifndef FLOATNODE_H
#define FLOATNODE_H

#define NEWFNODE ALLOC_STRUCT(FloatNode)

typedef struct fnode FloatNode;

/**
* Define a estrutura basica de
* um nodo.
*/
struct fnode{
    float info;
    FloatNode* next;
    FloatNode* prev;
};

/**
* Cria um nodo vazio
*/
FloatNode* createF(void){
    return NULL;
}

#endif



