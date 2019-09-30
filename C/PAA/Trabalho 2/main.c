#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct label {
    char *nome;
} Label;

typedef struct grafo{
    int **grafo, vertices, nNomeado;
    float peso,  **pesos;
    char linha[200], orientado[4], label[200];
    Label **rotulos, *nomes;
} Grafo;

char nomeArq[] = "grafoNOrientado.txt";

int ** initGrafo(int v){

    int ** graf = (int**)malloc(sizeof(int*)*v);

    for(int i = 0; i < v; i++){

        graf[i] = (int*)malloc(sizeof(int)*v);
        for(int j = 0; j < v; j++){

            graf[i][j] = 0;
        }
    }

    return graf;
}

float ** initPesos(int v){

    float ** pesos = (float**)malloc(sizeof(float*)*v);

    for(int i = 0; i < v; i++){

        pesos[i] = (float*)malloc(sizeof(float)*v);
        for(int j = 0; j < v; j++){

            pesos[i][j] = 0;
        }
    }

    return pesos;
}

Label** initLabels(int v){

    Label** lab = (Label**)malloc(sizeof(Label*)*v);

    for(int i = 0; i < v; i++){

        lab[i] = (Label*)malloc(sizeof(Label)*v);

        for(int j = 0; j < v; j++){
            lab[i][j].nome = (char *)malloc(sizeof(char)*v);
        }
    }

    return lab;
}

void printGrafo(int** grafo, int v){

    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            printf("[%d][%d] = %d\n", i, j, grafo[i][j]);
        }
    }
}

void printPesos(float** pesos, int v){

    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            printf("[%d][%d] = %f\n", i, j, pesos[i][j]);
        }
    }
}

void printLabel(Label** lab, int v){

    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            printf("[%d][%d] = %f\n", i, j, lab[i][j].nome);
        }
    }
}

void fazArquivoDot(int **grafo, float** pesos, Label** labels, Label *nomes, int nNomeado, int vertices, char orientado[]){

    FILE* out = fopen("out1.dot", "w");
    char type[3];

    if(strcmp(orientado, "sim") == 0){
        fprintf(out, "strict digraph {\n");
        strcpy(type, "->");
    }
    else{
        fprintf(out, "strict graph {\n");
        strcpy(type, "--");
    }

    fprintf(out, "\tgraph [pad=\"0.5\", nodesep=\"1\", ranksep=\"2\"]\n\trankdir=LR;\n");
    if(nNomeado == 1){
        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                if(grafo[i][j] == 1){
                    fprintf(out, "\t%d %s %d[label=\"%.2f\",labelfontcolor=black];\n", i, type, j, pesos[i][j]);
                    fprintf(out, "\t%d %s %d[taillabel=\"%s\",labeldistance=9,labelfontcolor=blue,labelangle=-5];\n", i, type, j, labels[i][j].nome);
                }
            }
        }
    }
    else{
        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                if(grafo[i][j] == 1){
                    fprintf(out, "\t\"%s\" %s \"%s\"[label=\"%.2f\",labelfontcolor=black];\n", nomes[i], type, nomes[j], pesos[i][j]);
                    fprintf(out, "\t\"%s\" %s \"%s\"[taillabel=\"%s\",labeldistance=9,labelfontcolor=blue,labelangle=-5];\n", nomes[i], type, nomes[j], labels[i][j].nome);
                }
            }
        }
    }

    fprintf(out, "}");
}

int main(){

    int **grafo, vertices, row, col, nNomeado;
    float peso,  **pesos;
    char linha[200], orientado[4], aux[500];
    Label **labels, *nomes;
    FILE* arq = fopen(nomeArq, "r+");

    while(fgets(linha, 200, arq)){

        if(strncmp(linha, "orientado", 9) == 0){
            sscanf(linha, "orientado=%[^\n]%*c", orientado);
        }
        else if(linha[0] == 'V'){

            if(linha[2] == '{'){

                sscanf(linha, "V={ %[^}] }", aux);
                nomes = (Label*)malloc(sizeof(Label)*10);
                for(int j = 0; j < 10; j++) nomes[j].nome = (char*)malloc(sizeof(char)*300);
                int percorre, i;
                for(percorre = 0, i = 0; percorre < strlen(aux); percorre += strlen(nomes[i].nome)+1, i++)
                {
                    sscanf(aux+percorre, "%[^,],", nomes[i].nome);
                    if(i >= 10){
                        nomes = realloc(nomes, i);
                    }
                }
                vertices = i;
            }
            else{
                nNomeado = 1;
                sscanf(linha, "V=%d%*c", &vertices);
            }

            grafo = initGrafo(vertices);
            pesos = initPesos(vertices);
            labels = initLabels(vertices);
        }
        else{

            sscanf(linha, "(%d,%d):%f,%[^\n]%*c", &row, &col, &peso, aux);
            printf("[%f]", peso);
            grafo[row][col] = 1;
            if(strcmp(orientado, "nao") == 0) grafo[col][row] = 1;
            pesos[row][col] = peso;
            printf("{%f}", pesos[row][col]);
            strcpy(labels[row][col].nome, aux);
        }
    }

    //printGrafo(grafo, vertices);
    //printPesos(pesos, vertices);
    //printLabel(labels, vertices);

    fazArquivoDot(grafo, pesos, labels, nomes, nNomeado, vertices, orientado);

    return 0;
}