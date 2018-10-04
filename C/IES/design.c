#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<Windows.h>
#include "design.h"
float versao = 2.0;

int charToNum(char c)
{
	if(isdigit(c))
		return (c - '0');
	return -1;
}

void gotoXY(int x, int y){
	
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD posicao;
	
	posicao.X = x;
	posicao.Y = y;
	
	SetConsoleCursorPosition(out, posicao);
}

void printaSuperior()
{
	system("CLS");
	printf(" _________________________________________________________________________\n");
	printf("|                                                                         |\n");
	printf("|                                  Ares                    Versao: %.2f   |\n", versao);
	printf("|_________________________________________________________________________|\n");
	printf(". .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .\n");
}

void printaNaoEncontrouA()
{
	printaSuperior2();
	printf(". .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .\n");
	printf(":                                               _______                                                 :\n");
	printf(":                                              |  ___  |                                                :\n");
	printf(":                                              | (*^*) |                                                :\n");
	printf(":                                              |(| @ |)|                                                :\n");
	printf(":                                              |_______|                                                :\n");
	printf(":                                                                                                       :\n");
	printf(":                                        Autor nao existente :(                                         :\n");
	printf(":                                                                                                       :\n");
	printaInferior2();
}

void printaNaoEncontrouG()
{
	printaSuperior2();
	printf(". .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .\n");
	printf(":                                               _______                                                 :\n");
	printf(":                                              |  ___  |                                                :\n");
	printf(":                                              | (*^*) |                                                :\n");
	printf(":                                              |(| @ |)|                                                :\n");
	printf(":                                              |_______|                                                :\n");
	printf(":                                                                                                       :\n");
	printf(":                                       Genero nao existente :(                                         :\n");
	printf(":                                                                                                       :\n");
	printaInferior2();
}

void printaInferior()
{
	printf(": .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. :\n");
	printf(" _________________________________________________________________________\n");
	printf("|                                                                         |\n");
	printf("|                                          Software de Engenheiro, 2018   |\n");
	printf("|_________________________________________________________________________|\n");
}

void printaSuperior2()
{
	system("CLS");
	printf(" _______________________________________________________________________________________________________\n");
	printf("|                                                                                                       |\n");
	printf("|                                              Ares                                      Versao: %.2f   |\n", versao);
	printf("|_______________________________________________________________________________________________________|\n");
}

void printaInferior2()
{
	printf(": .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. :\n");
	printf(" _______________________________________________________________________________________________________\n");
	printf("|                                                                                                       |\n");
	printf("|                                                                        Software de Engenheiro, 2018   |\n");
	printf("|_______________________________________________________________________________________________________|\n");
}

void printaEstrelas(int avaliacao)
{
	int i = 10 - avaliacao;

	while(avaliacao)
	{
		printf("*");
		avaliacao--;
	}

	while(i)
	{
		printf(" ");
		i--;
	}
	printf(":\n");
}

void printaEstrelas2(int avaliacao)
{
	int i = 43 - avaliacao;

	while(avaliacao)
	{
		printf("*");
		avaliacao--;
	}

	while(i)
	{
		printf(" ");
		i--;
	}
	printf(":\n");
}

void consulList(Playlist play){

	int i, opcao, j = 0;;

	do{
	printaSuperior();
	printf(":                                                                         :\n");
	printf(":                           Escolha uma opcao:                            :\n");
	printf(":                                                                         :\n");
	printf(":                    [1] - Consultar a capa da playlist                   :\n");
	printf(":                    [2] - Consultar a capa e a playlist                  :\n");
	printf(":                    [3] - Filtrar por autor                              :\n");
	printf(":                    [4] - Filtrar por genero                             :\n");
	printf(":                    [0] - Voltar                                         :\n");
	printf(":                                                                         :\n");
	printf(":                        Opcao:                                           :\n");
	printaInferior();
	
	gotoXY(32, 14);
	
	char c = getch();
	int opcao = charToNum(c);

	if(opcao == 1){
		
		printaSuperior2();
		printf(". .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .\n");
		printf(":                                                                                                       :\n");
		printf(":  Playlist: %-91s:\n", play.tituloLista);
		printf(":  _______                                                                                              :\n");
		printf(": |  ___  |                                                                                             :\n");
		printf(": | (*-*)/|  Proprietario: %-77s:\n", play.proprietario);
		printf(": |(|   | |  N. de musicas: %-4d                                                                        :\n", play.quantMus);
		printf(": |_______|  Duracao total: %2d:%-73d:\n", play.duracaoTotal.min, play.duracaoTotal.seg);
		printf(":                                                                                                       :\n");
		printaInferior2();
	}

	if(opcao == 2){
		
		printaSuperior2();
		printf(". .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .\n");
		printf(":                                                                                                       :\n");
		printf(":  Playlist: %-91s:\n", play.tituloLista);
		printf(":  _______                                                                                              :\n");
		printf(": |   _   |                                                                                             :\n");
		printf(": |  |_|  |                                                                                             :\n");
		printf(": | (*-*) |  Proprietario: %-77s:\n", play.proprietario);
		printf(": |(|  /| |  N. de musicas: %-4d                                                                        :\n", play.quantMus);
		printf(": |_______|  Duracao total: %2d:%-73d:\n", play.duracaoTotal.min, play.duracaoTotal.seg);
		printf(":                                                                                                       :\n");
		printf(": Musicas:                                                                                              :\n");
		printf(": Nome                   Autor                Cantor               Genero      Ano   Duracao  Avaliacao :\n");
	
		for(i=0; i< play.quantMus+1; i++)
		{
			if(play.musicas[i].ocupado)
			{

				printf(": %-23s", play.musicas[i].tituloMus);
				
				printf("%-21s", play.musicas[i].autorMus);		
				
				printf("%-21s", play.musicas[i].cantor);	
				
				printf("%-12s", play.musicas[i].genero);	

				printf("%-5d ", play.musicas[i].ano);

				if(play.musicas[i].duracao.min < 10)
				{
					if(play.musicas[i].duracao.seg < 10)
						printf("0%-2d:0%-3d", play.musicas[i].duracao.min, play.musicas[i].duracao.seg);
					else 
						printf("0%-2d:%-4d", play.musicas[i].duracao.min, play.musicas[i].duracao.seg);
				}
				else 
					printf("%-3d:%-6d", play.musicas[i].duracao.min, play.musicas[i].duracao.seg);
				
				printaEstrelas(play.musicas[i].avaliacao);
			}	
		}
		printaInferior2();
	}
	
	if(opcao == 3)
	{
		
		char nomeAutor[100];
		
		printaSuperior();
		printf(":                                                                         :\n");
		printf(":                       Entre com o autor da musica                       :\n");
		printf(":                                                                         :\n");
		printf(":                                                                         :\n");
		printf(":                       Autor:                                            :\n");
		printaInferior();
		
		gotoXY(31, 9);
		
		scanf("%[^\n]%*c", nomeAutor);
		
		printaSuperior2();
		printf(". .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .\n");
		printf(":  _______                                                                                              :\n");
		printf(": |  ___  |                                                                                             :\n");
		printf(": | (*-*)/|                                                                                             :\n");
		printf(": |(| $ | |                                                                                             :\n");
		printf(": |_______|  Autor: %-84s:\n", nomeAutor);
		printf(":                                                                                                       :\n");
		printf(": Musicas:                                                                                              :\n");
		printf(": Nome                           Cantor                Genero        Ano      Duracao         Avaliacao :\n");

		int i=0, j = 0, existe = 0;
		
		for(; j < MAX; j++)
		{
			if(!strcmp(play.musicas[i].autorMus, nomeAutor))
				existe = 1;	
		}

		if(existe)
		{
			i = 0;
			while(i < MAX)
			{ 
				if(!strcmp(play.musicas[i].autorMus, nomeAutor))
				{ 
					if(play.musicas[i].ocupado)
					{
						printf(": %-31s", play.musicas[i].tituloMus);

						printf("%-22s", play.musicas[i].cantor);	
						
						printf("%-14s", play.musicas[i].genero);

						printf("%-9d", play.musicas[i].ano);
						
						if(play.musicas[i].duracao.min < 10)
						{
							if(play.musicas[i].duracao.seg < 10)
								printf("0%2d:0%-11d", play.musicas[i].duracao.min, play.musicas[i].duracao.seg);
							else 
								printf("0%2d:%-11d", play.musicas[i].duracao.min, play.musicas[i].duracao.seg);
						}
						else 
							printf("%-3d:%-13d", play.musicas[i].duracao.min, play.musicas[i].duracao.seg);
						
						printaEstrelas(play.musicas[i].avaliacao);
					}	
				}
				i++;
			}
			printaInferior2();
		}
		else
		{
			printaNaoEncontrouA();
		}
	}

	if(opcao == 4){

		char nomeAutor[100];
	  	
		printaSuperior();
		printf(":                                                                         :\n");
		printf(":                       Entre com o genero da musica                      :\n");
		printf(":                                                                         :\n");
		printf(":                                                                         :\n");
		printf(":                       Genero:                                           :\n");
		printaInferior();
		
		gotoXY(32, 9);
		
		scanf("%[^\n]%*c", nomeAutor);
		
		printaSuperior2();
		printf(". .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .\n");
		printf(":  _______                                                                                              :\n");
		printf(": |  ___  |                                                                                             :\n");
		printf(": | (*-*) |                                                                                             :\n");
		printf(": |(| @/| |                                                                                             :\n");
		printf(": |_______|  Genero: %-83s:\n", nomeAutor);
		printf(":                                                                                                       :\n");
		printf(": Musicas:                                                                                              :\n");
		printf(": Nome                       Cantor                 Autor          Ano        Duracao         Avaliacao :\n");
		
		int i=0, existe = 0, j = 0;
		
		for(; j < MAX; j++)
		{
			if(!strcmp(play.musicas[i].genero, nomeAutor))
				existe = 1;
		}

		if(existe)
		{
			i = 0;
			while( i < MAX)
			{ 
				if(!strcmp(play.musicas[i].genero, nomeAutor))
				{ 
					if(play.musicas[i].ocupado)
					{
						printf(": %-27s", play.musicas[i].tituloMus);

						printf("%-23s", play.musicas[i].cantor);	
						
						printf("%-15s", play.musicas[i].autorMus);

						printf("%-11d", play.musicas[i].ano);
						
						if(play.musicas[i].duracao.min < 10)
						{
							if(play.musicas[i].duracao.seg < 10)
								printf("0%d:0%-12d", play.musicas[i].duracao.min, play.musicas[i].duracao.seg);
							else 
								printf("0%d:%-13d", play.musicas[i].duracao.min, play.musicas[i].duracao.seg);
						}
						else 
							printf("%2d:%-13d", play.musicas[i].duracao.min, play.musicas[i].duracao.seg);
						
						printaEstrelas(play.musicas[i].avaliacao);
					}
				}
				i++;
			}
			printaInferior2();
		}
		else
		{
			printaNaoEncontrouG();
		}

	}

	if(opcao == 0)
		break;

	getch();

	}while(opcao);
}

void printaNaoExistente(char *s)
{
	printaSuperior2();
	printf(". .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .\n");
	printf(":                                               _______                                                 :\n");
	printf(":                                              |  ___  |                                                :\n");
	printf(":                                              | (*^*) |                                                :\n");
	printf(":                                              |(| @ |)|                                                :\n");
	printf(":                                              |_______|                                                :\n");
	printf(":                                                                                                       :\n");
	printf(":                                              %-7s nao existente :(                          :\n", s);
	printf(":                                                                                                       :\n");
	printaInferior2();
}
