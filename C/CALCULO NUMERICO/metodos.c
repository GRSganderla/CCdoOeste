#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10
#define exp 2.718282

struct pilhaFloat
{
    int topo;
    float valor[MAX];
}pilhaNum;

struct pilhaChar
{
    int topo;
    char valor[MAX];
}pilhaCarac;

double fazConta(float valor, char operacao, float valor2)
{
    if(operacao == '+')
        return valor + valor2;
    if(operacao == '-')
        return valor - valor2;
    if(operacao == '*')
        return  valor * valor2;
    if(operacao == '/')
        return valor / valor2;
    if(operacao == '^')
    	return pow(valor, valor2);
}

float processaExpre(char funcao[], float x)
{
    int i;
    float valor;
    float valor2;
    char operacao;

    for ( i= 0; funcao[i] != '\0'; i++)
    {
    	if (funcao[i] == '+' || funcao[i] == '-' || funcao[i] == '*' || funcao[i] == '/' || funcao[i] == '^')
        {
            pilhaCarac.valor[pilhaCarac.topo++] = funcao[i];
        }
        else if (funcao[i] >= '0' && funcao[i] <= '9')
        {
           	sscanf(funcao+i, "%f", &valor);
            pilhaNum.valor[pilhaNum.topo++] = valor; 

            while (funcao[i+1] == '.' || (funcao[i+1] >= '0' && funcao[i+1] <= '9'))
            {	
                i++;
            }
        }
        else if(funcao[i] == 'x')
        {
        	pilhaNum.valor[pilhaNum.topo++] = x;
        }
        else if(funcao[i] == 'e')
        {
        	pilhaNum.valor[pilhaNum.topo++] = exp;
        }
        else if(funcao[i] == 'l' && funcao[i+1] == 'o' && funcao[i+2] == 'g')
        {
        	pilhaCarac.valor[pilhaCarac.topo++] = 'l'; 
        	i+=3; 
        }
        else if (funcao[i] == ')')
        {
            operacao = pilhaCarac.valor[--(pilhaCarac.topo)];
        	valor2 = pilhaNum.valor[--(pilhaNum.topo)];
        	valor = pilhaNum.valor[--(pilhaNum.topo)];    
        	pilhaNum.valor[pilhaNum.topo++] = fazConta (valor, operacao, valor2);
        }
    }
    return pilhaNum.valor[pilhaNum.topo - 1];
}

int main()
{
	int n;
	char funcao[100], intervalo[10];
	float h, a, b, fmeio = 0;
	float *xs, *fx;
	printf("Entre com a f(x) da Integral: ");
	scanf("%[^\n]%*c", funcao);
	printf("Entre com o intervalo da funcao no formato [a,b]: ");
	scanf("%[^\n]%*c", intervalo);
	sscanf(intervalo, " [ %f , %f ]%*c", &a, &b);

	h = b-a;

	printf("%f\n", h);

	float integral = (h/2);
	printf("H = %f\n",integral);
	float fa = processaExpre(funcao, a);
	printf("fa = %f\n", fa);
	float fb = processaExpre(funcao, b);
	printf("fb = %f\n", fb);
	float fsoma = fa + fb;

	integral *= fsoma;

	printf("Integral = %f\n", integral);
	
	/*scanf("%d%*c", &n);
	xs = (float*)malloc(sizeof(float)*n);
	fx = (float*)malloc(sizeof(float)*n);

	
	float h = (b-a)/n;

	for(int i = 0; i < n; i++)
	{
		x[i] = a + (i*h);
		fx[i] = processaExpre(funcao);
	}

	for(int j = 1; j < n-1; j++)
		fmeio += 2*fx[i];

	float integral = (h/2)*(fx[0] + fx[n-1] + fmeio);*/
}