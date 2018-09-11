#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define MAX 50

float versao = 1.0;

typedef struct musica
{
	char tituloMus[MAX];
	char cantor[100];
	int ano;
	char autorMus[100];
	char genero[MAX];
	float duracao;
	int avaliacao;
	int ocupado;
}Musica;

typedef struct playlist{
	char tituloLista[100];
	char proprietario[100];
	Musica musicas[100];
	int quantMus;
	float duracaoTotal;
	int ativa;
}Playlist;

typedef struct menu
{
	Playlist play[100];
	int quantPlay;
}Menu;

typedef struct tempo
{
	int min;
	int sec;
}Duracao;

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
	
	scanf("%d%*c", &opcao);

	if(opcao == 1){
		
		printaSuperior2();
		printf(". .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .\n");
		printf(":                                                                                                       :\n");
		printf(":  Playlist: %-91s:\n", play.tituloLista);
		printf(":  _______                                                                                              :\n");
		printf(": |  ___  |                                                                                             :\n");
		printf(": | (*-*)/|  Proprietario: %-77s:\n", play.proprietario);
		printf(": |(|   | |  N. de musicas: %-4d                                                                        :\n", play.quantMus);
		printf(": |_______|  Duracao total: %.2f                                                                        :\n", play.duracaoTotal);
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
		printf(": |_______|  Duracao total: %.2f                                                                        :\n", play.duracaoTotal);
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

				printf("%-9.2f", play.musicas[i].duracao);
				
				printaEstrelas(play.musicas[i].avaliacao);
			}	
		}
		printaInferior2();
	}
	
	if(opcao == 3){
		
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

		int i=0;
		while(i < 10)
		{ 
			if(!strcmp(play.musicas[i].autorMus, nomeAutor))
			{ 
				if(play.musicas[i].ocupado)
				{
					printf(": %-31s", play.musicas[i].tituloMus);

					printf("%-22s", play.musicas[i].cantor);	
					
					printf("%-14s", play.musicas[i].genero);

					printf("%-9d", play.musicas[i].ano);

					printf("%-16.2f", play.musicas[i].duracao);
					
					printaEstrelas(play.musicas[i].avaliacao);
				}	
			}
			i++;
		}
		printaInferior2();
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
		
		int i=0;
		
		while( i < 100)
		{ 
			if(!strcmp(play.musicas[i].genero, nomeAutor))
			{ 
				if(play.musicas[i].ocupado)
				{
					printf(": %-27s", play.musicas[i].tituloMus);

					printf("%-23s", play.musicas[i].cantor);	
					
					printf("%-15s", play.musicas[i].autorMus);

					printf("%-11d", play.musicas[i].ano);

					printf("%-16.2f", play.musicas[i].duracao);
					
					printaEstrelas(play.musicas[i].avaliacao);
				}
			}
			i++;
		}

		printaInferior2();
	}

	getch();

	}while(opcao);
}

void printaNaoExistente(char *s)
{
	printaSuperior();
	printf(":                                                                         :\n");
	printf(":                     %-7s nao existente                            :\n", s);
	printf(":                                                                         :\n");
	printf(":                                                                         :\n");
	printf(":                                                                         :\n");
	printaInferior();
}

void removeMusica(Playlist* play)
{
	char removeMus[256];
		
	printaSuperior();
	printf(":                                                                         :\n");
	printf(":             Entre com o nome da musica a ser removida                   :\n");
	printf(":                                                                         :\n");
	printf(":                                                                         :\n");
	printf(":             Nome:                                                       :\n");
	printaInferior();
	
	gotoXY(20, 9);
	
	scanf("%[^\n]%*c", removeMus);

	int i, j;
	
	for(i = j = 0; i < play->quantMus; i++)
	{
		if(!strcmp(removeMus, play->musicas[i].tituloMus))
		{
			if(play->musicas[i].ocupado)
			{
				play->musicas[i].ocupado = 0;
				play->duracaoTotal -= play->musicas[i].duracao;
				play->quantMus--;
				j++;
			}
		}
	}
	
	if(j)
		printaNaoExistente("Musica");
	getch();
}

Playlist adicionaMusica(Playlist *play){

	char escolha;
	int i;
	play->duracaoTotal = 0;
	play->quantMus = 0;

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
			
			scanf("%[^\n]%*c", play->musicas[i].tituloMus);
			
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                 Entre com o nome do cantor da musica                    :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                 Nome:                                                   :\n");
			printaInferior();
			
			gotoXY(24, 9);
			
			scanf("%[^\n]%*c", play->musicas[i].cantor);
	
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                  Entre com o nome do autor da musica                    :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                  Nome:                                                  :\n");
			printaInferior();
			
			gotoXY(25, 9);
			
			scanf("%[^\n]%*c", play->musicas[i].autorMus);

			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                       Entre com o ano da musica                         :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                       Ano:                                              :\n");
			printaInferior();
			
			gotoXY(29, 9);
			
			scanf("%d%*c", &play->musicas[i].ano);
			
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                      Entre com o genero da musica                       :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                      Genero:                                            :\n");
			printaInferior();

			gotoXY(31, 9);
						
			scanf("%[^\n]%*c", play->musicas[i].genero);
			
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                     Entre com a duracao da musica                       :\n");
			printf(":                                                                         :\n");
			printf(":                          Formato 99:99                                  :\n");
			printf(":                                                                         :\n");
			printf(":                     Duracao:                                            :\n");
			printaInferior();

			gotoXY(31 ,9);
			
			int min, seg;
			scanf("%d:%d%*c", 

			play->musicas[i].duracao);
			
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

			if(ava =>0 && ava <= 5)
				play->musicas[i].avaliacao = ava;
			else
			{
				while(ava < 0 && ava > 5)
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
					int ava;						
					scanf("%d%*c", &ava);
				}
			}

			play->quantMus++;
			play->duracaoTotal += play->musicas[i].duracao;
			play->musicas[i].ocupado = 1;
				
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

Musica inicializaMusica()
{
	Musica nova;

	nova.tituloMus[0] = '\0';
	nova.cantor[0] = '\0';
	nova.ano = 0;
	nova.autorMus[0] = '\0';
	nova.genero[0] = '\0';
	nova.duracao = 0;
	nova.avaliacao = 0;
	nova.ocupado = 0;

	return nova;
}

Playlist inicializaPlaylist()
{
	Playlist nova;
	
	nova.duracaoTotal = 0;
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
					
		int opcao;
	
		scanf("%d%*c", &opcao);
		
		switch(opcao){

			case 1: 
				adicionaMusica(&menu->play[i]); 
				break;
				
			case 2:
				removeMusica(&menu->play[i]);
				break;
			default:
				break;
		}

		continua = opcao;
	}

	getch();
}

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

void mudaInt(int *a)
{
	printaSuperior();
	printf(":                                                                         :\n");
	printf(":                          Novo:                                          :\n");
	printf(":                                                                         :\n");
	printaInferior();

	gotoXY(33, 6);
	int novo;
	
	scanf("%d%*c", &novo);
	
	*a = novo;
}

void mudaDur(float *dura)
{
	float dur;

	printaSuperior();
	printf(":                                                                         :\n");
	printf(":                          Nova duracao:                                  :\n");
	printf(":                                                                         :\n");
	printaInferior();

	gotoXY(41, 6);
	
	scanf("%f", &dur);
	
	*dura = dur;
}

void editMusica(Musica* alvo)
{
	printaSuperior();
	printf(":                                Editar:                                  :\n");
	printf(":                                                                         :\n");
	printf(":               [1]    Titulo:%s %-30s:\n", alvo->tituloMus, ' ');
	printf(":				[2]    Cantor:%s %-30s:\n", alvo->cantor, ' ');
	printf(":				[3]	    Autor:%s %-30s:\n", alvo->autorMus, ' ');
	printf(":				[4]       Ano:%d %-30s:\n", alvo->ano, ' ');
	printf(":				[5]   Duracao:%.2f %-30s:\n", alvo->duracao, ' ');
	printf(":				[6]    Genero:%s %-30s:\n", alvo->genero, ' ');
	printf(":				[7] Avaliacao:%s %-30s:\n", alvo->genero, ' ');
	printf(":				[0] 		  Voltar\n");
	printf(":                                                                         :\n");
	printf(":                       Opcao:                                            :\n");
	printaInferior();
	
	gotoXY(34, 16);
	
	int opcao;
	scanf("%d%*c", opcao);

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
			mudaInt(&alvo->ano);
			break;
		case 5:
			mudaDur(&alvo->duracao);
			break;
		case 6:
			mudaNome(alvo->genero);
			break;
		case 7:
			mudaInt(&alvo->avaliacao);
			break;
		case 0:
			break;
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

	for(i = 0; i < lista->quantMus; i++)
	{
		if(!strcmp(lista->musicas[i].tituloMus, nome))
			if(lista->musicas[i].ocupado)
			{
				achou = 1;
				editMusica(&lista->musicas[i]);
			}
	}

	if(!achou)
		printaNaoExistente("Musica");
}

void editPlay(Playlist* lista)
{
	int i = 0;
	while(i < 1)
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
		
		int opcao;
		scanf("%d%*c", &opcao);

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
				i = 1;
				break;
		}

		if(i != 1)
		{
			char escolha;
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                          Deseja continuar editando?                     :\n");
			printf(":                                                                         :\n");
			printf(":                             Sim(S)  |  Nao(N)                           :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                             R:                                          :\n");
			printaInferior();
			
			gotoXY(33, 11);
			
			scanf("%c%*c", &escolha);

			if(escolha == 'N' || escolha == 'n')
				i++;
		}
	}

	getch();
}

int main()
{
	Menu* menu = inicializaMenu();
	int escolha = 1, i;

	while(escolha != 0)
	{
		printaSuperior();
		printf(".                                                                         .\n");
		printf(":                             Escolha uma opcao:                          :\n");
		printf(":                                                                         :\n");
		printf(":                       [1] - Criar uma Playlist                          :\n");
		printf(":                       [2] - Remover uma playlist                        :\n");
		printf(":                       [3] - Consultar uma playlist                      :\n");
		printf(":                       [4] - Editar uma playlist                         :\n");
		printf(":                       [0] - Fechar                                      :\n");
		printf(":                                                                         :\n");
		printf(":                       Opcao:                                            :\n");
		printaInferior();
		
		gotoXY(31, 14);

		int escolha;
		scanf("%d%*c", &escolha);
		
		if(escolha == 1)
		{
			int i = 0;
			
			if(menu->play[i].ativa == 0)
			{
			  	printaSuperior();
				printf(":                                                                         :\n");
				printf(":                       Entre com o nome da playlist:                     :\n");
				printf(":                                                                         :\n");
				printf(":                                                                         :\n");
				printf(":                       Nome:                                             :\n");
				printaInferior();
				
				gotoXY(30, 9);
				
				scanf("%[^\n]%*c", menu->play[i].tituloLista);
				
				getch();
				
				printaSuperior();
				printf(":                                                                         :\n");
				printf(":            Entre com o nome do proprietario da playlist                 :\n");
				printf(":                                                                         :\n");
				printf(":                                                                         :\n");
				printf(":             Nome:                                                       :\n");
				printaInferior();
				
				gotoXY(20, 9);
				
				scanf("%[^\n]%*c", menu->play[i].proprietario);
				
				menu->play[i].ativa = 1;

				adicionaEremove(menu);

				menu->quantPlay++;
			}

			i++;
		}
		else if(escolha == 2)
		{
			char nomePlay[100];
			
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":          Entre com o nome da playlist a ser removida                    :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":          Nome:                                                          :\n");
			printaInferior();
			
			gotoXY(16, 9);
			
			scanf("%s%*c", nomePlay);
			
			int i, achou = 0;

			for(i = 0; i < 100; i++)
			{
				if(!strcmp(nomePlay, menu->play[i].tituloLista))
				{
					menu->play[i] = removePlaylist(menu->play[i]);
					menu->quantPlay--;
					achou = 1;
				}
			}

			if(!achou)
			{
				printaNaoExistente("Playlist");
			}

		}
		else if(escolha == 3)
		{
			char nomePlay[100];
			int achou = 0;
			
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":             Entre com o nome da playlist a ser consultada               :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":             Nome:                                                       :\n");
			printaInferior();

			gotoXY(20, 9);
						
			scanf("%s%*c", nomePlay);
			
			for(i = 0; i < 100; i++)
			{
				if(!strcmp(nomePlay, menu->play[i].tituloLista))
				{
					if(menu->play[i].ativa)
					{
						achou = 1;
						consulList(menu->play[i]);
					}
				}
			}

			if(!achou)
			{
				printaNaoExistente("Playlist");
			}
		}
		else if(escolha == 4)
		{
			int achou = 0;
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                          Playlist a ser editada?                        :\n");
			printf(":                                                                         :\n");\
			printf(":                                                                         :\n");
			printf(":                             R:                                          :\n");
			printaInferior();

			gotoXY(33, 9);

			char playlistAlvo[100];
			scanf("%[^\n]%*c", playlistAlvo);

			for(i = 0; i < menu->quantPlay; i++)
			{
				if(!strcmp(menu->play[i].tituloLista, playlistAlvo))
				{
					achou = 1;
					editPlay(&menu->play[i]);
				}
			}

			if(!achou)
			{
				printaNaoExistente("Playlist");
			}

		}
		else if(escolha == 0)
		{
			char c;
				
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                          Deseja sair do programa?                       :\n");
			printf(":                                                                         :\n");
			printf(":                             Sim(S)  |  Nao(N)                           :\n");
			printf(":                                                                         :\n");
			printf(":                                                                         :\n");
			printf(":                             R:                                          :\n");
			printaInferior();
			
			gotoXY(33, 11);
			
			scanf("%c%*c", &c);
			if(c == 'S' || c == 's')
				break;
		}
	}

	system("CLS");
	return 0;
}
