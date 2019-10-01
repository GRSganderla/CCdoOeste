#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "algoritmos.h"
#include "arquivo.h"

void fazArquivoAlg(Grafo* grf, FILE* out, int** res){

    char type[4];

    if(strcmp(grf->orientado, "sim") == 0){
        fprintf(out, "strict digraph {\n");
        strcpy(type, "->");
    }
    else{
        fprintf(out, "strict graph {\n");
        strcpy(type, "--");
    }

    fprintf(out, "\tgraph [pad=\"0.5\", nodesep=\"1\", ranksep=\"2\"]\n\trankdir=LR;\nnode[style=rounded];\n");
    if(grf->EhRotulado == 0){

        for(int i = 0; i < grf->nVertices; i++){
            for(int j = 0; j < grf->nVertices; j++){

                if(res[i][j] == 1){
                    fprintf(out, "\t%d %s %d[color=red];\n", i, type, j);
                }

                if(grf->adjacente[i][j] == 1){
                    fprintf(out, "\t%d %s %d[label=\"%d\",labelfontcolor=black];\n", i, type, j, grf->pesos[i][j]);
                    fprintf(out, "\t%d %s %d[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", i, type, j, grf->rotulos[i][j].nome);
                }
            }
        }
    }
    else{
        for(int i = 0; i < grf->nVertices; i++){

            fprintf(out, "\t\"%s\" [shape=box];\n", grf->nomes[i].nome);
        }
        for(int i = 0; i < grf->nVertices; i++){
            for(int j = 0; j < grf->nVertices; j++){

                if(res[i][j] == 1){
                    fprintf(out, "\t\"%s\" %s \"%s\"[color=red];\n", grf->nomes[i].nome, type, grf->nomes[j].nome);
                }

                if(grf->adjacente[i][j] == 1){
                    
                    fprintf(out, "\n");
                    fprintf(out, "\t\"%s\" %s \"%s\"[label=\"%d\",labelfontcolor=black];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->pesos[i][j]);
                    fprintf(out, "\t\"%s\" %s \"%s\"[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->rotulos[i][j].nome);

                }
            }
        }
    }

    fprintf(out, "}");
}

void fazArquivoDot(Grafo* grf, FILE* out){

    char type[4];

    if(strcmp(grf->orientado, "sim") == 0){
        fprintf(out, "strict digraph {\n");
        strcpy(type, "->");
    }
    else{
        fprintf(out, "strict graph {\n");
        strcpy(type, "--");
    }

    fprintf(out, "\tgraph [pad=\"0.5\", nodesep=\"1\", ranksep=\"2\"]\n\trankdir=LR;\nnode[style=rounded];\n");
    if(grf->EhRotulado == 0){
        for(int i = 0; i < grf->nVertices; i++){
            for(int j = 0; j < grf->nVertices; j++){
                if(grf->adjacente[i][j] == 1){
                    fprintf(out, "\t%d %s %d[label=\"%d\",labelfontcolor=black];\n", i, type, j, grf->pesos[i][j]);
                    fprintf(out, "\t%d %s %d[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", i, type, j, grf->rotulos[i][j].nome);
                }
            }
        }
    }
    else{
        for(int i = 0; i < grf->nVertices; i++){

            fprintf(out, "\t\"%s\" [shape=box];\n", grf->nomes[i].nome);
        }
        for(int i = 0; i < grf->nVertices; i++){
            for(int j = 0; j < grf->nVertices; j++){
                if(grf->adjacente[i][j] == 1){
                    
                    fprintf(out, "\n");
                    fprintf(out, "\t\"%s\" %s \"%s\"[label=\"%d\",labelfontcolor=black];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->pesos[i][j]);
                    fprintf(out, "\t\"%s\" %s \"%s\"[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->rotulos[i][j].nome);

                }
            }
        }
    }

    fprintf(out, "}");
}

int countVirgula(char *nome){

    int i = 0, count = 0;

    while(nome[i] != '\0'){
        if(nome[i] == ',')
            count++;
        i++;
    }

    return count+1;
}

void leArquivo(FILE* in){

    Grafo* grf;
    char linha[500], aux[300], orientado[3];
    int row, col, peso;

    while(fgets(linha, 500, in)){

        strtok(linha, "\n");
        printf("LIDO: %s\n", linha);

        if(strncmp(linha, "orientado", 9) == 0){
            sscanf(linha, "orientado=%[^\n]%*c", orientado);
            grf = initGrafo(orientado);
        }
        else if(linha[0] == 'V'){

            if(linha[2] == '{'){

                grf->EhRotulado = 1;

                sscanf(linha, "V={ %[^}] }", aux);
                strcat(aux, "\n");

                grf->nVertices = countVirgula(aux);

                grf->nomes = (Label*)malloc(sizeof(Label)*grf->nVertices);
                
                int percorre, i;
                
                for(percorre = 0, i = 0; percorre < strlen(aux) && i < grf->nVertices; percorre += strlen(grf->nomes[i].nome)+1, i++)
                {
                    sscanf(aux+percorre, "%[^,],", grf->nomes[i].nome);
                    
                    strtok(grf->nomes[i].nome, "\n");
                }
            }
            else{
                grf->EhRotulado = 0;
                sscanf(linha, "V=%d%*c", &grf->nVertices);
            }

            grf->pesos = init(grf->nVertices);
            grf->adjacente = init(grf->nVertices);
            grf->rotulos = initLabels(grf->nVertices);
        }
        else{

            int percorre;
            sscanf(linha, "(%d,%d):%d%n", &row, &col, &peso, &percorre);

            if((row >= 0 && row < grf->nVertices) && (col >= 0 && col < grf->nVertices))
            {
                strcpy(grf->rotulos[row][col].nome, " ");

                if(linha[percorre] == ','){
                    sscanf(linha+percorre, ",%[^\n]%*c", aux);
                    strcpy(grf->rotulos[row][col].nome, aux);
                }

                grf->adjacente[row][col] = 1;
                grf->pesos[row][col] = peso;
            }
        }
    }

    char nomeArq[200], dot[200];

    printf("Entre com o arquivo de saida (sem .dot): ");
    scanf("%s%*c", nomeArq);
    strcpy(dot, nomeArq);

    strcat(dot, ".dot");

    FILE* out = fopen(dot, "w+");

    fazArquivoDot(grf, out);

    strcat(nomeArq, "busca.dot");

    FILE* busca = fopen(nomeArq, "w+");

    int **res = buscaEmProfundidade(grf, 0);

    for(int i = 0; i < grf->nVertices; i++){

        for(int j = 0; j < grf->nVertices; j++){

            if(res[i][j] == 1){

                printf("%d -> %d\n", i, j);
            }
        }
    }

    fazArquivoAlg(grf, busca, res);
}