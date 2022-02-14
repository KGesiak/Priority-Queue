#pragma once
#include "global.h"
#include <float.h>
#define PRIOR_ERROR INT_MIN
#define POS_ERROR -1
typedef struct 
{
  PQINFO* pInfo;
  int nPrior; 
} PQITEM;
typedef struct 
{
 PQITEM* pPQueue; 
 int nPQSize; 
 int nPQCurrSize;
} PQueue;

PQueue* PQInit( int size );
int PQisEmpty( PQueue* Q );
int PQSize( PQueue* Q ); 
int PQMaxPrior( PQueue* Q );
int PQEnqueue( PQueue* Q, PQINFO* inf, int Prior );
PQINFO* PQDequeue( PQueue* Q );
void PQClear( PQueue* Q, void( __cdecl* freeInfo )( const void* ) );
void PQRelease( PQueue** Q, void( __cdecl* freeInfo )( const void* ) );
void PQPrint( PQueue* Q, void( __cdecl* printItem )( const void* ), int index );
int PQSetPrior( PQueue* Q, int( __cdecl* findItem )( const void* inf1, const void* inf2 ), PQINFO* inf, int prior );
int PQsetPrior( PQueue* Q,int index,int prior );
int PQGetPrior( PQueue* Q, int( __cdecl* findItem )( const void* inf1, const void* inf2 ), PQINFO* inf );
int PQgetPrior( PQueue* Q, int index );
int PQFind( PQueue* Q, int( __cdecl* findItem )( const void* inf1, const void* inf2 ), PQINFO* inf );