#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include "ArvoreB.h"

int main()
{	
	int opcao;
	char *arquivo;

	FILE* nova = fopen("arvores.bin", "wb+");

	criaIndicesArq(nova);

	for(int i = 1; i < 100; i++)
		insere(nova, i);

	do{
		system("CLS");
		printf("[1] - Carregar arquivos de inicializacao\n");
		printf("[2] - Inserir Medico\n");
		printf("[3] - Alterar Medico\n");
		printf("[4] - Buscar dados de Medico\n");
		printf("[5] - Remover Medico\n");
		printf("[6] - Imprimir Cadastro\n");
		printf("[7] - Imprimir a Arvore-B\n");
		printf("[0] - Fechar\n");
		printf("    Opcao: ");

		scanf("%d", &opcao);

		switch(opcao)
		{
			case 1:
				printf("Arquivo de entrada: ");
				//scanf("%[^\n]%*c", arquivo);
				Cadastro* medicos = lerArquivo("cadastros.txt");
				break;
			case 2:
			//em construcao
			case 3:
			//em construcao
			case 4:
			//em construcao
			case 5:
			//em construcao
			case 6:
				printaCadastro(medicos);
				break;
			case 7:
				printaArvore(nova);
				break;
			default:
				break;
		}

		getch();

	}while(opcao);

	return 0;
}