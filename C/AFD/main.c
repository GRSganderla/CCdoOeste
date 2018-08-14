#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
#define MAXQ 20
#define MAXF 10
#define MAXA 20

typedef struct transicoes
{
    int estado;
    char terminal;
    int proximoEstado;
}Transicao;

typedef struct afd
{
    char alfa[MAXA];
    char q[MAXQ];
    char finais[MAXF];
    char inicial;
    Transicao trans[MAX];
}AFD;

int entrada(char s[], AFD *afds)
{
    FILE* entry = fopen(s, "r");

    if(entry == NULL)
    {
        printf("Arquivo nao encontrado ou vazio\n");
        return 0;
    }
    
    while(!feof(entry))
    {
        char linha[MAX];
        fgets(linha, MAX, entry);
        int transAtual = 0;

        int i;

        if(memcmp(linha, "alfabeto={", 10) == 0)
        {
            for(i = 0; linha[i+5] != '}' ; i+=2)
                sscanf(linha+10+i,"%c", &afds->alfa[i]);
        }
        else if(memcmp(linha, "inicial=", 8) == 0)
        {
            afds->inicial = linha[i+9] - '0';
        }
        else if(memcmp(linha, "estados={", 9) == 0)
        {

        }
        else if(memcmp(linha, "finais={", 7) == 0)
        {

        }
        else if(linha[0] == '(')
        {
            int i = 2;
            Transicao aux;
            aux.estado = 0;

            while(linha[i] != ',')
            {
                aux.estado = aux.estado * 10 + linha[i] - '0';
                i++;
            }
            i++;
            aux.terminal = linha[i];
            i+= 4;

            aux.proximoEstado = 0;
            while(linha[i] != ',')
            {
                aux.proximoEstado = aux.proximoEstado*10 + linha[i] - '0';
            }

            afds->trans[transAtual] = aux;
            transAtual++;
        }
    }

    fclose(entry);
    return 1;
    
}

int main(int argc, char const *argv[])
{
    AFD afd = {};
    
    if(entrada( (char*) argv[1], &afd))
    {
        //leiaAFD(afd);
        printf("%c\n", afd.trans[0].estado);
    }
    return 0;
}