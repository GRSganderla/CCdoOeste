#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
#define MAXQ 20
#define MAXF 10
#define MAXA 20

#include "arquivo.h"

///
/// \brief qualEstado, procura por todos os estados guardados do AFD o estado que tenha tal nome
/// \param afd, struct com os estados a serem pesquisados
/// \param str, nome do estado que está sendo buscado
/// \return retorna o indice a qual o estado esta dentro do vetor de estados do AFD ou -1 se não for encontrado
/// \pre nenhum
/// \post nenhum
///
int qualEstado(AFD* afd, char str[])
{
    int i;
    //ate o numero de estados contidos, procura qual indice o estado que carrega esse nome está
    for(i = 0; i < afd->tamanhoE; i++)
        if(!strcmp(afd->estados[i].nome, str))
            return i;
    return -1;
}

///
/// \brief entrada, função que abre o arquivo do nome de entrada e guarda as informações que o AFD precisa conter
/// \param s, string com o nome do arquivo a ser aberto
/// \param afds, struct que ira guardar as informações do AFD a ser usado
/// \return retorna 1 se for aberto corretamente ou 0 se não foi aberto corretamente
/// \pre o arquivo de nome s tem que ter sido criado e estar contido no computador
/// \post o afds conterá cada um das informações do AFD que será usado
///
int entrada(char s[], AFD *afds)
{
    //abre o arquivo
    FILE* entry = fopen(s, "r");

    //se tiver vazio
    if(entry == NULL)
    {
        printf("Arquivo nao encontrado ou vazio\n");
        return 0;
    }

    //enquanto não for o final do arquivo
    while(!feof(entry))
    {
        char linha[MAX], estados[MAX], estadonome[MAX];
        //coloca no vetor de caracter a linha inteiro do arquivo
        fgets(linha, MAX, entry);

        int i, j;

        //verifica se a linha vai conter o alfabeto
        if(memcmp(linha, "alfabeto={", 10) == 0)
        {
            //guarda tudo que esta dentro dos {}
            sscanf(linha, "alfabeto={ %[^}] }", estados);
            for(i = j = 0; i < strlen(estados) ; i++)
            {
                //se não for uma virgula, guarda o alfabeto dentro do vetor alfa de afds
                if(estados[i] != ',')
                    afds->alfa[j++] = estados[i];
            }
            afds->alfa[j] = '\0';
        }
        //verifica se a linha vai conter os estados
        else if(memcmp(linha, "estados={", 9) == 0)
        {
            //guarda oque tiver dentro dos {}
            sscanf(linha, "estados={ %[^}] }", estados);
            int percorre;
            for(percorre = 0; percorre < strlen(estados); percorre += strlen(estadonome)+1)
            {
                //guarda tudo até a proxima virgula e guarda no vetor de estados
                sscanf(estados+percorre, "%[^,],", estadonome);
                strcpy(afds->estados[afds->tamanhoE++].nome, estadonome);
            }
        }
        //verifica se a linha vai conter os estados finais
        else if(memcmp(linha, "finais=", 7) == 0)
        {
            //guarda tudo dentro dos {}
            sscanf(linha, "finais={ %[^}] }", estados);
            int percorre;
            for(percorre = 0; percorre < strlen(estados); percorre += strlen(estadonome)+1)
            {
                //guarda tudo até a proxima virgula
                sscanf(estados+percorre, "%[^,],", estadonome);
                int ind = qualEstado(afds, estadonome);
                //coloca o estado final de afds referenciando o estado no indice ind do vetor de estados
                if(ind != -1)
                    afds->finais[afds->tamanhoF++] = &afds->estados[ind];
            }
        }
        //verifica se a linha vai conter o estado inicial
        else if(memcmp(linha, "inicial=", 8) == 0)
        {
            //guarda tudo até o \n
            sscanf(linha, "inicial=%[^\n]%*c", estadonome);
            int indI = qualEstado(afds, estadonome);
            //referencia o estado inicial ao estado no indice ind do vetor de estados
            if(indI != -1)
                afds->inicial = &afds->estados[indI];
        }
        //se for as linha de transições
        else if(linha[0] == '(')
        {
            int n;
            int indProx;
            char terminalLido;
            //scaneia e guarda o nome do estado a fazer a transição
            sscanf(linha, "(%[^,],%n", estadonome, &n);
            //pega o indice em que esse estado esta no vetor de estados
            int indEst = qualEstado(afds, estadonome);
            //se existir o estado dentro do vetor de estados
            if(indEst != -1)
            {
                //guarda o terminal lido e o proximo estado
                sscanf(linha+n, "%c)= %[^\n]", &terminalLido, estadonome);

                //o estado no indice indEst do vetor de estados tem seu vetor de transições guardando o terminal lido
                afds->estados[indEst].transicoes[afds->estados[indEst].tamanhoT].terminal = terminalLido;

                //procura o indice do estado proximo
                indProx = qualEstado(afds, estadonome);

                //se tiver dentro do vetor de estados
                if(indProx != -1)
                {
                    //referencia o proximo estado que o estado do vetor de indice indEst aponta depois de ter feito a transição, atualiza a quantidade de transições feitas
                    afds->estados[indEst].transicoes[afds->estados[indEst].tamanhoT++].proximoEstado = &afds->estados[indProx];
                }
            }
        }
    }

    //fecha o arquivo de entrada
    fclose(entry);
    return 1;

}
