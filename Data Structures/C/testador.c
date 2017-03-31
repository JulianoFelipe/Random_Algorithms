#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>
#include "implementacoes.h"
#include "Macros.h"
#include "LinkedList.h"
#include "LinkedList(Float).h"
#include "LinkedList(CharArr).h"
#include "StaticDoubleStack.h"
#include "StaticQueue.h"
#include "StaticDeque.h"
#include "PriorityQueue.h"

int first (int lim, short flagNotNull, short notInvalidToken);
int second (int lim, short flag1, short flag2);
int third (int lim, unsigned int n, short flagNotNull);
int fourth (unsigned int lim, unsigned short testChar);
int fifth(unsigned int lim, unsigned int rem);
int sixth(unsigned int lim);
int seventh();
int eighth (int lim, short flagNotNull, short notInvalidToken);
int ninth(unsigned int lim);
int tenth(unsigned int lim);
int eleventh(unsigned int lim, unsigned int rem);

int main (){
    //0 para testar todas.
    //Entre 1 e 11 para testar uma especifica (2 para questao 2).
    //Oferece pausa entre exercicios, para nao "testar tudo de uma vez"
    short whichQuestion = 0;

    if (whichQuestion == 0 || whichQuestion == 1){
        printf ("Testanto exercicio 1: \n");
        first (6, 1, 1);
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 2){
        printf ("Testanto exercicio 2: \n");
        second(6, 1, 1);
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 3){
        printf ("Testanto exercicio 3: \n");
        third (6, 3, 1);
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 4){
        printf ("Testanto exercicio 4: \n");
        printf ("Testanto com termo existente: \n");
        fourth(6, 2);
        printf ("\nTestanto com termo inexistente: \n");
        fourth(6, 7);
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 5){
        printf ("Testanto exercicio 5: \n");
        fifth(10, 10);
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 6){
        printf ("Testanto exercicio 6: \n");
        sixth(10);
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 7){
        printf ("Testanto exercicio 7: \n");
        seventh();
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 8){
        printf ("Testanto exercicio 8: \n");
        eighth(6, 1, 1);
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 9){
        printf ("Testanto exercicio 9: \n");
        ninth(10);
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 10){
        printf ("Testanto exercicio 10: \n");
        tenth(6);
        continuar;
        CLR;
    }

    if (whichQuestion == 0 || whichQuestion == 11){
        printf ("Testanto exercicio 11: \n");
        eleventh(11, 11);
        continuar;
        CLR;
    }

    return 0;
}

/**
*   Testa o primeiro exercicio da lista. Parametros:
* - lim: Numero de itens para inserir em uma lista de exemplo.
* - flagNotNull: Se "false" (0), passa uma lista nula; para testar.
* - notInvalidToken: Se "false" (0), passa um token invalido para tentar separar.
*
* Retorna error level.
*/
int first (int lim, short flagNotNull, short notInvalidToken){
    int token = lim/2;
    if (!notInvalidToken) token = lim+4;

    SLL* lista1 = create();
    SLL* lista2 = create();

    int i;
    for (i=0; i<lim; i++) if (flagNotNull) lista1 = SLLinsert(lista1, i);

    printf ("Lista1: "); SLLprint(lista1);
    printf ("Lista a receber retorno: "); SLLprint(lista2);

    printf ("\nRealiza-se o split em %d... \n\n", token);

    lista2 = SLLsplit(lista1, token);

    printf ("Lista1: "); SLLprint(lista1);
    printf ("Lista retornada: "); SLLprint(lista2);

    return 0;
}

/**
*   Testa o segundo exercicio da lista. Parametros:
* - lim: Numero de itens para inserir em uma lista de exemplo.
* - flag1: Se "false" (0), seta a primeira lista como nula; para testar.
* - flag2: Idem para anterior, mas com a segunda lista.
*
* Retorna error level.
*/
int second (int lim, short flag1, short flag2){
    SLLFloat* lista1 = createF();
    SLLFloat* lista2 = createF();

    int i;
    for (i=0; i<lim; i++){
        if (flag1) lista1 = SLLFloatinsert(lista1, i*1.0);
        if (flag2) lista2 = SLLFloatinsert(lista2, (lim-i)*0.1);
    }

    printf ("\nLista1: \n"); SLLFloatprint(lista1);
    printf ("\nLista2: \n"); SLLFloatprint(lista2);

    printf ("\nRealiza-se a concatenacao das listas ... \n\n");

    SLLFloat* ret = SLLFloatAppend(lista1, lista2);

    printf ("Lista Resultante: \n"); SLLFloatprint(ret);

    //Verificacao extra. Imprime-se os ponteiros que se tinha anteriormente
    //, para confirmar que o primeiro aponta para toda a lista. E que o segundo
    //aponta, apenas, para o \"meio\" da lista.

    printf ("\nLista1: \n"); SLLFloatprint(lista1);
    printf ("\nLista2: \n"); SLLFloatprint(lista2);

    return 0;
}

/**
*   Testa o terceiro exercicio da lista. Parametros:
* - lim: Numero de itens para inserir em uma lista de exemplo.
* - n: Numero de elementos para serem removidos da lista.
* - flagNotNull: Se "false" (0), passa uma lista nula; para testar.
*
* Retorna error level.
*/
int third (int lim, unsigned int n, short flagNotNull){
    SLLFloat* lista = createF();

    int i;
    for (i=0; i<lim; i++) if (flagNotNull) lista = SLLFloatinsert(lista, i*0.1);

    printf ("Lista, antes: \n"); SLLFloatprint(lista);

    printf ("\nRealiza-se a operacao nos %d primeiro(s) termo(s)...\n", n);

    lista = SLLFloatSublist(lista, n);

    printf ("\nLista, depois: \n"); SLLFloatprint(lista);

    return 0;
}

/**
*   Testa o quarto exercicio da lista.
*   Gerara lim+1 strings, strcat para gerar "stringX", com X com um valor.
*   Parametros:
* - lim: Numero de itens para inserir em uma lista de exemplo.
* - testChar: Num entre 0 e 9 para testar com o Ranking (Entre 0 e lim para poder
*   subir no ranking, outro para, nao encontrar).
*
*   Por causa do modo que foi testado, e melhor passar lim entre 0 e 9.
* Retorna error level.
*/
int fourth (unsigned int lim, unsigned short testChar){
    SLLChar* lista = createC();
    char t[]="String";
    char testC[2];
    testC[0] = testChar + '0'; //Soma valor de '0' para poder mostrar digitos numericos
    //da tabela ASC II. Desta forma, lim e testChar entre 0 e 9 facilitam vizualizacao.
    testC[1] = '\0';

    char* val = strcat(t, testC); //Cria string no formato "String%testChar%\0"

    int i;
    for (i=0; i<=lim; i++){ //Insere elementos no formato "String%char%\0"
            char s[]="StringI\0";
            s[6] = i + '0';
            lista = SLLCharinsert(lista, s);
    }

    printf ("\nLista antes: "); SLLCharprint(lista);

    printf ("\nTesta-se com %s.\n\n", val);

    int ret = SLLCharRanking (lista, val); //Chamada para func. e atribuicao de retorno

    printf ("\nLista depois: "); SLLCharprint(lista);

    printf ("\nPosicao retornada: %d.\n", ret);

    return 0;
}

/**
*   Testa o quarto exercicio da lista.
*   Gerara lim+1 strings, strcat para gerar "stringX", com X com um valor.
*   Parametros:
* - lim: Numero de itens para inserir nas pilhas ("lim" em cada).
* - rem: Numero de itens para remover das pilhas ("rem" de cada).
*
* Retorna error level.
*/
int fifth(unsigned int lim, unsigned int rem){
    StaticDoubleStack* pilha = createStaticStack();

    int i;
    for (i=0; i<lim; i++) SDStackPush(pilha, 1, i); //Add pilha1

    SDStackPrint(pilha);

    for (i=lim; i<lim*2; i++) SDStackPush(pilha, 2, i); //Add pilha2

    SDStackPrint(pilha); //Prints
//    SDStackExtendedPrint(pilha);

    printf ("\n"); //Espaco

    for (i=0; i<rem; i++) SDStackPop(pilha, 1); //Rem. pilha1

    for (i=0; i<rem; i++) SDStackPop(pilha, 2); //Rem. pilha2

    SDStackPrint(pilha); //Prints
//    SDStackExtendedPrint(pilha);

    return 0;
}

/**
*   Testa o sexto exercicio da lista.
*   Gera uma lista com "lim" elementos. Trasforma ela em pilha.
*   Depois gera pilha, e transforma em fila.
*   Parametros:
* - lim: Numero de itens para inserir na pilha e, depois, na fila.
*
* Retorna error level.
*/
int sixth(unsigned int lim){
    //Q1 - QueueToStack
    printf ("Teste Q1 - QueueToStack.\n");

    Queue* fila = QueueCreate(lim);
    int i;
    for (i=0; i<lim; i++){
        fila = EnQueue(fila, i);
    }

    Stack* pilha = QueueToStack(fila);

    StackPrint(pilha);

    printf ("Pilha Current/Size: %d/%d.\n", pilha->current, pilha->MAXSIZE);

    StackDestroi(pilha);
    //QueueDestroi(fila);

    printf ("Fim da teste Q1.  "); continuar; CLR;

    //Q2 - StackToQueue
    printf ("Teste Q2 - StackToQueue.\n");

    pilha = StackCreate(lim);
    for (i=0; i<lim; i++){
        pilha = StackPush(pilha, i);
    }
    StackPrint(pilha);

    fila = StackToQueue(pilha);

    QueuePrint(fila);

    printf ("Fila Current/Size: %d/%d.\n", fila->impN->current, fila->impN->MAXSIZE);

    printf ("Fim da teste Q2.\n");

    return 0;
}

/**
* Testa o 7 exercicio. Se escolher testar manual, ha menus para guiar o teste.
* Estruturas sequenciais com tamanho MAX fixo.
* Obs.: Por simplicidade, a mesma estrutura da questao 5 foi usada,
* mas apenas a "primeira pilha".
*/
int seventh(){
    char op;
    printf("|===================== Questao 7 ======================|\n");
    printf(" - Teste automatico?(y/n). \"n\" vai para teste manual.\n");
    op = _getch();
    if (op == 'N' || op == 'n'){ seventhManual(); return 0;}
    else if (op == 'Y' || op == 'y'){}
    else {printf (" - Opcao invalida. Saindo...\n"); return 0;}
    CLR;

    printf ("Modo automatico... \n");
    const int pil = 1; //Qual pilha inserir
    StaticDoubleStack* pilha = createStaticStack();
    StaticQueue* fila = createStaticQueue(1);

    SDStackPush(pilha, pil, 1);
    SDStackPush(pilha, pil, 2);
    SDStackPush(pilha, pil, 3);
    SQEnqueue(fila, -1);
    SQEnqueue(fila, -2);
    SQEnqueue(fila, -3);

    SDStackPrint(pilha);
    SQueuePrint(fila);

    int toPass2;
    toPass2 = SDStackPop(pilha, pil);
    SQEnqueue(fila, toPass2);

    SDStackPrint(pilha);
    SQueuePrint(fila);

    toPass2 = SQDequeue(fila);
    SDStackPush(pilha, pil, toPass2);

    SDStackPrint(pilha);
    SQueuePrint(fila);

    destroiStatickDoubleStack(pilha);
    destroiStaticQueue(fila);

    return 0;
}

/**
*   Testa o oitavo exercicio da lista. Parametros:
* - lim: Numero de itens para inserir em uma lista de exemplo.
* - flagNotNull: Se "false" (0), passa uma lista nula; para testar.
* - notInvalidToken: Se "false" (0), passa um token invalido para tentar separar.
*
* Retorna error level.
*/
int eighth (int lim, short flagNotNull, short notInvalidToken){
    int priorityToken = lim/2;
    if (!notInvalidToken) priorityToken = lim*-1;

    PQueue* lista1 = PQueueCreate(lim);
    PQueue* lista2 = PQueueCreate(lim);

    int i;
    for (i=0; i<lim; i++) if (flagNotNull) lista1 = PEnQueue(lista1, i, lim-i, 0.0);

    printf ("Lista1: \n"); PQueuePrint(lista1);
    printf ("\nLista a receber retorno: \n"); PQueuePrint(lista2);

    printf ("\nRealiza-se o split em %d... \n\n", priorityToken);

    lista2 = PQueueSplitPriority(lista1, priorityToken);

    printf ("Lista1: \n"); PQueuePrint(lista1);
    printf ("\nLista retornada: \n"); PQueuePrint(lista2);

    return 0;
}

/**
*   Testa o nono exercicio da lista.
*   Testa inversao de listas.
* - lim: Numero de itens para inserir no deque ("lim" em cada lado).
*
* Retorna error level.
*/
int ninth(unsigned int lim){
    Queue* fila = QueueCreate(lim);
    int i;
    for (i=0; i<lim; i++){
        fila = EnQueue(fila, i);
    }
    QueuePrint(fila);

    fila = InvertQueue(fila);

    QueuePrint(fila);

    return 0;
}

/**
*   Testa o nono exercicio da lista.
*   Testa inversao de listas.
* - lim: Numero de itens para inserir na lista;
*   Nao sera usado se escolher teste manual.
*
* Retorna error level.
*/
int tenth(unsigned int lim){
    char op;
    printf("|===================== Questao 10 ======================|\n");
    printf(" - Teste automatico?(y/n). \"n\" vai para teste manual.\n");
    op = _getch();
    if (op == 'N' || op == 'n'){ tenthManual(); return 0;}
    else if (op == 'Y' || op == 'y'){}
    else {printf (" - Opcao invalida. Saindo...\n"); return 0;}
    CLR;

    printf ("Modo automatico... \n");

    PQueue* fila = PQueueCreate(lim);
    int i;
    for (i=0; i<lim; i++){
        fila = PEnQueue(fila, i, 0, i);
    }
    ProcessListPrint(fila);
    removeHighestTime (fila);
    ProcessListPrint(fila);
    return 0;
}

/**
*   Testa o decimo primeiro exercicio da lista.
*   Testa Deque estatico.
* - lim: Numero de itens para inserir no deque ("lim" em cada lado).
* - rem: Numero de itens para remover do deque ("rem" de cada lado).
*
* Retorna error level.
*/
int eleventh(unsigned int lim, unsigned int rem){
    StaticDeque* sdeque = createStaticDeque(1); //Passa 1 para inicializar tudo em 0
                                                //Passa 0 para nao inicializar (ExtendedPrint pode apresentar lixo).
    int i;
    for (i=1; i<lim; i++){ //Insere do lado esquerdo
        SDEnqueue(sdeque, 1, i);
    }

    SDequePrint(sdeque);
    //SDequeExtendedPrint(sdeque);

    for (i=lim; i<lim*2; i++){ //Insere do lado direito
        SDEnqueue(sdeque, 2, i);
    }

    SDequePrint(sdeque);
    //SDequeExtendedPrint(sdeque);

    for (i=0; i<rem; i++){ //Remove do lado esquerdo
        SDDequeue(sdeque, 1);
    }

    SDequePrint(sdeque);
    //SDequeExtendedPrint(sdeque);

    for (i=0; i<rem; i++){ //Remove do lado direito
        SDDequeue(sdeque, 2);
    }

    SDequePrint(sdeque);

    //printf ("\n\n Imprime-se todo o vetor de dados para debug (Pode incluir pos. ja deletadas): \n");
    //SDequeExtendedPrint(sdeque);

    return 0;
}
