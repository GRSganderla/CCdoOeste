#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "edit.h"

int main()
{
	HANDLE consoleInicial = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD atributos;
    GetConsoleScreenBufferInfo(consoleInicial, &consoleInfo);
    atributos = consoleInfo.wAttributes;
	
	Menu* menu = inicializaMenu();
	int escolha = 1, i, final = 0;

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

		printf(":                       [0] - Fechar                                      :\n");

		printf(":                                                                         :\n");
		printf(":                       Opcao:                                            :\n");
		printaInferior();
		
		gotoXY(31, 14);

		char c = getch();
		int escolha = charToNum(c);
	
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
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                   Escolha a playlist a ser removida                     :\n");
			printf(":                                                                         :\n");

			for (int i = 0; i < menu->quantPlay; ++i)
			{
				if(menu->play[i].ativa)
					printf(":              [%d] %-55s:\n", i+1, menu->play[i].tituloLista);
			}

			printf(":                                                                         :\n");
			printf(":           Opcao:                                                        :\n");
			printaInferior();
			
			gotoXY(19, 9+menu->quantPlay);
			
			char c = getch();
			int nomePlay = charToNum(c);

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
		}
		else if(escolha == 3)
		{
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                   Escolha a playlist a ser consultada                   :\n");
			printf(":                                                                         :\n");
			
			for(i = 0; i < menu->quantPlay; i++)
			{
				if(menu->play[i].ativa)
					printf(":              [%d] %-55s:\n", i+1, menu->play[i].tituloLista);
			}
			
			printf(":                                                                         :\n");
			printf(":            Opcao:                                                       :\n");
			printf(":                                                                         :\n");
			printaInferior();

			gotoXY(20, 9+menu->quantPlay);
		
			char c = getch();
			int nomePlay = charToNum(c);
			
			if(nomePlay > 0 && nomePlay <= menu->quantPlay)
			{
				if(menu->play[nomePlay-1].ativa)
				{
					consulList(menu->play[nomePlay-1]);
				}
			}

			else
				printaNaoExistentePlaylist();
		}
		else if(escolha == 4)
		{
			int achou = 0, j;
			printaSuperior();
			printf(":                                                                         :\n");
			printf(":                          Playlist a ser editada?                        :\n");
			printf(":                                                                         :\n");

			for(i = 0; i < menu->quantPlay; i++)
			{
				if(menu->play[i].ativa)
					printf(":                [%d] %-53s:\n", i+1, menu->play[i].tituloLista);
			}

			printf(":                                                                         :\n");
			printf(":                             R:                                          :\n");
			printf(":                                                                         :\n");
			printaInferior();

			gotoXY(33, 9+menu->quantPlay);
			
			char c = getch();
			int playlistAlvo = charToNum(c);

			if(playlistAlvo > 0 && playlistAlvo <= menu->quantPlay)
				if(menu->play[playlistAlvo-1].ativa)
					editPlay(&menu->play[playlistAlvo-1]);
			else 
				printaNaoExistentePlaylist();

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
				final = 1;
		}

		if(final == 1)
			break;
	}

	system("CLS");
	return 0;
}
