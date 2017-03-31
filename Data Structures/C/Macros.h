#include <stdlib.h>
#include <stdio.h>

#ifndef MACROS_H
#define MACROS_H

///Define uma funcao para limpeza de tela
#ifdef WIN32 //Win
    #define CLR system("cls\n");
#else //Unix
    #define CLR system ("clear\n");
#endif

///Debug para usado no final da main.
#define ENDM printf("\n\n\n END MAIN\n")
///Outro debug
#define DBG printf ("\t\tDebug\n\n");

///Display de mensagem, espera por enter para continuar
#define continuar printf(" - Enter para continuar...\n");getchar();
///Imprimir todas as infos. Se 0, imprime so o essencial
#define DISPLAY_INFO 1

///Aloca o tamanho de uma determinada struct. Retorna ponteiro
#define ALLOC_STRUCT( Struct ) ((Struct *)malloc( sizeof( Struct )))

#define EXERCISE_SEPARATOR printf ("\n\n\n------------------------------------------------------------------------------\n\n\n");

#endif



