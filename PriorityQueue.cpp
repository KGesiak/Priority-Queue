#include <stdlib.h>
#include <stdio.h>
#include "PQueue.h"
int main()
{
    PQueue* Q = PQInit( 20 );
	PQINFO* F1 = ( PQINFO* )calloc( 1,sizeof( PQINFO ) );
	F1->pTab = ( int* )calloc( 1,sizeof( int ) );
	F1->pTab[0] = 1;
	F1->nKey = 1;
	PQINFO* F2 = ( PQINFO* )calloc( 1,sizeof( PQINFO ) );
	F2->pTab = ( int* )calloc( 1,sizeof( int ) );
	F2->pTab[0] = 2;
	F2->nKey = 2;
	PQINFO* F3 = ( PQINFO* )calloc( 1,sizeof( PQINFO ) );
	F3->pTab = ( int* )calloc( 1,sizeof(int ) );
	F3->pTab[0] = 3;
	F3->nKey = 3;
	PQINFO* F4 = ( PQINFO* )calloc( 1,sizeof( PQINFO ) );
	F4->pTab = ( int* )calloc( 1,sizeof( int ) );
	F4->pTab[0] = 4;
	F4->nKey = 4;
	PQINFO* F5 = ( PQINFO* )calloc( 1,sizeof( PQINFO ) );
	F5->pTab = ( int* )calloc( 1,sizeof( int ) );
	F5->pTab[0] = 5;
	F5->nKey = 5;
	PQINFO* F6 = ( PQINFO* )calloc( 1,sizeof( PQINFO ) );
	F6->pTab = ( int* )calloc( 1,sizeof( int ) );
	F6->pTab[0] = 6;
	F6->nKey = 6;
	PQINFO* F7 = ( PQINFO* )calloc( 1,sizeof( PQINFO ) );
	F7->pTab = ( int* )calloc( 1,sizeof( int ) );
	F7->pTab[0] = 7;
	F7->nKey = 7;
	PQINFO* F8 = ( PQINFO* )calloc( 1,sizeof( PQINFO ) );
	F8->pTab = ( int* )calloc( 1,sizeof( int ) );
	F8->pTab[0] = 8;
	F8->nKey = 8;
	PQEnqueue( Q,F1,1 );
	PQEnqueue( Q,F4,4 );
	PQEnqueue( Q,F3,3 );
	PQEnqueue( Q,F2,2 );
	PQEnqueue( Q,F5,5 );
	PQEnqueue( Q,F6,6 );
	PQPrint( Q,printItem,0 );
	printf( "\n" );
	PQDequeue( Q );
	PQPrint( Q,printItem,0 );
	printf( "\n" );
	PQEnqueue( Q,F7,5 );
	PQPrint( Q,printItem,0 );
	printf( "\n" );
	PQEnqueue( Q,F8,6 );
	PQPrint( Q,printItem,0 );
	printf( "\n" );
	printf( "Priority of F7: %d, index of F7: %d", PQGetPrior( Q,findItem,F7 ), PQFind( Q,findItem,F7 ) );
	printf( "\n" );
	PQSetPrior( Q,findItem,F7,9 );
	PQPrint( Q,printItem,0 );
	printf( "\n" );
	PQSetPrior( Q,findItem,F7,6 );
	PQPrint( Q,printItem,0 );
	PQRelease( &Q,freeInfo );
}
void freeInfo( const void* item )
{
	free( ( ( PQInfo* )item )->pTab );
	free( ( PQInfo* )item );
}
void printItem( const void* item )
{
	PQITEM* temp = ( PQITEM* )item;
	printf( " Key: %d (%d) ", temp->pInfo->nKey,temp->nPrior );
}
int findItem( const void* inf1, const void* inf2 )
{
	if( ( PQINFO* )inf1 > ( PQINFO* )inf2 )  return 1;
	else if ( ( PQINFO* )inf1 < ( PQINFO* )inf2 ) return -1;
	return 0;

}
