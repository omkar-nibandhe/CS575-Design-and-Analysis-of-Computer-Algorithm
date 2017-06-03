#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* handlefile(FILE* fp, int argc, char **argv);
int getNodes(FILE * fptr);
void display(int ** a, int size);
int ** floyd(int ** adjacency, int nodes, int **distance, int **P);
void path( int **P,int q,int r);




//-----------------------------------------------------------------------------------
FILE* handlefile(FILE* fp, int argc, char **argv){
	if (argc > 2) {
		fprintf(stderr,"  Arguements invalid.Provide:\n  .\\nibandhe_pa2_floyd FILENAME.txt\nExiting\n");
		exit(0);
		
	}
	if (argc < 2) {
		//fprintf(stderr,"  Arguements invalid.Provide:\n  .\\nibandhe_pa2_floyd FILENAME.txt\nExiting\n");
		//exit(0);
		fp=fopen("inputfloyd.txt","r");
		if(NULL == fp){
			fprintf(stderr,"\nUnable to open file floyd's input.txt .\n");
			exit(0);
		}
	}
	else {
		fp=fopen(argv[1],"r");
		if(NULL == fp){
			fprintf(stderr,"\nUnable to open file %s.\n",argv[1]);
			exit(0);
		}
	}
}

//-----------------------------------------------------------------------------------

int getNodes(FILE * fptr)
{
	int ch, count = 0;
	while (!feof(fptr))
		if ((ch = fgetc(fptr)) == '\n')
			count++;
	//printf();
	return count;
}

//-----------------------------------------------------------------------------------

void display(int ** a, int size)	
{
	int i=0, j=0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			printf("%4d ", a[i][j]);
		printf("\n");
	}
}

//-----------------------------------------------------------------------------------


int ** floyd(int ** adjacency, int nodes, int **distance, int **P)
{
	int i=0, j=0, k=0;
	for (k = 0; k < nodes; k++)
		for (i = 0; i < nodes; i++)
			for (j = 0; j < nodes; j++)
				if ((distance[i][j] > distance[i][k] + distance[k][j]) ){
					distance[i][j] = distance[i][k] + distance[k][j];
					P[i][j]=k+1;
				}	

	return distance;
}


//-----------------------------------------------------------------------------------


void path( int **P,int q,int r){
	//printf("\n%d\n",P[q][r]);
	if (P[q][r]!=0){
	             path(P, q, P[q][r]);
	             printf("\n\t%d\t\t%d \t\t\tv%d ",q+1,r+1, P[q][r] + 1);
			//if(P[q][r]!=0)
		     printf("\t[v%d]",P[q][r]);
			//getchar();
			
	             path(P, P[q][r], r);
	}
	return;
}

//-----------------------------------------------------------------------------------



