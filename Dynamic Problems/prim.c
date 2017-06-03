
#include "prim.h"


/*
	function to get number of line to determine vertices.
 */
int 
getCount(FILE * fptr)
{
	int ch=0, count = 0;
	while (!feof(fptr))
		if ((ch = fgetc(fptr)) == '\n')
			count++;
	return count;
}
/*
	function to be index of min weight edge in g.
*/
int 
minWeight(int weight[], int queueMstSet[], int numEdges)
{
   // Initialize min value
   int min = INF, minIndex=0, v=0;
 
   for (v = 0; v < numEdges; v++)
     if (queueMstSet[v] == FALSE && weight[v] < min){
         min = weight[v];
	 minIndex = v;}
 
   return minIndex;
}
/*
	P R I M   function.
*/
void 
prim(int ** g, int numEdges)
{
	int root[numEdges]; 		// Array to store constructed MST
	int weight[numEdges];   	// weight values used to pick minimum weight edge in cut
	int queueMstSet[numEdges];  	// To represent set of vertices not yet included in MST
	int count=0, i=0, v=0;
	
	for (i = 0; i < numEdges; i++){
		weight[i] = INF;
		queueMstSet[i] = FALSE;
 	}
	weight[0] = 0;     
	root[0] = -1; 
 	for( i=0; i < numEdges; i++){
	while(queueMstSet[i] == FALSE)
		for (count = 0; count < numEdges-1; count++)
		{
			int u = minWeight(weight, queueMstSet, numEdges);
			queueMstSet[u] = TRUE;
			for (v = 0; v < numEdges; v++)
				if (g[u][v] && queueMstSet[v] == FALSE && g[u][v] <  weight[v]){
					root[v]  = u;
					 weight[v] = g[u][v];
				}
		}
 	}
	int minweight=0;
  	 for (i = 1; i < numEdges; i++){
     		 fprintf(stderr,"\nEdge: (%d-%d)\tWeight: %d", root[i] + 1, i + 1, g[i][root[i]]);
		minweight=minweight+g[i][root[i]];
	}
	fprintf(stderr,"\n\tMinimum cost = %d\n",minweight);
}
/*
	 validate command line argument's count. 
*/
void
validateArguments(int argc){
	if(argc != 2){
		fprintf(stderr,"\nInvalid number of arguments:\nexpected\t./prim.out Filename.txt\n");
		exit(0);
	}
}
/*
	open file for reading.
*/
void*
myopen(char const *argv,FILE *fp){
	if((fp = fopen(argv, "r")) == NULL) {
		fprintf(stderr,"\nError opening file %s!\n",argv);
		exit(1);
	}
	return fp;
}

/*
	M A I N     function
*/
int 
main(int argc, char const *argv[])
{
	validateArguments(argc);
	FILE *fp = NULL;
	fp=myopen(argv[1],fp);

	int numEdges = 0, i=0, j=0, k=0;
	numEdges = getCount(fp);
	fseek(fp, 0, SEEK_SET);

	int ** g = malloc (numEdges * sizeof(int *));
		if(g == NULL){
			fprintf(stderr,"\nMalloc error.\n");
			exit(1);
		}
	for (i = 0; i < numEdges; i++){
		g[i] = malloc (numEdges * sizeof(int));
			if(g[i] == NULL){
				fprintf(stderr,"\nMalloc error.\n");
				exit(1);
			}
	}
	int * tempArray =  malloc (numEdges * numEdges * sizeof(int));
			if(tempArray == NULL){
				fprintf(stderr,"\nMalloc error.\n");
				exit(1);
			}

	char * line =  malloc (sizeof(char) * 100);
			if(line == NULL){
				fprintf(stderr,"\nMalloc error.\n");
				exit(1);
			}
	char * tokens;
	/*
		Taking inputs from file.
	*/
	i = 0;
	while (fgets(line, 100, fp) != NULL) {
		tokens = strtok(line, ",");
		while (tokens) {
			tempArray[i++] = atoi(tokens);
			tokens = strtok(NULL, ",");
		}
	}

	/* 
		Copying values from temporary array to the adjacency matrix 
	*/
	for (i = 0, k = 0; i < numEdges; ++i) {
		for (j = 0; j < numEdges; ++j, k++) {
			g[i][j] = tempArray[k];
		}
	}
	/*
		Display initial g
	*/
	fprintf(stderr,"\nInput graph.\n\n");
	for (i = 0; i < numEdges; i++) {
		fprintf(stderr,"\n");
		for (j = 0; j < numEdges; j++)
			fprintf(stderr,"%3d ", g[i][j]);
	}
	fprintf(stderr,"\n");
	prim(g, numEdges);
	
	/*
		Free memory.
	*/
	for(i=0; i<numEdges; i++)
		free(g[i]);
	free(line);
	free(g);
	free(tempArray);
	fclose(fp);	
	return 0;
}
