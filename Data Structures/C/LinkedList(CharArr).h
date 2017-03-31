#ifndef LINKEDLIST_CHARARR_H
#define LINKEDLIST_CHARARR_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "CharNode.h"
#include "Macros.h"

#define LinkedListChar SLLChar
typedef struct cnode SLLChar;
///SLLChar_char* - Singly Linked List cujo "info" é um char*
SLLChar* SLLChardestroi (SLLChar* lista);
SLLChar* SLLCharinsert(SLLChar* lista, char* val);
SLLChar* SLLCharremoveIndex (SLLChar* lista, int index);
int SLLCharsearch(SLLChar* lista, char* P);
char* SLLChargetFromIndex (SLLChar* lista, int index);
int SLLChargetSize (SLLChar* lista);
SLLChar* SLLChargetTail (SLLChar* head);
SLLChar* SLLCharinsertTail(SLLChar* lista, char* val);
void swapString(char *str1, char *str2);

int SLLCharRanking (SLLChar* lista, char* val); /// Exercicio 4.a
void SLLCharprint (SLLChar* lista);             /// Exercicio 4.b

/**
* Aumenta uma posicao no "Ranking" da lista.
* Retorna o index atual da expressao que foi elevada.
* -1 caso nao tenha sido encontrado.
*/
int SLLCharRanking (SLLChar* lista, char* val){
    if (lista == NULL){
        lista = SLLCharinsert(lista, val);
        return 1;
    }

    int index=1;
    SLLChar* p = lista;
    SLLChar* aux;
    while (p->next != NULL){
        aux = p->next;
        if ( strcmp(aux->info, val) == 0 ){ //Swap entre essa var e a anterior
            swapString(p->info, aux->info);
            return index;
        }
        index++;
        p = p->next;
    }

    if ( strcmp(p->info, val) == 0 ){ //Swap entre essa var e a anterior
            swapString(p->info, val);
            return index+1;
    }

    if (DISPLAY_INFO) printf ("  -- String nao encontrada. Acrescenta-se ao final da lista...\n");

    lista = SLLCharinsertTail(lista, val);

    return index+1;
}

/**
* Insere nodo na cauda da lista. Se nula, insere no unico local possivel.
* Retorna ponteiro para a mesma.
*/
SLLChar* SLLCharinsertTail(SLLChar* lista, char* val){
    SLLChar* novo = NEWCNODE;
    strcpy( novo->info, val);

    if (lista == NULL){
        if (DISPLAY_INFO) printf ("  -- Lista Nula. Insere-se o primeiro elemento.\n");
        return SLLCharinsert(lista, val);
    } else {
        SLLChar* tail = SLLChargetTail(lista);
        tail->next = novo;
    }

    novo->next=NULL;
    if (DISPLAY_INFO) printf("  -- Elemento %s inserido na tail.\n", val);

    return novo;
}

//Swap entre duas Strings. Nao e de minha autoria
void swapString(char *str1, char *str2){
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  free(temp);
}

///Funcoes auxiliares e implementadas anteriormente

/**
* Destroi a lista e libera toda a memoria.
* Retorna NULL para substituir o ponteiro.
*/
SLLChar* SLLChardestroi (SLLChar* lista){
    if (lista==NULL){
        if (DISPLAY_INFO) printf("  -- Lista nula. Retorna-se NULL\n");
        return NULL;
    }

    if (lista->next == NULL){
        SLLChar* aux = lista->next;
        free(aux);
        if (DISPLAY_INFO) printf("  -- Lista destruida. Apenas um elemento.\n");
        return NULL;
    }

    SLLChar* aux;
    SLLChar* p = lista;
    while (p->next != NULL){
        aux = p->next;
        free (p);
        p = aux;
    }

    if (DISPLAY_INFO) printf("  -- Lista destruida.\n");

    return NULL;
}

/**
* Insere SLLChars na lista
* Retorna lista com o elemento adicionado.
*/
SLLChar* SLLCharinsert(SLLChar* lista, char* val){
    SLLChar* novo = NEWCNODE;
    strcpy( novo->info, val);
    novo->next=lista;
    if (DISPLAY_INFO) printf("  -- Elemento %s inserido.\n", val);

    return novo;
}

/**
* Remove elemento da lista.
* Retorna a lista com o elemento removido.
* Se o elemento nao foi encontrado, a mesma
* lista e retornada.
*/
SLLChar* SLLCharremoveElement (SLLChar* lista, char* R){
    if (lista->info == R){
        SLLChar* tmp = lista;
        lista = tmp->next;
        free(tmp);
        if (DISPLAY_INFO) printf("  -- Elemento %s removido da head.\n", R);
        return lista;
    }
    short found_flag=0;
    SLLChar* p;
    SLLChar* aux;
    for (p=lista;p->next!=NULL;p=p->next){
        aux=p->next;
        if (aux->info==R){
            p->next=aux->next;
            free(aux);
            if (DISPLAY_INFO) printf("  -- Elemento %s removido.\n", R);
            found_flag++;
            break;
        }
    }

    if (DISPLAY_INFO==1 && found_flag==0) printf("  -- Elemento %s nao encontrado.\n", R);

    return lista;
}

/**
* Remove elemento da lista em um determinado indice.
* (1º elemento -> indice = 0.)
* Retorna a lista com o elemento removido.
* Se o indice for invalido, a mesma
* lista e retornada.
*/
SLLChar* SLLCharremoveIndex (SLLChar* lista, int index){
    if (lista == NULL) return NULL;

    if (index == 0){
        SLLChar* tmp = lista;
        if (DISPLAY_INFO) printf("  -- Elemento na posicao %d (head) removido: %s\n", index, tmp->info);
        lista = tmp->next;
        free(tmp);
        return lista;
    }

    SLLChar* p = lista;
    SLLChar* aux;
    int i=1;
    p = p->next;
    for (p=lista;p->next!=NULL;p=p->next){
        aux=p->next;
        if (i==index){
            if (DISPLAY_INFO) printf("  -- Elemento %s removido.\n", aux->info);
            p->next=aux->next;
            free(aux);
            return lista;
        }
        i++;
    }

    if (DISPLAY_INFO==1) printf("  -- Posicao %d invalida.\n", index);

    return lista;
}

/**
* Busca node na lista.
* Retorna o index (index >= 0) se encontrou;
* E -1 se não encontrou.
*/
int SLLCharsearch(SLLChar* lista, char* P){
    if (lista == NULL){
        if(DISPLAY_INFO)
            printf("  -- Lista nula. Nao existem elementos.\n");
        return -1;
    }

    int cont=0;
    SLLChar* p;
    for (p=lista;p!=NULL;p=p->next){
        if(p->info==P){
            if (DISPLAY_INFO)
                printf("  -- Encontrado em  %s -> Index(%d).\n", P, cont);
            return cont;
        }
        cont++;
    }

    if (DISPLAY_INFO)
        printf("  -- Elemento nao encontrado. Inspecionados %d elemento(s).\n", cont);

    return -1;
}

/**
* Retorna o inteiro em um indice da lista.
* Se lista NULL, retorna INT_MAX.
* Se indice invalido, retorna INT_MIN.
*/
char* SLLChargetFromIndex (SLLChar* lista, int index){
    if (lista == NULL) {
        if (DISPLAY_INFO) printf("  -- Lista nula.\n");
        return NULL;
    }


    if (index == 0) return lista->info;

    SLLChar* p = lista;
    int i=1;
    p = p->next;
    for (;p!=NULL;p=p->next){
        if (i == index) return p->info;
        i++;
    }

    if (DISPLAY_INFO) printf("  -- Posicao invalida.\n");

    return NULL;
}

/**
* Retorna o tamanho da lista.
* Lista com um elemento Size=1.
* Lista nula, retorna INT_MIN.
*/
int SLLChargetSize (SLLChar* lista){
    if (lista == NULL){
        if (DISPLAY_INFO) printf("  -- Lista nula.\n");
        return INT_MIN;
    }

    SLLChar* p;
    int i=0;
    for (p=lista; p!=NULL; p=p->next){
        i++;
    }
    return i;
}

/**
* Retorna o ponteiro para a cauda a head.
*/
SLLChar* SLLChargetTail (SLLChar* head){
    if (head==NULL){
        if (DISPLAY_INFO)
            printf("  -- Lista vazia. Nao existe cauda.\n");
        return NULL;
    }

    if (head->next == NULL) {
        return head;
    }

    SLLChar* p = head;
    while (p->next != NULL)
        p = p->next;

    return p;
}

/**
* Imprime lista
* Formato: [x, y, z] - Size: l
*/
void SLLCharprint (SLLChar* lista){
    if (lista == NULL){
        printf("  -- [NULL] - Size: -1.\n");
        return;
    }

    SLLChar* p = lista;
    int i=0;
    printf("  -- [ %s", p->info);
    p = p->next;
    for (;p!=NULL;p=p->next){
        printf(", %s", p->info);
        i++;
    }
    printf("] - Size: %d.\n", i+1);
}

#endif
