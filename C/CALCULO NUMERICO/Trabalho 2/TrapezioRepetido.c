#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10
#include "runExpr.h"

int main()
{
	int n;
	char funcao[100], intervalo[10];
	float h, a, b, fsoma = 0;
	float *xs, *fx;
	system("CLS");
    printf("Entre com a f(x) da Integral: ");
    scanf("%[^\n]%*c", funcao);
    
	printf("Entre com o intervalo da funcao no formato [a,b]: ");
    scanf("%[^\n]%*c", intervalo);
    
	sscanf(intervalo, " [ %f , %f ]%*c", &a, &b);

    printf("Entre com o numero de sub-Intervalos: ");
    scanf("%d%*c", &n);

    printf("    h = (b - a)/n\n");
    printf("    h = (%f - %f)/%d\n", b, a, n);
    h = (b-a)/n;
    n++;
    printf("    h = %f\n", h);

    int i;
    fx = (float*)malloc(sizeof(float)*n);
    xs = (float*)malloc(sizeof(float)*n);

    printf("    Xn = a + i*h\n", i);
    for(i = 0; i < n; i++)
    {
        printf("    X%d = %f + %d*%f\n", i, a, i, h);
        xs[i] = a + i * h;
        printf("    X%d = %f\n", i, xs[i]);
    }

    for(i = 0; i < n; i++)
    {
        fx[i] = runExpr(funcao, xs[i]);
        printf("    f(x%-d) = %f\n", i, fx[i]);
    }
    
    printf("I[a, b] %s dx = (h/2)*[f(x0) + f(x%d) + 2*( ", funcao, n-1);

    for(i = 1; i < n-1; i++)
    {
        printf(" f(x%d)", i);
        if(i+1 < n-1)    
            printf(" +");   
    }

    printf(")]\n");

    printf("I[%.4f, %.4f] %s dx = (%f/2)*[%f + %f + 2*( ", a, b, funcao, h, fx[0], fx[n-1]);
    
    for(i = 1; i < n-1; i++)
    {
        printf(" %f", fx[i]);
        
        if(i+1 < n-1)
            printf(" +");
        
        fsoma += fx[i];
    }
    printf(")]\n");

    fsoma *= 2;

    fsoma += fx[0];
    fsoma += fx[n-1];
    
    h /= 2;
    printf("I[%.4f, %.4f] %s dx = %f*[%f]\n", a, b, funcao, h, fsoma);

    float resultado = h*fsoma;
    printf("I[%.4f, %.4f] %s dx = %f\n", a, b, funcao, resultado);
    
    return 0;   
}