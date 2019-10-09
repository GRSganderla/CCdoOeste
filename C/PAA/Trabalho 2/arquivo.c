#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arquivo.h"

/**
 * @brief  função que insere no arquivo .dot a sintaxe para se criar um grafo com o resultado sendo do algoritmo de Bellman-Ford, Kruskal, Prim ou Ford-Fulkerson
 * @param  grf: grafo carregado a ter dados inserido no arquivo de saida
 * @param  outFile: arquivo .dot que será escrito os dados
 * @param  res: matriz de resultado do algoritmo escolhido
 * @param  fluxo: variavel que pode guardar o valor do fluxo total ou ser 0
 * @param  ralo: variavel que guarda o vertice ralo do grafo, sendo usado quando for o algoritmo de Fulkerson
 * @param  ehFluxo: variavel que diz se o algoritmo que foi executado antes era o de Fulkerson ou não
 * @retval None
 */
void fazArquivoFord(Grafo* grf, FILE* outFile, int** res, int ralo, int fluxo, int ehFluxo){

    char type[4];
    // determina o tipo do grafo e começa a sintaxe
    if(strcmp(grf->orientado, "sim") == 0){
        fprintf(outFile, "strict digraph {\n");
        strcpy(type, "->");
    }
    else{
        fprintf(outFile, "strict graph {\n");
        strcpy(type, "--");
    }
    // escreve as propriedades do grafo
    fprintf(outFile, "\tgraph [pad=\"0.5\", nodesep=\"1 equally\", ranksep=\"1 equally\"]\n\trankdir=LR;\n");
    // para cada vertice
    for(int i = 0; i < grf->nVertices; i++){

        // se o grafo for rotulado escreve em estilo caixa
        if(grf->EhRotulado == 1) fprintf(outFile, "\t\"%s\" [shape=box];\n", grf->nomes[i].nome);

        // para cada vertice
        for(int j = 0; j < grf->nVertices; j++){

            // se forem adjacentes
            if(grf->adjacente[i][j] == 1)
            {
                // se forem parte da matriz de resposta
                if(res[i][j] > 0)
                {
                    // se não for rotulado o vertice
                    if(grf->EhRotulado == 0)
                    {
                        fprintf(outFile, "\t%d %s %d[label=\"%d\", fontcolor=red,color=red];\n", i, type, j, res[i][j]);
                    }else
                    {
                        // se for
                        fprintf(outFile, "\t\"%s\" %s \"%s\"[label=\"%d\", fontcolor=red, color=red];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, res[i][j]); 
                    }
                }else
                {
                    // se não for rotulado o vertice
                    if(grf->EhRotulado == 0)
                    {
                        fprintf(outFile, "\t%d %s %d[label=\"%d\",labelfontcolor=black];\n", i, type, j, grf->pesos[i][j]);
                    }else
                    {
                        // se for
                        fprintf(outFile, "\t\"%s\" %s \"%s\"[label=\"%d\",labelfontcolor=black];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->pesos[i][j]);
                    }
                }
                if(grf->EhRotulado == 0)
                {
                    fprintf(outFile, "\t%d %s %d[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", i, type, j, grf->rotulos[i][j].nome);
                }else
                {
                    fprintf(outFile, "\t\"%s\" %s \"%s\"[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->rotulos[i][j].nome);                    
                }
            }
        }

    }

    // se for depois do algoritmo de Fulkerson, imprime o valor do fluxo total no vertice ralo
    if(ehFluxo == 1){
        if(grf->EhRotulado == 0)
            fprintf(outFile, "\t%d[xlabel=\"%d\"]", ralo, fluxo);
        else
            fprintf(outFile, "\t%s[xlabel=\"%d\"]", grf->nomes[ralo], fluxo);
    }

    fprintf(outFile, "}");
}

/**
 * @brief  função que insere no arquivo .dot a sintaxe para ser usada no comando dot para gerar o grafo resultante dos algoritmos de profundidade e largura
 * @param  g: grafo carregado que terá os dados guardados nesse arquivo .dot
 * @param  out: arquivo .dot a ter a sintaxe inserida
 * @param  res: matriz que contem o resultado do algoritmo de profundidade ou largura
 * @retval None
 */
void fazArquivoBusca(Grafo* grf, FILE* out, int** res){

    char type[4];
    // se não tem matriz de resultado
    if(res == NULL) return;
    // determina o tipo do grafo e escreve o começo da sintaxe .dot
    if(strcmp(grf->orientado, "sim") == 0){
        fprintf(out, "strict digraph {\n");
        strcpy(type, "->");
    }
    else{
        fprintf(out, "strict graph {\n");
        strcpy(type, "--");
    }

    // coloca as propriedades do grafo
    fprintf(out, "\tgraph [pad=\"0.5\", nodesep=\"1 equally\", ranksep=\"1 equally\"]\n\trankdir=LR;\n");

    // para cada vertice que existe no grafo
    for(int i = 0; i < grf->nVertices; i++){

        // se os vertices forem rotulados, cria um grafo com vertices estilo caixa
        if(grf->EhRotulado == 1) fprintf(out, "\t\"%s\" [shape=box];\n", grf->nomes[i].nome);

        // para cada vertice do grafo
        for(int j = 0; j < grf->nVertices; j++){
            // se a aresta pertence ao resultado do algoritmo 
            if(res[i][j] == 1){
                // se forem rotuladas
                if(grf->EhRotulado == 0) fprintf(out, "\t%d %s %d[color=red];\n", i, type, j);
                else fprintf(out, "\t\"%s\" %s \"%s\"[color=red];\n", grf->nomes[i].nome, type, grf->nomes[j].nome);
            }
            // se os vertices i e j forem adjacentes
            if(grf->adjacente[i][j] == 1){

                if(grf->EhRotulado == 0){
                    if(res[i][j] != 1) fprintf(out, "\t%d %s %d[label=\"%d\",labelfontcolor=black];\n", i, type, j, grf->pesos[i][j]);
                    fprintf(out, "\t%d %s %d[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", i, type, j, grf->rotulos[i][j].nome);
                }else{

                    if(res[i][j] != 1) fprintf(out, "\t\"%s\" %s \"%s\"[label=\"%d\",labelfontcolor=black];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->pesos[i][j]);
                    fprintf(out, "\t\"%s\" %s \"%s\"[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->rotulos[i][j].nome);
                }
            }
        }
    }

    fprintf(out, "}");
}

/**
 * @brief  função que insere no arquivo .dot a sintaxe para criar o grafo
 * @param  grf: grafo a ser inserido no arquivo
 * @param  out: arquivo a ser escrito os dados
 * @retval None
 */
void fazArquivoDot(Grafo* grf, FILE* out){

    // verifica o tipo de orientado e cria a sintaxe do tipo de grafo a partir disso
    char type[4];
    if(strcmp(grf->orientado, "sim") == 0){
        fprintf(out, "strict digraph {\n");
        strcpy(type, "->");
    }
    else{
        fprintf(out, "strict graph {\n");
        strcpy(type, "--");
    }
    // coloca as propriedades do grafo
    fprintf(out, "\tgraph [pad=\"0.5\", nodesep=\"1 equally\", ranksep=\"1 equally\"]\n\trankdir=LR;\n");
    // para cada vertice que existe no grafo
    for(int i = 0; i < grf->nVertices; i++){
        // se os vertices forem rotulados, cria um grafo com vertices estilo caixa
        if(grf->EhRotulado == 1) fprintf(out, "\t\"%s\" [shape=box];\n", grf->nomes[i].nome);
        // para cada vertice do grafo
        for(int j = 0; j < grf->nVertices; j++){
            // se i e j forem adjacentes
            if(grf->adjacente[i][j] == 1){

                // se o grafo for do tipo não rotulo nos vertices
                if(grf->EhRotulado == 0){
                    // escreve a aresta
                    fprintf(out, "\t%d %s %d[label=\"%d\",labelfontcolor=black];\n", i, type, j, grf->pesos[i][j]);
                    fprintf(out, "\t%d %s %d[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", i, type, j, grf->rotulos[i][j].nome);
                }
                else{
                    //se o grafo for do tipo de vertice com nome, escreve a aresta
                    fprintf(out, "\t\"%s\" %s \"%s\"[label=\"%d\",labelfontcolor=black];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->pesos[i][j]);
                    fprintf(out, "\t\"%s\" %s \"%s\"[taillabel=\"%s\",labeldistance=8,labelfontcolor=blue,labelangle=-5];\n", grf->nomes[i].nome, type, grf->nomes[j].nome, grf->rotulos[i][j].nome, grf->rotulos[i][j].nome);
                }
            }
        }
    }
    
    // fecha a sintaxe
    fprintf(out, "}");
}

/**
 * @brief  função que determina quantos nomes tem dentro de uma string 
 * @param  *nome: string que contem varios nomes, separados por virgula
 * @retval um número que será o quanto de nomes há na string
 */
int countVirgula(char *nome){

    // cria e inicializa os contadores
    int i = 0, count = 0;

    // enquanto não for o final da string
    while(nome[i] != '\0'){
        // se for uma virgula, quer dizer que acabou de ler um nome do vertice, incrementa o contador
        if(nome[i] == ',')
            count++;
        i++;
    }

    // retorna o numero de nomes da string + 1, este que é o ultimo nome que não tem uma virgula após ele
    return count+1;
}

/**
 * @brief  função que verifica qual o tipo da linha do arquivo está sendo lida, e retorna o tipo dessa linha
 * @param  linha[]: linha lida do arquivo a ter o seu tipo determinada
 * @retval número que indica qual o tipo da linha
 */
int qualLinha(char linha[]){

    // se for do tipo orientado, retorna o numero dele
    if(strncmp(linha, "orientado", 9) == 0) {
        return LINHA_ORIENTADO;
    }
    // se for a linha de vertice
    else if(linha[0] == 'V'){
        
        // se for vertices com rotulos, retorna o numero desse tipo
        if(strncmp(linha, "V={", 3) == 0) {
            return LINHA_ROTULO_VERTICES;
        }
        else{
            // se não retorna o número do tipo de numero que indica a quantidade de vertices
            return LINHA_N_VERTICES;
        }
    }
    else{
    // se não for nenhum dos outros tipos, então é a linha de arestas
    } return LINHA_ARESTAS;
}

/**
 * @brief  função que chama os metodos de alocação dos campos da variavel do tipo Grafo*
 * @param  grf: grafo a ter os campos alocados
 * @retval None
 */
void alocaCampos(Grafo* grf){

    // chama os metodos que alocam cada campo do grafo
    grf->pesos = init(grf->nVertices);
    grf->adjacente = init(grf->nVertices);
    grf->rotulos = initLabels(grf->nVertices);
}

/**
 * @brief  função que verifica qual o tipo de orientação do arquivo e aloca a estrutura Grafo* e guarda o dado orientado
 * @param  linha[]: linha do arquivo lida
 * @retval uma variavel do tipo Grafo* alocada e com o campo orientado preenchido
 */
Grafo* linha_orientado(char linha[]){
    
    // cria o grafo
    Grafo* grf;
    char orientado[4];

    // pega o tipo de orientado
    sscanf(linha, "orientado= %[^\n]%*c", orientado);
    // aloca o grafo com o campo orientado
    grf = initGrafo(orientado);

    // retorna o novo grafo
    return grf;
}

/**
 * @brief  função que o numero de vertices e guarda na estrutura Grafo*
 * @param  linha[]: linha lida do arquivo
 * @param  grf: grafo a ter o número de vertices atualizado
 * @retval None
 */
void linha_n_vertices(char linha[], Grafo* grf){
    // atribui que o grafo não tem vertices com nomes
    grf->EhRotulado = 0;
    // lê o numero de vertices
    sscanf(linha, "V= %d%*c", &grf->nVertices);
    // chama a função de alocar os campos
    alocaCampos(grf);
}

/**
 * @brief  função que le a linha e pega o nome dos vertices e guarda na estrutura Grafo*
 * @param  linha[]: linha lida do arquivo
 * @param  grf: grafo a ter os dados inseridos
 * @retval None
 */
void linha_rotulo_vertices(char linha[], Grafo* grf){

    char aux[300];
    int percorre, i;

    // diz que ele tem vertice com nome
    grf->EhRotulado = 1;

    // le a linha inteira contendo os nomes dos vertices
    sscanf(linha, "V={ %[^}] }", aux);
    strcat(aux, "\n");

    // determina a quantidade de nomes
    grf->nVertices = countVirgula(aux);

    // aloca o campo nomes para essa quantidade
    grf->nomes = (Label*)malloc(sizeof(Label)*grf->nVertices);
    
    // para cada possivel nome, scaneia e guarda dentro do campo nome
    for(percorre = 0, i = 0; percorre < strlen(aux) && i < grf->nVertices; percorre += strlen(grf->nomes[i].nome)+1, i++)
    {
        sscanf(aux+percorre, " %[^,],", grf->nomes[i].nome);
        strtok(grf->nomes[i].nome, "\n");
    }

    // chama o metodo de alocar os campos
    alocaCampos(grf);
}

/**
 * @brief  função que le da linha do arquivo a aresta e guarda os dados do vertice u, v e o peso no grafo
 * @param  linha[]: linha do arquivo lida que contém uma aresta
 * @param  *grf: grafo a ter dados inseridos
 * @retval None
 */
void linha_arestas(char linha[], Grafo *grf){

    char aux[300];
    int percorre, row, col, peso;
    // scaneia os vertices u, v e o peso
    sscanf(linha, "( %d , %d ): %d%n", &row, &col, &peso, &percorre);

    // se os vertices estão dentro do numero de vertices
    if((row >= 0 && row < grf->nVertices) && (col >= 0 && col < grf->nVertices))
    {
        strcpy(grf->rotulos[row][col].nome, " ");

        // insere o rotulo da aresta, se tiver
        if(linha[percorre] == ','){
            sscanf(linha+percorre, ", %[^\n]%*c", aux);
            strcpy(grf->rotulos[row][col].nome, aux);
        }
        // insere na matriz de adjacencia a aresta dos vertices u -> v
        grf->adjacente[row][col] = 1;

        // insere o peso da aresta u -> v
        grf->pesos[row][col] = peso;

        // verifica se não é orientado, se não for, adiciona na matriz de adjacencia, de peso e nos nomes de rotulos, o inverso
        if(strcmp(grf->orientado, "nao") == 0) {
            grf->adjacente[col][row] = 1;
            grf->pesos[col][row] = peso;
            strcpy(grf->rotulos[col][row].nome, grf->rotulos[row][col].nome);
        }
    }
}

/**
 * @brief  função que pega o arquivo aberto e lê as linhas dele e armazena em um grafo
 * @param  in: arquivo a ser lido
 * @retval uma variavel do tipo Grafo* contendo os dados do grafo passado por arquivo
 */
Grafo* leArquivo(FILE* in){

    // cria uma variavel 
    Grafo* grf = NULL;
    char linha[500];

    // enquanto tiver linha a ser lida no arquivo
    while(fgets(linha, 500, in)){
        
        // remove o quebra linha do final da string da linha lida
        strtok(linha, "\n");

        // determina qual o tipo da linha e chama o metodo para resolver a linha
        switch(qualLinha(linha)){
            case 1:
                grf = linha_orientado(linha);
                break;
            case 2:
                linha_rotulo_vertices(linha, grf);
                break;
            case 3:
                linha_n_vertices(linha, grf);
                break;
            case 4:
                linha_arestas(linha, grf);
                break;     
        }
    }

    // retorna o grafo alocado e atribuido
    return grf;
}