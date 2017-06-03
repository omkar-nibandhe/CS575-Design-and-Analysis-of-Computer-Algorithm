#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE 0

#define INF 999
int 
getCount(FILE * fptr);

void*
myopen(char const *argv,FILE *fp);

void
validateArguments(int argc);

void 
prim(int ** graph, int numEdges);

int 
minWeight(int weight[], int queueMstSet[], int numEdges);

