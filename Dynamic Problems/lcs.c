
#include "lcs.h"

/*
	function to get the length of the string
*/
int 
getLength(FILE *fp)
{	if(fp==NULL)
	{
		fprintf(stderr,"\nInvalind data in file.\n");
		exit(0);
	}
	int count = 0;
	while(fgetc(fp) != '\n') {
		count++;
	}
	if(count == 0){
		fprintf(stderr,"\nError reading file.\n");
		exit(0);
	}
	return count;  
	
}

/*
	function to calculate the length of
	the common subswquence.
*/

int 
lcs_length(char *x, char *y, int xLen, int yLen, int **b, int **c)
{
	int i=0,j=0;

	for (i = 0; i <= xLen; ++i)
		c[i][0] = 0;

	for (j = 0; j <= yLen; ++j)
		c[0][j] = 0;

	for (i = 1; i <= xLen; i++){
		for (j = 1; j <= yLen; j++) {
			if (x[i-1] == y[j-1]) {
				c[i][j] = c[i-1][j-1] + 1;
				b[i][j] = DIAGONAL;
			} else if (c[i-1][j] >= c[i][j-1]) {
					c[i][j] = c[i-1][j];
					b[i][j] = UP;
				} else {
					c[i][j] = c[i][j-1];
					b[i][j] = LEFT;
				}
			}
	}
	return c[xLen][yLen];
	
}

/*
	Function to print the biggest subsequence.
*/
void 
printerLcs(char *x, char *y, int i, int j, int **b, int **c)
{
	if( i < 0 || j < 0)
		return;
	if(b[i][j]==DIAGONAL){
		printerLcs(x,y,i-1,j-1,b,c);
		fprintf(stderr,"%c",x[i-1]);
	}
	else if(b[i][j]==UP)
		printerLcs(x,y,i-1,j,b,c);
	else
		printerLcs(x,y,i,j-1,b,c);
}

/*
	function to validate the number of arguments.
*/
void
validateArguments(int argc){
	if(argc != 2){
		fprintf(stderr,"\nInvalid number of arguments:\nexpected\t./lcs.out Filename.txt\n");
		exit(0);
	}
}

/*
	funtion to open the file for reading purposes.
*/
void*
myopen(char *argv,FILE *fp){
	if((fp = fopen(argv, "r")) == NULL) {
		fprintf(stderr,"\nError opening file!\n");
		exit(1);
	}
	return fp;
}

/*
		M A I N    function
*/
int 
main(int argc, char *argv[])
{
	/*
		Validate the arguments.
	*/
	validateArguments(argc);
	FILE *fp=NULL;
	fp=myopen(argv[1],fp);
	

	char *x=NULL, *y=NULL;
	int xLen=0, yLen=0;
	int i=0, j=0;
	/*
		Get lentgth of the strings in the file and rewind the file pointer.
	*/
	xLen = getLength(fp);
	yLen = getLength(fp);

	rewind(fp);

	/*
		Declare & initialize the data struture needed.
	*/
	x = malloc ((xLen+1) * sizeof(char));
		if(x == NULL){
			fprintf(stderr,"\nMalloc Failed.\n");
			exit(0);
		}
	y = malloc ((yLen+1) * sizeof(char));
		if(y == NULL){
			fprintf(stderr,"\nMalloc Failed.\n");
			exit(0);
		}
	
	if(fgets(x, xLen + 1, fp) == NULL)
		fprintf(stderr,"Error reading string in x.\n");

	if(fseek(fp, 1, SEEK_CUR)== -1){
			fprintf(stderr,"\nSeek error\n");	
			exit(0);
		}
	
	if(fgets(y, yLen + 1, fp) == NULL)
		fprintf(stderr,"Error reading string in y.\n");
	if(x == NULL || y == NULL){
		fprintf(stderr,"\nInputs not proper in %s file.\n",argv[1]);		
		exit(0);
	}
	int ** B = malloc ((xLen + 1) * sizeof(int *));
	int ** C = malloc ((xLen + 1) * sizeof(int *));

	for(i = 0; i <= xLen+1; ++i) {
		B[i] = calloc((yLen + 1) , sizeof(int));
		C[i] = calloc((yLen + 1) , sizeof(int));
	}
	/*
		calculate the length.
	*/
	int length = lcs_length(x, y, xLen, yLen, B, C);

	fprintf(stderr,"\n\tLCS\n%s and %s\n\t", x, y);
	printerLcs(x, y, xLen, yLen, B, C);
	printf(":%d\n",length);

	/*
		free the memory.
	*/
	for(i=0; i <= xLen+1;i++){
		
		free(C[i]);
	}
	free(x);
	free(y);
	
	fclose(fp);
	return 0;
}
/*
	end
*/
