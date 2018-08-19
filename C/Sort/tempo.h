#ifndef TEMPOOP_H
#define TEMPOOP_H

#include "operacoes.h"

void fazOpN(int v[], ArgumentosCMD* arg);

void fazTodasOrdN(int vet[], int tam);

void copiaVet(int vet[], int vAux[], int tam);

float ordN(int vet[], char *tipoSort, int tam);

void ordArq(int v[], ArgumentosCMD* a);

char** lerArq(char* nome, int *tam);

char** abreArq(char* nome, int *tam);

void copiaVetC(char* v[], char* vet[], int tam);

float tempoC(char* v[], char* tipoSort, int tam);

void comparaTempo(char *vet[], int tam);

void opeArq(char* v[], ArgumentosCMD* a);

void fazOpC(char* v[], ArgumentosCMD* a);

#endif // TEMPOOP_H
