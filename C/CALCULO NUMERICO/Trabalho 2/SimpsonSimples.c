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

    printf("h = (b - a)/ 2\n");
    printf("h = (%f - %f)/2\n", b, a);
    h = (b-a)/2;
    printf("h = %f\n", h);

    fx = (float*)malloc(sizeof(float)*3);
    xs = (float*)malloc(sizeof(float)*3);
    
    printf("x0 = a\n");
    xs[0] = a;
    printf("x0 = %f\n", xs[0]);
    printf("x1 = a + h\n");
    printf("x1 = %f + %f\n", a, h);
    xs[1] = a + h;
    printf("x1 = %f\n", xs[1]);
    printf("x2 = a + 2*h\n");
    printf("x2 = %f + 2*%f\n", a, h);
    xs[2] = a + 2*h;
    printf("x2 = %f\n", xs[2]);
    
    fx[0] = runExpr(funcao, xs[0]);
    fx[1] = runExpr(funcao, xs[1]);
    fx[2] = runExpr(funcao, xs[2]);
    
    printf("f(x0) = %f\n", fx[0]);
    printf("f(x1) = %f\n", fx[1]);
    printf("f(x2) = %f\n", fx[2]);

    printf("I[%f, %f] %s dx = (h/3)*[f(x0) + 4*f(x1) + f(x2)]\n", a, b, funcao);

    printf("I[%f, %f] %s dx = (%f/3)*[%f + 4*%f +  %f]\n", a, b, funcao, h, fx[0], fx[1], fx[2]);
    float fsoma = fx[0] + (4* fx[1]) + fx[2];
    
    h /= 3;
    printf("I[%f, %f] %s dx = %f*[%f]\n", a, b, funcao, h, fsoma);

    float resultado = h*fsoma;
    printf("I[%f, %f] %s dx = %f\n", a, b, funcao, resultado);
    
    return 0;   
}