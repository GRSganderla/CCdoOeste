#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ORDEM 5

int main()
{	
	Cadastro *hospital = inicializaCadastro();
	lerCadastro(hospital);

	ArvoreB* nova = inicializaArvore();
	nova = insere(nova, hospital[0].codigo);
	//nova = insere(nova, hospital[1].codigo);
	//nova = insere(nova, hospital[2].codigo);

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
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				printaPorNivelB(nova);
			case 0:
				break;
		}

	}while(opcao);
}