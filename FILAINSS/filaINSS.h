/*
    @author: CJ PROG
    @name: José Eduardo Chico
*/

#ifndef FILAINSSS_H_DEFINED
#define FILAINSSS_H_DEFINED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "structInfo.h"

#define MAIOR_QUE(x, y) ( (x) > (y) ? TRUE : FALSE )
#define IGUAL_QUE(x, y) ( (x) == (y) ? TRUE : FALSE )

#define VERFYSPACE(x) if( (x) == NULL ) return NO_SPACE

// =================== STRUCTS DECLARATIONS =====================================

struct Atom{
    TInfo info;
    struct Atom *next;
    struct Atom *before;
    struct Atom *nextAge;
    struct Atom *beforeAge;
};

struct filaINSS{
    struct Atom *head;
};

/*struct Caixa{
    int status;
    int id;
    int tempCaixa;
    int totAtendidos;
    int totPensionistas;
    int totPrazo;
};*/
// =================== END OF STRUCTS DECLARATIONS =============================

typedef enum {FALSE = 0, TRUE = 1} Boolean;
typedef enum { OK = 0, NOT_FOUND, LIST_IS_FULL, LIST_IS_EMPTY, INVALID_INDEX, NO_SPACE, IVALID } Error;

// =============================== STRUCTS DECLARATIONS TYPES ====================================

typedef struct filaINSS TFINSS;
typedef struct Atom TAtom;

// ==================================== Prototypes of Functions ===================================

void printInfo( TInfo *info );
void errorMessage( Error codret );

TAtom *allocAtom();
Error addFINSSInfo( TFINSS *list, TInfo x );
Boolean isFINSSEmpty( TFINSS *list );
Boolean haveFINSSData( TFINSS *list );
Error initFINSS( TFINSS *list );
Error addFINSSInfo( TFINSS *list, TInfo x );
Error removeFirstFINSSNormal( TFINSS *list, TInfo *infoRemoved );
Error removeFirstFINSSPensionista( TFINSS *list, TInfo *infoRemoved );
Error removeFINSSByID( TFINSS *list, int id, TInfo *infoRemoved );
void printListByAge( TFINSS *list );
void printList( TFINSS *list );
int getLenthByAge( TFINSS *list );
int getNormalLenth( TFINSS *list );




#endif // FILAINSSS_H_DEFINED
