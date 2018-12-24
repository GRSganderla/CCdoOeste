#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"arquivos.h"

int main(int argc, char const *argv[])
{
	int opcao;
	Menu* menu = criaMenu();

	if(leLinhaCMD(argv, menu->arquivoStop, menu->arquivoCaminho, argc))
	{
		menu->stopWord = abreArqCMD(menu->arquivoStop, &menu->quantStopsWord);
		menu->caminho = abreArqCMD(menu->arquivoCaminho, &menu->quantCaminho);

		arquivoInvertido(menu);

		operacoes(menu);
	}else
		printf("Arquivos inexistentes!\n");

	return 0;
}