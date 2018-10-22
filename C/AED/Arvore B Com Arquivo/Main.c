#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ArvoreB.h"

int main()
{	
	int opcao;

	FILE* asod = fopen("arvores.bin", "wb+");

	criaIndicesArq(asod);

	for(int i = 1; i < 10; i++)
		insere(asod, i);

	printaArvore(asod);

	//printaB(asod);

	/*ArvoreB* nova = inicializaArvore();
	nova = insere(nova, hospital[0].codigo);
	nova = insere(nova, hospital[1].codigo);
	nova = insere(nova, hospital[2].codigo);

	do{
		printf("[1] - Carregar arquivos de inicializacao\n");
		printf("[2] - Inserir Medico\n");
		printf("[3] - Alterar Medico\n");
		printf("[4] - Buscar dados de Medico\n");
		printf("[5] - Remover Medico\n");
		printf("[6] - Imprimir Cadastro\n");
		printf("[7] - Imprimir a Arvore-B\n");
		printf("[0] - Fechar\n", );
		printf("    Opcao: ");

		scanf("%d", &opcao);

		switch(opcao)
		{
			case 1:
			//em construcao
			case 2:
			//em construcao
			case 3:
			//em construcao
			case 4:
			//em construcao
			case 5:
			//em construcao
			case 6:
			//em construcao
			case 7:
				printaPorNivelB(nova);
			default:
				break;
		}

	}while(opcao);*/

	return 0;
}