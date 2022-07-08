/* 
	@author: JOSÉ EDUARDO CJ
*/

#ifndef FILAINSSS_H_DEFINED
#define FILAINSSS_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include "structInfo.h"

#define MAIOR_QUE(x, y) ( (x) > (y) ? TRUE : FALSE )
#define IGUAL_QUE(x, y) ( (x) == (y) ? TRUE : FALSE )

#define VERFYSPACE(x) if( (x) == NULL ) return NO_SPACE

typedef enum {FALSE = 0, TRUE = 1} Boolean;
typedef enum { OK = 0, NOT_FOUND, LIST_IS_FULL, LIST_IS_EMPTY, INVALID_INDEX, NO_SPACE, IVALID } Error;

// =============================== STRUCTS DECLARATIONS TYPES ====================================

typedef struct filaINSS TFINSS;
typedef struct Atom TAtom;
typedef struct Info TInfo;

// ==================================== Prototypes of Functions ===================================

void printInfo( TInfo *info );
void errorMessage( Error codret );
Error addFINSSInfo( TFINSS *list, TInfo x );



#endif // FILAINSSS_H_DEFINED