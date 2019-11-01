#include<stdio.h>
#include<stdlib.h>

int main(){

    int mat[5][5], i, j;

    for(i = 0; i < 5; i++){

        for(j = 0; j < 5; j++){

            if(i >= j && i > 0){
                mat[i][j] = mat[i-1][j] + 5 - (i-1) + j;
            }
            else{
                mat[i][j] = 0;
            }
            mat[i][i] = i+1;
        }
    }

    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }

    return 0;
}