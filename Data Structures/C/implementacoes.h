#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>
#include "Macros.h"
#include "LinkedList.h"
#include "LinkedList(Float).h"
#include "LinkedList(CharArr).h"
#include "StaticDoubleStack.h"
#include "StaticQueue.h"
#include "StaticDeque.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"

//////////////////////////////////////////////////////////////////////////QUESTAO 7
/**
* Questao 7. Pilha e fila sequencial.
*/
short sub1() {
    short exit=0;
    char op;

    const int pil = 1; //Qual pilha inserir
    StaticDoubleStack* pilha = createStaticStack();
    StaticQueue* fila = createStaticQueue(1);

    while (exit != 1){
        printf("|============ P:Seq. F: Seq. ============|\n");
        printf("| 1 - Inserir valor.                     |\n");
        printf("| 2 - Remover pilha, inserir fila.       |\n");
        printf("| 3 - Remover fila, inserir pilha.       |\n");
        printf("| 4 - Imprimir pilha/fila.               |\n");
        printf("|----------------------------------------|\n");
        printf("| 0 - Sair.                              |\n");
        printf("|________________________________________|\n");
        printf("| Opcao: ");
        op = _getch();
        printf ("%c\n", op);
        int toPass;
        int toPass2;
        switch (op){
            case '0':
                exit=1;
                destroiStatickDoubleStack(pilha);
                destroiStaticQueue(fila);
                break;
            case '1':
                printf(" - Digite o valor para inserir: ");
                scanf("%d", &toPass);
                if (toPass >= 0){
                    printf (" - Positivo. Insere na pilha.\n");
                    SDStackPush(pilha, pil, toPass);
                } else {
                    printf (" - Negativo. Insere na fila.\n");
                    SQEnqueue(fila, toPass);
                }
                break;
            case '2':
                toPass2 = SDStackPop(pilha, pil);
                SQEnqueue(fila, toPass2);
                break;
            case '3':
                toPass2 = SQDequeue(fila);
                SDStackPush(pilha, pil, toPass2);
                break;
            case '4':
                SDStackPrint(pilha);
                SQueuePrint(fila);
                break;
            default:
                printf (" - Opcao invalida.\n");
        }
        fflush(stdin);
        continuar;
        CLR;
    }
    return 0;
}

/**
* Questao 7. Pilha e fila encadeada.
* Params.:
* -sizeP: Tamanho máx. da pilha.
* -sizeF: Tamanho máx. da fila.
*/
short sub2(short sizeP, short sizeF) {
    short exit=0;
    char op;

    Stack* pilha = StackCreate(sizeP);
    Queue* fila = QueueCreate(sizeF);

    while (exit != 1){
        printf("|============ P:Enc. F: Enc. ============|\n");
        printf("| 1 - Inserir valor.                     |\n");
        printf("| 2 - Remover pilha, inserir fila.       |\n");
        printf("| 3 - Remover fila, inserir pilha.       |\n");
        printf("| 4 - Imprimir pilha/fila.               |\n");
        printf("|----------------------------------------|\n");
        printf("| 0 - Sair.                              |\n");
        printf("|________________________________________|\n");
        printf("| Opcao: ");
        op = _getch();
        printf ("%c\n", op);
        int toPass;
        int toPass2;
        switch (op){
            case '0':
                exit=1;
                pilha = StackDestroi(pilha);
                fila = QueueDestroi(fila);
                break;
            case '1':
                printf(" - Digite o valor para inserir: ");
                scanf("%d", &toPass);
                if (toPass >= 0){
                    printf (" - Positivo. Insere na pilha.\n");
                    StackPush(pilha, toPass);
                } else {
                    printf (" - Negativo. Insere na fila.\n");
                    EnQueue(fila, toPass);
                }
                break;
            case '2':
                toPass2 = StackPop(pilha);
                EnQueue(fila, toPass2);
                break;
            case '3':
                toPass2 = DeQueue(fila);
                StackPush(pilha, toPass2);
                break;
            case '4':
                StackPrint(pilha);
                QueuePrint(fila);
                break;
            default:
                printf (" - Opcao invalida.\n");
        }
        fflush(stdin);
        continuar;
        CLR;
    }
    return 0;
}

/**
* Questao 7. Pilha encadeada, fila sequencial.
* Params.:
* -sizeP: Tamanho máx. da pilha.
*/
short sub3(short sizeP) {
    short exit=0;
    char op;

    Stack* pilha = StackCreate(sizeP);
    StaticQueue* fila = createStaticQueue(1);

    while (exit != 1){
        printf("|============ P:Enc. F: Seq. ============|\n");
        printf("| 1 - Inserir valor.                     |\n");
        printf("| 2 - Remover pilha, inserir fila.       |\n");
        printf("| 3 - Remover fila, inserir pilha.       |\n");
        printf("| 4 - Imprimir pilha/fila.               |\n");
        printf("|----------------------------------------|\n");
        printf("| 0 - Sair.                              |\n");
        printf("|________________________________________|\n");
        printf("| Opcao: ");
        op = _getch();
        printf ("%c\n", op);
        int toPass;
        int toPass2;
        switch (op){
            case '0':
                exit=1;
                pilha = StackDestroi(pilha);
                destroiStaticQueue(fila);
                break;
            case '1':
                printf(" - Digite o valor para inserir: ");
                scanf("%d", &toPass);
                if (toPass >= 0){
                    printf (" - Positivo. Insere na pilha.\n");
                    StackPush(pilha, toPass);
                } else {
                    printf (" - Negativo. Insere na fila.\n");
                    SQEnqueue(fila, toPass);
                }
                break;
            case '2':
                toPass2 = StackPop(pilha);
                SQEnqueue(fila, toPass2);
                break;
            case '3':
                toPass2 = SQDequeue(fila);
                StackPush(pilha, toPass2);
                break;
            case '4':
                StackPrint(pilha);
                SQueuePrint(fila);
                break;
            default:
                printf (" - Opcao invalida.\n");
        }
        fflush(stdin);
        continuar;
        CLR;
    }
    return 0;
}

/**
* Questao 7. Pilha sequencial, fila encadeada.
* Params.:
* -sizeF: Tamanho máx. da fila.
*/
short sub4(short sizeF) {
    short exit=0;
    char op;

    const int pil = 1; //Qual pilha inserir
    StaticDoubleStack* pilha = createStaticStack();
    Queue* fila = QueueCreate(sizeF);

    while (exit != 1){
        printf("|============ P:Seq. F: Enc. ============|\n");
        printf("| 1 - Inserir valor.                     |\n");
        printf("| 2 - Remover pilha, inserir fila.       |\n");
        printf("| 3 - Remover fila, inserir pilha.       |\n");
        printf("| 4 - Imprimir pilha/fila.               |\n");
        printf("|----------------------------------------|\n");
        printf("| 0 - Sair.                              |\n");
        printf("|________________________________________|\n");
        printf("| Opcao: ");
        op = _getch();
        printf ("%c\n", op);
        int toPass;
        int toPass2;
        switch (op){
            case '0':
                exit=1;
                destroiStatickDoubleStack(pilha);
                fila = QueueDestroi(fila);
                break;
            case '1':
                printf(" - Digite o valor para inserir: ");
                scanf("%d", &toPass);
                if (toPass >= 0){
                    printf (" - Positivo. Insere na pilha.\n");
                    SDStackPush(pilha, pil, toPass);
                } else {
                    printf (" - Negativo. Insere na fila.\n");
                    EnQueue(fila, toPass);
                }
                break;
            case '2':
                toPass2 = SDStackPop(pilha, pil);
                EnQueue(fila, toPass2);
                break;
            case '3':
                toPass2 = DeQueue(fila);
                SDStackPush(pilha, pil, toPass);
                break;
            case '4':
                SDStackPrint(pilha);
                QueuePrint(fila);
                break;
            default:
                printf (" - Opcao invalida.\n");
        }
        fflush(stdin);
        continuar;
        CLR;
    }
    return 0;
}

int seventhManual(){
    short exit=0;
    char op;
    while (exit != 1){
        printf("|============== Questao 7 ===============|\n");
        printf("| 1 - Pilha/Fila sequencial.             |\n");
        printf("| 2 - Pilha/Fila encadeada.              |\n");
        printf("| 3 - Pilha encadeada, Fila sequencial.  |\n");
        printf("| 4 - Pilha sequencial, Fila encadeada.  |\n");
        printf("|----------------------------------------|\n");
        printf("| 0 - Sair.                              |\n");
        printf("|________________________________________|\n");
        printf("| Opcao: ");
        op = _getch();
        printf ("%c\n", op);
        int toPass;
        int toPass2;
        CLR;
        switch (op){
            case '0':
                exit=1;
                break;
            case '1':
                sub1();
                break;
            case '2':
                printf(" - Digite tamanho da pilha: ");
                scanf("%d", &toPass);
                printf(" - Digite tamanho da fila: ");
                scanf("%d", &toPass2);
                sub2(toPass, toPass2);
                break;
            case '3':
                printf(" - Digite tamanho da fila: ");
                scanf("%d", &toPass2);
                sub3( toPass2);
                break;
            case '4':
                printf(" - Digite tamanho da pilha: ");
                scanf("%d", &toPass);
                sub4(toPass);
                break;
            default:
                printf (" - Opcao invalida.\n");
        }
        fflush(stdin);
        continuar;
        CLR;
    }
    return 0;
}
//////////////////////////////////////////////////////////////////////////FIM QUESTAO 7

/**
* Usa as funcoes acima e as de Queue para
* transformar uma pilha em uma fila. Param.:
* - Pilha para transformar.
* Retorna uma fila.
*/
Queue* StackToQueue (Stack* pilha){
    /*     Ordem das operacoes:
     - Retira todos da pilha e insere na fila.
    */

    int PilhaMax = pilha->MAXSIZE;
    Queue* fila = QueueCreate(PilhaMax);

    int val;
    while (pilha->current != 0){
        val = StackPop(pilha);
        fila = EnQueue(fila, val);
    }

    pilha = StackDestroi(pilha);
    return fila;
}

/**
* Usa as funcoes acima e as de Stack para
* transformar uma fila em uma pilha. Param.:
* - Fila para transformar.
* Retorna uma pilha.
*/
Stack* QueueToStack (Queue* fila){
    /*     Ordem das operacoes:
     - Retira todos da fila e coloca em uma pilha, a ordem estara invertida.
     - Retira todos da pilha e coloca em um fila, a ordem estara invertida (relacao com a primeira fila)
     - Retira da nova fila e coloca em uma pilha.
    */

    int FilaMax = fila->impN->MAXSIZE;
    Stack* pilha = StackCreate(FilaMax);

    int val;
    while (fila->impN->current != 0){
        val = DeQueue(fila);
        pilha = StackPush(pilha, val);
    }

    while (pilha->current != 0){
        val = StackPop(pilha);
        fila = EnQueue(fila, val);
    }

    while (fila->impN->current != 0){
        val = DeQueue(fila);
        pilha = StackPush(pilha, val);
    }

    fila = QueueDestroi(fila);
    return pilha;
}

/**
* Utiliza uma pilha para poder inverter uma fila.
* Retorna o mesmo ponteiro da fila que foi passada.
*/
Queue* InvertQueue (Queue* fila){
    int FilaMax = fila->impN->MAXSIZE;
    Stack* pilha = StackCreate(FilaMax);

    int val;
    while (fila->impN->current != 0){
        val = DeQueue(fila);
        pilha = StackPush(pilha, val);
    }

    while (pilha->current != 0){
        val = StackPop(pilha);
        fila = EnQueue(fila, val);
    }

    pilha = StackDestroi(pilha);
    return fila;
}

//////////////////////////////////////////////////////////////////////////QUESTAO 10

/**
* Remove o PNode da PQueue cujo extra info e
* o maior. Como se trata de uma fila, usa outra fila
* auxiliar (mesmo tamanho) para nao perder os dados.
*
* Retorna 0 em sucesso, 1 caso falha (NULA ou Vazia).
*/
int removeHighestTime (PQueue* fila){
    if (fila == NULL || fila->current==0){
        return 1;
    }

    PQueue* tempfila = PQueueCreate(fila->MAX);

    float highest=-1.0;
    float aux;
    int tempI;
    int tempP;
    while ( fila->current > 0){ //Tira de uma fila e coloca na outra
        tempI = fila->head->info;
        tempP = fila->head->priority;
        aux = fila->head->extraInfo;
        PDeQueue(fila);
        if (aux > highest) highest = aux;
        PEnQueue(tempfila, tempI, tempP, aux);
    }

    short flag=0;
    while ( tempfila->current > 0){ //Tira da nova fila, e coloca na primeira, exceto o de maior tempo.
        tempI = tempfila->head->info;
        tempP = tempfila->head->priority;
        aux = tempfila->head->extraInfo;
        PDeQueue(tempfila);
        if (aux != highest) PEnQueue(fila, tempI, tempP, aux); //So insere o diferente de highest
        if ((aux == highest) && flag==1) PEnQueue(fila, tempI, tempP, aux); //So nao insere a primeira ocorrencia de highest, melhor
        if (aux == highest) flag = 1;
    }
    return 0;
}

/**
* Imprime uma PQueue com uma formatacao "emuladora".
* - fila: Cujos elementos serao impressos.
*/
void ProcessListPrint (PQueue* fila){
    if (fila == NULL){
        printf("  -- PQueue: Topo->[NULL] - Size: -1\n");
        return;
    }

    if (fila->current == 0){
        printf("  -- PQueue vazia. %d/%d elemento(s). Size: 0\n", fila->current, fila->MAX);
        return;
    }

    PriorityNode* head = fila->head;
    if (head->next == NULL) {
        printf("  -- Process: Topo->\n ID:%d Priority:%d Waiting Time:%.3f] - Size: 1\n", head->info, head->priority, head->extraInfo);
        return;
    }

    PriorityNode* p = head;
    int i=0;
    printf("  -- PQueue: Topo->[\n");
    while (p->next != NULL){
        printf ("  -- ID:%d Priority:%d Waiting Time:%.3f\n", p->info, p->priority, p->extraInfo);
        p = p->next;
        i++;
    }
    printf("  -- ID:%d Priority:%d Waiting Time:%.3f] - Size: %d.\n", p->info, p->priority, p->extraInfo, i+1);
}

/**
* Menu manual para a questao 10.
*/
void tenthManual(){
    printf ("Qual o tamanho max. da lista de processos? ");
    int sizePQ;
    scanf("%d", &sizePQ);
    PQueue* fila = PQueueCreate(sizePQ);
    CLR;

    short exit=0;
    char op;
    while (exit != 1){
        printf("|================= Questao 10 =================|\n");
        printf("| 1 - Incluir novos processos.                 |\n");
        printf("| 2 - Retirar proc. com maior tempo de espera. |\n");
        printf("| 3 - Imprimir lista de processos.             |\n");
        printf("|----------------------------------------------|\n");
        printf("| 0 - Destruir fila e Sair.                    |\n");
        printf("|______________________________________________|\n");
        printf("| Opcao: ");
        op = _getch();
        printf ("%c\n", op);
        int prio = 1; //Prioridade hardcoded
        int id;
        float waitTime;
        CLR;
        switch (op){
            case '0':
                PQueueDestroi(fila);
                exit=1;
                break;
            case '1':
                printf ("Qual o ID do processo? ");
                scanf("%d", &id);
                printf ("Qual o tempo de espera do processo? ");
                scanf("%f", &waitTime);
                PEnQueue(fila, id, prio, waitTime);
                break;
            case '2':
                removeHighestTime(fila);
                break;
            case '3':
                ProcessListPrint(fila);
                break;
            default:
                printf (" - Opcao invalida.\n");
        }
        fflush(stdin);
        continuar;
        CLR;
    }
    return;
}

//////////////////////////////////////////////////////////////////////////FIM QUESTAO 10
