
/*

11 - Quadrant   
12 - Quadrant
21 - Quadrant
22 - Quadrant


*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>

int counter = 10;
int  missing_x = 0, missing_y = 0;
void display_matrix(int size, int array[][size]){
	int i = 0;
	int j = 0;
	printf("\n");
	for(i=0;i < size;i++){
		for(j=0; j < size; j++){
			 {
				printf("%4d", array[i][j]);
			}
		}
		printf("\n");
	}
}

void tromino_algo(int x_min, int y_min, int x_max, int y_max, int missing_x, int missing_y, int size,int new_size, int myboard[][new_size]){
	//printf("\n\nx_min : %d, y_min : %d, x_max : %d, y_max : %d",x_min, y_min, x_max, y_max);
	//printf("\nmissing_xs : %d, missing_ys : %d", missing_x, missing_y);
	if(size == 2){
		if(x_min == missing_x) {
			if(y_min == missing_y) {
				myboard[x_min][y_min + 1] = counter;
				myboard[x_min + 1][y_min] = counter;
				myboard[x_min + 1][y_min + 1] = counter;
			} else {
				myboard[x_min][y_min] = counter;
				myboard[x_min + 1][y_min] = counter;
				myboard[x_min + 1][y_min + 1] = counter;
			}
		}else {
			if(y_min == missing_y) {
				myboard[x_min][y_min] = counter;
				myboard[x_min][y_min + 1] = counter;
				myboard[x_min + 1][y_min + 1] = counter;
			} else {
				myboard[x_min][y_min] = counter;
				myboard[x_min][y_min + 1] = counter;
				myboard[x_min + 1][y_min] = counter;
			}
		}
		counter++;
		
		return;
	}	
	
	int x_center = 0, y_center = 0, x11_missing = 0, y11_missing = 0, x12_missing = 0, y12_missing = 0, x21_missing = 0, y21_missing = 0, x22_missing = 0, y22_missing = 0;
	x_center = x_min + (x_max - x_min) / 2;
	y_center = y_min + (y_max - y_min) / 2;

	//printf("\n--->x_center : %d",x_center);
	//printf("---> y_center : %d",y_center);
	
	if(missing_x < x_center){
		x21_missing = x_center;
		y21_missing = y_center - 1;
		x22_missing = x_center;
		y22_missing = y_center;
		//printf("\n--->x_center : %d",x_center);
		//printf("---> y_center : %d",y_center);
		myboard[x21_missing][y21_missing] = counter;
		myboard[x22_missing][y22_missing] = counter;
		if(missing_y < y_center){
			//printf("\n--->x_center : %d",x_center);
			//printf("---> y_center : %d",y_center);
			x11_missing = missing_x;
			y11_missing = missing_y;
			x12_missing = x_center - 1;
			y12_missing = y_center;
			myboard[x12_missing][y12_missing] = counter;
		}else {
			x12_missing = missing_x;
			y12_missing = missing_y;
			x11_missing = x_center - 1;
			y11_missing = y_center - 1;
			myboard[x11_missing][y11_missing] = counter;
		}
	}else {
		//printf("\n--->x_center : %d",x_center);
		//printf("---> y_center : %d",y_center);
		x11_missing = x_center - 1;
		y11_missing = y_center - 1;
		x12_missing = x_center - 1;
		y12_missing = y_center;
		myboard[x11_missing][y11_missing] = counter;
		myboard[x12_missing][y12_missing] = counter;
		if(missing_y < y_center){
			//printf("\n--->x_center : %d",x_center);
			//printf("---> y_center : %d",y_center);
			x21_missing = missing_x;
			y21_missing = missing_y;
			x22_missing = x_center;
			y22_missing = y_center;
			myboard[x22_missing][y22_missing] = counter;
		}else {
			//printf("\n--->x_center : %d",x_center);
			//printf("---> y_center : %d",y_center);
			x22_missing = missing_x;
			y22_missing = missing_y;
			x21_missing = x_center;
			y21_missing = y_center - 1;
			myboard[x21_missing][y21_missing] = counter;
		}
	}
	counter++;
	//printf("\n--->x_center : %d",x_center);
	//printf("---> y_center : %d",y_center);
	tromino_algo(x_min, y_min, x_min + (x_max-x_min)/2, y_min + (y_max-y_min)/2, x11_missing, y11_missing, size / 2, new_size, myboard);
	tromino_algo(x_min, y_center, x_min + (x_max-x_min)/2, y_max, x12_missing, y12_missing, size / 2, new_size, myboard);
	tromino_algo(x_center, y_min, x_max, y_min + (y_max-y_min)/2, x21_missing, y21_missing, size/2, new_size, myboard);
	tromino_algo(x_center, y_center, x_max, y_max, x22_missing, y22_missing, size/2, new_size, myboard);
}


int main(int argc, char *argv[])
{

	if(argc > 2){

	}
	srand(time(NULL));
	int k = 0, size = 0;
	int board=0;
	printf("\n Enter k :\t");
	scanf("%d",&board);
	if(board>0) {
		size = board;
		
		int myboard[size][size];
		// generate random co-ordinates as co-ordinates of a hole.
		missing_x = rand() % board;
		missing_y = rand() % board;
		
		myboard[missing_x][missing_y] = 0;
		tromino_algo(0, 0, size, size, missing_x, missing_y, size, size, myboard);
		printf("\n Tromino Tiling:\n");
		display_matrix(size, myboard);
	}
	printf("\n\n");
	return 0;
}


