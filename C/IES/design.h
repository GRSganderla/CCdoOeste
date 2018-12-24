#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct tempo
{
	int min;
	int seg;
}Duracao;

typedef struct musica
{
	char tituloMus[MAX];
	char cantor[100];
	int ano;
	char autorMus[100];
	char genero[MAX];
	Duracao duracao;
	int avaliacao;
	int ocupado;
}Musica;

typedef struct playlist{
	char tituloLista[100];
	char proprietario[100];
	Musica musicas[100];
	int quantMus;
	Duracao duracaoTotal;
	int ativa;
}Playlist;

typedef struct estacao
{
	char nomeEstacao[100];
	float frequencia;
	char genero[30];
}Estacao;

typedef struct menu
{
	Playlist play[50];
	Estacao radio[5];
	int quantPlay;
}Menu;

int charToNum(char c);

void gotoXY(int x, int y);

void printaSuperior();

void printaInferior();

void printaSuperior2();

void printaInferior2();

void printaEstrelas(int avaliacao);

void printaEstrelas2(int avaliacao, int alvo);

void consulList(Playlist play);

void printaNaoExistenteMusica();

void printaNaoExistentePlaylist();