#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define YES 1
#define NO 0
int *w, *p, maxprofit,C,num, *bestset, *include, *id;
float *ratio;
int total_item_number;

int
KWF2( int i, int weight, int profit){
	int bound = profit;

	while (weight < C && i <= total_item_number) {       //not “full” and more items
		if ((weight + w[i]) <= C ) {                 //room for next item
      	   	weight += w[i];
			bound += p[i];
		}
		else
		{
   	        float Ctemp = (float)  C;
			float Wtemp = (float) weight;
			float W2temp = (float) w[i];

			float temp = ((Ctemp - Wtemp) / W2temp);  //fraction of  i added to knapsack
      		weight = C; 
			bound += (p[i] * temp);
		}
		i++;                         
	}	// next item
	return bound;
}

int 
promising( int i, int weight, int profit){
    //Cannot get a solution by expanding node i
	int bound;
   	 if (weight >= C )
		return 0;
	
    //Compute upper bound
    bound = KWF2(i+1, weight, profit);	
	return (bound > maxprofit);

}
void
knapsack(int i, int profit, int weight){

	if ( weight <= C && profit > maxprofit ){
		//save better solution
		maxprofit = profit; //save new profit
		num = i;
		int j = 0;

		for( j = 0 ; j <= total_item_number ; j++)
			bestset[j] = include[j]; //save solution

	}

	if (promising(i, weight, profit) ){
	   include[i + 1] = 1;
	   knapsack((i + 1), (profit + p[i+1]), (weight + w[i+1]));
	   include[i + 1] = 0;
	   knapsack((i + 1), profit, weight);
	}
}

void
filewrite(int finalWeight, int finalProfit){

	FILE *ptr = fopen("backtrack_output.txt","w");
		if(ptr == NULL ){
			fprintf(stderr,"Cannout open backtrack_output.txt");
			exit(1);
		}
	rewind(ptr);
	fprintf(ptr,"%d\n%d\n",finalProfit,finalWeight);
	
	int i = 0;
	for ( i = 0 ; i <= total_item_number ; i++ ){
		//fprintf(stderr,"\n %d",id[i]);
		if(bestset[i] == YES ){
			fprintf(ptr,"%d, ",id[i]);
		}
	}
	fclose(ptr);
	
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
my_calloc(size_t size)
{
	void *w = malloc(size);
	if(w == NULL)
	{
		fprintf(stderr,"\nMalloc error.\n");
		exit(1);
	}
	memset(w, 0, size);

	return w;
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
sort1(int n){
	int i = 0, j = 0;
	for(i = 0 ; i <= total_item_number; i++){
		id[i] = i-1;
	}
	float a ;
	int temp;
	for (i = 1; i <= n; i++)
    {
        for (j = i + 1; j <= n; j++) 					// j<=n
        {
            if (ratio[i] < ratio[j])
            {
                // ratio 
				a =  ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = a;
				
				// weight
				temp = w[i];
				w[i] = w[j];
				w[j] = temp;
				
				// profit
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
				
				//id
				temp = id[i];
				id[i] = id[j];
				id[j] = temp;
				
            }
        }
    }
}
void
validateArguments(int argc){
	if(argc != 2){
		fprintf(stderr,"\nInvalid number of arguments:\nexpected\t./backtrack.o knapsack.txt\n");
		exit(0);
	}
}

int
main(int argc , const char * argv[]){
	
	validateArguments(argc);
	fprintf(stderr,"\n\nBacktrack 0/1 Knapsack\n");
	
	FILE *fp = NULL;
	fp=myopen(argv[1],fp);
	
	int no_of_elements = getCount(fp);
	total_item_number = no_of_elements;
	
	w = my_calloc((no_of_elements+1) * sizeof(int));
	p = my_calloc ((no_of_elements+1) * sizeof(int));
	id = my_calloc((no_of_elements+1)* sizeof(int));
	ratio = my_calloc ((no_of_elements+1) * sizeof(float));
	bestset = my_calloc((no_of_elements+1) * sizeof(int));
	include = my_calloc((no_of_elements+1) * sizeof(int));
	
	int * tempArray =  my_calloc(((2 * no_of_elements)+1 )*sizeof(int));

	char * line =  malloc (sizeof(char) * 100);
	if(line == NULL){
		fprintf(stderr,"\nMalloc error.\n");
		exit(1);
	}

	char * tokens;
	fseek(fp, 2, SEEK_SET);
	int i = 0;
	while (fgets(line, 100, fp) != NULL) {
		tokens = strtok(line, ",");
		while (tokens) {
			//fprintf(stderr, "\n[%d] 0-> %d",i,atoi(tokens));	
			tempArray[i++] = atoi(tokens);
			tokens = strtok(NULL, ",");
		}
	}

	int j = 0;
	for( i = 1 ; i <= no_of_elements ; i ++){
		w[i] = tempArray[j];
		p[i] = tempArray[j+no_of_elements];
		ratio[i] = ((float)p[i]/(float)w[i]);
	
		j++;
	}

	j = (2*no_of_elements);
	C = tempArray[j];
	sort1(no_of_elements);

	maxprofit = 0;
	for(i = 1; i <= no_of_elements; i ++){
		//fprintf(stderr, "\n i: %d,id:%d\tw[%d]:%d\tp[%d]:%d\tratio[%d]:%f",i,id[i],i,w[i],i,p[i],i,ratio[i]);
		
	}
	knapsack(0,0,0);
	
	int ResultProfit = 0, ResultWeight = 0;	

	fprintf(stderr, "\n Item\t\tProfit\n");
	for ( i = 0; i <= no_of_elements; i++){
		if (bestset[i]){
			fprintf(stderr, "   Item [%d]\t%d\n",id[i], p[i]);
			ResultProfit += p[i];
			ResultWeight += w[i];
		}
	}

	fprintf(stderr, " Max weight :\t%d \n Max profit :\t%d\n", ResultWeight, ResultProfit);
	fprintf(stderr,"Output File for Backtrack created.\n\n");
	filewrite(ResultWeight, ResultProfit);
	free(w);
	free(p);
	free(ratio);
	free(id);
	free(include);
	free(bestset);
	free(tempArray);
	free(line);
	fclose(fp);
	return 0;
}
