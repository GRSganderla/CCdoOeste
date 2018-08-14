#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
#define MAXQ 20
#define MAXF 10
#define MAXA 20

struct estado;

typedef struct transicao
{
    char terminal;
    struct estado *proximoEstado;
}Transicao;

typedef struct estado
{
    char nome[MAX];
    Transicao transicoes[MAX];
    int tamanhoT;
}Estado;

typedef struct afd
{
    char alfa[MAXA];
    Estado estados[MAXQ];
    int tamanhoE;
    int tamanhoF;
    Estado *finais[MAXF];
    Estado *inicial;
}AFD;

int qualEstado(AFD* afd, char str[])
{
    int i;
    for(i = 0; i < afd->tamanhoE; i++)
        if(!strcmp(afd->estados[i].nome, str))
            return i;
    return -1;
}

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
        char linha[MAX], estados[MAX], estadonome[MAX];
        fgets(linha, MAX, entry);
        int transAtual = 0;

        int i, j;

        if(memcmp(linha, "alfabeto={", 10) == 0)
        {
            sscanf(linha, "alfabeto={ %[^}] }", estados);
            for(i = j = 0; i < strlen(estados) ; i++)
            {
                if(estados[i] != ',')
                    afds->alfa[j++] = estados[i];
            }
            afds->alfa[j] = '\0';
        }
        else if(memcmp(linha, "estados={", 9) == 0)
        {
            sscanf(linha, "estados={ %[^}] }", estados);
            int percorre;
            for(percorre = 0; percorre < strlen(estados); percorre += strlen(estadonome)+1)
            {
                sscanf(estados+percorre, "%[^,],", estadonome);
                strcpy(afds->estados[afds->tamanhoE++].nome, estadonome);
            }
        }
        else if(memcmp(linha, "finais=", 7) == 0)
        {
            sscanf(linha, "finais={ %[^}] }", estados);
            int percorre;
            for(percorre = 0; percorre < strlen(estados); percorre += strlen(estadonome)+1)
            {
                sscanf(estados+percorre, "%[^,],", estadonome);
                int ind = qualEstado(afds, estadonome);
                if(ind != -1)
                    afds->finais[afds->tamanhoF++] = &afds->estados[ind];
            }
        }
        else if(memcmp(linha, "inicial=", 8) == 0)
        {
            sscanf(linha, "inicial=%[^\n]%*c", estadonome);
            int indI = qualEstado(afds, estadonome);
            if(indI != -1)
                afds->inicial = &afds->estados[indI];
        }
        else if(linha[0] == '(')
        {
            int n;
            int indProx;
            char terminalLido;
            sscanf(linha, "(%[^,],%n", estadonome, &n);
            int indEst = qualEstado(afds, estadonome);
            if(indEst != -1)
            {
                sscanf(linha+n, "%c)= %[^\n]", &terminalLido, estadonome);
                afds->estados[indEst].transicoes[afds->estados[indEst].tamanhoT].terminal = terminalLido;

                indProx = qualEstado(afds, estadonome);

                if(indProx != -1)
                    afds->estados[indEst].transicoes[afds->estados[indEst].tamanhoT++].proximoEstado = &afds->estados[indProx];
            }
        }
    }

    fclose(entry);
    return 1;

}

int alfabetoCMP(AFD afd, char terminal)
{
    int i;
    for(i =0; i < strlen(afd.alfa); i++)
        if(afd.alfa[i] == terminal)
            return 1;

    return 0;
}

Estado* fazerTrans(AFD afd, Estado* atual, char terminal)
{
    int i;
    for(i = 0; i < atual->tamanhoT; i++)
        if(atual->transicoes[i].terminal == terminal)
            return atual->transicoes[i].proximoEstado;

    return NULL;
}

int ehFinal(AFD* afd, Estado* atual)
{
    int i;

    for(i = 0; i < afd->tamanhoF; i++)
        if(!strcmp(afd->finais[i]->nome, atual->nome))
            return 1;

    return 0;
}

int verificaPalavra(AFD afd, char str[], Estado* atual)
{
    if(!atual) return 0;

    char terminal = str[0];

    printf("[%s] %s\n", atual->nome, str);

    if(terminal == '\0') return ehFinal(&afd, atual);
    if(!alfabetoCMP(afd, terminal)) return 0;

    return verificaPalavra(afd, str+1, fazerTrans(afd, atual, terminal));
}

void aceitaOUnao(AFD afd, char str[])
{
    if(verificaPalavra(afd, str, afd.inicial))
        printf("ACEITA\n");
    else
        printf("REJEITA\n");
}

int etois(Estado *alvo)
{
    return atoi(alvo->nome+1);
}

void printaLinhas(AFD* afd, char nTerminal[], Estado* atual)
{
    int i;

    int local = etois(atual);

    printf("%c -> ", nTerminal[local]);

    for(i = 0; i < atual->tamanhoT; i++)
    {
        printf("%c%c ", atual->transicoes[i].terminal, nTerminal[etois(atual->transicoes[i].proximoEstado)]);

        if(atual->tamanhoT > i + 1)
        {
            printf("| ");

        }
    }

    if(ehFinal(afd, atual))
        printf("| @");

    printf("\n");
}

void fazGramatica(AFD* afd)
{
    int i, letra, nTerminalInd;
    char nTerminal[MAXQ];

    nTerminalInd = etois(afd->inicial);

    nTerminal[nTerminalInd] = 'S';

    for(i = letra = 0; i < afd->tamanhoE; i++)
    {
        if(strcmp(afd->estados[i].nome, afd->inicial->nome))
        {
            nTerminalInd = etois(&afd->estados[i]);
            nTerminal[nTerminalInd] = 'A' + letra++;
        }
    }

    printaLinhas(afd, nTerminal, afd->inicial);

    for(i = 0; i < afd->tamanhoE; i++)
    {
        if(strcmp(afd->estados[i].nome, afd->inicial->nome))
        {
            printaLinhas(afd, nTerminal, &afd->estados[i]);
        }
    }
}

int main(int argc, char const *argv[])
{
    AFD afd = {};
    afd.tamanhoE = 0;
    afd.tamanhoF = 0;

    if(entrada( (char*) argv[1], &afd))
    {
        char s[MAX], choice;
        printf("Deseja mostrar a Gramatica?\n");
        scanf("%c", &choice);
        fflush(stdin);

        if(choice == 'S');
            fazGramatica(&afd);

        printf("\nEntre com uma palavra a ser testada pelo AFD: ");

        scanf("%[^\n]%*c", s);

        while(s[0] != '\0')
        {
            printf("Derivacao da palavra:\n");
            aceitaOUnao(afd, s);

            printf("\nEntre com uma palavra a ser testada pelo AFD: ");
            scanf("%[^\n]%*c", s);
        }
    }

    return 0;
}
