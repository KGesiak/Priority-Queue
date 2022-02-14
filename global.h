#pragma once
typedef struct
{
 int nKey;
 int* pTab;
} PQInfo;
void freeInfo( const void* item );
void printItem( const void* item );
int findItem( const void* inf1, const void* inf2 );
#define PQINFO PQInfo