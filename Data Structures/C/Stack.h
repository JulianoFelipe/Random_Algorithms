#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Node.h"
#include "ImprovedNode.h"
#include "Macros.h"

#define Stack Stack
typedef struct impnode Stack;

Stack* StackCreate(int maxSize);
Stack* StackDestroi (Stack* pilha);
Stack* StackCreateFirst (Stack* pilha, int val);
Stack* StackPush(Stack* pilha, int val);
int StackPop (Stack* list);
int StackSearch(Stack* pilha, int P);
int StackNumElements (Stack* pilha);
int StackGetMaxSize (Stack* pilha);
void StackPrint (Stack* pilha);

/**
* Cria uma pilha com no maximo "maxSize" elementos.
*/
Stack* StackCreate(int maxSize){
    Stack* t = impCreate(maxSize);
    t->current=0;
    return t;
}

/**
* Destroi a pilha e libera toda a memoria.
* Retorna NULL para substituir o ponteiro.
*/
Stack* StackDestroi (Stack* pilha){
    if (pilha == NULL){
        if (DISPLAY_INFO) printf("  -- Pilha nula. Retorna-se NULL.\n");
        return pilha;
    }

    if (pilha->current == 0){
        if (DISPLAY_INFO) printf("  -- Pilha vazia. Destroi-se estrutura.\n");
        free(pilha);
        return NULL;
    }

    Node* aux;
    Node* p = pilha->node;
    while (p->next != NULL){
        aux = p;
        p = p->next;
        free(aux);
    }
    free(p);
    free(pilha);
    if (DISPLAY_INFO) printf("  -- Pilha destruida.\n");

    return NULL;
}

/**
* Insere primeiro nodo na pilha
* Retorna pilha com o elemento adicionado.
*/
Stack* StackCreateFirst (Stack* pilha, int val){
    Node* first = NEWNODE;
    first->info = val;
    first->next = NULL;

    pilha->node = first;
    pilha->current=1;

    if (DISPLAY_INFO) printf("  -- Inserido primeiro elemento: %d. Pilha: %d/%d elemento(s).\n", val, pilha->current, pilha->MAXSIZE);
    return pilha;
}

/**
* Insere Nodes na pilha
* Retorna pilha com o elemento adicionado.
*/
Stack* StackPush(Stack* pilha, int val){
    if (pilha->current == -1){
        if (DISPLAY_INFO) printf("  -- Pilha nao inicializada.\n");
        return pilha;
    }
    if (pilha->current == 0) return StackCreateFirst (pilha, val);
    if (pilha->current == pilha->MAXSIZE){
        if (DISPLAY_INFO) printf("  -- Pilha cheia. %d/%d elemento(s).\n", pilha->current, pilha->MAXSIZE);
        return pilha;
    }

    Node* novo = NEWNODE;
    novo->info=val;
    novo->next=pilha->node;

    pilha->node = novo;
    pilha->current++;
    if (DISPLAY_INFO) printf("  -- Inserido elemento: %d. Pilha: %d/%d elemento(s).\n", val, pilha->current, pilha->MAXSIZE);
    return pilha;
}

///TODO: Arrumar desalocacao de elementos na pilha (Especialmente o  first)
/**
* Retira o primeiro node da pilha.
* Retorna o elemento retirado (0 em caso de erro).
* Obs.: Se retirar o elemento  0, retornara 0. Assim,
* 0 nao deve ser usado como deteccao de erro.
*/
int StackPop (Stack* pilha){
    if (pilha==NULL){
        if (DISPLAY_INFO) printf("  -- Pilha nula.\n");
        return 0;
    }

    if (pilha->current == 0){
        if (DISPLAY_INFO) printf("  -- Pilha vazia. %d/%d elemento(s).\n", pilha->current, pilha->MAXSIZE);
        return 0;
    }

    Node* tmp = pilha->node;
    int val=0;
    if (tmp->next == NULL){
        val = tmp->info;
        if (DISPLAY_INFO) printf("  -- Removido ultimo elemento: %d. Pilha: %d/%d elemento(s).\n", tmp->info, pilha->current-1, pilha->MAXSIZE);
        free(tmp);
        //pilha->node=NULL;
        pilha->current=0;
        return val;
    }
    val = tmp->info;
    if (DISPLAY_INFO) printf("  -- Removido elemento: %d. Pilha: %d/%d elemento(s).\n", tmp->info, pilha->current, pilha->MAXSIZE);

    pilha->node = pilha->node->next; //Avanca a cabeca
    free(tmp);
    pilha->current--;
    return val;
}

/**
* Busca Node na pilha.
* Retorna o index (index >= 0) se encontrou;
* E -1 se não encontrou.
*/
int StackSearch(Stack* pilha, int P){
    if (pilha == NULL){
        if (DISPLAY_INFO)
            printf("  -- Pilha nula. Nao existem elementos.\n");
        return -1;
    }

    Node* p = pilha->node;
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
* e.g.: pilha->current
*/
int StackNumElements (Stack* pilha){
    return (pilha->current);
}

/**
* Retorna o tamanho maximo da pilha.
* pilha nula, retorna INT_MIN.
*/
int StackGetMaxSize (Stack* pilha){
    if (pilha == NULL){
        if (DISPLAY_INFO) printf("  -- Pilha nula.\n");
        return INT_MIN;
    }

    return pilha->MAXSIZE;
}

/**
* Imprime pilha. Esquerda = topo.
* Formato: Topo->[x, y, z] - Size: l
*/
void StackPrint (Stack* pilha){
    if (pilha == NULL){
        printf("  -- Stack: Topo->[NULL] - Size: -1.\n");
        return;
    }

    if (pilha->current == 0){
        printf("  -- Pilha vazia. %d/%d elemento(s). Size: 0.\n", pilha->current, pilha->MAXSIZE);
        return;
    }

    Node* head = pilha->node;
    if (head->next == NULL) {
        printf("  -- Stack: Topo->[%d] - Size: 1.\n", head->info);
        return;
    }

    Node* p = head;
    int i=0;
    printf("  -- Stack: Topo->[");
    while (p->next != NULL){
        printf ("%d, ", p->info);
        p = p->next;
        i++;
    }
    printf("%d] - Size: %d.\n",p->info, i+1);
}

#endif
