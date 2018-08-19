#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "operacoes.h"

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    ArgumentosCMD* args = inicializa();

    args = linhaDeArgumentos(args, argv, argc);

    determinaOp(args);

    limpaArg(args);

    return 0;s
}
