#include "algoritmos.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

/**
 * @brief  função que visita o vertice e atualiza os campos dele, e continua a busca a partir dele
 * @param  vertice: vertice que ta sendo visitado
 * @param  busca: estrutura que guarda a instancia do algoritmo de busca em profundidade atual
 * @param  n: quantidade de vertices
 * @param  **ordem: matriz que guarda o resultado do caminho
 * @retval None
 */
void visita_buscaProf(int vertice, Profundidade* busca, int n, int **ordem){
    // troca a cor para finalizado
    busca[vertice].cor = 'C';
    // atualiza o tempo
    timestamp++;
    // atribui o tempo de descoberta
    busca[vertice].d = timestamp;

    // para cada adjacente
    for(int i = 0; i < n; i++){
        // se não foram descobertos
        if(busca[vertice].adj[i] == 1 && busca[i].cor == 'B'){
            // marca o caminho e quem precede o adjacente, e visita ele
            ordem[vertice][i] = 1;
            busca[i].pred = vertice;
            visita_buscaProf(i, busca, n, ordem);
        }
    }
    // troca a cor para fim de exploração e atribui o tempo de finalização após este atualizado
    busca[vertice].cor = 'P';
    timestamp++;
    busca[vertice].f = timestamp; 
}

/**
 * @brief  função do algoritmo de busca em profundidade, que gera um caminho a partir da descoberta dos vertices adjacentes do vertice inicial
 * @param  grf: grafo a ser feito a busca
 * @param  inicial: vertice escolhido para ser o inicio da busca
 * @param  res: matriz resultado do caminho feito pela busca
 * @retval None
 */
void buscaEmProfundidade(Grafo* grf, int inicial, int** res){

    //cria o vetor da estrutura para a busca
    Profundidade* busca = (Profundidade*)malloc(sizeof(Profundidade)*grf->nVertices);

    //para cada vertice
    for(int i = 0; i < grf->nVertices; i++){
        // atribui a cor branco de não descoberto, e coloca o predecessor em não existente
        busca[i].cor = 'B';
        busca[i].pred = -1;
    
        //pega os adjacentes
        busca[i].adj = (int*)malloc(sizeof(int)*grf->nVertices);
        for(int j = 0; j < grf->nVertices; j++){

            busca[i].adj[j] = (grf->adjacente[i][j] == 1);
        }
    }
    // inicia o tempo
    timestamp = 0;
    int i = 0;
    // para o vertice inicial, chama a visita para ele
    if(busca[inicial].cor == 'B'){

        visita_buscaProf(inicial, busca, grf->nVertices, res);

    }
    // para os outros nós que faltarem serem descobertas, chama a visita para eles
    for(int i = 0; i < grf->nVertices; i++){

        if(busca[i].cor == 'B'){

            visita_buscaProf(i, busca, grf->nVertices, res);

        }
    }
}

/**
 * @brief  função do algoritmo de busca em largura, que gera um caminho a partir dos adjacentes do vertice origem
 * @param  g: grafo a ser feito a busca
 * @param  origem: vertice de origem da busca
 * @param  res: matriz de resultado do caminho
 * @retval 
 */
int buscaEmLargura(Grafo* g, int origem, int **res){
    // inicia a fila
    Fila* q = start();
    int u, i, j;
    // aloca o vetor de estrutura
    Largura* l = (Largura*)malloc(sizeof(Largura)*g->nVertices);
    // para cada vertice
    for(i = 0; i < g->nVertices; i++){
        // se não for o de origem
        if(i != origem){
            // colocar a cor em não descoberto(Branco), coloca a distancia em infinito e coloca o precessor como indefinido
            l[i].cor = 'B';
            l[i].d = INT_MAX;
            l[i].pred = -1;
            //pega os adjacentes
            l[i].adj = (int*)malloc(sizeof(int)*g->nVertices);

            for(j = 0; j < g->nVertices; j++){
                l[i].adj[j] = (g->adjacente[i][j] == 1);
            }
        }
    }
    // para a origem, atribui ela como descoberta, 0 para a distancia dela, ninguem como precessor dela
    l[origem].cor = 'C';
    l[origem].pred = -1;
    l[origem].d = 0;
    l[origem].adj = (int*)malloc(sizeof(int)*g->nVertices);

    for(j = 0; j < g->nVertices; j++){
        l[origem].adj[j] = (g->adjacente[origem][j] == 1);
    }
    // enfileira ela
    enqueue(q, origem);
    // enquanto houver uma fila
    while(!empty(q)){
        // tira a cabeça da fila
        u = dequeue(q);

        if(u == -1) return 0;
        // para cada adjacente desse vertice
        for(i = 0; i < g->nVertices; i++){
            // se não foi descoberto
            if(l[u].adj[i] && l[i].cor == 'B'){
                // marca o caminho na matriz resultante, e atribui a distancia e descoberto ao vertice adjacente
                res[u][i] = 1;
                l[i].cor = 'C';
                l[i].d = l[u].d + 1;
                l[i].pred = u;
                // enfileira esse vertice
                enqueue(q, i);
            }
        }   
        // atualiza a cor do vertice atual para fim de exploração
        l[u].cor = 'P';
    }
    // ocorreu bem
    return 1;
}

/**
 * @brief  função inicial para o algoritmo de Bellman-Ford, este inicializa a estrutura do algoritmo e retorna
 * @param  n: quantidade de vertices do grafo
 * @param  origem: vertice de origem do algoritmo
 * @retval uma variavel inicializa do tipo BellmanFord* com os campos atribuidos
 */
BellmanFord* inicializaOrigem(int n, int origem){
    //cria e aloca
    BellmanFord* bf = (BellmanFord*)malloc(sizeof(BellmanFord)*n);
    // para cada vertice
    for(int i = 0; i < n; i++){
        // se não for a origem
        if(i != origem){
            // coloca infinito e indefinido precessor
            bf[i].d = INT_MAX;
            bf[i].pred = -1;
        }
    }
    // para a origem, atribui valores iniciais
    bf[origem].d = 0;
    bf[origem].pred = -1;

    return bf;
}

/**
 * @brief  função auxiliar do metodo do Bellman-Ford, que verifica o menor caminho
 * @param  bf: estrutura que guarda a instância do algoritmo em execução
 * @param  pesos: matriz que contem os pesos de cada aresta
 * @param  u: vertice de origem da aresta
 * @param  v: vertice de destino da aresta
 * @retval None
 */
void relax(BellmanFord* bf, int** pesos, int u, int v){
    // se o peso for menor por essa aresta, atribui o novo peso
    if(bf[v].d > (bf[u].d + pesos[u][v])){
        bf[v].d = bf[u].d + pesos[u][v];
        bf[v].pred = u;
    }
}
/**
 * @brief  função do algoritmo de Bellman-Ford, para calcular o menor caminho a partir de um vertice de origem
 * @param  g: grafo a ser buscado o menor caminho
 * @param  origem: vertice de origem da busca
 * @param  res: matriz de resultado do menor caminho
 * @retval 1 se o algoritmo foi realizado com sucesso, 0 se não
 */
int BellmanFordAlg(Grafo* g, int origem, int **res){
    // aloca a partir da função inicializar
    BellmanFord* bf = inicializaOrigem(g->nVertices, origem);
    
    int i, j, k;
    // para cada aresta, chama o metodo de relax para eles
    for(i = 0; i < g->nVertices -1; i++){
        for(k = 0; k < g->nVertices; k++){
            for(j = 0; j < g->nVertices; j++){
                if(g->adjacente[k][j] == 1)
                    relax(bf, g->pesos, k, j);
            }
        }
    }
    // se houver um ciclo negativo, retorna não sucedido
    for(i = 0; i < g->nVertices; i++){
        for(j = 0; j < g->nVertices; j++){
            if(g->adjacente[i][j] == 1 && (bf[j].d > bf[i].d + g->pesos[i][j])){
                return 0;
            }
        }
    }
    // forma a matriz de resultado
    for(i = 0; i < g->nVertices; i++){
        for(j = 0; j < g->nVertices; j++){
            if(g->adjacente[i][j] && (bf[j].pred == i)){

                res[i][j] = bf[j].d;
            }
        }
    }

    free(bf);
    // bem sucedido
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
/**
 * @brief  função auxiliar do algoritmo de kruskal, que procura o valor do conjunto gerador
 * @param  alvo: indice a ser buscado o valor do gerador
 * @param  *conj: vetor de conjunto a ser buscado
 * @retval 
 */
int findV(int alvo, int *conj){
    // se for oq busca, retorna o valor do indice, se não for continua buscando
    if(conj[alvo] < 0) {
        return alvo;
    }else{
        return findV(conj[alvo], conj);
    }
}

/**
 * @brief  função auxiliar do algoritmo de Kruskal, que verifica se os conjuntos u e v são diferentes
 * @param  u: indice do conjunto u
 * @param  v: indice do conjunto v
 * @param  *conj: vetor dos conjuntos
 * @retval 1 se forem diferentes, 0 se não forem
 */
int diferente(int u, int v, int *conj){
    // se forem diferentes de começo
    if(findV(u, conj) == u && findV(v, conj) == v)
        return 1;
    else{
        // se não forem, busquem mais adentro
        int a = (conj[u] < 0)? u : findV(conj[u], conj), b = (conj[v] < 0)? v: findV(conj[v], conj);
        
        if(a != b) return 1;

        return 0;
    }
}

/**
 * @brief  função para realizar a contra de um valor de um indice para outro indice
 * @param  u: indice a ser um dos trocados
 * @param  v: indice a ser trocado
 * @param  *conj: vetor que tera os valores dos indices trocados
 * @retval None
 */
void troca(int u, int v, int *conj){
    int temp;

    temp = conj[u];
    conj[u] = v;
    conj[v] += temp;
}

/**
 * @brief  função auxiliar do algoritmo de Kruskal, que une os conjuntos u e v
 * @param  u: indice do conjunto de uma arvore
 * @param  v: indice do conjunto de uma arvore
 * @param  *conj: vetor contendo os conjuntos das arvores
 * @retval None
 */
void Uniao(int u, int v, int *conj){

    int temp;
    // se forem o que busca
    if(findV(u, conj) == u && findV(v, conj) == v){
        // se um for maior, insere no maior, se não insere no outro
        if(conj[u] >= conj[v]){
            troca(u, v, conj);
        }else{
            troca(v, u, conj); 
        }
    }else{
        // busca o pai da arvore e insere no que for maior
        int a = findV(u, conj), b = findV(v, conj);
        if(conj[a] >= conj[b]){
            troca(a, b, conj);
        }else{
            troca(b, a, conj); 
        }
    }
}

/**
 * @brief  função auxiliar do algoritmo de Kruskal, que percorre as arestas e verifica se ja existe a aresta de origem i, destino j e peso
 * @param  i: vertice de origem de uma aresta a ser verificada
 * @param  j: vertice de destino da aresta
 * @param  peso: peso da aresta i -> j
 * @param  e: vetor de Aresta guardadas
 * @param  n: tamanho do vetor de Aresta
 * @retval 1 se existe, 0 se não existe
 */
int jaExiste(int i, int j, int peso, Aresta* e, int n){

    for(int k = 0; k < n; k++){

        if(((e[k].u == i && e[k].v == j) || (e[k].u == j && e[k].v == i)) && e[k].peso == peso) return 1;
    }

    return 0;
}

/**
 * @brief  função que cria as arestas e guarda na estrutura Aresta*
 * @param  g: grafo a ter suas arestas verificas
 * @param  *n: varivel que guarda a quantidade de arestas
 * @retval um vetor de estrutura Aresta contendo todas as arestas do grafo
 */
Aresta* fazAresta(Grafo* g, int *n){

    Aresta* novo = (Aresta*)malloc(sizeof(Aresta)*g->nVertices*g->nVertices);

    int i, j, k = 0;
    // para cada aresta, cria um Aresta
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

/**
 * @brief  função do algoritmo de Kruskal, para fazer a árvore geradora minima
 * @param  g: grafo a ser buscada uma árvore minima
 * @param  **res: matriz de resultado contendo a árvore
 * @retval 1 se for bem sucedido, 0 se não
 */
int KruskalAlgm(Grafo* g, int **res){
    // aloca os conjuntos
    int *conj = (int*)malloc(sizeof(int)*g->nVertices);
    // todos com -1
    for(int k = 0; k < g->nVertices; k++) conj[k] = -1;

    int i, j, n, ki = 0;
    Aresta* E = fazAresta(g, &n);
    Aresta* kruskal = (Aresta*)malloc(sizeof(Aresta)*n);
    // ordena as arestas
    mergeSortN(E, 0, n);
    // para cada conjunto
    for(i = 0 ; i < n; i++){
        // se formam arvores diferentes, insere no vetor solucao e une as arvores
        if(diferente(E[i].u, E[i].v, conj)){
            kruskal[ki].u = E[i].u;
            kruskal[ki].v = E[i].v;
            kruskal[ki++].peso = E[i].peso;
            Uniao(E[i].u, E[i].v, conj);
        }
    }
    // cria a matriz resultante
    kruskal = (Aresta*)realloc(kruskal, sizeof(Aresta)*ki);
    for(i = 0; i < ki; i++){
        res[kruskal[i].u][kruskal[i].v] = kruskal[i].peso;
    }

    free(kruskal);
    free(E);
    // bem sucedido
    return 1;
}

// busca se há vertices conhecidos
int houverNaoConhecidos(Prim* p, int n){

    int i;

    for(i = 0; i < n; i++){
        
        if(p[i].conhecido == 0) return 1;
    }

    return 0;
}

// busca o menor custo de todos os vertices
int menorCusto(Prim* p, int n){

    int i, menorVal = INT_MAX, indMenor = -1;

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
// retorna se foi conhecido
int procuraV(Prim* p, int n, int alvo){

    return !(p[alvo].conhecido);
}

/**
 * @brief  função do algoritmo Prim, que faz a árvore geradora minima a partir de uma vertice 
 * @param  g: grafo a ser busca a árvore minima
 * @param  r: vertice de origem da árvore
 * @param  res: matriz do resultado que guarda a arvore
 * @retval 1 se for um sucesso o algoritmo, 0 se não
 */
int PrimAlgm(Grafo* g, int r, int **res){
    // aloca o vetor Prim
    Prim *p = (Prim*)malloc(sizeof(Prim)*g->nVertices);

    int i, j, u, n = g->nVertices;
    // para cada vertice
    for(i = 0; i < n; i++){

        p[i].conhecido = 0;
        p[i].key = INT_MAX;

        p[i].pred = -1;
        p[i].adj = (int*)malloc(sizeof(int)*n);

        for(j = 0; j < g->nVertices; j++){
            p[i].adj[j] = (g->adjacente[i][j] == 1);
        }
    }
    // vertice inicial
    p[r].key = 0;
    p[r].pred = -1;
    // se tiver vertices não conhecidos
    while(houverNaoConhecidos(p, n)){
        // busca o vertice não conhecido com menor custo
        u = menorCusto(p, n);

        if(u == -1) return 0;
        p[u].conhecido = 1;
        // para cada vertice
        for(i = 0; i < n; i++){

            if(p[u].adj[i] == 1){
                // procura os vertices não conhecidos que são menor caminho para ele
                if(procuraV(p, n, i) && (g->pesos[u][i] < p[i].key)){
                    // atualiza o caminho
                    p[i].pred = u;
                    p[i].key = g->pesos[u][i];
                }
            }
        }
    }
    // forma a matriz resultante
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

// algoritmo igual a busca em largura mas alterada para o algoritmo de fulkerson
int buscaEmLarguraFordFulk(Grafo* g, int origem, int fim, int *parente, int **fluxo){

    Fila* q = start();
    int u, i, j;

    Largura* l = (Largura*)malloc(sizeof(Largura)*g->nVertices);

    for(i = 0; i < g->nVertices; i++){

        if(i != origem){

            parente[i] = 0;
            l[i].cor = 'B';
            l[i].d = INT_MAX;
            l[i].pred = -1;

            l[i].adj = (int*)malloc(sizeof(int)*g->nVertices);

            for(j = 0; j < g->nVertices; j++){
                l[i].adj[j] = (g->adjacente[i][j] == 1);
            }
        }
    }

    parente[origem] = -1;
    l[origem].cor = 'C';
    l[origem].pred = -1;
    l[origem].d = 0;
    l[origem].adj = (int*)malloc(sizeof(int)*g->nVertices);

    for(j = 0; j < g->nVertices; j++){
        l[origem].adj[j] = (g->adjacente[origem][j] == 1);
    }
    enqueue(q, origem);

    while(!empty(q)){

        u = dequeue(q);

        if(u == -1) return 0;

        for(i = 0; i < g->nVertices; i++){

            if(l[u].adj[i] && l[i].cor == 'B' && (g->pesos[u][i] - fluxo[u][i] > 0)){
                
                parente[i] = u;
                l[i].cor = 'C';
                l[i].d = l[u].d + 1;
                l[i].pred = u;
                enqueue(q, i);
            }
        }

        l[u].cor = 'P';
    }

    return (l[fim].cor == 'P');
}

/**
 * @brief  função que verifica e retorna o menor dos dois numeros passados
 * @param  a: numero a ser verificado e possivelmente retornado
 * @param  b: numero a ser verificado e possivelmente retornado
 * @retval retorna o numero menor dentre os dois
 */
int minimo(int a, int b){

    return (a < b)? a : b;
}

/**
 * @brief  função do algoritmo de Ford-Fulkerson, que calcula o fluxo maximo de um grafo
 * @param  g: grafo a ser calculado o fluxo maximo
 * @param  fonte: vertice de origem do grafo
 * @param  ralo: vertice de fim do grafo
 * @param  **res: matriz de resultado contendo os fluxos
 * @retval retorna o valor do fluxo maximo
 */
int FordFulkerson(Grafo* g, int fonte, int ralo, int **res){
    // faz o vetor de parentes
    int parente[g->nVertices], n = g->nVertices, i, j = 0, fluxoMax = 0;

    //zera a matriz resultado
    for(i = 0; i < n; i++) 
        for(j = 0; j < n; j++)
            res[i][j] = 0;

    // enquanto achar caminho da fonte ao ralo
    while(buscaEmLarguraFordFulk(g, fonte, ralo, parente, res)){
        // faz o fluxo ser infinito
        int fluxo_caminho = INT_MAX;
        //busca o menor fluxo
        for(i = ralo; i!=fonte; i=parente[i]){
            fluxo_caminho = minimo(fluxo_caminho, g->pesos[parente[i]][i] - res[parente[i]][i]);
        }
        // atualiza as arestas
        for(i = ralo; i!=fonte; i=parente[i]){
            res[parente[i]][i] += fluxo_caminho;
            res[i][parente[i]] -= fluxo_caminho;
        }
        // aumenta o fluxo maximo
        fluxoMax += fluxo_caminho;
    }
    // retorn o fluxo maximo
    return fluxoMax;
}