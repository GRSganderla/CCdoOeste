#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10
#define MAXI 50

double erroAbs(double a, double b)
{
	double e = (a-b);
	
	if(e < 0)
		e *= -1;

	return e;
}

double* fazErro(double kA[], double kB[], int n)
{
	int i;
	double* erros = (double*)malloc(sizeof(double)*n);
	

	for(i = 0; i < n; i++)
		erros[i] = erroAbs(kA[i], kB[i]);

	return erros;
}

int criterioDeParada(double e[], int n, double err)
{
	int i, parada = 0;

	for(i = 0; i < n; i++)
	{
		if(e[i] < err)
		{
			if(parada > 0)
				parada--;
			else 
				parada = 0;
		}
		else 
			parada++;
	}

	return parada;
}

void lerEntrada(double eq[][MAX], double b[], int n, double xs[][MAXI], double* erro)
{
	int i, j;
	double criterio;

	printf("Matriz A: ");
	for(i =0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%lf", &eq[i][j]);

	printf("Vetor b: ");
	for(i = 0; i < n; i++)
		scanf("%lf", &b[i]);

	printf("X's iniciais: ");
	for(i = 0; i < n; i++)
		scanf("%lf", &xs[0][i]);

	printf("Criterio de parada: ");
	scanf("%lf", &criterio);

	*erro = criterio;
}

void imprimeEq(double eq[][MAX], double b[], double xs[][MAXI], int n)
{
	int i, j;

	printf("\n");
	for(i = 0; i < n; i++)
	{
		printf("| %c[k+1] = 1/%.6lf * (%.6lf", 'x' + i, eq[i][i], b[i]);
		
		for(j = 0; j < n; j++)
		{
			if(i != j)
				printf(" - (%.6lf* %c[k])", eq[i][j], 'x' + j);
		}

		printf(")|\n");
	}
	printf("\n");
}

void imprimeCabecalho(double xs[][MAXI], int n)
{
	int i;

	printf(" K\t|");
	for(i = 0; i < n; i++)
		printf(" %-10c\t|", 'x' + i);

	for(i = 0; i < n; i++)
		printf(" E%-9c\t|", 'x' + i);

	printf("\n--------|");

	for(i = 0; i < n*2; i++)
		printf("---------------|");

	printf("\n 0\t|");

	for(i = 0; i < n; i++)
		printf(" %-10.6lf\t|", xs[0][i]);

	for(i = 0; i < n; i++)
		printf(" %-10c\t|", '-', '-');
	printf("\n");
}

void gaussJacobi(double eq[][MAX], double b[], double xs[][MAXI], int n, double err)
{
	int i, j, k, parada = 1;
	double *e;

	imprimeEq(eq, b, xs, n);
	
	imprimeCabecalho(xs, n);
	
	for(k = 1; parada; k++)
	{
		printf(" %d\t|", k);
		double s = 0;
		for(i = 0; i < n; i++)
		{
			s = b[i];

			for(j = 0; j < n; j++)
			{
				if(i != j)
					s = s - (eq[i][j]*xs[k-1][j]);
			}

			xs[k][i] = (s/eq[i][i]);
			printf(" %-10.6lf\t|", xs[k][i]);
		}
		
		e = fazErro(xs[k], xs[k-1], n);

		for(i = 0; i < n; i++)
			printf(" %-10.6lf\t|", e[i]);

		parada = criterioDeParada(e, n, err);
			
		printf("\n");
	}
}

int main()
{
	int n;
	printf("Linhas X Colunas: ");
	scanf("%d", &n);

	double eq[MAX][MAX], b[MAX], xs[MAXI][MAXI], erro;

	lerEntrada(eq, b, n, xs, &erro);

	gaussJacobi(eq, b, xs, n, erro);

	return 0;
}