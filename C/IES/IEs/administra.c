#include "administra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
int anoAtual = 2018;

Playlist lerBiblio()
{
	Playlist first = inicializaPlaylist();
	FILE* f = fopen("biblioteca.txt", "r");

	char s[MAX];
	int i = 0;

	while(!feof(f))
	{
		if(s[0] == '-')
			fgets(s, MAX, f);
		
		if(!memcmp(s, "Nome:", 5))
			sscanf(s+5, " %[^\n]", first.musicas[i].tituloMus);
		
		if(!memcmp(s, "Cantor:", 7))
			sscanf(s+7, " %[^\n]", first.musicas[i].cantor);
		
		if(!memcmp(s, "Autor:", 6))
			sscanf(s+6, " %[^\n]", first.musicas[i].autorMus);
		
		if(!memcmp(s, "Genero:", 7))
			sscanf(s+7, " %[^\n]", first.musicas[i].genero);
		
		if(!memcmp(s, "Ano:", 4))
			sscanf(s+4, "%d", &first.musicas[i].ano);
		
		if(!memcmp(s, "Duracao:", 8))
		{
			sscanf(s+8, "%d:%d", &first.musicas[i].duracao.min, &first.musicas[i].duracao.seg);
			first.duracaoTotal.min += first.musicas[i].duracao.min;
			first.duracaoTotal.seg += first.musicas[i].duracao.seg;
		}
		
		if(!memcmp(s, "Avaliacao:", 10))
		{
			sscanf(s+10, "%d", &first.musicas[i].avaliacao);
			first.musicas[i].ocupado = 1;
			first.quantMus++;
			i++;
		}

		fgets(s, MAX, f);
	}

	return first;
}

void removeMusica(Playlist* play)
{		
	printaSuperior();
	printf(":                                                                         :\n");
	printf(":                   Escolha a musica a ser removida                       :\n");
	printf(":                                                                         :\n");

	for(int i = 0; i <= play->quantMus; i++)
	{
		if(play->musicas[i].ocupado)
			printf(":              [%d] %-55s:\n", i, play->musicas[i].tituloMus);
	}

	printf(":                                                                         :\n");
	printf(":             Opcao:                                                      :\n");
	printaInferior();
	
	gotoXY(22, 9+play->quantMus);
	
	char c = getch();
	int escolha = charToNum(c);

	int i, achou = 0;
	
	if(play->musicas[escolha].ocupado && (escolha >= 0 && escolha <= play->quantMus))
	{
		play->musicas[escolha].ocupado = 0;
		
		play->duracaoTotal.min -= play->musicas[escolha].duracao.min;
		play->duracaoTotal.seg -= play->musicas[escolha].duracao.seg;

		if(play->duracaoTotal.seg < 0)
		{
			play->duracaoTotal.seg += 60;
			play->duracaoTotal.min--;
		}

		play->quantMus--;
	}
	else
		printaNaoExistenteMusica();
}

int cmp(Musica mus, Playlist* play)
{
	int i = 0;
	for(; i < MAX; i++)
	{
		if(!strcmp(play->musicas[i].tituloMus, mus.tituloMus))
			if(!strcmp(play->musicas[i].cantor, mus.cantor))
				if(!strcmp(play->musicas[i].autorMus, mus.autorMus))
					if(!strcmp(play->musicas[i].genero, mus.genero))
						if(play->musicas[i].ano == mus.ano)
							if(play->musicas[i].avaliacao == mus.avaliacao)
								if((play->musicas[i].duracao.min == mus.duracao.min) && (play->musicas[i].duracao.seg == mus.duracao.seg))
									return 1;
	}

	return 0;
}

Playlist adicionaMusica(Playlist *play)
{
	char escolha;
	Musica aux;
	int i, opcao;
	Playlist biblioteca = lerBiblio();

	for(i=0; i<MAX; i++)
	{
		printaSuperior();
		for(int j = 0; j < biblioteca.quantMus; j++)
		{
			printf(":                                                                         :\n");
			if(j < 10)
				printf(": [%d]                                                                     :\n", j);
			else
				printf(": [%d]                                                                    :\n", j);
			
			printf(": Nome: %-66s:\n", biblioteca.musicas[j].tituloMus);
			printf(": Cantor: %-64s:\n", biblioteca.musicas[j].cantor);
			printf(": Autor: %-65s:\n", biblioteca.musicas[j].autorMus);
			printf(": Genero: %-64s:\n", biblioteca.musicas[j].genero);
			printf(": Duracao: %4d:%-58d:\n", biblioteca.musicas[j].duracao.min, biblioteca.musicas[j].duracao.seg);
			printf(": Avaliacao: ");
			printaEstrelas2(biblioteca.musicas[j].avaliacao, 61);
		}

		printf(":                                                                         :\n");			
		printf(": Escolha:                                                                :\n");
		printf(":                                                                         :\n");
		printaInferior();

		gotoXY(11, 6+(biblioteca.quantMus * 8));
		scanf("%d%*c", &opcao);

		aux = biblioteca.musicas[opcao];

		if(cmp(aux, play))
		{
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                              Musica Duplicada                           :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printaInferior();
			getch();
		}
		else
		{
			play->musicas[i] = aux;
		
			play->quantMus++;

			play->duracaoTotal.min += play->musicas[i].duracao.min;
			play->duracaoTotal.seg += play->musicas[i].duracao.seg;

			if(play->duracaoTotal.seg >= 60)
			{
				play->duracaoTotal.seg -= 60;
				play->duracaoTotal.min++;
			}

			play->musicas[i].ocupado = 1;
		}

		printaSuperior();
		printf(":                                                                         :\n");
		printf(":                       Deseja continuar adicionando?                     :\n");
		printf(":                                                                         :\n");
		printf(":                             Sim(S)  |  Nao(N)                           :\n");
		printf(":                                                                         :\n");
		printf(":                                                                         :\n");
		printf(":                             R:                                          :\n");
		printaInferior();
		
		gotoXY(33, 11);
					
		char escolha;
		scanf("%c%*c", &escolha);
		
		if(escolha == 'N' || escolha == 'n')
			break;
	}
}

Duracao inicializaDur()
{
	Duracao duracao;

	duracao.min = 0;
	duracao.seg = 0;

	return duracao;
}

Musica inicializaMusica()
{
	Musica nova;

	nova.tituloMus[0] = '\0';
	nova.cantor[0] = '\0';
	nova.ano = 0;
	nova.autorMus[0] = '\0';
	nova.genero[0] = '\0';
	nova.duracao = inicializaDur();
	nova.avaliacao = 0;
	nova.ocupado = 0;

	return nova;
}

Playlist inicializaPlaylist()
{
	Playlist nova;
	
	nova.duracaoTotal = inicializaDur();
	nova.quantMus = 0;
	nova.tituloLista[0] = '\0';
	nova.proprietario[0] = '\0';

	int i;
	for(i = 0; i < 100; i++)
		nova.musicas[i] = inicializaMusica();
	
	nova.ativa = 0;

	return nova;
}

Menu* inicializaMenu()
{
	Menu *novo = (Menu*)malloc(sizeof(Menu));
	int i = 0;

	for(i = 0; i < 100; i++)
		novo->play[i] = inicializaPlaylist();

	novo->quantPlay = 0;

	return novo;
}

Playlist removePlaylist(Playlist alvo)
{
	if(alvo.ativa)
		alvo.ativa = 0;
	return alvo;
}

void adicionaEremove(Menu *menu)
{
	int continua = 1;

	while(continua)
	{
		int i = 0;
		
		printaSuperior();
		printf(":                       Escolha uma das opcoes:                           :\n");
		printf(":                                                                         :\n");
		printf(":                   [1] - Adicionar musica a playlist                     :\n");
		printf(":                   [2] - Remover musica a playlist                       :\n");
		printf(":                   [0] - Voltar                                          :\n");
		printf(":                                                                         :\n");
		printf(":                   Opcao:                                                :\n");
		printaInferior();
		
		gotoXY(27, 11);
	
		char c = getch();
		int escolha = charToNum(c);
		
		switch(escolha){

			case 1: 
				adicionaMusica(&menu->play[i]); 
				break;
				
			case 2:
				removeMusica(&menu->play[i]);
				break;
			default:
				break;
		}

		if(escolha == 0)
			break;

		continua = escolha;
	}
}