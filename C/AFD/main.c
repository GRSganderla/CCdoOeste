#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
#include "arquivo.h"
#include "gramatica.h"

int main(int argc, char const *argv[])
{
    AFD afd = {};
    afd.tamanhoE = 0;
    afd.tamanhoF = 0;
    int continua = 1;

    //se deu certo em abrir e guardar o conteudo do arquivo no afd
    if(entrada( (char*) argv[1], &afd))
    {
        //menu para fazer o processamento de palavra ou exibir a gramatica do afd
        while(continua)
        {
            //escolha do usuario
            printf("0 - Fechar programa\n");
            printf("1 - Deseja mostrar a Gramatica?\n");
            printf("2 - Entrar com uma cadeia para ser processada pelo AFD?\n");

            //guarda a escolha
            scanf("%d", &continua);
            fflush(stdin);
            system("CLS");

            //se for 1, printa a gramatica
            if(continua == 1)
            {
                fazGramatica(&afd);
                printf("\n");
            }

            //se for 2..
            if(continua == 2)
            {
                //ve a palavra a ser processada
                char s[MAX];
                printf("Entre com uma palavra a ser testada pelo AFD: ");

                scanf("%[^\n]%*c", s);
                fflush(stdin);

                //determina se ela é aceita ou não pelo AFD
                printf("\nProcesso da cadeia:\n");
                aceitaOUnao(afd, s);
                printf("\n");
            }
        }
    }

    return 0;
}
