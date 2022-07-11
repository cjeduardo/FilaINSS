/*
	@author: CJ PROG
    @name: José Eduardo Chico
*/

//#include "filaINSS.c"
#include <stdlib.h>
#include <stdio.h>
#include "filaINSS.h"
#include "structCaixa.h"
#include "unistd.h"

#define TEMP_TRAB 36//360  // Tempo de trabalho
#define TEMP_INSERT_CLI 5
#define TEMP_CLI 30
#define TEMP_CLI_MIN 1
#define TEMP_CLI_MAX 10
#define MAX_CLI_MIN 5 //Maximo numero de clientes em dado minuto

#define IS_PENSIONISTA(x) ( (x) >= 60 ? TRUE : FALSE )

void printInfo( TInfo *info ){
	printf( "\n | Cliente{ id = %d ; idade = %d ; tempo = %d } |", info->id, info->age, info->time );
}

int generate( int limit, int init ){
	return init + ( rand() % ( ++limit-init ) );
}

TInfo newCustommer( int id ){
	return  ( TInfo ) { id, generate( 90, 18 ), generate( TEMP_CLI_MAX, TEMP_CLI_MIN ), 0 };
}

//typedef enum { EQUILIBRADO = 0, NAO_PENSIONISTA = 1, PENSIONISTA = 2 } Equilibrio;
/*Equilibrio estado( TFINSS *list ){
    return ( getLenth - getNormalLenth ) ;
}*/

void updateTimeQueue( TFINSS *list, int *abandonos ){
	TAtom *paux = list->head->next, *pdel;
	while( paux != list->head ){
		paux->info.timeQueue++;
		if( paux->info.timeQueue == 30 ){
			pdel = paux;
			paux = paux->next;

			pdel->next->before = pdel->before;
			pdel->before->next = pdel->next;

			pdel->nextAge->beforeAge = pdel->beforeAge;
			pdel->beforeAge->nextAge = pdel->nextAge;

			printf( "\n=================== Cliente-ID = %d, abandonando da FILA ====================\n", pdel->info.id );
			free( pdel );
			*abandonos++;

		}else
			paux = paux->next;
	}

}

int main(){
    
    // Equilibrio eq = EQUILIBRADO;
	srand( time( NULL ) );
	int id = 1, minutos = 0, pensConsec = 0, totAbandono = 0, foraPrazo, counter = 0;
	int indexCaixa = 0, filaPensionista, filaNormal;
	TInfo infoAux = {0, 0, 0, 0};
	Error e;
	FILE *l;
	TCaixa caixas[3] = { { 1, 0, 0, 0, 0, 0, 0, 0 }, { 2, 0, 0, 0, 0, 0, 0, 0 }, { 3, 0, 0, 0, 0, 0, 0, 0 } };

	TFINSS list;
	errorMessage( initFINSS( &list ) );

	printf( "\n================================= INICIO AGENCIA ========================================== \n\n" );

	while( minutos < TEMP_TRAB || haveFINSSData( &list ) || !(isCaixaFree( &caixas[0] ) || isCaixaFree( &caixas[1] ) || isCaixaFree( &caixas[2] )) )
	{
        printf( "\n================================= Minuton %d ========================================== \n\n", minutos );
		if( minutos < TEMP_TRAB ){
			if( minutos % TEMP_INSERT_CLI == 0 ){
				counter = generate( MAX_CLI_MIN, 1 );
				while( counter-- > 0 ){
					e = addFINSSInfo( &list, ( infoAux = newCustommer( id++ ) ) );
					printf( "\n CLIENTE ADICIONADO: \n" );
					if( e == OK )
						printInfo( &infoAux );
					else{
						errorMessage( e );
						exit( 0 );
					}
				}
				printf( "\n ------------------------------------------------------- \n" );
			}
		}
		indexCaixa = 0;
		while( indexCaixa < 3 ){
			if( isCaixaFree( &caixas[indexCaixa] ) )
			{
				filaNormal = getNormalLenth( &list );
				filaPensionista = getLenthByAge( &list );

				if( filaNormal >= filaPensionista * 1.6  ){
					e = removeFirstFINSSNormal( &list, &infoAux );
                    pensConsec = 0;
				}
				else if( filaPensionista > filaNormal*1.6 ){
					e = removeFirstFINSSPensionista( &list, &infoAux );
					pensConsec++;
				}
				else
				{
					if( pensConsec >= 3 ){
						e = removeFirstFINSSNormal( &list, &infoAux );
						pensConsec = 0;
					}
					else{
						e = removeFirstFINSSPensionista( &list, &infoAux );
						pensConsec++;
					}
				}

				if( e == OK )
				{
					updateCaixaIn( &caixas[indexCaixa], infoAux );
					if( minutos < TEMP_TRAB ){
						caixas[indexCaixa].totPrazo++;
					}
				}
			}

			updateCaixaOut( &caixas[indexCaixa] );
			indexCaixa++;
		}

		updateTimeQueue( &list, &totAbandono );
		printf( "\nTOTAL PENSIONISTAS NA FILA: %d", getLenthByAge( &list ) );
		printf( "\nTOTAL NAO PENSIONISTAS NA FILA: %d\n", getNormalLenth( &list ) );
		minutos++;
		sleep( 1 );
		//system("CLS");
	}

	//==== IMPRIMIR RELATORIO FINAL ======================================
	printf( "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< AGENCIA ENCERRADA, DADOS DIARIO >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n " );

	indexCaixa = 0;
	foraPrazo = 0;
	while( indexCaixa < 3 ){
		printCaixa( &caixas[indexCaixa] );
		foraPrazo = foraPrazo + ( caixas[indexCaixa].totAtendidos - caixas[indexCaixa].totPrazo );
		indexCaixa++;
	}

	printf( "\n\n | ATENDIDOS FORA DO PRAZO: %d \n", foraPrazo );
	printf( " | TOTAL DE ABANDONOS DE FILA: %d \n", totAbandono );

	printf( "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n " );

	printf("\n\n");
	system("PAUSE");
    return 0;
}


