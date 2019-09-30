#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct label {
    char nome[200];
} Label;

char nomeArq[] = "grafoOrientado.txt";

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

void fazArquivoDot(int **grafo, float** pesos, Label** labels, int nNomeado, int vertices, char orientado[]){

    FILE* out = fopen("out1.dot", "w");
    char type[3] = { };

    if(strcmp(orientado, "sim") == 0){
        fprintf(out, "digraph {\n");
        strcpy(type, "->");
    }
    else{
        fprintf(out, "graph {\n");
        strcpy(type, "--");
    }

    fprintf(out, "rankdir=LR;");
    if(nNomeado == 1){
        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                if(grafo[i][j] == 1){
                    fprintf(out, "\t%d %s %d[headlabel=\"%s\",label=\"%s\"];\n", i, type, j, labels[i][j].nome, pesos[i][j]);
                }
            }
        }
    }

    fprintf(out, "}");
}

int main(){

    int **grafo, vertices, row, col, nNomeado;
    float peso,  **pesos;
    char linha[200], orientado[4], label[200];
    Label **labels;
    FILE* arq = fopen(nomeArq, "r+");

    while(fgets(linha, 200, arq)){

        printf("Lido: %s\n", linha);

        if(strncmp(linha, "orientado", 9) == 0){

            printf("orientado? ");
            sscanf(linha, "orientado=%[^\n]%*c", orientado);
            printf("%s\n", orientado);
        }
        else if(linha[0] == 'V'){

            printf("vertices? ");

            if(linha[3] == '{'){
                //bla
            }
            else{
                nNomeado = 1;
                sscanf(linha, "V=%d%*c", &vertices);
                printf("%d\n", vertices);
                grafo = initGrafo(vertices);
                pesos = initPesos(vertices);
                labels = initLabels(vertices);
            }
        }
        else{

            sscanf(linha, "(%d,%d):%f,%{^\n]%*c", &row, &col, &peso, label);
            grafo[row][col] = 1;
            if(strcmp(orientado, "nao") == 0) grafo[col][row] = 1;
            pesos[row][col] = peso;
            strcpy(labels[row][col].nome, label);
        }
    }

    printGrafo(grafo, vertices);
    printPesos(pesos, vertices);
    printLabel(labels, vertices);

    fazArquivoDot(grafo, pesos, labels, nNomeado, vertices, orientado);

    return 0;
}