#include "algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void visita_buscaProf(int vertice, Profundidade* busca, int n, int **ordem){

    busca[vertice].cor = 'C';
    timestamp++;
    busca[vertice].d = timestamp;

    for(int i = 0; i < n; i++){

        if(busca[vertice].adj[i] == 1 && busca[i].cor == 'B'){

            ordem[vertice][i] = 1;
            busca[i].pred = vertice;
            visita_buscaProf(i, busca, n, ordem);
        }
    }

    busca[vertice].cor = 'P';
    timestamp++;
    busca[vertice].f = timestamp; 
}

void buscaEmProfundidade(Grafo* grf, int inicial, int** res){

    Profundidade* busca = (Profundidade*)malloc(sizeof(Profundidade)*grf->nVertices);

    for(int i = 0; i < grf->nVertices; i++){
        
        busca[i].cor = 'B';
        busca[i].pred = -1;
        busca[i].adj = (int*)malloc(sizeof(int)*grf->nVertices);

        for(int j = 0; j < grf->nVertices; j++){

            busca[i].adj[j] = (grf->adjacente[i][j] == 1);
        }
    }

    timestamp = 0;
    int i = 0;

    if(busca[inicial].cor == 'B'){

        visita_buscaProf(inicial, busca, grf->nVertices, res);

    }

    for(int i = 0; i < grf->nVertices; i++){

        if(busca[i].cor == 'B'){

            visita_buscaProf(i, busca, grf->nVertices, res);

        }
    }
}

int vertice_origem(Grafo* g){

    int vertice;
    system("clear");


    printf("Vertices={");
    for(int i = 0; i < g->nVertices; i++){

        printf(" %d", i);
        if(g->EhRotulado){
            printf(": %s", g->nomes[i].nome);
        }

        (i < g->nVertices-1)? printf(","): printf("}\n");
    }

    do {
        printf("Entre com o vertice de origem: ");
        scanf("%d%*c", &vertice);
    }while(vertice < 0 && vertice > g->nVertices);

    return vertice;
}

int buscaEmLargura(Grafo* g, int origem, int **res){

    Fila* q = start();
    int u, i, j;

    Largura* l = (Largura*)malloc(sizeof(Largura)*g->nVertices);

    for(i = 0; i < g->nVertices; i++){

        if(i != origem){

            l[i].cor = 'B';
            l[i].d = 999999;
            l[i].pred = -1;

            l[i].adj = (int*)malloc(sizeof(int)*g->nVertices);

            for(j = 0; j < g->nVertices; j++){
                l[i].adj[j] = (g->adjacente[i][j] == 1);
            }
        }
    }

    l[origem].cor = 'C';
    l[origem].pred = -1;
    l[origem].d = 0;
    l[origem].adj = (int*)malloc(sizeof(int)*g->nVertices);

    for(j = 0; j < g->nVertices; j++){
        l[origem].adj[j] = (g->adjacente[origem][j] == 1);
    }
    enqueue(q, origem);

    while(!empty(q)){

        imprime(q);
        u = dequeue(q);

        if(u == -1) return 0;

        for(i = 0; i < g->nVertices; i++){

            if(l[u].adj[i] && l[i].cor == 'B'){
                
                res[u][i] = 1;
                l[i].cor = 'C';
                l[i].d = l[u].d + 1;
                l[i].pred = u;
                enqueue(q, i);
            }
        }

        l[u].cor = 'P';
    }

    return 1;
}

BellmanFord* inicializaOrigem(int n, int origem){

    BellmanFord* bf = (BellmanFord*)malloc(sizeof(BellmanFord)*n);

    for(int i = 0; i < n; i++){

        if(i != origem){
            bf[i].d = 99999999;
            bf[i].pred = -1;
        }
    }

    bf[origem].d = 0;
    bf[origem].pred = -1;

    return bf;
}

void relax(BellmanFord* bf, int** pesos, int u, int v){

    if(bf[v].d > (bf[u].d + pesos[u][v])){
        bf[v].d = bf[u].d + pesos[u][v];
        bf[v].pred = u;
    }
}

int BellmanFordAlg(Grafo* g, int origem, int **res){

    BellmanFord* bf = inicializaOrigem(g->nVertices, origem);
    
    int i, j, k;

    for(i = 0; i < g->nVertices -1; i++){
        for(k = 0; k < g->nVertices; k++){
            for(j = 0; j < g->nVertices; j++){
                if(g->adjacente[k][j] == 1)
                    relax(bf, g->pesos, k, j);
            }
        }
    }

    for(i = 0; i < g->nVertices; i++){
        for(j = 0; j < g->nVertices; j++){
            if(g->adjacente[i][j] == 1 && (bf[j].d > bf[i].d + g->pesos[i][j])){
                return 0;
            }
        }
    }

    for(i = 0; i < g->nVertices; i++){
        for(j = 0; j < g->nVertices; j++){
            if(g->adjacente[i][j] && (bf[j].pred == i)){

                res[i][j] = bf[j].d;
            }
        }
    }

    getchar();

    free(bf);

    return 1;
}

///
/// \brief intercala, função auxiliar do algoritmo de ordenação Merge Sort
/// \param vet, vetor a ser ordenado
/// \param inicio, indice do inicio da parte do vetor separada
/// \param meio, indice do meio do vetor partido
/// \param fim, tamanho maximo da partição
/// \pre nenhuma
/// \post nenhuma
///
void intercala(Aresta* vet, int inicio, int meio, int fim)
{
    int i, j, k;
    Aresta *vet_aux;

    //aloca o vetor
    vet_aux = malloc((fim-inicio)*sizeof(Aresta));

    i = inicio; j = meio; k = 0;

    //enquanto não for o meio ou o fim
    while( i < meio && j < fim)
    {
        //se o vetor J é maior ou igual a o vetor I, adiciona o valor de I em K, aumenta ambos
        if(vet[i].peso <= vet[j].peso)
            vet_aux[k++] = vet[i++];
        else
        {
            //se não é menor ou igual, adiciona o valor de J em K, aumenta ambos
            vet_aux[k++] = vet[j++];
        }
    }

    //enquanto não for o meio, adiciona I em K, aumenta ambos
    while (i < meio)
        vet_aux[k++] = vet[i++];

    //enquanto não for o meio, adiciona J em K, aumenta ambos
    while (j < fim)
        vet_aux[k++] = vet[j++];

    //adiciona no vetor original, o vetor K
    for(i = inicio; i < fim; i++)
        vet[i] = vet_aux[i-inicio];

    //libera o vetor auxiliar
    free(vet_aux);
}

///
/// \brief mergeSortN, algoritmo de ordenação por metodo de separar, ordenar e reajuntar e ordenar...
/// \param v, vetor a ser ordenado
/// \param inicio, indice do inicio do vetor
/// \param fim, tamanho maximo do vetor
/// \pre nenhuma
/// \post nenhuma
///
void mergeSortN(Aresta* v, int inicio, int fim)
{
    if( inicio < fim - 1)
    {
        //chama recursivamente ate tiver um vetor separado com 2 valores
        int meio = (inicio + fim) / 2;
        mergeSortN(v, inicio, meio);
        mergeSortN(v, meio, fim);
        intercala(v, inicio, meio, fim);
    }
}

int findV(int alvo, int *conj){
    
    if(conj[alvo] < 0) {
        return alvo;
    }else{
        return findV(conj[alvo], conj);
    }
}

int diferente(int u, int v, int *conj){
    
    if(findV(u, conj) == u && findV(v, conj) == v)
        return 1;
    else{
        int a = (conj[u] < 0)? u : findV(conj[u], conj), b = (conj[v] < 0)? v: findV(conj[v], conj);
        
        if(a != b) return 1;

        return 0;
    }
}

void troca(int u, int v, int *conj){
    int temp;

    temp = conj[u];
    conj[u] = v;
    conj[v] += temp;
}

void Uniao(int u, int v, int *conj){

    int temp;

    if(findV(u, conj) == u && findV(v, conj) == v){

        if(conj[u] >= conj[v]){
            troca(u, v, conj);
        }else{
            troca(v, u, conj); 
        }
    }else{

        int a = findV(u, conj), b = findV(v, conj);
        if(conj[a] >= conj[b]){
            troca(a, b, conj);
        }else{
            troca(b, a, conj); 
        }
    }
}

int jaExiste(int i, int j, int peso, Aresta* e, int n){

    for(int k = 0; k < n; k++){

        if(((e[k].u == i && e[k].v == j) || (e[k].u == j && e[k].v == i)) && e[k].peso == peso) return 1;
    }

    return 0;
}

Aresta* fazAresta(Grafo* g, int *n){

    Aresta* novo = (Aresta*)malloc(sizeof(Aresta)*g->nVertices*g->nVertices);

    int i, j, k = 0;

    for(i = 0; i < g->nVertices; i++){
        for(j = 0; j < g->nVertices; j++){
            if(g->adjacente[i][j] == 1 && !jaExiste(i, j, g->pesos[i][j], novo, k)){
                novo[k].u = i;
                novo[k].v = j;
                novo[k++].peso = g->pesos[i][j];
            }
        }
    }

    *n = k;

    novo = (Aresta*)realloc(novo, sizeof(Aresta)*k);

    return novo;
}

int KruskalAlgm(Grafo* g, int **res){

    int *conj = (int*)malloc(sizeof(int)*g->nVertices);

    for(int k = 0; k < g->nVertices; k++) conj[k] = -1;

    Kruskal* k = (Kruskal*)malloc(sizeof(Kruskal));

    int i, j, n, ki = 0;
    Aresta* E = fazAresta(g, &n);
    k->A = (Aresta*)malloc(sizeof(Aresta)*n);

    mergeSortN(E, 0, n);

    for(i = 0 ; i < n; i++){

        if(diferente(E[i].u, E[i].v, conj)){
            k->A[ki].u = E[i].u;
            k->A[ki].v = E[i].v;
            k->A[ki++].peso = E[i].peso;
            Uniao(E[i].u, E[i].v, conj);
        }
    }

    k->A = (Aresta*)realloc(k->A, sizeof(Aresta)*ki);
    for(i = 0; i < ki; i++){
        res[k->A[i].u][k->A[i].v] = k->A[i].peso;
    }

    free(k);
    free(E);

    return 1;
}

int houverNaoConhecidos(Prim* p, int n){

    int i;

    for(i = 0; i < n; i++){
        
        if(p[i].conhecido == 0) return 1;
    }

    return 0;
}

int menorCusto(Prim* p, int n){

    int i, menorVal = 99999, indMenor = -1;

    for(i = 0; i < n; i++){
        
        if(p[i].conhecido == 0){
            
            if(p[i].key < menorVal){
                indMenor = i;
                menorVal = p[i].key;
            }
        }
    }

    return indMenor;
}

int procuraV(Prim* p, int n, int alvo){

    return !(p[alvo].conhecido);
}

int PrimAlgm(Grafo* g, int r, int **res){

    Prim *p = (Prim*)malloc(sizeof(Prim)*g->nVertices);

    int i, j, u, n = g->nVertices;

    for(i = 0; i < n; i++){

        p[i].conhecido = 0;
        p[i].key = 99999999;

        p[i].pred = -1;
        p[i].adj = (int*)malloc(sizeof(int)*n);

        for(j = 0; j < g->nVertices; j++){
            p[i].adj[j] = (g->adjacente[i][j] == 1);
        }
    }

    p[r].key = 0;
    p[r].pred = -1;

    while(houverNaoConhecidos(p, n)){

        u = menorCusto(p, n);

        if(u == -1) return 0;
        p[u].conhecido = 1;

        for(i = 0; i < n; i++){

            if(p[u].adj[i] == 1){

                if(procuraV(p, n, i) && (g->pesos[u][i] < p[i].key)){

                    p[i].pred = u;
                    p[i].key = g->pesos[u][i];
                }
            }
        }
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(p[j].pred == i){
                res[i][j] = p[j].key;
            }
        }
    }

    free(p);
    
    return 1;
}