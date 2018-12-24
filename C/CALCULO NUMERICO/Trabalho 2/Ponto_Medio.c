#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"runExpr.h"
#define MAX 40

int main()
{
	char funcao[100];
	double x[MAX], y[MAX], xMAX, k1[MAX], k2[MAX], h, resultado, erro;
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
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|       xn+1 = xn + h       |           |           yn+1 = yn + h*k2            |  k1 = f(xn, yn) |             k2 = f(xn+h/2, yn+(h/2)*k1)         |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|           xn              |     yn    |                 yn+1                  |        k1       |                      k2                         |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");

	for(i=0; x[i] < xMAX;i++)
	{
		printf("|      x%-2d = x%-2d + h        |           |         y%-2d = y%-2d+ %-8lf*k2        ", i+1, i, i+1, i, h, i, i);
		printf("| k1 = f(x%-2d, y%-2d)| k2 = f(x%-2d + (%-8lf/2), y%-2d +(%-8lf/2)*k1)|\n", i, i, i, h, i, h);
		
		k1[i] = runExprDif(funcao, x[i], y[i]);
		k2[i] = runExprDif(funcao, x[i] + (h/2), y[i] + (h/2)*k1[i]);
		
		printf("| x%-2d = %8lf + %-8lf | %-10lf| y%-2d = %-8lf + %-10lf*%-9lf | k1 = %-11lf| k2 = %-42lf |\n", i+1, x[i], h, y[i], i+1, y[i], h, k2[i], k1[i], k2[i]);
		
		resultado = y[i] + h*k2[i];
		
		printf("| x%-2d = %-19lf |           | y%-2d = %-31lf |                 |                                                 | \n", i+1, x[i+1] = (x[i] + h), i+1, resultado);
		
		y[i+1] = resultado;
		printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
}
