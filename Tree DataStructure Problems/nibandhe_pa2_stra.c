#include "nibandhe_pa2_stra_helper.c"




int main( int argc, char *argv[] ){
	if(argc < 2){
		printf("\nInvalid number of input at command line. \nExiting.\n");
		exit(0);
	}else if( argc > 2 ) {
      		printf("\nToo many arguments supplied.\n");
		exit(0);
   	}
	//size = atoi( argv[1]);
	//size = padding(size);
	size = padding(atoi(argv[1]));
	int size1=size;


	srand(time(NULL));
	printf("\nStrassen's Algorith for matrix size: %d x %d \n", size, size);

	int a[size][size], b[size][size], c[size][size], d[size][size];
	
	int i=0,j=0,k=0;
					//------------------------------------------init a and b and c martix	
	
	myinit(a,b,c,d);
					//------------------------------------------print a matrix
	printf("\n--------------------------------------Matrix A.\n");	
	display(a,size);
	
					//------------------------------------------print b matrix
	printf("\n--------------------------------------Matrix B.\n");	
	display(b,size);
	begin=clock();
	strassen(a, b, c, size);
	end=clock();
	timeNeeded = (long)(end-begin)/CLOCKS_PER_SEC;
	//printf("\nTime needed for strassen is: %f\n",timeNeeded);
		begin=clock();
					//-----------------------------------------Normal multiplication 																			
	for(i=0; i<size1; ++i)
		for(j=0; j<size1; ++j)
			for(k=0; k<size1; ++k){
				d[i][j]+=a[i][k]*b[k][j];
    		    	}
	end=clock();
	timeNeeded = (long)(end-begin)/CLOCKS_PER_SEC;
	//printf("\nTime needed for normal multiplication is: %f\n",timeNeeded);
	printf("\n--------------------------------------Final Results using strassen.\n");	
	display(c,size1);

	printf("\n--------------------------------------Results using normal multiplication.\n");	
	display(d,size1);

	printf("\n--------------------------------------end.\n");
	printf("\n");

	return 0;
}
