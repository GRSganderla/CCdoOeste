#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"runExpr.h"
#define MAX 40

int main()
{
	char funcao[100];
	double x[MAX], y[MAX], xMAX, k1[MAX], k2[MAX], k3[MAX], k4[MAX], h, resultado, erro;
	int i = 1;
	system("CLS");
	printf("y' = f(x,y)\n");
	printf("y' = ");
    scanf("%[^\n]%*c", funcao);

    printf("y(x0) = y0\n");

	printf("Entre com o maximo de X: ");
    scanf("%lf%*c", &xMAX);

	printf("Entre com o x0: ");
	scanf("%lf%*c", &x[0]);
	printf("Entre com o y0: ");
	scanf("%lf%*c", &y[0]);
	printf("Entre com o H: ");
	scanf("%lf%*c", &h);
	printf("\n");

	printf("\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|       xn+1 = xn + h     |           |           yn+1 = yn + h*k2              |  k1 = f(xn, yn) |             k2 = f(xn+h/2, yn+h/2*k1)      |        k3 = f(xn+h/2, yn+h/2*k1            |     k4 = f(xn + h, yn + h*k3)      |\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|           xn            |     yn    |                 yn+1                    |        k1       |                      k2                    |                    k3                      |                 k4                 |\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	for(i=0; x[i] < xMAX;i++)
	{
		printf("|      x%-2d= x%-2d+ h        |           | y%-2d=y%-2d+%-8lf*(1/6*(k1+2*k2+2*k3+k4))", i+1, i, i+1, i, h, i, i);
		printf("| k1 = f(x%-2d, y%-2d)| k2=f(x%-2d+(%-8lf/2), y%-2d+(%-8lf/2)*k1)| k3=f(x%-2d+(%-8lf/2), y%-2d+(%-8lf/2)*k2)| k4=f(x%-2d+%-8lf, y%-2d+%-8lf*k3)|\n", i, i, i, h, i, h, i, h, i, h, i, h, i, h);

		k1[i] = runExprDif(funcao, x[i], y[i]);
		k2[i] = runExprDif(funcao, x[i] + (h/2), y[i] + (h/2)*k1[i]);
		k3[i] = runExprDif(funcao, x[i] + (h/2), y[i] + (h/2)*k2[i]);
		k4[i] = runExprDif(funcao, x[i] + h, y[i] + h*k3[i]);
		double k = 0.1666667*( k1[i] + 2*( k2[i] + k3[i]) + k4[i]);

		printf("| x%-2d = %8lf+%-8lf | %-10lf| y%-2d = %-8lf + %-10lf*%-11lf | k1 = %-11lf| k2 = %-37lf | k3 = %-37lf | k4 = %-30lf| \n", i+1, x[i], h, y[i], i+1, y[i], h, k, k1[i], k2[i], k3[i], k4[i]);

		resultado = y[i] + h*k;

		printf("| x%-2d = %-18lf|           | y%-2d = %-33lf |                 |                                            |                                            |                                    |\n", i+1, x[i+1] = (x[i] + h), i+1, resultado);

		y[i+1] = resultado;
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	printf("\nResultado final: %lf\n\n",y[i]);
	system("pause");
	return 0;
}

