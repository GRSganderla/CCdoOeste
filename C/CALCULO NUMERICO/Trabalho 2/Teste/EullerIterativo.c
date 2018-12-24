#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"runExpr.h"
#define MAX 40

double erroAbs(double y1, double y2)
{
	double e = (y1-y2);

	if(e < 0)
		e *= -1;

	return e;
}

double erroRel(double y1, double y2)
{
	double e = (y1-y2);

	if(e < 0)
		e *= -1;

	return (e/y2);
}

int main()
{
	char funcao[100];
	double x[MAX], y[MAX], h, resultado, erro;
	int i = 1, qualErro;
	system("CLS");
	printf("y' = f(x,y)\n");
	printf("y' = ");
    scanf("%[^\n]%*c", funcao);

    printf("y(x0) = y0\n");

	printf("Escolha o Erro: \n"
		   "[1] Absoluto.\n"
		   "[2] Relativo.\n"
		   "Escolha: ");
    scanf("%d%*c", &qualErro);

    printf("Entre com o Erro: ");
    scanf("%lf%*c", &erro);

	printf("Entre com o x0: ");
	scanf("%lf%*c", &x[0]);
	printf("Entre com o y0: ");
	scanf("%lf%*c", &y[0]);
	printf("Entre com o H: ");
	scanf("%lf%*c", &h);
	printf("\n");

	printf("\n");

	printf("-----------------------------------------------------------------------------------------------------------------\n");
	printf("|       xn+1 = xn + h       |                          |           yn+1 = yn + h*k2         |");

	if(qualErro == 1)
		printf("  erro = yn+1 - yn  |\n");
	else
		printf(" erro=(yn+1 - yn)/yn|\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	printf("|            xn             |            yn            |                  yn+1              |       erro         |\n");
	printf("------------------------------------------------------------------------------------------------------------------\n");
	for(i=0; ;i++)
	{
		printf("| x%-2d =  x%-2d     + h        |                          | y%-2d = y%-2d+ %-8.4lf*f(x%-2d, y%-2d)    |                    |\n", i+1, i, i+1, i, h, i, i);

		resultado = runExprDif(funcao, x[i], y[i]);

		printf("| x%-2d = %8.4lf + %-8.4lf |      %-20.4lf| y%-2d = %-9.4lf+ %-8.4lf*%-9.4lf|                    |\n", i+1, x[i], h, y[i], i+1, y[i], h, resultado);

		resultado = y[i] + h*resultado;

		printf("| x%-2d = %-19.4lf |                          | y%-2d = %-28.4lf | ", i+1, x[i+1] = (x[i] + h), i+1, resultado);

		y[i+1] = resultado;

		if(qualErro == 1 )
		{
			printf(" %-18lf|\n", erroAbs(y[i+1], y[i]));
			printf("------------------------------------------------------------------------------------------------------------------\n");
			if(erro > erroAbs(y[i+1], y[i]))
				break;
		}
		else if(qualErro == 2)
		{
			printf(" %-18lf|\n", erroRel(y[i+1], y[i]));
			printf("------------------------------------------------------------------------------------------------------------------\n");
		  	if(erro > erroRel(y[i+1], y[i]))
				break;
		}
	}

	printf("\nResultado final: %lf\n\n",y[i+1]);

    system("pause");
	return 0;
}
