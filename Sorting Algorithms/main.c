//sorting program
//use * to demonstrate graphically if input size is less than or equal to 20
#include "mysort.c"

int main(){

	int choice = 0;
	do{
	printf("\n.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n");
	printf("\n\t\tS o r t i n g    P r o g r a m.\n\n\t\t   1. Insertion Sort.\n\t\t   2. Counting Sort. \n\t\t   3. Merge Sort. \n\t\t   4. Randomized quick sort.\n\t\t   5. Exit\n\n\t Select an sort algorithm:\t ");
	scanf("%d",&choice);
	switch(choice){
		case 1:						//Insertion sort
			myInsertionSort();
			
			break;
	
		case 2:						//count sort
			myCountSort();
			
			break;

		case 3:						//merge sort
			myMergeSort();
			
			break;

		case 4:						//randomized quick sort
			myRandomizedQuickSort();
			
			break;

		case 5:						//exit
			exit(0);
			break;
	
		default:
			printf("\n\n\tInvalid choice.\n");
			break;
	
		}
	}while(choice != 5);
	printf("\n");
	return 0;
}
