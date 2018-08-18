#ifndef OPERACAO_H
#define OPERACAO_H

#include "sorts.h"

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

#endif // OPERACAO_H
