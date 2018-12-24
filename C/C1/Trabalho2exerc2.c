#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef struct elementos
{	
	int numAtomico;
	char nomeElemento[100];
	double massaAtomica;
}Elemento;

int pertence(int numAtomico, Elemento elementos[], int n)
{
	int i;
	
	if(n == 0)
		printf("Carregue o Arquivo antes de buscar no Vetor\n");

	for(i = 0; i < n; i++)
	{
		if(elementos[i].numAtomico == numAtomico)
			return 1;
	}

	return 0;
}

void buscaElemento(int numAtomico, Elemento elementos[], int n)
{
	int i;

	for(i = 0; i < n; i++)
	{
		if(elementos[i].numAtomico == numAtomico)
		{
			printf("Nome do Elemento: %s\n", elementos[i].nomeElemento);
			printf("Numero Atomico: %d\n", elementos[i].numAtomico);
			printf("Massa Atomica: %lf\n", elementos[i].massaAtomica);
			return;
		}
	}

	printf("Elemento nao pertence ao arquivo\n");
}

void imprimeSequencia(Elemento elemento[], int n)
{
	int i;
	if(n == 0)
		printf("Carregue o Arquivo antes de Imprimir o Vetor de Elementos\n");

	for(i = 0; i < n; i++)
	{
		printf("-------------------------------------------------------\n");
		printf("Nome do Elemento: %s\n", elemento[i].nomeElemento);
		printf("Numero Atomico: %d\n", elemento[i].numAtomico);
		printf("Massa Atomica: %lf\n", elemento[i].massaAtomica);
		printf("-------------------------------------------------------\n");
	}
}

void ordenaSequencia(Elemento v[], int n)
{
    int i = 0,j;
    if(n == 0)
    {
    	printf("Carregue o Arquivo Antes de Ordenar\n");
    }
    Elemento temp;

    for(i = n - 1; i >= 0; i--)
    {
        for(j = 1; j <= i; j++)
            if(v[j-1].numAtomico > v[j].numAtomico)
            {
                temp = v[j-1];
                v[j-1] = v[j];
                v[j] = temp;
            }
    }
}

int carregaElemento(char* nomeArq, Elemento elementos[])
{
	int i = 0;
	FILE* arquivo = fopen(nomeArq, "r");
	if(arquivo == NULL)
	{
		printf("Arquivo Vazio\n");
		return 0;
	}

	fseek(arquivo, 0, SEEK_SET);

	while(!feof(arquivo))
	{
		fscanf(arquivo, "Nome do Elemento = %s\n", elementos[i].nomeElemento);
		fscanf(arquivo, "Numero Atomico = %d\n", &elementos[i].numAtomico);
		fscanf(arquivo, "Massa do Elemento = %lf\n", &elementos[i].massaAtomica);
		i+=1;
	}
	return i;
}

char* guardaElemento(char *nomeArq, char *nomeElemento, int numAtomico, double massaAtomica)
{
	FILE* arquivo = fopen(nomeArq, "a");
	int n;

	char *retorno = (char*)malloc(sizeof(char)*100);
	if(arquivo == NULL)
	{
		retorno = "ocorreu algum erro ao gravar/abrir o arquivo ";
		strcat(retorno, nomeArq);
		return retorno;
	}
	Elemento elementos[118];

	n = carregaElemento(nomeArq, elementos);

	if(!pertence(numAtomico, elementos, n))
	{
		fprintf(arquivo, "Nome do Elemento = %s\n", nomeElemento);
		fprintf(arquivo, "Numero Atomico = %d\n", numAtomico);
		fprintf(arquivo, "Massa do Elemento = %lf\n", massaAtomica);
		fclose(arquivo);
		strcpy(retorno, "Elemento ");
		strcat(retorno, nomeElemento);
		strcat(retorno, " foi adicionado ao arquivo ");
		strcat(retorno, nomeArq);
		return retorno;
	}
	else
	{
		strcpy(retorno, "Ja existe um elemento chamado ");
		strcat(retorno, nomeElemento);
		strcat(retorno, " no arquivo ");
		strcat(retorno, nomeArq);
		return retorno;
	}

	fclose(arquivo);		
}

int main()
{
	Elemento elementos[118];
	int numAtomico, opcao, busca, n = 0;
	double massaAtomica;
	char nomeElemento[100], nomeArq[100];

	system("CLS");
	printf("Entre com o Nome do Arquivo: ");
	scanf("%[^\n]%*c", nomeArq);
	
	do{

		system("CLS");	
		printf("[1] Guardar um Elemento\n");
		printf("[2] Carregar Elementos\n");
		printf("[3] Imprime Sequencia\n");
		printf("[4] Ordenar Sequencia\n");
		printf("[5] Busca Elemento\n");
		printf("[0] Fechar\n");
		scanf("%d%*c", &opcao);
		system("CLS");
		switch(opcao)
		{
			case 1:
				printf("Nome do Elemento: ");
				scanf("%[^\n]%*c", nomeElemento);

				printf("Numero Atomico do Elemento: ");
				scanf("%d%*c", &numAtomico);

				printf("Massa Atomica do Elemento: ");
				scanf("%lf%*c", &massaAtomica);

				char *msg = guardaElemento(nomeArq, nomeElemento, numAtomico, massaAtomica);

				printf("------------------------------------------------------------\n");
				printf("| %-32s|\n", msg);
				printf("------------------------------------------------------------\n");
				break;

			case 2:
				n = carregaElemento(nomeArq, elementos);
				break;

			case 3:
				imprimeSequencia(elementos, n);
				break;

			case 4:
				ordenaSequencia(elementos, n);
				break;

			case 5:
				printf("Numero Atomico do Elemento a ser Buscado: ");
				scanf("%d%*c", &busca);
				buscaElemento(busca, elementos, n);
				break;

			case 0:
			default:
				break;
		}
		getch();

	}while(opcao);

	return 0;
}