/* 
	@author: JOSÉ EDUARDO CJ
*/

#ifndef FILAINSSS_DEFINED
#define FILAINSSS_DEFINED

#include "filaINSS.h"
#include <time.h>

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

// =================== METHODS IMPLEMENTATION ==================================
TAtom *allocAtom(){
    return (TAtom*) malloc( sizeof(TAtom) );
}

Boolean isFINSSEmpty( TFINSS *list ){
	return ( list->head == NULL );
}

Boolean haveFINSSData( TFINSS *list ){
	return ( list->head->next != list->head );
}

Error initFINSS( TFINSS *list ){
    list->head = allocAtom();
    if( list->head == NULL ){
    	errorMessage( NO_SPACE );
    	exit( 0 );
	}
	
    list->head->info.id = -1;
    list->head->info.age = -1;
    list->head->info.time = -1;
    
    list->head->before = list->head;
    list->head->next = list->head;
    list->head->beforeAge = list->head;
    list->head->nextAge = list->head;
    
    return OK;
}

Error addFINSSInfo( TFINSS *list, TInfo x ){
	if ( isFINSSEmpty( list ) ) initFINSS( list );
	TAtom *newAtom = allocAtom();
	VERFYSPACE( newAtom );

	newAtom->info = x;
	
	newAtom->next = list->head;
	newAtom->before = list->head->before;
	list->head->before->next = newAtom;
	list->head->before = newAtom;
	
	//Preferencial File insertion
	TAtom *paux = list->head->nextAge;
	while( paux != list->head && paux->info.age >= newAtom->info.age )
		paux = paux->nextAge;
	
	newAtom->nextAge = paux;
	newAtom->beforeAge = paux->beforeAge;
	paux->beforeAge->nextAge = newAtom;
	paux->beforeAge = newAtom;
	
	return OK;
}

Error removeFirstFINSSNormal( TFINSS *list, TInfo *infoRemoved ){
	if ( isFINSSEmpty( list ) ) initFINSS( list );
	if( !haveFINSSData( list ) )
		return LIST_IS_EMPTY;
	
	//Normal Queue Remove
	TAtom *paux = list->head->next;

	while( paux != list->head && paux->info.age >= 60 )
		paux = paux->next;

	if( paux == list->head )
		return NOT_FOUND;
	
	paux->next->before = paux->before;
	paux->before->next = paux->next;

	paux->nextAge->beforeAge = paux->beforeAge;
	paux->beforeAge->nextAge = paux->nextAge;
	
	*infoRemoved = paux->info;

	free( paux );

	return OK;
}

Error removeFirstFINSSPensionista( TFINSS *list, TInfo *infoRemoved ){
	if ( isFINSSEmpty( list ) ) initFINSS( list );
	if( !haveFINSSData( list ) )
		return LIST_IS_EMPTY;
	
	//Normal Queue Remove
	TAtom *paux = list->head->nextAge;

	if( paux->info.age < 60  )
		return NOT_FOUND;
	
	paux->next->before = paux->before;
	paux->before->next = paux->next;

	paux->nextAge->beforeAge = paux->beforeAge;
	paux->beforeAge->nextAge = paux->nextAge;

	*infoRemoved = paux->info;

	free( paux );

	return OK;
}

Error removeFINSSByID( TFINSS *list, int id, TInfo *infoRemoved ){
	if ( isFINSSEmpty( list ) ) initFINSS( list );
	if( !haveFINSSData( list ) )
		return LIST_IS_EMPTY;
	
	//Normal Queue Remove
	TAtom *paux = list->head->next;
	while( paux != list->head && paux->info.id != id )
		paux = paux->next;

	if( paux == list->head )
		return NOT_FOUND;
	
	paux->next->before = paux->before;
	paux->before->next = paux->next;

	paux->nextAge->beforeAge = paux->beforeAge;
	paux->beforeAge->nextAge = paux->nextAge;
	
	*infoRemoved = paux->info;

	free( paux );

	return OK;
}

void printList( TFINSS *list )
{
	TAtom *at = list->head->next;
	
	printf("------------------------- list ----------------------------------- \n" );
	//printf( " Head: %d | %d | %d \n ", list->head->info.id, list->head->info.age, list->head->info.time );
	while( at != list->head ){
		printInfo( &at->info );
		at = at->next;
	}
	printf("\n--------------------- END list ---------------------------------- \n" );
}

void printListByAge( TFINSS *list )
{
	TAtom *at = list->head->nextAge;
	
	printf("------------------------- list ----------------------------------- \n" );
	//printf( " Head: %d | %d | %d \n ", list->head->info.id, list->head->info.age, list->head->info.time );
	while( at != list->head ){
		printInfo( &at->info );
		at = at->nextAge;
	}
	printf("\n--------------------- END list ---------------------------------- \n" );
}

int getLenthByAge( TFINSS *list )
{
	int count = 0;
	TAtom *at = list->head;
	while( ( at = at->nextAge ) != list->head )
		if( at->info.age > 59 )
			count++;
	return count;
}

int getNormalLenth( TFINSS *list ){
	int count = 0;
	TAtom *at = list->head;
	while( ( at = at->nextAge ) != list->head )
		if( at->info.age < 60 )
			count++;
	return count;
}

int getLenth( TFINSS *list ){
	int count = 0;
	TAtom *at = list->head;
	while( ( at = at->nextAge ) != list->head )
		count++;
	return count;
}

void insertCaixa(  ){
	
}

void errorMessage( Error codret )
{
	switch (codret)
	{
		case NOT_FOUND:
			printf( "\n Erro: Codigo/Chave inexistente..!" );
		break;
		case LIST_IS_FULL:
			printf( "\n Erro: lista esta Cheia..!" );
		break;
		case LIST_IS_EMPTY:
			printf( "\n Erro: lista esta Vazia..!" );
		break;
		case INVALID_INDEX:
			printf( "\n Erro: Indice Invalido..!" );
		break;
		case NO_SPACE:
			printf( "\n Erro: Memoria insuficiente..!" );
		break;
		case IVALID:
			printf( "\n Erro: Opcao IVALIDA..!" );
		break;
	}
}

// ==========================================================================
/*
main(){
	srand( time( NULL ) );
	TInfo info1 = { 1, generate(80, 10), generate(20, 1)}, 
		info2 = { 2, generate(80, 10), generate(20, 1) }, 
		info3 = { 3, generate(80, 10), generate(20, 1) };
	TFINSS list;
	initFINSS( &list );
	addFINSSInfo( &list, info1 );
	addFINSSInfo( &list, info2 );
	addFINSSInfo( &list, info3 );
	printList( &list );
	printf( "\n=============== LIST BY AGE ====================== \n" );
	printListByAge( &list );
	
	getLenthByAge( &list );
	
	sleep( 2 );
	while( true )
	{
		
	}
	
	
	printf("\n\n");
	system("PAUSE");
	
}
*/

#endif // FILAINSSS_DEFINED

