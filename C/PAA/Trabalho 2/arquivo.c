#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

char *orientacao(Grafo* grf){

    return (strcmp(grf->orientado, "sim") == 0)? "digraph" : "graph"; 
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

int qualLinha(char linha[]){

    if(strncmp(linha, "orientado", 9) == 0) {
        printf("%s\n", linha);
        return LINHA_ORIENTADO;
    }
    else if(linha[0] == 'V'){
        printf("linha: %s", linha);
        
        if(strncmp(linha, "V={", 3) == 0) {
            printf("linha: %s", linha);
            return LINHA_ROTULO_VERTICES;
        }
        else{
            printf("linha: %s", linha);
            return LINHA_N_VERTICES;
        }
    }
    else{
        
    } return LINHA_ARESTAS;
}

void alocaCampos(Grafo* grf){

    grf->pesos = init(grf->nVertices);
    grf->adjacente = init(grf->nVertices);
    grf->rotulos = initLabels(grf->nVertices);
}

Grafo* linha_orientado(char linha[]){
    
    Grafo* grf;
    char orientado[4];

    sscanf(linha, "orientado=%[^\n]%*c", orientado);
    grf = initGrafo(orientado);

    return grf;
}

void linha_n_vertices(char linha[], Grafo* grf){
    
    grf->EhRotulado = 0;
    sscanf(linha, "V=%d%*c", &grf->nVertices);

    alocaCampos(grf);
}

void linha_rotulo_vertices(char linha[], Grafo* grf){

    char aux[300];
    int percorre, i;

    grf->EhRotulado = 1;

    sscanf(linha, "V={ %[^}] }", aux);
    strcat(aux, "\n");

    grf->nVertices = countVirgula(aux);

    grf->nomes = (Label*)malloc(sizeof(Label)*grf->nVertices);
    
    for(percorre = 0, i = 0; percorre < strlen(aux) && i < grf->nVertices; percorre += strlen(grf->nomes[i].nome)+1, i++)
    {
        sscanf(aux+percorre, "%[^,],", grf->nomes[i].nome);
        
        strtok(grf->nomes[i].nome, "\n");
    }

    alocaCampos(grf);
}

void linha_arestas(char linha[], Grafo *grf){

    char aux[300];
    int percorre, row, col, peso;
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

Grafo* leArquivo(FILE* in){

    Grafo* grf = NULL;
    char linha[500];

    while(fgets(linha, 500, in)){
        
        strtok(linha, "\n");

        switch(qualLinha(linha)){
            case 1:
                grf = linha_orientado(linha);
                printf("%s\n", grf->orientado);
                break;
            case 2:
                printf("ALO\n");
                linha_rotulo_vertices(linha, grf);
                if(grf->EhRotulado){
                    printf("%s\n", grf->nomes[0]);
                }
                printf("%d\n", grf->nVertices);
                break;
            case 3:
                linha_n_vertices(linha, grf);
                printf("%d\n", grf->nVertices);
                break;
            case 4:
                linha_arestas(linha, grf);
                printf("%d %d\n", grf->adjacente[0][1], grf->pesos[0][1]);
                break;     
        }
    }

    return grf;
}