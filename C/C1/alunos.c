#include <stdio.h>
#include <stdlib.h>

struct Data{
    
    int dia;
    int mes;
    int ano;
    
}; typedef struct Data TData;

struct Aluno{
    
    char nome[100];
    TData data;
    float nota;

}; typedef struct Aluno TAluno;

TAluno* aloca(int n){
    
    TAluno *aluno = (TAluno*)malloc(sizeof(TAluno)*n);
    
    for(int i = 0; i < n; i++)
    {
        aluno[i].nome[0] = '\0';
        aluno[i].data.dia = 0;
        aluno[i].data.mes = 0;
        aluno[i].data.ano = 0;
        aluno[i].nota = 0;
    }

    return aluno;
}

void carrega(TAluno *aluno){
    
    printf("Entre com o nome completo: ");
    scanf("%s", (*aluno).nome);
    
    printf("Entre com a data de matricula: ");
    scanf("%d %d %d", &(*aluno).data.dia, &(*aluno).data.mes, &(*aluno).data.ano);
    
    printf("Entre com a nota: ");
    scanf("%f", &(*aluno).nota);
}

void mediaArit(TAluno *aluno, int n){
    
    float media;
    int i;
    
    for(i = 0; i < n; i++){
        
        media += aluno[i].nota;
    }
    
    media = media/n;
    
    printf("Media Aritmetica: %f", media);
}

void desaloca(TAluno *aluno, int n){
        
    (*aluno).nome[0] = '\0';
    (*aluno).data.dia = 0;
    (*aluno).data.mes = 0;
    (*aluno).data.ano = 0;
    (*aluno).nota = 0;
}

int main(){
    
    int n, i;
    TAluno* aluno;
    
    printf("Entre com o numero de alunos: ");
    scanf("%d", &n);
    
    aluno = aloca(n);
    
    for(i = 0; i < n; i++){
        
        printf("\nAluno[%d]:\n", i);
        carrega(&aluno[i]);
    }
    
    mediaArit(aluno, n);
    desaloca(aluno, n);
    
    return 0;
}