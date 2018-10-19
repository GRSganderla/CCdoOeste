#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "design.h"

void removeMusica(Playlist* play);

int cmp(Musica mus, Playlist* play);

Playlist adicionaMusica(Playlist *play);

Duracao inicializaDur();

Musica inicializaMusica();

Playlist inicializaPlaylist();

Menu* inicializaMenu();

Playlist removePlaylist(Playlist alvo);

void adicionaEremove(Menu *menu);