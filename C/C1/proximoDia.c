#include<stdio.h>
#include<stdlib.h>

void diaseguinte(int *dia, int *mes, int *ano){

    if((*dia)<30)
        (*dia)++;

    else if((*dia)==30 && (*mes)<12){
        (*dia)=1;
        (*mes)++;
    }

    else if((*dia)==30 && (*mes)==12){

        (*dia)=1;
        (*mes)=1;
        (*ano)++;
    }
}


int main(){

    int n,i=0;
    int dia, mes, ano;

    printf("digite a quantidade de datas que deseja adicionar: ");
    scanf("%d",&n);
    printf("\n");

    while(i<n){

        printf("digite a data: ");
        scanf("%d %d %d",&dia,&mes,&ano);
        printf("\n");

        if((dia>0 && dia<=30)&&(mes>0 && mes<=12) && (ano>0)){
            
            diaseguinte(&dia, &mes, &ano);

            printf("dia seguinte: %d %d %d\n", dia, mes, ano);

            i++;
        }

        else 
            printf("data invalida\n");

    }


    return 0;
} 