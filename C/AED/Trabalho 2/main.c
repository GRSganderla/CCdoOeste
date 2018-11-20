#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "operacoes.h"

int main(int argc, const char *argv[])
{
    //determina o tempo do srand
    srand(time(NULL));

    //inicializa a estrutura e pega os argumentos do CMD
    ArgumentosCMD* args = inicializa();
    args = linhaDeArgumentos(args, argv, argc);

    //determina qual o dado e direciona para qual operação será feita
    determinaDado(args);

    //limpa a variavel do tipo ArgumentosCMD*
    limpaArg(args);

    return 0;
}
