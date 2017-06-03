#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE 0

#define INF 999
#define MYMAX 1001

typedef struct kruskalTypeEdge{
	int xCoord;
	int yCoord;
	int weight;
}edge;
typedef struct Set{
	int parent;
	int height;
}Set;

int 
partion(struct kruskalTypeEdge *kedge, int p, int r);
void 
quick_sort(struct kruskalTypeEdge *kedge, int p, int q, int length);
int 
checker(int length, int max);
int 
getCount(FILE * fptr);
void*
myopen(char const *argv,FILE *fp);
void
validateArguments(int argc);
void
kruskal(int ** g, struct kruskalTypeEdge *kedge, int numEdges);
int 
uni(int i,int j, Set *set1);
int 
find(int i, Set *set1);
