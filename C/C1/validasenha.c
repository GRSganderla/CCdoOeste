#include <stdio.h>
#include <string.h>

int validaSenha(char senha[]){

    int i, certo=0, errado = 0;
    int tam = strlen(senha);

    if(tam >= 6 && tam <= 32){

        errado = 1;
        for(i = 0; i < tam; i++){

            if((senha[i] >= '0') && (senha[i] <= '9')){

                certo++;
            }

            else if((senha[i] >= 'a' && senha[i] <= 'z')){

                    certo++;
            }

            else if((senha[i] >= 'A' && senha[i] <= 'Z')){

                    certo++;
            }

            else 
            {
                errado = 0;
                break;
            }
        }
    }

    if(certo >= 3 && errado){

        return 1;
    }

    else{

        return 0;
    }
}

int main(){
    
    char senha[50];
    int i, chamaFun;

    while(gets(senha)){
    
        chamaFun = validaSenha(senha);

        if(chamaFun == 1){

            printf("Senha valida.\n");
        }

        else{

            printf("Senha invalida.\n");
        }
    }

    return 0;
}