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
	double x0, x1, y1, y0, h, resultado, erro;
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
	scanf("%lf%*c", &x0);
	printf("Entre com o y0: ");
	scanf("%lf%*c", &y0);
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
	
	printf("| x1 =  x0     + h        |                          | y1 = y0+ %-8.4lf*f(x0, y0)    |                    |\n", h);
		
	resultado = runExprDif(funcao, x0, y0);
	
	printf("| x1 = %8.4lf + %-8.4lf |      %-20.4lf| y1 = %-9.4lf+ %-8.4lf*%-9.4lf|                    |\n",  x0, h, y0, y0, h, resultado);
	
	resultado = y0 + h*resultado;
	
	printf("| x1 = %-19.4lf |                          | y1 = %-28.4lf | ",x1 = (x0 + h), resultado);
	
	y1 = resultado;

	if(qualErro == 1 )
	{
		printf(" %-18lf|\n", erroAbs(y1, y0));
		printf("------------------------------------------------------------------------------------------------------------------\n");
		
	}
	else if(qualErro == 2)
	{
		printf(" %-18lf|\n", erroRel(y1, y0));
		printf("------------------------------------------------------------------------------------------------------------------\n");
	  	
	}
}
