#include "kruskal.h"

/*
//---------------------------------------------------------------------      function find3.
*/
int 
find(int i, Set *set1){
	//fprintf(stderr,"\n~~%d:%d:%d",i,set1->parent,set1->height);
	if(set1[i].parent != i)
		set1[i++].parent = find(set1[i].parent,set1);
	else
		return set1[i].parent;
}
/*
//---------------------------------------------------------------------       function union3.
*/
int 
uni(int i,int j, Set *set1){
	int repx = find(i, set1);
	int repy = find(j, set1);
    	 if (set1[repx].height == set1[repy].height){
		//fprintf(stderr,"\nHere!");
     		set1[repx].height++;
        	set1[repy].parent = repx;//y’s tree points to x’s tree 
	}
     	else
        	if (set1[repx].height > set1[repy].height){ 
		//fprintf(stderr,"\nHere!!!!!!!!!!!!!");
            		set1[repy].parent = repx;  //y’s tree points to x’s tree 
		}
     		else{
		//	fprintf(stderr,"\nHere~~~~~~~~~~~");
           		set1[repx].parent = repy;  //x’s tree points y’s tree
		}
}
void
kruskal(int ** g, struct kruskalTypeEdge *kedge, int numEdges){
	int ne=0, min = INF,z=0,u=0,v=0,a=0,b=0,mincost=0,i=0,j=0;
	edge finalResult[numEdges];
	Set set[numEdges];
	Set *set1 = malloc(sizeof(Set)*numEdges);
		if(set1 == NULL){
			fprintf(stderr,"\nMalloc error.\n");
			exit(0);
		}
	for(i=0;i<numEdges;i++){
		set[i].parent=i;
		set[i].height =0;
		set1[i].parent=i;
		set1[i].height =0;
		finalResult[i].xCoord=0;
		finalResult[i].yCoord=0;
		finalResult[i].weight=INF;
	}
	for(i=0; i < numEdges*numEdges; i++){

			//fprintf(stderr,"\n[%d:%d->%d]",kedge[i].xCoord, kedge[i].yCoord, kedge[i].weight);
	}
	i=0; ne=0;
	edge temp = kedge[z];
	while(ne < numEdges+1)
	{
	//fprintf(stderr,"\nno of edges: %d:%d\n",numEdges,ne);
		u=find(temp.xCoord,set1);
		v=find(temp.yCoord,set1);
		//	fprintf(stderr,"\n\t\tHere %d:%d!%d:%d\n",u,v,temp.xCoord,temp.yCoord);
		if(u != v){
			//fprintf(stderr,"\n~~~~~~~~~Here %d!\n",i);
			uni(u,v,set1);
			//finalResult[i++] = temp;
			mincost=mincost+temp.weight;
			fprintf(stderr,"\nEdge: (%d-%d)\tWeight: %d",temp.xCoord,temp.yCoord,temp.weight);
		}
		
		temp = kedge[z++];
	ne++;	
		//g[a][b]=g[b][a]=999;
	}
	printf("\n\tMinimum cost = %d\n",mincost);
	free(set1);
}

/*
//---------------------------------------------------------------------	 validate command line argument's count. 
*/
void
validateArguments(int argc){
	if(argc != 2){
		fprintf(stderr,"\nInvalid number of arguments:\nexpected\t./prim.out Filename.txt\n");
		exit(0);
	}
}
/*
//---------------------------------------------------------------------	open file for reading.
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
//---------------------------------------------------------------------	function to get number of line to determine vertices.
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
	for (i = 0; i <= numEdges; i++){
		g[i] = malloc (numEdges * sizeof(int));
			if(g[i] == NULL){
				fprintf(stderr,"\nMalloc error.\n");
				exit(1);
			}
	}
	int * tempArray =  calloc ((numEdges * numEdges)+1, sizeof(int));
			if(tempArray == NULL){
				fprintf(stderr,"\nMalloc error.\n");
				exit(1);
			}

	char * line = calloc (10,sizeof(char));
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
	edge kedge[numEdges*numEdges];
	for(i=0;i<numEdges*numEdges;i++){
		kedge[i].xCoord = 0;
		kedge[i].yCoord = 0;
		kedge[i].weight = INF;
	}
	/* 
//---------------------------------------------------------------------		Copying values from temporary array to the adjacency matrix 
	*/
	for (i = 0, k = 0; i < numEdges; i++) {
		for (j = 0; j < numEdges; j++, k++) {
			g[i][j] = tempArray[k];
			kedge[k].xCoord = i+1;
			kedge[k].yCoord = j+1;
			kedge[k].weight = tempArray[k];
			if(i==j)
				kedge[k].weight = INF;
		}
	}
	
	/*
//---------------------------------------------------------------------		Display initial graph
	*/
	fprintf(stderr,"\nInput graph.\n");
	for (i = 0; i < numEdges; i++) {
		fprintf(stderr,"\n");
		for (j = 0; j < numEdges; j++)
			fprintf(stderr,"%3d ", g[i][j]);
	}
	fprintf(stderr,"\n\n");
	//prim(g, numEdges);
	quick_sort(kedge,0,numEdges*numEdges-1,numEdges);
	kruskal(g,kedge,numEdges);
	
	/*
		Free memory.
	*/
	for(i=0; i<=numEdges; i++)
		free(g[i]);
	free(line);
	free(g);
	free(tempArray);
	fclose(fp);	
	return 0;
}
//---------------------------------------------------------------------RandomQuickSort

	void quick_sort(struct kruskalTypeEdge *kedge, int p, int q, int length){

	   	int j=0;
	    	if (p < q)		// since overlapped pointers will be give wrong results
	    	{
		j = partion(kedge, p, q);
			/*if(length<=20){		//print *s
			printf("\n------\n");
			int k =0 ;		
			for(k=0; k < length; k++){
				int q = 0;
				for(q = 0; q < arr[k]; q++){
					printf("*");
				}
				printf("\n");
			}
			}*/
		quick_sort(kedge, p, j-1,length);
		quick_sort(kedge, j+1, q,length);
		
	    	}
	}
	int partion(struct kruskalTypeEdge *kedge, int p, int r){
		//pivot has to be within the new array range. calculate the index and then select that indexed array as pivot.
		int pivotIndex = p + rand()%(r - p + 1); //generates a random number as a pivot within the specified range.
		//printf("\n%d->pivot",pivotIndex);	
		struct kruskalTypeEdge pivot = kedge[pivotIndex];	
		int i = p - 1;
		int j = 0;
		struct kruskalTypeEdge temp;
	
		temp = kedge[pivotIndex];
		kedge[pivotIndex]=kedge[r];
		kedge[r]=temp;
		
		for (j = p; j < r; j++){
			if (kedge[j].weight < pivot.weight){
		       		i++;
				struct kruskalTypeEdge temp;
				temp=kedge[i];
				kedge[i]=kedge[j];
				kedge[j]=temp;	
			}
		}
		temp=kedge[i+1];
		kedge[i+1]=kedge[r];
		kedge[r]=temp;
		
		return(i + 1);
	}
	
