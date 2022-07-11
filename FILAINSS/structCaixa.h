/*
    @author: CJ PROG
    @name: José Eduardo Chico
*/

#ifndef CAIXA_DEFINED
#define CAIXA_DEFINED

struct Caixa{
    int idCaixa;
	int status;
	int id;
	int tempCaixa;
	int totAtendidos;
	int totPensionistas;
	int totPrazo; // Total Atendidos no prazo de trabalho
    int totTemp; // Total de tempo de atendimento
};

typedef struct Caixa TCaixa;
// ============================ PROTOTYPES OF FUNCTIONS ============================
void printIdTimeCaixa( TCaixa *caixa );
void printCaixa( TCaixa *caixa );
void initCaixa( TCaixa *caixa );
Boolean isCaixaFree( TCaixa *caixa );
// ================================= FUNCTIONS =====================================

void initCaixa( TCaixa *caixa ){
	*caixa = (TCaixa) {2, 0, 0, 0, 0, 0, 0, 0};
}

void printIdTimeCaixa( TCaixa *caixa ){
	printf( "\n ======== CAIXA %d ===============\n", caixa->idCaixa );
	printf( "Id cliente = %d | Tempo no caixa = %d \n", caixa->id, caixa->tempCaixa );
}

void printCaixa( TCaixa *caixa ){
	printf( "\n =========== CAIXA %d  - ATENDIMENTO ===============\n", caixa->idCaixa );
	printf( " | ATENDIDOS: %d \n", caixa->totAtendidos);
    printf( " | PENSIONISTAS: %d \n", caixa->totPensionistas);
    printf( " | NAO PENSIONISTAS: %d \n", ( caixa->totAtendidos - caixa->totPensionistas ) );
    
    printf( " | TEMPO MEDIO DE ATENDIMENTOS: %.2f \n",  (float)(caixa->totTemp)/( caixa->totAtendidos == 0 ? 1 : caixa->totAtendidos ) );
}

Boolean isCaixaFree( TCaixa *caixa ){
	return ( caixa->status == 0 );
}

void updateCaixaOut( TCaixa *caixa )
{
	if( !isCaixaFree( caixa ) ){
		if( caixa->tempCaixa == 0 )
			caixa->status = 0;
		else{
            printIdTimeCaixa( caixa );
			caixa->tempCaixa--;
		}
	}	
}

void updateCaixaIn( TCaixa *caixa, TInfo x )
{
	caixa->status = 1;
	caixa->id = x.id;
	caixa->tempCaixa = x.time;
	caixa->totAtendidos++;
	if( x.age >= 60 )
		caixa->totPensionistas++;
    caixa->totTemp += x.time;
}

#endif // CAIXA_DEFINED
