#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#define MAX 100
#include "arquivo.h"
#include "gramatica.h"

int main(int argc, char const *argv[])
{
    MT mt = {};
    mt.tamanhoE = 0;
    mt.tamanhoF = 0;
    int continua = 1;

    //se deu certo em abrir e guardar o conteudo do arquivo no mt
    if(entrada( (char*) argv[1], &mt))
    {
        //menu para fazer o processamento de palavra
        while(continua)
        {
	        system("CLS");
            //escolha do usuario
            printf("0 - Fechar programa\n");
            printf("1 - Entrar com uma cadeia para ser processada pelo MT?\n");

            //guarda a escolha
            scanf("%d", &continua);
            fflush(stdin);
            system("CLS");

            //se for 1..
            if(continua == 1)
            {
                //ve a palavra a ser processada
                char s[MAX], palavra[MAX];
                printf("Entre com uma palavra a ser testada pelo MT: ");

                scanf("%[^\n]%*c", s);
                strcpy(palavra, "*");
                strcat(palavra, s);
                strcat(palavra, "$");
                fflush(stdin);

                //determina se ela é aceita ou não pelo MT
                printf("\nProcesso da cadeia:\n");
                aceitaOUnao(mt, palavra);
		        s[0] = '\0';
                palavra[0] = '\0';
            }

            getch();
        }
    }

    return 0;
}
