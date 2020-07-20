#include "mesa.h"
#include "operacoes.h"
#include "arquivobin.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

///
/// \brief imprimeCarta, imprime o valor e naipe da carta, sendo a carta imprimida do tipo '|valor,naipe|'
/// \param carta, estrutura do tipo carta, tendo consigo o seu valor e naipe
/// \pre a carta esteja nos padrões do tipo de carta usado para imprimir
/// \post nenhuma
///
void imprimeCarta(Carta* carta)
{
    //variaveis para a guardar o status do console e seus atributos
    HANDLE consoleInicial = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD atributos;

    //funções do cmd
    GetConsoleScreenBufferInfo(consoleInicial, &consoleInfo);
    atributos = consoleInfo.wAttributes;

    //se a carta é 'O' ou 'C' muda a cor do texto para vermelho
    if((carta->naipe == 0) || (carta->naipe == 2)){
        SetConsoleTextAttribute(consoleInicial, FOREGROUND_RED);
    }else{
    //se não, ela é 'E' ou 'P', muda a cor do texto para azul
        SetConsoleTextAttribute(consoleInicial, FOREGROUND_BLUE);
    }
    //se o valor está dentro dos valores possiveis para as cartas, 0(A),1(2),2(3),3(4),4(5),5(6),6(7),7(8),8(9),9(10),10(J),11(Q),12(K).
    if(carta->hierarquia >=0 && carta->hierarquia < 13)
    {
        //se a carta esta entre as 9 primeiras cartas
        if(carta->hierarquia < 9)
        {
            //se ela é a primeira carta imprime ela como A
            if(carta->hierarquia == 0)
                printf("| A,");

            //se não, imprime o valor da carta + 1, sendo o valor 1, imprime 2 e etc...
            else
                printf("| %d,",carta->hierarquia+1);
        }
        //se não é as 9 primeiras, então são as 4 ultimas
        else
        {
            //se a carta é o valor 10, imprime 10
            if(carta->hierarquia == 9)
                printf("|10,");
            //se a carta é 10, imprime J
            if(carta->hierarquia == 10)
                printf("| J,");
            //se a carta é 11, imprime Q
            if(carta->hierarquia == 11)
                printf("| Q,");
            //se a carta é 12, imprime K
            if(carta->hierarquia == 12)
                printf("| K,");
        }
        //se for o primeiro naipe, imprime 'O'
        if(carta->naipe == 0) printf(" O|");
        //se for o segundo, imprime 'E'
        if(carta->naipe == 1) printf(" E|");
        //se for o terceiro, imprime 'C'
        if(carta->naipe == 2) printf(" C|");
        //se for o quarto naipe, imprime 'P'
        if(carta->naipe == 3) printf(" P|");
    }

    //volta a cor original do console
    SetConsoleTextAttribute(consoleInicial, atributos);
}

///
/// \brief criaMesa, cria e inicializa uma estrutura Mesa* alocando memória para todo o seu conteudo
/// \return retorna a nova mesa com suas pilhas cartas, pilhas naipes, celulas livres e variaveis inicializadas como nulo
/// \pre nenhuma
/// \post nenhuma
///
Mesa* criaMesa()
{
    //cria e inicializa uma nova estrutura do tipo Mesa*, aloca na memória o tamanho da estrutura
    Mesa* novaMesa = (Mesa*)malloc(sizeof(Mesa));
    //variavel de repetição
    int i;

    //para cada uma das 4 celulas, sejam as livres e as naipes
    for(i=0;i<4;i++)
    {
        //inicializa cada uma das celulas, das naipes como estrutura pilha, e das livres como nula, por ser carta
        novaMesa->celulasNaipes[i] = criaPilha();
        novaMesa->cartaLivres[i] = NULL;
    }

    //a quantidade de celulas livres é definido por 4
    novaMesa->quantDeCartaLivres = i;

    //para cada uma das 8 celulas de cartas do tipo pilha
    for(i=0; i<8; i++)
    {
        //inicializa cada uma das 8 pilhas
        novaMesa->celulasPilhasDeCartas[i] = criaPilha();
    }

    //define a quantidade de pilhas de cartas vazia por 8 e a quantidade de pilhas naipes cheias como 0
    novaMesa->quantDePilhasDeCartasLivres = i;

    //retorna a nova Mesa* inicializada
    return novaMesa;
}

///
/// \brief comecarJogo, cria o baralho, embaralha ele e distrui as cartas para cada uma das pilhas de cartas
/// \param mesa inicializa e contendo pilhas de cartas, pilhas de naipes e celulas livres vazias
/// \pre mesa estar inicializada
/// \post as pilhas de cartas agora contém as 52 cartas do baralho
///
void comecarJogo(Mesa* mesa)
{
    //variavel i de repetição e variavel j que guarda o valor de i no limite que i pode ter, variavel e para embaralhar o baralho n vezes
    int i = 0, j, e = rand()%5 + 1;

    //cria um vetor de cartas e inicializa eles como nulo
    Carta* baralho[MAX_CARTAS] = {NULL};

    //coloca no vetor de cartas cada uma das 52 cartas, inicializadas e divididas por naipes
    criaBaralho(baralho);

    //embaralha o baralho por e vezes, e sendo um numero aleatorio de 1 a 5
    for(; e > 0; e--){
        //embaralha o vetor, randomizando como vai ser o vetor de cartas
        embaralhar(baralho);
    }

    //para cada umas das 52
    while(i<MAX_CARTAS)
    {
        //j vai ter o limite ate 8
        j = i%8;
        //insere na pilha de cartas ate 8, a carta do vetor de indice i
        mesa->celulasPilhasDeCartas[j] = inserirDoTipoPilha(mesa->celulasPilhasDeCartas[j], baralho[i]);
        i++;
    }
    //a quantidade de pilhas de cartas vazias é definido por 0
    mesa->quantDePilhasDeCartasLivres = 0;
}

///
/// \brief vazia, verifica se a pilha esta vazia, ou seja, não tem topo
/// \param pilha que será verifica se está vazia
/// \return o inverso do topo da pilha, se tem algo no topo, volta 0, se não tem, volta 1
/// \pre pilha inicializada
/// \post nenhuma
///
int vazia(Pilha* pilha)
{
    //retorna 1 se o topo for nulo, 0 se tiver topo
    return !pilha->topo;
}

///
/// \brief mostrarMesa, limpa a tela e imprime em sequencia: os indicadores, as celulas livres, as pilhas naipes e as pilhas cartas
/// \param mesa, contem os ponteiros para as pilhas de cartas, pilhas de naipes e celulas livres, para imprimir os conteudo
/// \pre mesa inicializada e contendo elementos
/// \post nenhuma
///
void mostrarMesa(Mesa* mesa)
{
    //variavel de repetição e a quantidade de linhas que a mesa tem, definida como 10 para ter um espaço a mais
    int i, linhas = 8;
    //vetor de nó, tendo maximo de 8
    Noh* inversas[MAX_PILHAS] = {NULL};

    //limpa todo o cmd
    system("CLS");

    printf("                                 FREE CELL\n");

    //imprime no cmd os indices das celulas livres e das celulas naipes que são os naipes
    printf("       A      B      C      D                 O      E      C      P    \n    ");


    //para cada celula livre
    for(i=0;i<4;i++)
    {
        //verifica se tem uma carta ocupando a celula
        if(mesa->cartaLivres[i]){
            //se tem, imprime a carta ocupante
            imprimeCarta(mesa->cartaLivres[i]);
        }
        //se não, imprime uma carta vazia
        else
            printf("|  ,  |");
    }

    printf("\t   ");

    //para cada uma das celulas naipes
    for(i=0;i<4;i++)
    {
        //se não esta vazia a celula naipe
        if(!vazia(mesa->celulasNaipes[i]))
            imprimeCarta(mesa->celulasNaipes[i]->topo->carta);
        //se esta vazia, imprime carta vazia
        else
            printf("|  ,  |");
    }

    //para cada pilha de carta
    for(i = 0 ; i < 8; i++)
    {
        //se tem a pilha de carta de indice i
        if(mesa->celulasPilhasDeCartas[i])
        {
            //inverte a pilha e guarda o nó cabeça da pilha no vetor de nó inversas
            inversas[i] = inverterParaPrintar(mesa->celulasPilhasDeCartas[i]->topo);
        }
    }

    //para cada pilha de carta
    for(i = 0; i < 8; i++)
    {
        //se o tamanho da pilha de carta é maior que o número de linhas definido
        if(mesa->celulasPilhasDeCartas[i]->tamanho > linhas)
        {
            //atribui o valor do tamanho da pilha + 1 a linhas
            linhas = mesa->celulasPilhasDeCartas[i]->tamanho+1;
        }
    }

    printf("\n");

    //para cada uma das linhas
    for(; linhas > 0; linhas--)
    {
        printf("\n      ");
        //para cada uma das 8 pilhas
        for(i=0; i<8;i++)
        {
            //se o nó tem algo
            if(inversas[i])
            {
                //imprime a carta do nó
                imprimeCarta(inversas[i]->carta);

                //avança o nó para o proxima nó
                inversas[i] = inversas[i]->prox;
                printf(" ");
            }
            //se o nó é nulo, imprime espaço em branco
            else
                printf("        ");
        }
    }

    //imprime os nomes de cada coluna pilha
    printf("\n         A       B       C       D       E       F       G       H\n");
}

///
/// \brief tipoDeOperacao, verifica qual é o tipo do comando que sera executado
/// \param leituraCMD, string contendo a linha de comando
/// \return o número da determinada operação a ser feita
/// \pre nenhuma
/// \post nenhuma
///
int operacao(char leituraCMD[])
{
    char colunaO, colunaD, celulaO;
    int quantCartas;
    char nomeArQ[MAX_STRING] = {0};
    int feito;

    //se nenhum comando foi escrito
    if(!leituraCMD[0]) return 7;

    //comando para fechar o jogo
    if(leituraCMD[0] == '*') return 10;

    //comando de ajuda
    if(leituraCMD[0] == '?') return 6;

    //scaneia e verifica se as regras para salvar o nome do arquivo é correto
    if(sscanf(leituraCMD, "salvar \"%[^\"]\%n", nomeArQ, &feito))
    {
        //se tiver um nome de arquivo
        if(feito)
        {
            int i;
            //verifica para cada caracter do nome
            for(i = 0; nomeArQ[i]; i++)
            {
                //se não é um caracter do alphabeto e essa letra é difente de '.' e de '_'
                if(!isalpha(nomeArQ[i]) && (nomeArQ[i] != '.' && nomeArQ[i] != '_'))
                {
                    return 8;
                }
            }
            //retorna o número da operação
            return 5;
        }
    }

    //se o comando é para passar uma carta para outra pilha
    if(sscanf(leituraCMD, " %d %c = %c", &quantCartas, &colunaO, &colunaD))
    {
        //se entra na regra da coluna origem de A até H
        if(toupper(colunaO) >='A' && toupper(colunaO) <='H')
        {
            //se a coluna destino é A até H
            if(toupper(colunaD) >='A' && toupper(colunaD) <='H')
                return 4;
        }
    }

    //se o comando é para colocar nas celulas livres
    if(sscanf(leituraCMD, " +%c > %c", &colunaO, &colunaD))
    {
        //se atende a regra de ser das colunas A até H
        if(toupper(colunaO) >= 'A' && toupper(colunaO) <='H')
        {
            //se a celula alvo é pertencente as celulas livres
            if(toupper(colunaD) >='A' && toupper(colunaD) <='D')
                return 1;
        }
    }

    //se o comando é para tirar das celulas livres
    if(sscanf(leituraCMD," -%c > %c", &celulaO, &colunaD))
    {
        //verifica se a celula origem pertence as celulas livres
        if(toupper(celulaO) >= 'A' && toupper(celulaO) <= 'D')
        {
            //se a coluna destino pertence as colunas pilhas de cartas
            if(toupper(colunaD) >= 'A' && toupper(colunaD) <= 'H')
                return 3;
        }
    }

    //se é para mandar a carta para as celulas naipes
    if(sscanf(leituraCMD," !%c ", &colunaO))
    {
        //se a coluna origem é pertencente as colunas de cartas
        if(toupper(colunaO) >='A' && toupper(colunaO) <= 'H')
            return 2;
    }

    return 8;
}

///
/// \brief operacoes, busca qual o tipo de operação e faz a chamada para essa operação ser feita
/// \param mesa, guarda e guardará qualquer operação a ser feita
/// \return se a operação foi feita ou não
/// \pre a mesa ser inicializada
/// \post a mesa vai ter seu conteudo alterado dependendo do tipo de operação feita
///
int operacoes(Mesa* mesa)
{
    char cmdCom, leituraCMD[MAX_STRING] = {0}, nomeArQ[MAX_STRING] = {0};
    char colunaI = 0, colunaF = 0;
    int quantDeMovimentos = 0;

    //scaneia a string do comando a ser feito
    scanf("%[^\n]%*c", leituraCMD);

    //chama a função que ve qual é o comando a ser feito
    cmdCom = operacao(leituraCMD);

    //enquanto tiver comandos
    while(cmdCom)
    {
        fflush(stdin);

        //se o comando é para colocar uma carta da pilha na celula livre
        if(cmdCom == 1)
        {
            //scaneia qual é a coluna de saida da carta e qual é a celula livre destino
            sscanf(leituraCMD, " +%c > %c", &colunaI, &colunaF);

            casoCartaLivre(mesa, toupper(colunaI), toupper(colunaF));
            break;
        }

        //se o comando é para colocar uma carta da pilha na pilha naipe
        if(cmdCom == 2)
        {
            //scaneia a coluna de saida
            sscanf(leituraCMD, " !%c", &colunaI);

            casoPilhaNaipe(mesa, toupper(colunaI));
            break;
        }

        //se o comando é para tirar da celula livre e colocar nas pilhas cartas
        if(cmdCom == 3)
        {
            //scaneia a celula livre de saida da carta e a pilha destino
            sscanf(leituraCMD, " -%c > %c", &colunaI, &colunaF);

            tiraDaCartaLivre(mesa, toupper(colunaI), toupper(colunaF));
            break;
        }

        //se é para mover a carta para outra coluna
        if(cmdCom == 4)
        {   //scaneia a quantidade de cartas a ser movidas e as colunas origem e destino
            sscanf(leituraCMD, " %d %c = %c", &quantDeMovimentos, &colunaI, &colunaF);

            moverParaTalPilha(mesa, toupper(colunaI), quantDeMovimentos,toupper(colunaF));
            break;
        }

        //se é para salvar o jogo
        if(cmdCom == 5)
        {
            sscanf(leituraCMD, " salvar \"%[^\"]\"", nomeArQ);
            //salva o jogo no arquivo
            salvarOJogo(mesa, nomeArQ);
            break;
        }

        //se é ajuda
        if(cmdCom == 6)
        {
            mostrarAjuda();
            break;
        }

        //se é para parar o jogo
        if(cmdCom == 10)
            return 1;

        //se não é nenhum dos comando listado acima
        else
        {
            //limpa a tela e imprime a mesa
            mostrarMesa(mesa);

            //mensagens de error no comando e chamada de novo comando
            printf("                              Comando Invalido!\n");
            printf("    Entre com um comando: ");

            //scaneia a nova string comando e verifica que tipo de operação é
            scanf("%[^\n]%*c", leituraCMD);
            cmdCom = operacao(leituraCMD);
        }
    }

    getch();

    return 0;
}

