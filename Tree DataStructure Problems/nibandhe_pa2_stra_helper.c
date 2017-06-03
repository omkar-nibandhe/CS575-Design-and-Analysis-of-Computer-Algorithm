#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
clock_t begin,end;
double timeNeeded; 
int size=0;
int padding(int num);


int padding(int num) {

	int original_num = num, lower_power = 0, i, actual_num = 1;
	if(num == 1)
		return 1;

	while(num > 1) {
		lower_power++;
		num /= 2;
	}
	for(i = 0; i < lower_power; i++) {
		actual_num *= 2;
	}
	if(actual_num == original_num){
		return original_num;
	}else{
		return actual_num * 2;
	}
}
void myinit(int a[size][size], int b[size][size], int c[size][size], int d[size][size]){
	int i=0,j=0;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++){
			a[i][j]=rand() % 21 + (-10);
			b[i][j]=rand() % 21 + (-10);
			c[i][j]=0;
			d[i][j]=0;
			}
}
void display(int a[size][size],int size){
	int i=0,j=0;
	for(i=0;i<size;i++){
		printf("\n");
		for(j=0;j<size;j++){
			printf("\t%d",a[i][j]);
		}
	}
	printf("\n");	
}
void strassen(int a[size][size], int b[size][size], int c[size][size], int newsize) {

	int p1[newsize/2][newsize/2], p2[newsize/2][newsize/2], p3[newsize/2][newsize/2], p4[newsize/2][newsize/2], p5[newsize/2][newsize/2], p6[newsize/2][newsize/2], p7[newsize/2][newsize/2];
	int t1[newsize/2][newsize/2], t2[newsize/2][newsize/2];
	int q1=0, q2=0, q3=0, q4=0, q5=0, q6=0, q7=0, i=0, j=0;

	if(newsize >= 2) { 					//give recursive calls p1
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t1[i][j] = a[i][j] + a[i + newsize / 2][j + newsize / 2];
			}
		}
	
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t2[i][j] = b[i][j] + b[i + newsize / 2][j + newsize / 2];
			}
		}
		size = newsize / 2;

		strassen(t1, t2, p1, newsize / 2);	//p2




		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t1[i][j] = a[i + newsize / 2][j] + a[i + newsize / 2][j + newsize / 2];
			}
		}

		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t2[i][j] = b[i][j];
			}
		}

		size = newsize / 2;
		strassen(t1, t2, p2, newsize / 2);	//p3




		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t1[i][j] = a[i][j];	
			}
		}

		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t2[i][j] = b[i][j + newsize / 2] - b[i + newsize / 2][j + newsize / 2];
			}	
		}

		size = newsize / 2;
		strassen(t1, t2, p3, newsize / 2);	//p4



		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {	
				t1[i][j] = a[i + newsize / 2][j + newsize / 2];
			}
		}

		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t2[i][j] = b[i + newsize / 2][j] - b[i][j];
			}

		}

		size = newsize / 2;
		strassen(t1, t2, p4, newsize / 2);	//p5



		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {	
			for(j = 0; j < newsize / 2; j++) {
				t1[i][j] = a[i][j] + a[i][j + newsize / 2];
			}	
		}

		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t2[i][j] = b[i + newsize / 2][j + newsize / 2];
			}
		}	

		size = newsize / 2;
		strassen(t1, t2, p5, newsize / 2);	//p6




		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t1[i][j] = a[i + newsize / 2][j] - a[i][j];	
				}	
		}

		size = newsize / 2;
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t2[i][j] = b[i][j] + b[i][j + newsize / 2];
			}
		}

		size = newsize / 2;
		strassen(t1, t2, p6, newsize / 2);	//p7





		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t1[i][j] = a[i][j + newsize / 2] - a[i + newsize / 2][j + newsize / 2];
			}	
		}

		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				t2[i][j] = b[i + newsize / 2][j] + b[i + newsize / 2][j + newsize / 2];
				}
		}

		size = newsize / 2;
		strassen(t1, t2, p7, newsize / 2);	//c11




		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				c[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
			}
		}

								//c12




		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				c[i][j + newsize / 2] = p3[i][j] + p5[i][j];
			}
		}

								//c21



		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				c[i + newsize / 2][j] = p2[i][j] + p4[i][j];
			}
		}

								//c22



		//--------------------------------------------------------------------------------------
		for(i = 0; i < newsize / 2; i++) {
			for(j = 0; j < newsize / 2; j++) {
				c[i + newsize / 2][j + newsize / 2] = p1[i][j] + p3[i][j] - p2[i][j] + p6[i][j];
			}
		}
	}else if(newsize == 1) {
		c[0][0] = a[0][0] * b[0][0];
		}

}

