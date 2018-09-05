#include<stdio.h>
#include "calculo.h"
#include<stdlib.h>
#include<math.h>

float divisao(float a, float b)
{
	return (a/b);
}

void printaMatriz(float a[][MAXC], float b[MAXL], int n)
{
	int i, j;

	for(i = 0; i < n; i++)
	{
		printf("| ");
		for (j = 0; j < n; j++)
			printf("%-10.2f ", a[i][j]);
		printf("| ");

		if(i == (ceil(n/2)))
		{
			printf(" * ");
			printf(" | ");
		}
		else
			printf("    | ");
		
		printf("x%d ", i + 1);
		printf("| ");

		if(i == (ceil(n/2)))
		{
			printf(" = ");
			printf(" | ");
		}
		else
			printf("    | ");
		
		printf("%-10.2f ", b[i]);
		printf("|\n");
	}

}

void gauss(float a[][MAXC], float b[MAXL], float lu[MAXL], int n)
{
	int i, j, k, u = 0;

	for(k = 0; k <  n-1; k++)
	{
		for(i = k + 1; i < n; i++)
		{
			float m = divisao(a[i][k], a[k][k]);
			a[i][k] = 0;
			printf("%.2f\n", m);

			for(j = k + 1; j < n; j++)
			{
				a[i][j] = a[i][j] - (m * a[k][j]);
			}

			b[i] = b[i] - (m * b[k]);

			lu[u++] = m;
		}
	}
}

int leAeB(float a[][MAXL], float b[MAXL])
{
	int n, i, j;
	
	printf("Linhas x Colunas: ");
	scanf("%d%*c", &n);

	printf("Matriz: ");
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			scanf("%f%*c", &a[i][j]);
	}
	
	printf("Termos independentes: ");
	for(j = 0; j < n; j++)
		scanf("%f%*c", &b[j]);
}

float* descobreX(float a[][MAXC], float b[], int n)
{
	int i, j;
	float s, m;
	float *x = (float*)malloc(sizeof(float) * n);

	for(i = n-1; i >= 0; i--)
	{
		s = 0;
		for(j = i + 1; j < n; j++)
		{
			m = divisao(b[j], a[j][j]); 
			s += a[i][j] * m;
		}
		printf("%.2f\n", s);
	
		x[i] = ((b[i] - s)/ a[i][i]);
	}

	return x;
}