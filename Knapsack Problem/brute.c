#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct knapsack{

	int weight ;
	int profit ;
}knapsack;

void printarray(int **array, int maxX, int maxY){
	int i = 0,j = 0;
	for(i=0; i < maxX ; i++ ){
		fprintf(stderr,"\n");
		for(j=0; j< maxY; j++){
			fprintf(stderr,"\t%d",array[i][j]);
		}
	}
	
}
void 
binaryentry(int *knap_mat, int number, int no_of_elements){
	int location = no_of_elements;
	while(number>0)
      	{
		//fprintf(stderr,"\n[%d],%d->%d,locn",number%2,number,location);
           knap_mat[location]=number%2;
           location--;
           number=number/2;
      	}
}
void
fillupbinary(int **knap_mat, int no_of_entries, int no_of_elements){
	
	int i=0, number = 0;
	for(i=0; i< no_of_entries; i++){
		binaryentry(knap_mat[i], number, no_of_elements+1);
		number++;

	}
	
	
	
}
void
fillupmatrix(int **knap_mat, int maxX, int maxY, struct knapsack *input_elements, int total_weight){
	
	int i = 0,j = 0;
	for( i = 0 ; i < maxY; i ++){
//fprintf(stderr,"\n  input_elemtns[%d] =prof %d, weight %d",i, input_elements[i].profit, input_elements[i].weight);
	}
//fprintf(stderr,"\n%d maxX, %dmaxY",maxX, maxY);
	for(i = 0; i < maxX ; i++ ){
		int sum = 0;
		for(j = 2; j<= maxY; j++){
			if (knap_mat[i][j] == 1){	
//fprintf(stderr,"\n before knap_mat[%d][%d]:%d",i,j,knap_mat[i][j]);
				knap_mat[i][j] = input_elements[j-2].profit;
				sum += input_elements[j-2].weight;
				knap_mat[i][1] += input_elements[j-2].profit;
				//fprintf(stderr,"\n%d.sum:%d.j",sum,j);
//fprintf(stderr,"->after %d\t input_element= %d",knap_mat[i][j],input_elements[j].profit);
			}
		}
		if( sum > total_weight){
			knap_mat[i][0] = 0; 
			//mark invalid.
			}else
				knap_mat[i][0] = sum;
				//mark valid.
	}	
	
}

void
displayresult(int **knap_mat, int no_of_entries, int no_of_elements, struct knapsack *input_elements, int total_weight){
	int max = 0, i = 0, entry_number = 0 ;
	for( i = 0; i < no_of_entries; i++){
		if( (knap_mat[i][0] > 0) && (knap_mat[i][0] <= total_weight) && (max < knap_mat[i][1]) ){
			max = knap_mat[i][1];
			entry_number = i;
//fprintf(stderr,"\n MAX : %d",max);	
		}
	}
	fprintf(stderr,"\n Item \t\tProfit");

	for ( i = 2 ; i < no_of_elements ; i++){
		if(knap_mat[entry_number][i] != 0){
			fprintf(stderr,"\n   Item [%d]\t%d",i-2,knap_mat[entry_number][i]);
		}
	}
	fprintf(stderr,"\n Max Weight :\t%d",knap_mat[entry_number][0]);
	fprintf(stderr,"\n Max Profit :\t%d", knap_mat[entry_number][1]);
	FILE *ptr = fopen("brute_output.txt","w");
		if(ptr == NULL ){
			fprintf(stderr,"Cannout open brute_output.txt");
			exit(1);
		}
	//fseek(ptr, 0L , SEEK_SET );
	rewind(ptr);
	fprintf(ptr,"%d\n",knap_mat[entry_number][1]);
	fprintf(ptr,"%d\n",knap_mat[entry_number][0]);
	for ( i = 2 ; i < no_of_elements ; i++){
		if(knap_mat[entry_number][i] != 0){
			fprintf(ptr,"%d, ",i-2);
		}
	}
	fprintf(ptr,"\n");
	fclose(ptr);
	ptr=NULL;
	fprintf(stderr,"\nOutput File for brute created.\n");
	//fprintf(stderr,"\nAnswer entry %d = %d + %d + %d",entry_number, knap_mat[entry_number][1], knap_mat[entry_number][2], knap_mat[entry_number][3]);
}
int 
getCount(FILE * fptr)
{
	int count = 0;
	fscanf(fptr,"%d",&count);
	//fprintf(stderr,"\n--%d--",count);
	return count;
}
void*
myopen(char const *argv,FILE *fp){
	if((fp = fopen(argv, "r")) == NULL) {
		fprintf(stderr,"\nError opening file %s!\n",argv);
		exit(1);
	}
	return fp;
}
void
validateArguments(int argc){
	if(argc != 2){
		fprintf(stderr,"\nInvalid number of arguments:\nexpected\t./brute.o knapsack.txt\n");
		exit(0);
	}
}
int 
main(int argc, char const *argv[]){
	
	validateArguments(argc);
	fprintf(stderr,"\n\nBrute force 0/1 Knapsack\n");
	FILE *fp = NULL;
	fp=myopen(argv[1],fp);
	int no_of_elements = getCount(fp);
	int no_of_entries = pow(2,no_of_elements);
	int total_weight = 0;
	knapsack *input_elements = calloc(no_of_elements, sizeof(struct knapsack));
		if(input_elements == NULL){
			fprintf(stderr, "\nmalloc error.\n");
			exit(1);
		}
	
	int i=0;
	//fprintf(stderr,"\n no_of_elements: %d", no_of_elements);
		
	//Read from file no_of_elements
	//Read from file weight and profits.
	
	int **knap_mat = calloc(no_of_entries,sizeof(int*));
		if(knap_mat == NULL){
			fprintf(stderr,"\nMalloc error.\n");
			exit(1);
		}
	for (i = 0; i <= no_of_entries; i++){
		knap_mat[i] = calloc (no_of_elements+2,sizeof(int));
			if(knap_mat[i] == NULL){
				fprintf(stderr,"\nMalloc error.\n");
				exit(1);
			}
	}
	int * tempArray =  calloc((no_of_elements * no_of_elements)+1,sizeof(int));
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

	fseek(fp, 2, SEEK_SET);
	i = 0;
	while (fgets(line, 100, fp) != NULL) {
		tokens = strtok(line, ",");
		while (tokens) {
			//fprintf(stderr, "\n[%d] 0-> %d",i,atoi(tokens));	
			tempArray[i++] = atoi(tokens);
			tokens = strtok(NULL, ",");
		}
	}
	int j = 0; 
	for( i = 0; i < no_of_elements ; i++)
		input_elements[i].weight = tempArray[j++];
	for( i = 0; i < no_of_elements ; i++)
		input_elements[i].profit = tempArray[j++];

	total_weight = tempArray[j];
	fclose(fp);
	fp=NULL;
	//printarray(knap_mat, no_of_entries, no_of_elements+2);
	
	//initialize the array to binary counts leaving 1st bit for valid entries.
	fillupbinary(knap_mat, no_of_entries, no_of_elements);
	//printarray(knap_mat, no_of_entries, no_of_elements+2);
	//fprintf(stderr,"\n");
	
	fillupmatrix(knap_mat, no_of_entries, no_of_elements+2, input_elements, total_weight);
	
	//printarray(knap_mat, no_of_entries, no_of_elements+2);
	displayresult(knap_mat, no_of_entries, no_of_elements+2, input_elements, total_weight);
	fprintf(stderr,"\n");
	free(line);
	free(tempArray);
	for (i = 0; i <= no_of_entries ; i++){
		free(knap_mat[i]);
	}
	free(knap_mat);
	free(input_elements);
	
	return 0;
}
