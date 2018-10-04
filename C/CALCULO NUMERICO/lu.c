#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10

void imprimeA(double a[][MAX], int n)
{
	int i, j;

	printf("\n");
	for(i = 0; i < n; i++)
	{
		printf("|");
		
		for(j = 0; j < n; j++)
			printf(" %-10.6lf", a[i][j]);

		if(i < n - 1)
			printf(" |\n");
		else 
			printf(" |");
	}
}

void imprimeEq1(double a[][MAX], double b[], int n)
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

void lerEq(double a[][MAX], double b[], int n)
{
	int i, j;

	printf("Matriz A: ");
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%lf", &a[i][j]);

	printf("Vetor B: ");
	for(i = 0; i < n; i ++)
		scanf("%lf", &b[i]);
	printf("\nA = L.U:");
}

double divisao(double a, double b)
{
	return a/b;
}

void upper(double a[][MAX], double l[][MAX], int n)
{
	int i, j, k;

	for(k = 0; k < n-1; k++)
	{
		for(i = k + 1; i < n; i++)
		{
			double m = divisao(a[i][k], a[k][k]);
			
			imprimeA(a, n);
			printf(" L%d <- L%d - (%.6lf) * L%d\n", i+1, i+1, m, k+1);

			a[i][k] = 0;

			for(j = k+1; j < n; j++)
			{
				a[i][j] = a[i][j] - (m*a[k][j]);
			}

			l[i][k] = m;
		}
	}

	printf("\nUpper: ");
	imprimeA(a, n);

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{	
			if(j > i)
				l[i][j] = 0;
		}

		l[i][i] = 1.0;
	}

	printf("\n\nLower: ");
	imprimeA(l, n);
}

void imprimeY(double *y, int n)
{
	int i;
	printf("\n\ty\n");

	for(i = 0; i < n; i++)
		printf("| %-10.6lf|\n", y[i]);
}

void imprimeX(double *xn, int n)
{
	int i;
	printf("\n\tx\n");

	for(i = 0; i < n; i++)
		printf("| %-10.6lf|\n", xn[i]);
}

double* lyb(double l[][MAX], double b[], int n)
{
	double *y = (double*)malloc(sizeof(double) * n);

	int k, i, j;

	printf("\n\nL.y = b:");
	imprimeEq(l, b, n);
	
	for(k = 0; k < n; k++)
	{
		double s = 0;
		
		for(j = 0; j < k; j++)
		{
			s += l[k][j] * y[j];
		}

		y[k] = ((b[k] - s)/l[k][k]);
	}

	return y;
}

double *uxy(double a[][MAX], double y[], int n)
{
	double *xn = (double*)malloc(sizeof(double)*n);
	double s;
	int j, k;

	printf("\nU.x = y:");
	imprimeEq(a, y, n);
	for(k = n-1; k >= 0; k--)
	{
		s = 0;

		for(j = k + 1; j < n; j++)
		{
			s += (a[k][j] * xn[j]);
		}

		xn[k] = ((y[k] - s)/a[k][k]);
	}

	return xn;
}

int main()
{
	double a[MAX][MAX], b[MAX], l[MAX][MAX];
	int n;

	printf("Linhas x Colunas: ");
	scanf("%d", &n);

	lerEq(a, b, n);

	upper(a, l, n);
	
	double *y = lyb(l, b, n);

	imprimeY(y, n);

	double *xn = uxy(a, y, n);

	imprimeX(xn, n);

	return 0;
}