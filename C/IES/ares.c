#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "edit.h"

int main()
{
	HANDLE consoleInicial = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD atributos;
    GetConsoleScreenBufferInfo(consoleInicial, &consoleInfo);
    atributos = consoleInfo.wAttributes;

    srand(time(0));
	
	Menu* menu = inicializaMenu();
	int escolha = 1, i = 0, final = 0, nomePlay, achou, playlistAlvo, random, aleatorio;
	char c;

	while(escolha != 0)
	{

		printaSuperior();
		printf(".                                                                         .\n");
		printf(":                             Escolha uma opcao:                          :\n");
		printf(":                                                                         :\n");
		printf(":                       [1] - Criar uma Playlist                          :\n");

		printf(":");                 
	    if(!menu->quantPlay)
	        SetConsoleTextAttribute(consoleInicial, FOREGROUND_RED);
		printf("                       [2] - Remover uma playlist");
		SetConsoleTextAttribute(consoleInicial, atributos);
		printf("                        :\n");

		printf(":");                 
	    if(!menu->quantPlay)
	        SetConsoleTextAttribute(consoleInicial, FOREGROUND_RED);
		printf("                       [3] - Consultar uma playlist");
		SetConsoleTextAttribute(consoleInicial, atributos);

		printf("                      :\n");
		printf(":");                 
	    if(!menu->quantPlay)
	        SetConsoleTextAttribute(consoleInicial, FOREGROUND_RED);
		printf("                       [4] - Editar uma playlist");
		SetConsoleTextAttribute(consoleInicial, atributos);
		printf("                         :\n");

		printf(":                       [5] - Radio                                       :\n");
		printf(":                       [0] - Fechar                                      :\n");

		printf(":                                                                         :\n");
		printf(":                       Opcao:                                            :\n");
		printaInferior();
		
		gotoXY(31, 15);

		char c = getch();
		int escolha = charToNum(c);
	
		switch(escolha)
		{
			case 1:
			
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
				break;
		
			case 2:

				printaSuperior();
				printf(":                                                                         :\n");
				printf(":                   Escolha a playlist a ser removida                     :\n");
				printf(":                                                                         :\n");

				for (int j = 0; j < menu->quantPlay; ++j)
				{
					if(menu->play[j].ativa)
						printf(":              [%d] %-55s:\n", j+1, menu->play[j].tituloLista);
				}

				printf(":                                                                         :\n");
				printf(":           Opcao:                                                        :\n");
				printaInferior();
				
				gotoXY(19, 9+menu->quantPlay);
				
				c = getch();
				nomePlay = charToNum(c);

				if(nomePlay > 0 && nomePlay <= menu->quantPlay)
				{
					menu->play[nomePlay-1] = removePlaylist(menu->play[nomePlay-1]);
					if(menu->quantPlay == 1)
						menu->quantPlay = 0;
					else 
						menu->quantPlay--;
				}
				else
					printaNaoExistentePlaylist();
				break;

			case 3:

				printaSuperior();
				printf(":                                                                         :\n");
				printf(":                   Escolha a playlist a ser consultada                   :\n");
				printf(":                                                                         :\n");
				
				for(int j = 0; j < menu->quantPlay; j++)
				{
					if(menu->play[j].ativa)
						printf(":              [%d] %-55s:\n", j+1, menu->play[j].tituloLista);
				}
				
				printf(":                                                                         :\n");
				printf(":            Opcao:                                                       :\n");
				printf(":                                                                         :\n");
				printaInferior();

				gotoXY(20, 9+menu->quantPlay);
			
				c = getch();
				nomePlay = charToNum(c);
				
				if(nomePlay > 0 && nomePlay <= menu->quantPlay)
				{
					if(menu->play[nomePlay-1].ativa)
					{
						consulList(menu->play[nomePlay-1]);
					}
				}

				else
					printaNaoExistentePlaylist();
				break;
		
			case 4:
		
				achou = 0;
				printaSuperior();
				printf(":                                                                         :\n");
				printf(":                          Playlist a ser editada?                        :\n");
				printf(":                                                                         :\n");

				for(int j = 0; j < menu->quantPlay; j++)
				{
					if(menu->play[j].ativa)
						printf(":                [%d] %-53s:\n", j+1, menu->play[j].tituloLista);
				}

				printf(":                                                                         :\n");
				printf(":                             R:                                          :\n");
				printf(":                                                                         :\n");
				printaInferior();

				gotoXY(33, 9+menu->quantPlay);
				
				c = getch();
				playlistAlvo = charToNum(c);

				if(playlistAlvo > 0 && playlistAlvo <= menu->quantPlay)
					if(menu->play[playlistAlvo-1].ativa)
						editPlay(&menu->play[playlistAlvo-1]);
				else 
					printaNaoExistentePlaylist();
				break;

			case 5:

				fazEstacao(menu->radio);

				printaSuperior();
				printf(":                                                                         :\n");
				printf(":  Radios :                                                               :\n");
				printf(":                                                                         :\n");

				for(int j = 0; j < 5; j++)
				{
					printf(": %-13s ~ %-10.3lf~ Estilo: %-35s :\n", menu->radio[j].nomeEstacao, menu->radio[j].frequencia, menu->radio[j].genero);
				}

				printf(":                                                                         :\n");
				printaInferior();

				c = getch();
				playlistAlvo = charToNum(c);
				break;

			case 0:
					
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
					final = 1;
				break;
		}

		fflush(stdin);

		if(final == 1)
			break;
	}

	system("CLS");
	return 0;
}
