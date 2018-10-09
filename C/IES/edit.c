#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "edit.h"

void mudaNome(char mudar[])
{

	printaSuperior();
	printf(":                                                                         :\n");
	printf(":                          Novo nome?                                     :\n");
	printf(":                                                                         :\n");
	printf(":                                                                         :\n");
	printf(":                        R:                                               :\n");
	printaInferior();

	gotoXY(28, 9);
	char nome[100];

	scanf("%[^\n]%*c", nome);

	strcpy(mudar, nome);
}

void mudaAva(int *a)
{
	printaSuperior();
	printf(":                                                                         :\n");
	printf(":                Nova Avaliacao:                                          :\n");
	printf(":                                                                         :\n");
	printaInferior();

	gotoXY(33, 6);
	int novo;
	
	scanf("%d%*c", &novo);
	
	if(novo >= 0 && novo <= 5)
		*a = novo;
	else
	{
		while(novo < 0 && novo > 5)
		{
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                Nova Avaliacao:                                          :\n");
			printf(":                                                                         :\n");
			printaInferior();

			gotoXY(33, 6);
			int novo;
		
			scanf("%d%*c", &novo);
		}

		*a = novo;
	}
}

void mudaAno(int *a)
{
	printaSuperior();
	printf(":                                                                         :\n");
	printf(":                      Novo Ano:                                          :\n");
	printf(":                                                                         :\n");
	printaInferior();

	gotoXY(33, 6);
	int novo;
	
	scanf("%d%*c", &novo);
	
	if(novo <= 2018)
		*a = novo;
	else
	{
		while(novo > 2018)
		{
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                      Novo Ano:                                          :\n");
			printf(":                                                                         :\n");
			printaInferior();

			gotoXY(33, 6);
			int novo;
			
			scanf("%d%*c", &novo);
		}

		*a = novo;
	}
}

void mudaDur(Duracao *dura)
{
	Duracao dur;

	printaSuperior();
	printf(":                                                                         :\n");
	printf(":                          Nova duracao:                                  :\n");
	printf(":                                                                         :\n");
	printaInferior();

	gotoXY(41, 6);
	
	scanf("%d:%d", &dur.min, &dur.seg);

	while(dur.seg >= 60)
	{
		dur.seg -= 60;
		dur.min++;
	}
	
	*dura = dur;
}

void editMusica(Musica* alvo)
{
	int opcao = 1;
	while(opcao > 0)
	{
		printaSuperior();
		printf(":                                Editar:                                  :\n");
		printf(":                                                                         :\n");
		printf(":               [1]    Titulo: %-43s:\n", alvo->tituloMus);
		printf(":               [2]    Cantor: %-43s:\n", alvo->cantor);
		printf(":               [3]     Autor: %-43s:\n", alvo->autorMus);
		printf(":               [4]       Ano: %-43d:\n", alvo->ano);
		printf(":               [5]   Duracao: %-2d:%-40d:\n", alvo->duracao.min, alvo->duracao.seg);
		printf(":               [6]    Genero: %-43s:\n", alvo->genero);
		printf(":               [7] Avaliacao: ");
		printaEstrelas2(alvo->avaliacao, 43);
		printf(":               [0]    Voltar                                             :\n");
		printf(":                                                                         :\n");
		printf(":                      Opcao:                                             :\n");
		printaInferior();

		gotoXY(31, 16);
	
		char c = getch();
		int opcao = charToNum(c);

		switch(opcao)
		{
			case 1:
				mudaNome(alvo->tituloMus);
				break;
			case 2:
				mudaNome(alvo->cantor);
				break;
			case 3:
				mudaNome(alvo->autorMus);
				break;
			case 4:
				mudaAno(&alvo->ano);
				break;
			case 5:
				mudaDur(&alvo->duracao);
				break;
			case 6:
				mudaNome(alvo->genero);
				break;
			case 7:
				mudaAva(&alvo->avaliacao);
				break;
			default:
				break;
		}
	}
	getch();
}

void editar(Playlist* lista)
{
	int i;
	char nome[100];

	printaSuperior();
	printf(":                                                                         :\n");
	printf(":          Musica a ser editada:                                          :\n");
	printf(":                                                                         :\n");
	printaInferior();

	gotoXY(33, 6);

	int achou = 0;

	scanf("%[^\n]%*c", nome);

	char *s = strupr(nome);

	for(i = 0; i < lista->quantMus; i++)
	{
		char *s2 = strupr(lista->musicas[i].tituloMus);
		if(!strcmp(s2, s))
			if(lista->musicas[i].ocupado)
			{
				achou = 1;
				editMusica(&lista->musicas[i]);
			}
	}

	if(!achou)
		printaNaoExistenteMusica();
	getch();
}

void editPlay(Playlist* lista)
{
	int opcao = 1;
	while(opcao > 0)
	{
		printaSuperior();
		printf(":                                                                         :\n");
		printf(":                             %-44s:\n", lista->tituloLista);
		printf(":                                                                         :\n");
		printf(":                       [1] - Mudar nome da Playlist                      :\n");
		printf(":                       [2] - Remover uma musica                          :\n");
		printf(":                       [3] - Adicionar uma musica                        :\n");
		printf(":                       [4] - Editar uma musica                           :\n");
		printf(":                       [0] - Voltar                                      :\n");
		printf(":                                                                         :\n");
		printf(":                       Opcao:                                            :\n");
		printaInferior();
		
		gotoXY(31, 14);
		
		char c = getch();
		int opcao = charToNum(c);

		switch(opcao)
		{
			case 1:
				mudaNome(lista->tituloLista);
				break;
			case 2:
				removeMusica(lista);
				break;
			case 3:
				adicionaMusica(lista);
				break;
			case 4:
				editar(lista);
				break;
			default:
				break;
		}

		if(opcao == 0)
			break;
	}
}