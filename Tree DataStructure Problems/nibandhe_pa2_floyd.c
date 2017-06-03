#include"nibandhe_pa2_floyd_helper.c"



int main(int argc, char *argv[])
{

	FILE *fp = handlefile(fp,argc,argv);
	int nodes = 0;

	/* Get number of nodes from the file */
	nodes = getNodes(fp);
	fseek(fp, 0, SEEK_SET);
	printf("\n--->%d\n",nodes);
	char * line = (char *) malloc (sizeof(char) * 100);
	char * tokens;
	int i = 0, j = 0;
	
	int ** finalArray;
	int ** distance =  malloc (nodes * sizeof(int *));
	int ** p = malloc(nodes * sizeof(int *));
	if(distance == NULL || p == NULL){
		fprintf(stderr,"\nMalloc fail.\n");
		exit(1);
	}
	for (i = 0; i < nodes; i++){
		distance[i] =  malloc (nodes * sizeof(int));
		p[i] = malloc (nodes *sizeof(int));
		if(distance[i] == NULL || p[i] == NULL){
			fprintf(stderr,"\nMalloc fail.\n");
			exit(1);
		}
	
		}
	for(i=0;i<nodes;i++)
		for(j=0;j<nodes;j++){
			p[i][j]=0;
			
		}
	/* Allocating memory for adjacency matrix */
	int ** adjacency_matrix = (int **) malloc (nodes  * sizeof(int *));
	for (i = 0; i < nodes; i++)
		adjacency_matrix[i] = (int *) malloc (nodes * sizeof(int));



	int array[nodes*nodes];
	i=0;
	j=0;
	char ch;
	char digi[100]="";
	int length=0;
	ch=(fgetc(fp));
	while(ch != EOF && i < nodes*nodes){
		if(isalnum(ch) || ch=='-' ){
			digi[length]=ch;	
			length++;
			digi[length]='\0';	
		//printf("\t\t%c",ch);
		}else{
			//if((j-1) == nodes){
	
			//	j=0;	
			//	i++;
	
			//	}
			//printf("\n-->%d %d:%d",atoi(digi),i,j);
			array[i]=atoi(digi);
			i++;
			//adjacency_matrix[i][j]=atoi(digi);
			//distance[i][j]=atoi(digi);
			length=0;
			//j++;
			digi[0]='\0';
			digi[1]='\0';
			}	
		ch=(fgetc(fp));
	}
	for(i=0;i<nodes*nodes;i++){
		if(i % nodes ==0 ){
			printf("\n");
		}
	//printf("\t %d",array[i]);
	}
	int k=0;
	for(i=0,k=0;i<nodes;i++)
		for(j=0;j<nodes;j++,k++){
			adjacency_matrix[i][j]=array[k];
			distance[i][j]=array[k];
			}



	/* Display the initial adjacency matrix */
	printf("\n--------------------------------------Adjacency matrix:\n");
	display(adjacency_matrix, nodes);

	/* Get shortest path for each pair of nodes using Floyd's algorithm */
	/* and save to distanceMatrix */
	finalArray = floyd(adjacency_matrix, nodes, distance, p);

	/* Display the final distance matrix */
	printf("\n--------------------------------------The distance matrix is: \n");
	display(finalArray, nodes);
	printf("\n--------------------------------------Path array denoting \"k\"\n");
	display(p, nodes);

	printf("\nShortest Path\n\t Node\t Destination\t\t\tVIA\n");
	printf("\n-------------------------------------------------------\n");
	i=0;
	while(i<nodes){
		for(j=nodes-1;j>=0;j--){
			printf("\n %d %d",i,j);
			//path function goes here.
			path(p, i, j);
		}
		i++;
	}
	//for(i=0;i<nodes;i++)
	//	for(j=0;j<nodes;j++){
			//printf("%d",i+1);
			//path(p, i, p[i][j]);
			//printf("   [v%d]",j+1);
			//printf("\n");
	            	//printf("v%d",P[q][r]);
	             	//path(P, P[q][r], r);

	//	}
	//path(p, 1, 2);
	//path(nodes, distanceMatrix, 0, 4);
	printf("\n\n");
	return 0;
}
