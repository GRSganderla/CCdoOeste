#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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
	printf("\nF(t) = f(x)\t\tx = a -> t = -1\n");
	printf("F(t) = %s\t\tx = b -> t = 1\n", funcao);

	printf("\nI[%lf; %lf] %s dx = (%lf - %lf)/2 * I[-1; 1] F(t) dt = w1*F(t1) + w2*F(t2)\n\n",a, b, funcao, b, a);

	printf("p = 2*n -1 = 2*2 - 1 = 3\n");
	printf("F(t) = t^k\n\n");

	printf("k = {0,1,2,3}\n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("k = 0\n\tI[-1, 1] F(t)dt = I[-1; 1] t^0 dt\n\t\tI[-1; 1] 1dt = t|[-1; 1] = 1 - (-1) = 2\n");
	printf("\tw1*F(t1) = 2 -> w1*t1^0 + w2*t2^0 = 2 => w1 + w2 = 2\n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("k = 1\n\tI[-1, 1] F(t)dt = I[-1; 1] t^1 dt\n\t\tI[-1; 1] 1dt = (t^2)/2 |[-1; 1] -> (1^2)/2 - (-1^2)/2 = 0\n");
	printf("\tw1*F(t1) + w2*F(t2) = 0\n\tw1*t1^1 + w2*t2^1 = 0\n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("k = 2\n\tI[-1, 1] F(t)dt = I[-1; 1] t^2 dt\n\t\tI[-1; 1] (t^3/3) = (t^3/3)|[-1; 1] = (1^3)/3 - (-1^3)/3 = 2/3\n");
	printf("\tw1*F(t1) + w2*F(t2) = 2/3 \n\tw1*t1^2 + w2*t2^2 = 2/3 \n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("k = 3\n\tI[-1, 1] F(t)dt = I[-1; 1] t^3 dt\n\t\tI[-1; 1] 1dt = (t^2)/2 |[-1; 1] -> (1^4)/4 - (-1^4)/4 = 0\n");
	printf("\tw1*F(t1) + w2*F(t2) = 0\n\tw1*t1^3 + w2*t2^3 = 0\n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("\tw1 + w2 = 2\n");
	printf("\tw1*t1 + w2*t2 = 2\t\tw1 = w2 = 1\n");
	printf("\tw1*t1^2 + w2*t2^2 = 2\t\tt1 = -1/sqrt(3)\n");
	printf("\tw1*t1^3 + w2*t2^3 = 2\t\tt2 = 1/sqrt(3)\n");
	printf("----------------------------------------------------------------------------------------\n");

	double h = (b-a);

	printf("(%lf/2)*I[-1; 1] F(t) dt = w1*F(-1/sqrt(3)) + w2*F(-1/sqrt(3))\n", h);
	printf("(%lf/2)*I[-1; 1] F(t) dt = 1*F(-1/sqrt(3)) + 1*F(-1/sqrt(3))\n\n", h);

	printf("F(-1/sqrt(3)) = f(%lf + ((%lf - %lf)/2)*((-1/sqrt(3))+1))               |                     F(1/sqrt(3)) = f(%lf + ((%lf - %lf)/2)*((1/sqrt(3))+1))\n",a, b, a, a, b, a);

	double t1 = (a + (h/2)*((-1/sqrt(3))+1));
	double t2 = (a + (h/2)*((1/sqrt(3))+1));

	printf("F(-1/sqrt(3)) = f(%lf)                                                            |                               F(1/sqrt(3)) = f(%lf)\n", t1, t2);

	double ft1 = runExpr(funcao, t1);
	double ft2 = runExpr(funcao, t2);
	
	printf("F(-1/sqrt(3)) = %lf                                                               |                               F(1/sqrt(3)) = %lf\n", ft1, ft2);

	h = h/2;

	printf("\nI[%lf; %lf] %s dx = %lf * ( %lf + %lf) \n",a, b, funcao, h, ft1, ft2);

	double resposta = h*(ft1+ft2);

	printf("--------------------------------------------------\n");
	printf("| I[%lf; %lf] %s dx = %lf |\n", a, b, funcao, resposta);
	printf("--------------------------------------------------\n");

	system("pause");
}