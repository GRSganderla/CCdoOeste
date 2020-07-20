#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

#include "arquivobin.h"

///
/// \brief main, função que comanda o jogo
/// \param argc, quantidade de argumentos passados pelo cmd(QT)
/// \param argv, vetor dos argumentos passados pelo cmd(QT)
/// \return se o programa foi executado
/// \pre nenhum
/// \post nenhum
///
int main(int argc, char const *argv[])
{
    Mesa* mesa = criaMesa();

    //define o rande e o local
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    //se não for para carregar
    if(argc == 1)
    {
        //começe um novo jogo
        comecarJogo(mesa);
    }else{
        //verifica se é para carregar o jogo
        if(carregarJogo(mesa, (char*) argv[1]))
        {
            //fecha o programa se não foi executado corretamente
            return 0;
        }
    }

    //imprime o hub mesa
    mostrarMesa(mesa);

    printf("    Entre com um comando: ");

    //enquanto tiver operações a serem feitas
    while(!operacoes(mesa))
    {
        //mostra a mesa depois de ter sido alterada
        mostrarMesa(mesa);
        printf("    Entre com um comando: ");

    }

    return 0;
}
