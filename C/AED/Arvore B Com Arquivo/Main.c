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

	printaPorNivelB(nova);
}