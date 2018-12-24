#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int converte(char s[])
{
	int i = 0, tam = 0;
	int numero[50], resultado = 0, positivo = 1;

	while(s[i] != '\0')
	{
		if(s[i] == '-' && (s[i+1] >= '0' && s[i+1] <= '9'))
		{
			positivo = 0;
		}
		if(s[i] >= '0' && s[i] <= '9')
		{
			numero[tam] = s[i] - '0';
			tam++;
		}
		i++;
	}

	i = 0;
	tam--;
	while(tam >= 0)
	{
		int dez = pow(10, tam);
		resultado += dez * numero[i++];
		tam -= 1;
	}

	if(!positivo)
		resultado *= -1;

	return resultado;
}

int main()
{
	char s[100];
	int resultado;

	printf("Entre com a String: ");
	scanf("%[^\n]%*c", s);

	resultado = converte(s);
	printf("%d\n", resultado);

	return 0;
}