#include "administra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
int anoAtual = 2018;

void fazEstacao(Estacao programa[])
{
	strcpy(programa[0].nomeEstacao,"Jovem Pan");
	programa[0].frequencia = 93.3;
	strcpy(programa[0].genero, "Pop-Rock");

	strcpy(programa[1].nomeEstacao, "Itaipu");
	programa[1].frequencia = 105.7;
	strcpy(programa[1].genero, "Pop-Rock");
	
	strcpy(programa[2].nomeEstacao, "TransAmerica");
	programa[2].frequencia = 104.5;
	strcpy(programa[2].genero, "Pop-Rock");
	
	strcpy(programa[3].nomeEstacao, "WOODS");
	programa[3].frequencia = 101.1;
	strcpy(programa[3].genero, "Sertanejo");
	
	strcpy(programa[4].nomeEstacao, "Morumbi Foz");
	programa[4].frequencia = 106.3;
	strcpy(programa[4].genero, "Pop-Rock / Eletronica");
}

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

void adicionaMusicaManual(Playlist *play)
{
	char escolha;
	Musica aux;
	int i;

	for(i=0; i<MAX; i++){

		if(play->musicas[i].ocupado == 0)
		{

			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                       Entre com o nome da musica                        :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                       Nome:                                             :\n");
			printaInferior();
			
			gotoXY(30, 9);
			
			scanf("%[^\n]%*c", aux.tituloMus);
			
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                 Entre com o nome do cantor da musica                    :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                 Nome:                                                   :\n");
			printaInferior();
			
			gotoXY(24, 9);
			
			scanf("%[^\n]%*c", aux.cantor);
	
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                  Entre com o nome do autor da musica                    :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                  Nome:                                                  :\n");
			printaInferior();
			
			gotoXY(25, 9);
			
			scanf("%[^\n]%*c", aux.autorMus);

			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                       Entre com o ano da musica                         :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                       Ano:                                              :\n");
			printaInferior();
			
			gotoXY(29, 9);
			
			int anoAux;
			scanf("%d%*c", &anoAux);
			
			if(anoAux <= anoAtual)
				aux.ano = anoAux;
			else
			{
				while(anoAux > anoAtual && anoAux != anoAtual)
				{
					printaSuperior();
					printf(":                                                                         :\n");
					printf(":                       Entre com o ano da musica valido                  :\n");
					printf(":                                                                         :\n");
					printf(":                                                                         :\n");
					printf(":                       Ano:                                              :\n");
					printaInferior();

					gotoXY(29, 9);
				
					int anoAux;
					scanf("%d%*c", &anoAux);
				}

				aux.ano = anoAux;
			}
			

			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                      Entre com o genero da musica                       :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                      Genero:                                            :\n");
			printaInferior();

			gotoXY(31, 9);
						
			scanf("%[^\n]%*c", aux.genero);
			
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                     Entre com a duracao da musica                       :\n");
			printf(":                                                                         :\n");
			printf(":                          Formato 99:99                                  :\n");
			printf(":                                                                         :\n");
			printf(":                     Duracao:                                            :\n");
			printaInferior();

			gotoXY(31, 10);
			
			int min, seg;
			scanf("%d:%d%*c", &min, &seg);

			while(seg >= 60)
			{
				seg -= 60;
				min++;
			}

			aux.duracao.min = min;
			aux.duracao.seg = seg;
			
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                    Entre com a avaliacao da musica                      :\n");
			printf(":                                                                         :\n");
			printf(":                      	      De 0 a 5                                    :\n");
			printf(":                                                                         :\n");
			printf(":                    Avaliacao:                                           :\n");
			printaInferior();
			
			gotoXY(32, 10);
			int ava;						
			scanf("%d%*c", &ava);

			if(ava >= 0 && ava <= 5)
				aux.avaliacao = ava;
			else
			{
				while(ava < 0 || ava > 5)
				{
					printaSuperior();
					printf(":                                                                         :\n");
					printf(":                    Entre com a avaliacao valida                         :\n");
					printf(":                                                                         :\n");
					printf(":                            De 0 a 5                                     :\n");
					printf(":                                                                         :\n");
					printf(":                    Avaliacao:                                           :\n");
					printaInferior();
					
					gotoXY(32, 10);					
					scanf("%d%*c", &ava);
				}

				aux.avaliacao = ava;
			}

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
			
			if(escolha == 'N' || escolha == 'n'){
			
				break;
			}
		} 
	}
}

void adicionaMusicaDaBiblio(Playlist *play)
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

void adicionaMusica(Playlist* play)
{
	int continua = 1;
	while(continua)
	{
		int i = 0;
		
		printaSuperior();
		printf(":                       Escolha uma das opcoes:                           :\n");
		printf(":                                                                         :\n");
		printf(":                   [1] - Adicionar da Biblioteca                         :\n");
		printf(":                   [2] - Adicionar Manualmente uma musica                :\n");
		printf(":                   [0] - Voltar                                          :\n");
		printf(":                                                                         :\n");
		printf(":                   Opcao:                                                :\n");
		printaInferior();
		
		gotoXY(27, 11);
	
		char c = getch();
		int escolha = charToNum(c);
		
		switch(escolha){

			case 1: 
				adicionaMusicaDaBiblio(play); 
				break;
				
			case 2:
				adicionaMusicaManual(play);
				break;
			default:
				break;
		}

		if(escolha == 0)
			break;

		continua = escolha;
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

Estacao inicializaRadio()
{
	Estacao nova;

	nova.nomeEstacao[0] = '\0';
	nova.frequencia = 0;
	nova.genero[0] = '\0';

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

	for(i = 0; i < 50; i++)
		novo->play[i] = inicializaPlaylist();

	novo->quantPlay = 0;

	for(i = 0; i < 5; i++)
		novo->radio[i] = inicializaRadio();

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
		printf(":                   [1] - Adicionar musica na playlist                    :\n");
		printf(":                   [2] - Remover musica da playlist                      :\n");
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