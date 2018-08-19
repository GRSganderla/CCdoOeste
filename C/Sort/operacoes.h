#ifndef OPERACAO_H
#define OPERACAO_H

#include "ordenacao.h"

typedef struct argumentos
{
    char tipoDado;
    char* arqEntrada;
    char* arqSaida;
    char* tipoSort;
    int quantN;
}ArgumentosCMD;

ArgumentosCMD* inicializa();

char* pegarArg(char const *argv[]);

ArgumentosCMD* linhaDeArgumentos(ArgumentosCMD* args, char const *argv[], int argc);

char pegaTipo(char const *argv[]);

void limpaArg(ArgumentosCMD *arg);

int* criaVetor(int tam);

void determinaOp(ArgumentosCMD* arg);

#endif // OPERACAO_H
