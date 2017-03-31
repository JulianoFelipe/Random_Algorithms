#include "Macros.h"

#ifndef CHARNODE_H
#define CHARNODE_H

#define NEWCNODE ALLOC_STRUCT(CharNode)

typedef struct cnode CharNode;

/**
* Define a estrutura basica de
* um nodo.
*/
struct cnode{
    char info[81]; //char info[81];
    CharNode* next;
    CharNode* prev;
};

/**
* Cria um nodo vazio
*/
CharNode* createC(void){
    return NULL;
}

#endif



