#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 100
#define MAXQ 20
#define MAXF 10
#define MAXA 20

#include "arquivo.h"

///
/// \brief qualEstado, procura por todos os estados guardados do MT o estado que tenha tal nome
/// \param mt, struct com os estados a serem pesquisados
/// \param str, nome do estado que está sendo buscado
/// \return retorna o indice a qual o estado esta dentro do vetor de estados do MT ou -1 se não for encontrado
/// \pre nenhum
/// \post nenhum
///
int qualEstado(MT* mt, char str[])
{
    int i;
    //ate o numero de estados contidos, procura qual indice o estado que carrega esse nome está
    for(i = 0; i < mt->tamanhoE; i++)
        if(!strcmp(mt->estado[i].nome, str))
            return i;
    return -1;
}

///
/// \brief entrada, função que abre o arquivo do nome de entrada e guarda as informações que o MT precisa conter
/// \param s, string com o nome do arquivo a ser aberto
/// \param  mt, struct que ira guardar as informações do MT a ser usado
/// \return retorna 1 se for aberto corretamente ou 0 se não foi aberto corretamente
/// \pre o arquivo de nome s tem que ter sido criado e estar contido no computador
/// \post o  mt conterá cada um das informações do MT que será usado
///
int entrada(char s[], MT *mt)
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
            sscanf(linha, "alfabeto = { %[^}] }", estados);
            for(i = j = 0; i < strlen(estados) ; i++)
            {
                //se não for uma virgula, guarda o alfabeto dentro do vetor alfa de mt
                if(estados[i] != ',')
                    mt->alfa[j++] = estados[i];
            }
            mt->alfa[j++] = '*';
            mt->alfa[j++] = '$';
            mt->alfa[j] = '\0';
        }
        //verifica se a linha vai conter os estados
        else if(linha[0] == 'Q')
        {
            //guarda a quantidade de estados
            sscanf(linha, " Q = %[^\n]", estados);
            int percorre;
            for(percorre = 0; percorre < atoi(estados); percorre ++)
            {
                //cria os estados até a quantidade passada
                sprintf(estadonome, "q%d", percorre);
                strcpy(mt->estado[mt->tamanhoE++].nome, estadonome);
            }
        }
        //verifica se a linha vai conter os estados finais
        else if(linha[0] == 'F')
        {
            //guarda tudo dentro dos {}
            sscanf(linha, " F = { %[^}] }", estados);
            int percorre;
            for(percorre = 0; percorre < strlen(estados); percorre += strlen(estadonome)+1)
            {
                //guarda tudo até a proxima virgula
                sscanf(estados+percorre, " %[^,] ,", estadonome);
                printf("%s\n", estadonome);
                int ind = qualEstado(mt, estadonome);
                //coloca o estado final de mt referenciando o estado no indice ind do vetor de estados
                if(ind != -1)
                    mt->final[mt->tamanhoF++] = &mt->estado[ind];
            }
        }
        //se for as linha de transições
        else if(linha[0] == '(')
        {
            int n;
            int indProx;
            char terminalLido, sobrescrever, direcao, proximoEstado[MAX];
            //scaneia e guarda o nome do estado a fazer a transição
            sscanf(linha, " ( %[^,] ,%n", estadonome, &n);
            //pega o indice em que esse estado esta no vetor de estados
            int indEst = qualEstado(mt, estadonome);
            //se existir o estado dentro do vetor de estados
            if(indEst != -1)
            {
                //guarda o terminal lido e o proximo estado
                sscanf(linha+n, " %c ) = %[^\n]", &terminalLido, estadonome);

                //o estado no indice indEst do vetor de estados tem seu vetor de transições guardando o terminal lido
                mt->estado[indEst].transicoes[mt->estado[indEst].tamanhoT].terminal = terminalLido;

                sscanf(estadonome," ( %[^,] , %c , %c )", proximoEstado, &sobrescrever, &direcao);

                //procura o indice do estado proximo
                indProx = qualEstado(mt, proximoEstado);

                //se tiver dentro do vetor de estados
                if(indProx != -1)
                {
                    //referencia o proximo estado que o estado do vetor de indice indEst aponta depois de ter feito a transição, atualiza a quantidade de transições feitas
                    if(direcao == 'D')
                        mt->estado[indEst].transicoes[mt->estado[indEst].tamanhoT].direcao = 1;
                    else
                        mt->estado[indEst].transicoes[mt->estado[indEst].tamanhoT].direcao = -1;
                    
                    mt->estado[indEst].transicoes[mt->estado[indEst].tamanhoT].sobrescreve = sobrescrever;
                    mt->estado[indEst].transicoes[mt->estado[indEst].tamanhoT++].proximoEstado = &mt->estado[indProx];
                }
            }
        }
    }

    //fecha o arquivo de entrada
    fclose(entry);
    return 1;

}
