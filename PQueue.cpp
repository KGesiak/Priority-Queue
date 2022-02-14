#include "PQueue.h"
#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void UpdateDown( PQITEM* tab, int l, int p );
void UpdateUp( PQITEM* tab, int l, int p );
PQueue* PQInit( int size )
{
	if ( size < 1 )
	{ 
		perror( "Invalid size!" );
		return NULL;
	}
	PQueue* Q = ( PQueue* )calloc( 1,sizeof( PQueue ) );
	if( !Q )
	{
		perror( "ERROR in PQInit: Queue is not allocated! ");
		return NULL;
	}
	Q->pPQueue = ( PQITEM* )calloc( size,sizeof( PQITEM ) );
	if( !Q->pPQueue )
	{
		perror( "Allocation error in PQInit!" );
		return NULL;
	}
	Q->nPQSize = size;
	return Q;
}
int PQisEmpty( PQueue* Q )
{
	return !Q || !Q->nPQCurrSize;
}
int PQSize( PQueue* Q )
{
	return ( Q )? Q->nPQCurrSize: PRIOR_ERROR;
}
int PQMaxPrior( PQueue* Q )
{
	return ( !Q || PQisEmpty( Q ) )? PRIOR_ERROR: Q->pPQueue->nPrior;
}
int PQEnqueue( PQueue* Q, PQINFO* inf, int Prior )
{
	if ( !Q )
	{
		perror( "ERROR in PQEnqueue: Queue is not allocated!" );
		return 0;
	}
	if( PQSize( Q ) == Q->nPQSize )
	{
		perror( "Queue is full!" );
		return 0;
	}
	int size = PQSize( Q );
	PQITEM* temp = &Q->pPQueue[size];
	temp->nPrior = Prior;
	temp->pInfo = inf;
	if( size ) UpdateUp( Q->pPQueue,0,size );
	Q->nPQCurrSize++;
	return 1;

}
PQINFO* PQDequeue( PQueue* Q )
{
	if( !Q || PQisEmpty( Q ) )
	{
		perror( "ERROR in PQDequeue: Allocation error or the queue is empty!" );
		return NULL;
	}
	int lastItem = --Q->nPQCurrSize;
	PQINFO* temp = Q->pPQueue->pInfo;
	if( lastItem )
	{
		Q->pPQueue->nPrior = Q->pPQueue[lastItem].nPrior;
		Q->pPQueue->pInfo = Q->pPQueue[lastItem].pInfo;
	}
	Q->pPQueue[lastItem].nPrior = NULL;
	Q->pPQueue[lastItem].pInfo = NULL;
	if( lastItem > 1 ) UpdateDown( Q->pPQueue,0,lastItem - 1 );
	return temp;
}
void PQClear( PQueue* Q, void( __cdecl* freeInfo )( const void* ) )
{
	if( !Q || !freeInfo)
	{
		perror( "Error in PQClear: Issue with queue or freeItem!" );
		return;
	}
	while ( !PQisEmpty( Q ) )
		freeInfo( PQDequeue( Q ) );
}
void PQRelease( PQueue** Q, void( __cdecl* freeInfo )( const void* ) )
{
	if ( !Q || !*Q )
	{
		perror( "ERROR in PQRelease: Queue is not allocated!" );
		return;
	}
	PQClear( *Q,freeInfo );
	free( ( *Q )->pPQueue );
	free( *Q );
	*Q = NULL;
}
void PQPrint( PQueue* Q, void( __cdecl* printItem )( const void* ), int index )
{
	if( !Q )
	{
		perror( "Error in PQPrint: Queue is not allocated!" );
		return;
	}
	if( index < 0 )
	{
		perror( "Invalid index in PQPrint!" );
		return;
	}
	if( index >= PQSize( Q ) ) return;
	if( printItem ) printItem( &Q->pPQueue[index] );
	printf( "[%d], ",index );
	PQPrint( Q,printItem,2 * index + 1 );
	PQPrint( Q,printItem,2 * index + 2 );
}
int PQSetPrior( PQueue* Q, int( __cdecl* findItem )( const void* inf1, const void* inf2 ), PQINFO* inf, int prior )
{
	return PQsetPrior( Q ,PQFind( Q,findItem,inf ),prior );
}
int PQsetPrior( PQueue* Q,int index,int prior )
{
	if( !Q )
	{
		perror( "ERROR in PQsetPrior: Queue not allocated correctly!" );
		return PRIOR_ERROR;
	}
	int temp = PQgetPrior( Q, index );
	if( temp != PRIOR_ERROR && temp!= POS_ERROR )
	{
		Q->pPQueue[index].nPrior = prior;
		if( Q->pPQueue[index].nPrior > temp ) UpdateUp( Q->pPQueue, 0 ,index );
		else if ( Q->pPQueue[index].nPrior < temp ) UpdateDown( Q->pPQueue,index,PQSize( Q ) - 1);
	}
	return temp;
}
int PQGetPrior( PQueue* Q, int( __cdecl* findItem )( const void* inf1, const void* inf2 ), PQINFO* inf )
{
	return PQgetPrior( Q, PQFind( Q,findItem,inf ) );
}
int PQgetPrior( PQueue* Q, int index )
{
	if( !Q || PQisEmpty( Q ) ) 
	{
		perror( "ERROR in PQgetPrior: Queue is not allocated correctly or is empty!");
		return PRIOR_ERROR;
	}
	if( index >= PQSize( Q ) || index < 0 )
	{
		perror( "Invalid index!" );
		return POS_ERROR;
	}
	return Q->pPQueue[index].nPrior;
}
int PQFind( PQueue* Q, int( __cdecl* findItem )( const void* inf1, const void* inf2 ), PQINFO* inf )
{
	if( !Q )
	{
		perror( "Error in PQFind: Queue is not allocated!" );
		return PRIOR_ERROR;
	}
	if( !findItem )
	{
		perror( "Issue with finditem in PQFind!" );
		return PRIOR_ERROR;
	}
	for( int i = 0; i < PQSize( Q ); i++ )
	{
		if( !findItem(  Q->pPQueue[i].pInfo ,inf ) ) return i;
	}
	return POS_ERROR;
}
void UpdateDown( PQITEM* tab, int l, int p )
{
	if( l>=p ) return;
	int i=l;
	int j = 2*i +1;
	PQITEM x =  tab[i] ;
	while( j <= p )
	{
		if( j < p )
			if( tab[j+1].nPrior >= tab[j].nPrior ) j++;
		if( x.nPrior >= tab[j].nPrior ) break;
		tab[i] = tab[j];
		i=j;
		j=2*i +1;
	}
	tab[i] = x;
}
void UpdateUp( PQITEM* tab, int l, int p )
{
	if( l>=p ) return;
	int i=p;
	int j = ( i-1 )/2;
	PQITEM x = tab[i];
	while( j >= l && x.nPrior > tab[j].nPrior)
	{
		tab[i] = tab[j];
		i= j;
		j = (i + 1)/2 -1;
	}
	 tab[i] = x;
}