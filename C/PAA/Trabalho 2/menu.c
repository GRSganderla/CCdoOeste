#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

// variável usada para guardar os nomes dos algortimos para serem apresentados no menu
char *algoritmos[] = {
    "Busca em Profundidade", 
    "Busca em Largura",
    "Bellman-Ford",
    "Kruskal",
    "Prim",
    "Algoritmo de Ford-Fulkerson",
};

// variável para complementar o nome do arquivo de entrada para fazer os arquivos de saida de cada algoritmo
char *algoritmosDot[] = {
    "BuscaProfundidade.dot", 
    "BuscaLargura.dot",
    "BellmanFord.dot",
    "Kruskal.dot",
    "Prim.dot",
    "FordFulkerson.dot",
};

/**
 * @brief  função que le o número do vertice de fonte e ralo que o usuário quer que seja feito o algoritmo
 * @param  *fonte: variável responsavel por guardar o valor do vertice de fonte que será lido
 * @param  *ralo: variável responsavel por guardar o valor do vertice de ralo que será lido
 * @param  g: grafo carregado do arquivo dessa instância de execução
 * @retval None
 */
void fonte_ralo(int *fonte, int *ralo, Grafo* g){

    int fon, ral;
    // limpa a tela
    system("clear");

    // printa na tela os vertices do grafo
    printf("Vertices={");
    for(int i = 0; i < g->nVertices; i++){

        printf(" %d", i);
        // se o vertice tiver um nome, printa ele
        if(g->EhRotulado){
            printf(": %s", g->nomes[i].nome);
        }

        (i < g->nVertices-1)? printf(","): printf("}\n");
    }

    // enquanto a opcao de vertice de fonte ou de ralo não ser valida, ele vai executar
    do {
        printf("Entre com a fonte: ");
        scanf("%d%*c", &fon);
        printf("Entre com o ralo: ");
        scanf("%d%*c", &ral);
    }while(fon < 0 && fon > g->nVertices && ral < 0 && ral > g->nVertices);

    // guarda os indices
    *fonte = fon;
    *ralo = ral;
}

/**
 * @brief  função que lê o vertice de origem que o usuário deseja usar para os algoritmos
 * @param  g: grafo carregado do arquivo dessa instância de execução
 * @retval o vertice lido
 */
int vertice_origem(Grafo* g){

    int vertice;
    system("clear");
    // printa na tela os vertices do grafo
    printf("Vertices={");
    for(int i = 0; i < g->nVertices; i++){

        printf(" %d", i);
        // se o vertice tiver um nome, printa ele
        if(g->EhRotulado){
            printf(": %s", g->nomes[i].nome);
        }

        (i < g->nVertices-1)? printf(","): printf("}\n");
    }
    // enquanto a opcao de vertice não ser valida, ele vai executar
    do {
        printf("Entre com o vertice de origem: ");
        scanf("%d%*c", &vertice);
    }while(vertice < 0 && vertice > g->nVertices);

    return vertice;
}

/**
 * @brief  função de apresentar um menu iterativo onde o usuário escolherá os algoritmos a serem feito sobre o grafo guardado
 * @param  g: grafo carregado que será usado nos algoritmos
 * @param  nomeArq[]: nome do arquivo de saida padrão a ser usado para gerar os .dots dos algoritmos a serem feitos
 * @retval None
 */
void menu(Grafo* g, char nomeArq[]){

    char dotGerado[300], *command;
    FILE* f;
    int opcao, feito;

    // enquanto o usuário não sair
    do{
        feito = 0;
        // coloca o nome do arquivo de saida na string para o nome de arquivo de saida pros algoritmos
        strcpy(dotGerado, nomeArq);
        system("clear");
        printf("Algoritmos com Grafos\n");

        printf("------------------------------\n");

        // printa os algoritmos
        for(int i = 0; i < 6; i++){
            printf("%d - %s\n", i+1, algoritmos[i]);
        } 
        printf("0 - Sair\n");
        printf("------------------------------\n");
        printf("Opcao: ");

        scanf("%d%*c", &opcao);

        // se for sair quebra o while
        if(opcao == 0){
            break;
        }   
        // se der uma opcao errada
        else if(opcao > 6){
            continue;
        }

        // se não tem nada no nome de arquivo de saida
        if(nomeArq[0] == '\0'){
            // le o nome do arquivo de saida da escolha do usuário 
            printf("Entre com o nome do arquivo .dot a ser gerado: ");
            scanf("%s%*c", dotGerado);
        }
        else{
            // cria um nome de arquivo com o nome do algoritmo escolhido no final do nome
            strcat(dotGerado, algoritmosDot[opcao-1]);
        }

        // inicia a matriz responsavel pela resposta
        int **res = init(g->nVertices), vertice, fonte, ralo;

        // se for o metodo de Ford-Fulkerson, le o vertice de fonte e de ralo
        if(opcao == 6){
            fonte_ralo(&fonte, &ralo, g);
        }
        // se não for, le o vertice de origem
        else if(opcao != 4){
            vertice = vertice_origem(g);
        }

        // abre o arquivo para guardar o resultado do algoritmo
        f = fopen(dotGerado, "w+");

        switch (opcao)
        {
            case 1:
                // faz o algoritmo e escreve no arquivo
                buscaEmProfundidade(g, vertice, res);
                fazArquivoBusca(g,f,res);
                free(res);
                break;
            case 2:
                // faz o algoritmo e escreve no arquivo
                feito = buscaEmLargura(g, vertice, res);
                if(feito) fazArquivoBusca(g, f, res);
                free(res);
                break;
            case 3:
                // faz o algoritmo e escreve no arquivo
                feito = BellmanFordAlg(g, vertice, res);
                if(feito == 1) fazArquivoFord(g, f, res, 0, 0, 0);
                free(res);
                break;
            case 4:
                // faz o algoritmo e escreve no arquivo
                feito = KruskalAlgm(g, res);
                if(feito == 1) fazArquivoFord(g, f, res, 0, 0, 0);
                free(res);
                break;
            case 5:
                // faz o algoritmo e escreve no arquivo
                feito = PrimAlgm(g, vertice, res);
                if(feito == 1) fazArquivoFord(g, f, res, 0, 0, 0);
                free(res);
                break;
            case 6:
                // faz o algoritmo e escreve no arquivo
                feito = FordFulkerson(g, fonte, ralo, res);
                fazArquivoFord(g, f, res, ralo, feito, 1);
                free(res);
                break;
            case 0:
                break;
        }
        fclose(f);
        getchar();
        
    }while(opcao != 0);
}