#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include "arquivo.h"
#include "grafo.h"
#include "fila.h"

// estrutura para o algoritmo de profundidade
typedef struct profundidade{
    // cor do vertice
    char cor;
    // vertice pai desse vertice
    int pred;
    // tempo de descoberta e de final de exploração
    int d, f;
    // vertices adjacentes a esse vertice
    int *adj;

} Profundidade;

// estrutura para o algoritmo de largura
typedef struct largura{

    // cor do vertice
    char cor;
    // vertice que precede esse vertice
    int pred;
    // distancia do nó origem
    int d;
    // vertices adjacentes
    int *adj;
} Largura;

// estrutura para o algoritmo de Bellman-Ford
typedef struct bellmanford {
    // peso para chegar nesse vertice
    int d;
    // vertice que precede esse
    int pred;
} BellmanFord;

// estrutura para os algoritmos de arvore geradora minima
typedef struct aresta {
    // vertice de origem da aresta, vertice de destino da aresta
    int u, v;
    // peso da aresta
    int peso;
} Aresta;

// estrutura para o algoritmo de Prim
typedef struct prim{
    // se o vertice ja foi conhecido antes
    int conhecido;
    // valor para chegar a esse vertice
    int key;
    // vertice que precede esse
    int pred;
    // vertices adjacentes
    int *adj;
} Prim;

// variavel para guardar o tempo de descoberta para o algoritmo de profundidade
int timestamp;

/**
 * @brief  função do algoritmo de busca em profundidade, que gera um caminho a partir da descoberta dos vertices adjacentes do vertice inicial
 * @param  grf: grafo a ser feito a busca
 * @param  inicial: vertice escolhido para ser o inicio da busca
 * @param  res: matriz resultado do caminho feito pela busca
 * @retval None
 */
void buscaEmProfundidade(Grafo* grf, int inicial, int** res);

/**
 * @brief  função que visita o vertice e atualiza os campos dele, e continua a busca a partir dele
 * @param  vertice: vertice que ta sendo visitado
 * @param  busca: estrutura que guarda a instancia do algoritmo de busca em profundidade atual
 * @param  n: quantidade de vertices
 * @param  **ordem: matriz que guarda o resultado do caminho
 * @retval None
 */
void visita_buscaProf(int vertice, Profundidade* busca, int n, int **ordem);

/**
 * @brief  função do algoritmo de busca em largura, que gera um caminho a partir dos adjacentes do vertice origem
 * @param  g: grafo a ser feito a busca
 * @param  origem: vertice de origem da busca
 * @param  res: matriz de resultado do caminho
 * @retval 
 */
int buscaEmLargura(Grafo* g, int origem, int** res);

/**
 * @brief  função do algoritmo de Bellman-Ford, para calcular o menor caminho a partir de um vertice de origem
 * @param  g: grafo a ser buscado o menor caminho
 * @param  origem: vertice de origem da busca
 * @param  res: matriz de resultado do menor caminho
 * @retval 1 se o algoritmo foi realizado com sucesso, 0 se não
 */
int BellmanFordAlg(Grafo* g, int origem, int** res);

/**
 * @brief  função auxiliar do metodo do Bellman-Ford, que verifica o menor caminho
 * @param  bf: estrutura que guarda a instância do algoritmo em execução
 * @param  pesos: matriz que contem os pesos de cada aresta
 * @param  u: vertice de origem da aresta
 * @param  v: vertice de destino da aresta
 * @retval None
 */
void relax(BellmanFord* bf, int** pesos, int u, int v);

/**
 * @brief  função inicial para o algoritmo de Bellman-Ford, este inicializa a estrutura do algoritmo e retorna
 * @param  n: quantidade de vertices do grafo
 * @param  origem: vertice de origem do algoritmo
 * @retval uma variavel inicializa do tipo BellmanFord* com os campos atribuidos
 */
BellmanFord* inicializaOrigem(int n, int origem);

/**
 * @brief  função do algoritmo Prim, que faz a árvore geradora minima a partir de uma vertice 
 * @param  g: grafo a ser busca a árvore minima
 * @param  r: vertice de origem da árvore
 * @param  res: matriz do resultado que guarda a arvore
 * @retval 1 se for um sucesso o algoritmo, 0 se não
 */
int PrimAlgm(Grafo* g, int r, int** res);

/**
 * @brief  função do algoritmo de Kruskal, para fazer a árvore geradora minima
 * @param  g: grafo a ser buscada uma árvore minima
 * @param  **res: matriz de resultado contendo a árvore
 * @retval 1 se for bem sucedido, 0 se não
 */
int KruskalAlgm(Grafo* g, int **res);

/**
 * @brief  função que cria as arestas e guarda na estrutura Aresta*
 * @param  g: grafo a ter suas arestas verificas
 * @param  *n: varivel que guarda a quantidade de arestas
 * @retval um vetor de estrutura Aresta contendo todas as arestas do grafo
 */
Aresta* fazAresta(Grafo* g, int *n);

/**
 * @brief  função auxiliar do algoritmo de Kruskal, que percorre as arestas e verifica se ja existe a aresta de origem i, destino j e peso
 * @param  i: vertice de origem de uma aresta a ser verificada
 * @param  j: vertice de destino da aresta
 * @param  peso: peso da aresta i -> j
 * @param  e: vetor de Aresta guardadas
 * @param  n: tamanho do vetor de Aresta
 * @retval 1 se existe, 0 se não existe
 */
int jaExiste(int i, int j, int peso, Aresta* e, int n);

/**
 * @brief  função auxiliar do algoritmo de Kruskal, que une os conjuntos u e v
 * @param  u: indice do conjunto de uma arvore
 * @param  v: indice do conjunto de uma arvore
 * @param  *conj: vetor contendo os conjuntos das arvores
 * @retval None
 */
void Uniao(int u, int v, int *conj);

/**
 * @brief  função para realizar a contra de um valor de um indice para outro indice
 * @param  u: indice a ser um dos trocados
 * @param  v: indice a ser trocado
 * @param  *conj: vetor que tera os valores dos indices trocados
 * @retval None
 */
void troca(int u, int v, int *conj);

/**
 * @brief  função auxiliar do algoritmo de Kruskal, que verifica se os conjuntos u e v são diferentes
 * @param  u: indice do conjunto u
 * @param  v: indice do conjunto v
 * @param  *conj: vetor dos conjuntos
 * @retval 1 se forem diferentes, 0 se não forem
 */
int diferente(int u, int v, int *conj);

/**
 * @brief  função auxiliar do algoritmo de kruskal, que procura o valor do conjunto gerador
 * @param  alvo: indice a ser buscado o valor do gerador
 * @param  *conj: vetor de conjunto a ser buscado
 * @retval 
 */
int findV(int alvo, int *conj);

/**
 * @brief  mergeSortN, algoritmo de ordenação por metodo de separar, ordenar e reajuntar e ordenar...
 * @param  v: vetor a ser ordenado
 * @param  inicio: indice do inicio do vetor
 * @param  fim: tamanho maximo do vetor
 * @retval None
 */
void mergeSortN(Aresta* v, int inicio, int fim);

/**
 * @brief  função auxiliar do algoritmo de ordenação Merge Sort
 * @param  vet: vetor a ser ordenado
 * @param  inicio: indice do inicio da parte do vetor separada
 * @param  meio: indice do meio do vetor partido
 * @param  fim: tamanho maximo da partição
 * @retval None
 */
void intercala(Aresta* vet, int inicio, int meio, int fim);

/**
 * @brief  função que verifica e retorna o menor dos dois numeros passados
 * @param  a: numero a ser verificado e possivelmente retornado
 * @param  b: numero a ser verificado e possivelmente retornado
 * @retval retorna o numero menor dentre os dois
 */
int minimo(int a, int b);

/**
 * @brief  função do algoritmo de Ford-Fulkerson, que calcula o fluxo maximo de um grafo
 * @param  g: grafo a ser calculado o fluxo maximo
 * @param  fonte: vertice de origem do grafo
 * @param  ralo: vertice de fim do grafo
 * @param  **res: matriz de resultado contendo os fluxos
 * @retval retorna o valor do fluxo maximo
 */
int FordFulkerson(Grafo* g, int fonte, int ralo, int **res);

#endif // ALGORITMOS_H