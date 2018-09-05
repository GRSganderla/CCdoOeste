#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "calculo.h"
#define MAXL 100
#define MAXC 100

int main()
{
	float a[MAXL][MAXC], b[MAXL], lu[MAXL];
	int n, i, j;
	
	n = leAeB(a, b);
	
	gauss(a, b, lu, n);
	
	printaMatriz(a, b, n);

	float *xn = descobreX(a, b, n);

	for (i = 0; i < n; i++)
	{
		printf("x%d = | ", i + 1);
		printf("%-8.2f ", xn[i]);
		printf("|\n");
	}
}