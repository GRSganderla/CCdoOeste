#include <stdio.h>

void diaSeguinte(int *dia, int *mes, int *ano){
    
    if((*mes) == 12 && (*dia) == 30){
        
        (*dia) = 1;
        (*mes) = 1;
        (*ano)++;
    }
    else if((*dia) == 30){
        
        (*dia) = 1;
        (*mes)++;
    }
    else{
        
        (*dia)++;
    }
}

int main(){
    
    int i = 1, n, dia, mes, ano;
    
    printf("Entre com o numero de datas: ");
    scanf("%d", &n);
        
    while(i <= n){

        printf("Entre com a data: ");
        scanf("%d %d %d", &dia, &mes, &ano);
        
        if((dia >= 1 && dia <= 30) && (mes >=1 && mes <= 12)){
        
            diaSeguinte(&dia, &mes, &ano);
            printf("Data seguinte: %d/%d/%d\n", dia, mes, ano);
            i++;
        }
        
        else{
        
            printf("Data invalida. Tente outra.\n");
            scanf("%d %d %d", &dia, &mes, &ano);
        }
    }
    
    return 0;
}