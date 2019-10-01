#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "arquivo.h"

void fazArquivoDot(Grafo* grf, FILE* out){

    char type[3];

    if(strcmp(grf->orientado, "sim") == 0){
        fprintf(out, "strict digraph {\n");
        strcpy(type, "->");
    }
    else{
        fprintf(out, "strict graph {\n");
        strcpy(type, "--");
    }

    fprintf(out, "\tgraph [pad=\"0.5\", nodesep=\"1\", ranksep=\"2\"]\n\trankdir=LR;\n");
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
            for(int j = 0; j < grf->nVertices; j++){
                printf("%d %d", i, j);
                if(grf->adjacente[i][j] == 1){
                    printf("I: %d J: %d nomeI: %s nomeJ: %s label: %d\n", i, j, grf->nomes[i].nome, grf->nomes[j].nome, grf->pesos[i][j]);
                    fprintf(out, "\t\"%s\" %s \"%s\"[label=\"%d\",labelfontcolor=black];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->pesos[i][j]);
                    printf("I: %d J: %d nomeI: %s nomeJ: %s label: %s\n", i, j, grf->nomes[i].nome, grf->nomes[j].nome, grf->rotulos[i][j].nome);
                    fprintf(out, "\t\"%s\" %s \"%s\"[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->rotulos[i][j].nome);
                    printf("BYE\n");
                }
            }
        }
    }

    fprintf(out, "}");
}

void leArquivo(FILE* in, FILE* out){

    Grafo* grf;
    char **nomes;
    char linha[500], aux[300], orientado[3];
    int peso, vertices, row, col, EhRotulado;

    while(fgets(linha, 500, in)){

        strtok(linha, "\n");
        printf("LIDO: %s\n", linha);

        if(strncmp(linha, "orientado", 9) == 0){
            sscanf(linha, "orientado=%[^\n]%*c", orientado);
        }
        else if(linha[0] == 'V'){

            if(linha[2] == '{'){

                EhRotulado = 1;
                sscanf(linha, "V={ %[^}] }", aux);
                nomes = (char**)malloc(sizeof(char*)*50);
                
                for(int j = 0; j < 10; j++) nomes[j] = (char*)malloc(sizeof(char)*100);
                int percorre, i, atual = 10;
                
                for(percorre = 0, i = 0; percorre < strlen(aux); percorre += strlen(nomes[i])+1, i++)
                {
                    sscanf(aux+percorre, "%[^,],", nomes[i]);
                }

                nomes = realloc(nomes, i);
                vertices = i;
            }
            else{
                EhRotulado = 0;
                sscanf(linha, "V=%d%*c", &vertices);
            }

            grf = initGrafo(vertices, orientado, nomes, EhRotulado);
        }
        else{

            int percorre;
            sscanf(linha, "(%d,%d):%d%n", &row, &col, &peso, &percorre);
            strcpy(grf->rotulos[row][col].nome, " ");

            //printf("ALO: %s\n", grf->rotulos[row][col].nome);
            if(linha[percorre] == ','){
                printf("ALO");
                sscanf(linha+percorre, ",%[^\n]%*c", aux);
                strcpy(grf->rotulos[row][col].nome, aux);
            }

            grf->adjacente[row][col] = 1;
            //if(strcmp(grf->orientado, "nao") == 0) grf->adjacente[col][row] = 1;
            grf->pesos[row][col] = peso;
            
            printf("I: %d J: %d nomeI: %s nomeJ: %s labelA: %d", row, col, grf->nomes[row].nome, grf->nomes[col].nome, grf->pesos[row][col]);
            printf("labelB: %s\n", grf->rotulos[row][col].nome);
        }
    }

    fazArquivoDot(grf, out);
}