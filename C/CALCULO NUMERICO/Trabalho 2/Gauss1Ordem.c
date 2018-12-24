#include<stdio.h>
#include<stdlib.h>
#include "runExpr.h"

int main()
{
	double a, b;
	char funcao[100], intervalo[20];
	system("CLS");
	printf("Entre com a Integral: ");
	scanf("%[^\n]%*c", funcao);

	printf("Entre com o intervalo da Integral no formato [a;b]: ");
	scanf("%[^\n]%*c", intervalo);
	sscanf(intervalo, " [ %lf ; %lf ]", &a, &b);

	printf("-----------------------------------\n");
	printf("|\tx = a + ((b-a)/2)*(t+1) |\n");
	printf("|\tdx = ((b-a)/2)*dt       |\n");
	printf("-----------------------------------\n");
	
	printf("\nI[a; b] f(x) dx = I[%lf; %lf] %s dx\n", a, b, funcao);
	printf("\nF(t) = f(x)\n");
	printf("F(t) = %s\n", funcao);

	printf("\nx = a -> t = -1\n");
	printf("x = b -> t = 1\n");

	printf("\nI[%lf; %lf] %s dx = (%lf - %lf)/2 * I[-1; 1] F(t) dt\n",a, b, funcao, b, a);

	printf("I[-1; 1] F(t) = w1F(t1)\n");

	printf("\np = 2*n -1 = 2*1 - 1 -> p = 1\n");
	printf("F(t) = t^k\n\n");

	printf("k = {0,1}\n\n");
	printf("------------------------------------------------------------------------------------------------------------\n");
	printf("k = 0\n\tI[-1, 1] F(t)dt = I[-1; 1] t^0 dt\n\tI[-1; 1] 1dt = t|[-1; 1] = 1 - (-1) = 2\n\n");
	printf("\tw1*F(t1) = 2 -> w1*(t1^0) = 2 => w1 = 2\n");
	printf("------------------------------------------------------------------------------------------------------------\n");
	printf("k = 1\n\tI[-1, 1] F(t)dt = I[-1; 1] t^1 dt\n\tI[-1; 1] 1dt = (t^2)/2 |[-1; 1] -> (1^2)/2 - (-1^2)/2 = 0\n\n");
	printf("\tw1*F(t1) = 0 - > w1*(t1^1) = 0 = 2*t1 = 0 => t1 = 0\n");
	printf("------------------------------------------------------------------------------------------------------------\n");

	double h = (b-a);

	printf("\n(%lf/2)*I[-1; 1] F(t) dt = 2*F(0)\n\n", h);

	printf("F(0) = f(%lf + ((%lf - %lf)/2)*(0+1))\n",a, b, a);

	double t = (a + (h/2)*(0+1));

	printf("F(0) = f(%lf)\n", t);

	double ft = runExpr(funcao, t);
	printf("F(0) = %lf\n", ft);

	h = h/2;

	printf("\nI[%lf; %lf] %s dx = %lf * 2 * %lf\n", a, b, funcao, h, ft);

	double resposta = h*2*ft;

	printf("-------------------------------------------------------------------\n");
	printf("|\tI[%lf; %lf] %s dx = %lf\t|\n", a, b, funcao, resposta);
	printf("-------------------------------------------------------------------\n");

	system("pause");
}