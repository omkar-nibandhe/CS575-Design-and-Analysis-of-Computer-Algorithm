#include <stdio.h>
#include <stdlib.h>

#define DIAGONAL 1
#define UP 2
#define LEFT 3


void*
myopen(char *argv, FILE *fp);

void
validateArguments(int argc);

void 
printerLcs(char *x, char *y, int i, int j, int **b, int **c);

int 
lcs_length(char *x, char *y, int xLen, int yLen, int **b, int **c);

int 
getLength(FILE *fp);

