#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10

void lerEq(double a[][MAX], double b[], int n)
{
	int i, j;

	printf("Digite os valores da matriz A: ");
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%lf", &a[i][j]);

	printf("Digite os valores do vetor b: ");
	for(i = 0; i < n; i ++)
		scanf("%lf", &b[i]);
}

void imprimeMat(double m[], int n)
{
	int i, j;

	printf("\n");
	for(i = 0; i < n; i++)
	{
		printf("| %-10.6lf|\n", m[i]);
	}
}

void imprimeGs(double g[][MAX], double gt[][MAX], int n)
{
	int i, j;

	printf("\nG:\n");
	for(i = 0; i < n; i++)
	{	
		printf("|");
		for(j = 0; j < n; j++)
			printf(" %-10.6lf ", g[i][j]);
		printf("|\t\n");
	}

	printf("\nGT: \n");
	for(i = 0; i < n; i++)
	{
		printf("|");
		for(j = 0; j < n; j++)
			printf(" %-10.6lf ", gt[i][j]);
		printf("|");
		printf("\n");
	}
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

		printf("\n");
	}
}

void fazG(double a[][MAX], double g[][MAX], double gt[][MAX], int n)
{
	int i, k, j;

	for(k = 0; k < n; k++)
	{
		for(i = 0; i < n; i++)
		{
			double s = 0;

			if(i == 0 && k == 0)
			{
				g[k][k] = sqrt(a[k][k]);
				gt[i][i] = sqrt(a[k][k]);
			}
			else if(k == i)
			{
				s = a[k][k];
				for(j = 0 ; j < k; j++)
				{
					s -= pow(g[k][j], 2);
				}
			
				g[k][k] = sqrt(s);
				gt[i][i] = sqrt(s);
			}
			else if(i == 0)
			{
				g[k][i] = a[k][i]/g[i][i];
				gt[i][k] = a[k][i]/g[i][i];
			}
			else if(i < k && i > 0 && i != k) 
			{
				double m = a[k][i];

				for(j = 0; j < i; j++)
				{
					m = m - (g[k][j]*g[i][j]);
				}

				g[k][i] = (m)/g[i][i];
				gt[i][k] = (m)/g[i][i];
			}
			if(i > k)
			{
				g[k][i] = 0;
				gt[i][k] = 0;
			}
		}
	}
}

double* gyb(double g[][MAX], double b[], int n)
{
	double *y = (double*)malloc(sizeof(double) * n);

	int k, i, j;

	printf("\n\nG.y = b:");
	imprimeEq(g, b, n);
	
	for(k = 0; k < n; k++)
	{
		double s = 0;
		
		for(j = 0; j < k; j++)
		{
			s += g[k][j] * y[j];
		}

		y[k] = ((b[k] - s)/g[k][k]);
	}

	return y;
}

double *gtxY(double gt[][MAX], double y[], int n)
{
	double *xn = (double*)malloc(sizeof(double)*n);
	double s;
	int j, k;

	printf("\nGT.x = y:");
	imprimeEq(gt, y, n);
	for(k = n-1; k >= 0; k--)
	{
		s = 0;

		for(j = k + 1; j < n; j++)
		{
			s += (gt[k][j] * xn[j]);
		}

		xn[k] = ((y[k] - s)/gt[k][k]);
	}

	return xn;
}

int ehSimetricaEpositiva(double a[][MAX], int n)
{
	int i,j;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			if(a[i][j] != a[j][i])
				return 1;

		if(a[i][i] < 0)
			return 1;
	}

	return 0;
}

int main()
{
	double a[MAX][MAX], b[MAX], g[MAX][MAX], gt[MAX][MAX];
	int n;

	printf("Digite a dimensao da matriz quadrada (linhas x colunas): ");
	scanf("%d", &n);

	lerEq(a, b, n);
	if(!ehSimetrica(a,n))
	{
		printf("\n\tA = G.GT:");
		imprimeEq(a, b, n);
	
		fazG(a, g, gt, n);
		imprimeGs(g, gt, n);
		double *y = gyb(g, b, n);
		printf("\ty:");
		imprimeMat(y, n);
		double *x = gtxY(gt, y, n);
		printf("\tx:");
		imprimeMat(x, n);
	}else
		printf("Matriz nao simetrica ou diagonalmente negativa!!\n");

	return 0;
}