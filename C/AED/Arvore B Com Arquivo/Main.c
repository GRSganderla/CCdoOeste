#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include "ArvoreB.h"

int main()
{	
	int opcao;
	char arquivo[100];

	FILE* registroArv = fopen("arvores.bin", "wb+");
	FILE* registroDados = fopen("dados.bin", "wb+");

	criaIndicesArq(registroArv);
	criaIndicesArqDat(registroDados);

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

		scanf("%d%*c", &opcao);

		switch(opcao)
		{
			case 1:
				printf("Arquivo de entrada: ");
				scanf("%[^\n]%*c", arquivo);
				lerArquivo(registroDados, registroArv, arquivo);
				break;
			case 2:
				leituraEmCMD(registroArv, registroDados);
				break;
			case 3:
			//em construcao
			case 4:
				procuraCadastro(registroArv, registroDados);
			case 5:
			//em construcao
			case 6:
				imprimeRegistro(registroArv, registroDados);
				break;
			case 7:
				printaArvore(registroArv);
				break;
			default:
				break;
		}

		getch();

	}while(opcao);

	return 0;
}