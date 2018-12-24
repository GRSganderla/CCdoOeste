#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10

void lerEq(double a[][MAX], double b[], int n)
{
	int i, j;

	printf("Matriz A: ");
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%lf", &a[i][j]);

	printf("Vetor b: ");
	for(i = 0; i < n; i ++)
		scanf("%lf", &b[i]);
	printf("\n\tAx = b: ");
}

double divisao(double a, double b)
{
	if(b == 0)
		return 0;
	return a/b;
}

void imprimeEq(double a[][MAX], double b[], int n)
{
	int i, j;

	printf("\n");
	for(i = 0; i < n; i++)
	{
		printf("|");
		
		for(j = 0; j < n; j++)
			printf(" %-10.6lf", a[i][j]);

		if(ceil(n/2) == i)
			printf(" | * ");
		else 
			printf(" |   ");

		printf("| %c |", 'x' + i);

		if(ceil(n/2) == i)
			printf(" = ");
		else 
			printf("   ");

		printf("| %-10.6lf |", b[i]);

		if(i < n-1)
			printf("\n");
	}
}

double* gauss(double a[][MAX], double b[], int n)
{
	int i, j, k;

	for(k = 0; k < n-1; k++)
	{
		for(i = k + 1; i < n; i++)
		{
			double m = divisao(a[i][k], a[k][k]);
			
			imprimeEq(a, b, n);
			printf(" L%d <- L%d - (%.6lf) * L%d\n", i+1, i+1, m, k+1);

			a[i][k] = 0;

			for(j = k+1; j < n; j++)
			{
				a[i][j] = a[i][j] - (m*a[k][j]);
			}

			b[i] -= m*b[k];
		}
	}

	double *xn = (double*)malloc(sizeof(double)*n);
	double s;

	for(k = n-1; k >= 0; k--)
	{
		s = 0;
		for(j = k + 1; j < n; j++)
		{
			s += (a[k][j] * xn[j]);
		}

		if(a[k][k] == 0)
			xn[k] = 0;
		
		else
			xn[k] = ((b[k] - s)/a[k][k]);
	}

	return xn;
}

void imprimeRes(double xn[], int n)
{
	int i;
	printf("\n\n");
	for(i = 0; i < n; i++)
		printf(" %c = | %-10.6lf |\n", 'x' + i, xn[i]);
}

int main()
{
	int n;
	printf("Linhas x Colunas: ");
	scanf("%d", &n);
	double a[MAX][MAX];
	double b[MAX];

	lerEq(a, b, n);
	double *xn = gauss(a, b, n);

	imprimeEq(a, b, n);
	imprimeRes(xn, n);

	return 0;
}