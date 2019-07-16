#include<stdio.h>
#include<stdlib.h>
#include "problemaDaMochila.h"
#include "multiplicaMatriz.h"

int main(){

	int opcao;
	do{
		system("cls");
		printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
		printf("1 - Multiplicacao de Matrizes\n");
		printf("2 - Problema da Mochila\n");
		printf("0 - Sair\n");
		printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
		printf("Opcao: ");
		scanf("%d", &opcao);

		switch(opcao){

			case 1:
				matrizes();
			break;
			case 2:
				mochila();
			break;
			case 0:
			break;
		}
		getchar();
	
	} while(opcao != 0);

	return 0;
}