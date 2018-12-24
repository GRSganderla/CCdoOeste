#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10
#include "runExpr.h"

int main()
{
	int n;
	char funcao[100], intervalo[10];
	float h, a, b, fmeio = 0;
	float *xs, *fx;
	system("CLS");
    printf("Entre com a f(x) da Integral: ");
    scanf("%[^\n]%*c", funcao);

	printf("Entre com o intervalo da funcao no formato [a,b]: ");
    scanf("%[^\n]%*c", intervalo);

	sscanf(intervalo, " [ %f , %f ]%*c", &a, &b);

    printf("x0 = a\n");
    printf("x0 = %f\n", a);
    printf("x1 = b\n");
    printf("x1 = %f\n", b);

    fx = (float*)malloc(sizeof(float)*2);

    fx[0] = runExpr(funcao, a);
	fx[1] = runExpr(funcao, b);

    printf("f(x0) = %f\n", fx[0]);
    printf("f(x1) = %f\n", fx[1]);

    printf("h = b - a\n");
    printf("h = %f - %f\n", b, a);
    h = b-a;
    printf("h = %f\n", h);

    printf("I[%f, %f] %s dx = (h/2)*[f(x0) + f(x1)]\n", a, b, funcao);

    printf("I[%f, %f] %s dx = (%f/2)*[%f + %f]\n", a, b, funcao, h, fx[0], fx[1]);
    float fsoma = fx[0] + fx[1];

    h /= 2;
    printf("I[%f, %f] %s dx = %f*[%f]\n", a, b, funcao, h, fsoma);

    float resultado = h*fsoma;
    printf("I[%f, %f] %s dx = %f\n", a, b, funcao, resultado);

   system("pause");
    return 0;
}
