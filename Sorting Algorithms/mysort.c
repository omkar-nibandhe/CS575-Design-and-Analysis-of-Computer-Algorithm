	#include<stdio.h>
	#include<stdlib.h>
	#include<time.h>
	#define MYMAX 1001
	#define MYCOUNTMAX 100


	int checker(int length, int max){

		if( length < 1){
			printf("\t\tInvalid number.");
			return (0);
		}
		if(length >= max){
			printf("\n\t\tUnexpected number.\n");
			return (0);
		}
		return(1);
	}

	//---------------------------------------------------------------Insertion sort
	void insert_display(int arr[], int length){
		int i=0;
		if(length > 20){
							//normal printing
		for(i=0; i< length; i++)
			printf("\t %d", arr[i]);
		}
		else{					// * printer
		printf("\n-----------Insertion sort for items less than 20.");
		for(i=0;i<length;i++){
			int j=0;
			printf("\n\t");
			for(j=0;j<arr[i];j++)
				printf("*");			
			}
		}
		printf("\n");
	}

	void myInsertionSort(){
		srand(time(NULL));					//srand()
		int length =0;
		printf("\n Number of elements in the array: \t");
		scanf("%d",&length);
	
		int j = 0, temp = 0, i=1, arr[length];
		if(checker(length, MYMAX)){				//check if input length is valid
		if(length>20)
		for(i = 0; i < length; i++){
			arr[i]= ( rand() % 1000) + 1;	
		} 
		else{
		for(i = 0; i < length; i++){
			arr[i]= ( rand() % 15+1);			// length <20 so init arr with 0 <20
		} 
		}
		insert_display(arr, length);
		printf("\n-------Computation.\n");
		for(i = 1; i < length; i++){
			j=i;
			while(j>0 && arr[j] < arr[j-1]){
				//swap
				temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;
				j--;
			}
			if(length<20)
				insert_display(arr, length);		
		}
		printf("\nFinal results:\n");
		insert_display(arr, length);
		printf("\n");
		}
	}
	//----------------------------------------------------------------Count Sort
	void myCountSort(){

		//printf("\n here !");
		srand(time(NULL));	
		int length =0;
		printf("\n Number of elements in the array: \t");
		scanf("%d",&length);

		int arr[length], temp[100], finalResults[100];
		int j = 0, i = 1;
		if(checker(length,MYCOUNTMAX)){
			if(length>20)
			for(i = 0; i < length; ++i){ //initialize input array.
				arr[i]=( rand() % 100 );
			
			}
			else{
			for(i = 0; i < length; ++i){ //initialize input array.
				arr[i]=( rand() % 15+1 );
			
			}
			}
			for(i = 0; i < 100; i++){
				temp[i]=0;
				finalResults[i]=0;
			}
			printf("\nInitial input:\n");
			for(i = 0; i < length; i++){
				printf("\t%d",arr[i]);
			}
			printf("\n");
			for(j = 0; j < length; j++){
				temp[arr[j]] = ( temp[arr[j]] + 1 );
			}
		
			for(i=1;i<100;i++){
				temp[i]=temp[i]+temp[i-1];
		
			}
			for(j=length-1; j >= 0; j-- ){
				finalResults[ --temp[ arr[j] ] ] = arr[j];
					if(length<=20){
						printf("\n---------------------------------------------------------------\n");
						for(i = 0; i < length; i++){
							//printf("\t->%d",finalResults[i]);
							int k=0;
							for(k=0;k<finalResults[i];k++)
								printf("*");
							printf("\n");
						}
					}
				
				//temp[ arr[j] ] = ( temp [ arr[j] ] - 1 );
				}
/*					for(i = 0; i < length; i++){
						int k=0;
						printf("\n\t");
						
						*/						
				//printf("\t%d",arr[j]);
		
			
			printf("\n-------------------------Final Results\n");
			for(i = 0; i < length; i++){
				printf("\t%d",finalResults[i]);
			}
		}

	}
	//---------------------------------------------------------------------Merge Sort

	void merge(int arr[], int l, int m, int r)
	{
	    int i, j, k;
	    int n1 = m - l + 1;
	    int n2 =  r - m;
	    int Left[n1], Right[n2];
	 
	   
	    for(i = 0; i < n1; i++)
		Left[i] = arr[l + i];
	    for(j = 0; j < n2; j++)
		Right[j] = arr[m + 1+ j];
	 
	    					
	    i = 0;
	    j = 0;
	    k = l;
	    while (i < n1 && j < n2)
	    {
		if (Left[i] <= Right[j])
		{
		    arr[k] = Left[i];
		    i++;
		}
		else
		{
		    arr[k] = Right[j];
		    j++;
		}
		k++;
	    }
	 
	    						// remaining at left
	    while (i < n1)
	    {
		arr[k] = Left[i];
		i++;
		k++;
	    }
	 
	   						// remaining at right
	    while (j < n2)
	    {
		arr[k] = Right[j];
		j++;
		k++;
	    }
	}
	 

	void mergeSort(int arr[], int l, int r, int length)
	{
	    if (l < r)
	    {
		int m = l+(r-l)/2; //Same as (l+r)/2, but avoids overflow for large l and h
		int k=0;
		mergeSort(arr, l, m, length);
		mergeSort(arr, m+1, r, length);
		
		merge(arr, l, m, r);
		if(length<20){
		printf("\n-------------------------------------------------\n");
		for(k=0; k < length; k++){
			int q = 0;
			//printf("\n------");
			for(q = 0; q < arr[k]; q++){
				printf("*");
			}
			printf("\n");
		}}
	    }
	}

	void mergePrinter(int arr[], int length){
		int i = 0;
		if(length>20){
		printf("\n");
		for(i = 0; i < length; i++)
			printf("\t%d",arr[i]);
		printf("\n");
		}else{
			int k =0 ;		
			for(k=0; k < length; k++){
				int q = 0;
			printf("\n------");
				for(q = 0; q < arr[k]; q++){
					printf("*");
				}
				printf("\n");
			}
		}
		
	}
	void myMergeSort(){

		printf("\n Merge sort here !");
		srand(time(NULL));	
		int length = 0, i = 0;
		printf("\n Number of elements in the array: \t");
		scanf("%d",&length);
		int arr[length];
		printf("\n");
		if(checker(length, MYMAX)){
			if(length>20)
			for(i = 0; i < length; i++){
				arr[i]= ( rand() % 1000) + 1;	
			}		
			else{
			for(i = 0; i < length; i++){
				arr[i]= ( rand() % 15) + 1;	
				}
			}
			printf("\nInitial array:\n");
			mergePrinter(arr,length);		
			mergeSort(arr,0,length-1,length);
			printf("\nFinal array:\n");
			mergePrinter(arr,length);
			 
	
		}
	}
	//---------------------------------------------------------------------RandomQuickSort
	void quick_sort(int arr[], int p, int q, int length){

	   	int j;
	    	if (p < q)
	    	{
		j = partion(arr, p, q);
			if(length<=20){
			printf("\n------\n");
			int k =0 ;		
			for(k=0; k < length; k++){
				int q = 0;
				for(q = 0; q < arr[k]; q++){
					printf("*");
				}
				printf("\n");
			}
			}
		quick_sort(arr, p, j-1,length);
		quick_sort(arr, j+1, q,length);
		
	    	}
	}
	int partion(int arr[], int p, int r){

		int pivotIndex = p + rand()%(r - p + 1); //generates a random number as a pivot
		//printf("\n%d->pivot",pivotIndex);	
		int pivot;	
		int i = p - 1;
		int j;
		pivot = arr[pivotIndex];
		int temp;
		temp=arr[pivotIndex];
		arr[pivotIndex]=arr[r];
		arr[r]=temp;
		
		for (j = p; j < r; j++){
			if (arr[j] < pivot){
		       	i++;
			int temp;
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;	
			}
		}
		temp=arr[i+1];
		arr[i+1]=arr[r];
		arr[r]=temp;
		
		return(i + 1);
	}
	void myRandomizedQuickSort(){

		//printf("\n here !");
		srand(time(NULL));	
		int length = 0, i = 0;
		printf("\n Number of elements in the array: \t");
		scanf("%d",&length);
		int arr[length];
		printf("\n");
		if(checker(length, MYMAX)){
			if(length>20)
			for(i = 0; i < length; i++){
				arr[i]= ( rand() % 1000) + 1;	
			}
			else
			for(i = 0; i < length; i++){
				arr[i]= ( rand() % 15) + 1;
			}
			printf("\nInput array:\n");
			    for (i = 0; i < length; i++)
				 printf("\t%d ", arr[i]);
			printf("\n");			
			quick_sort(arr, 0, length-1,length); 
			printf("\nFinal Results:\n");
			    for (i = 0; i < length; i++)
				 printf("\t%d ", arr[i]);
			printf("\n");

		}
	}
