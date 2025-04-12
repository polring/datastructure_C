//2022110037 전민제
#include <stdio.h>
#include <stdlib.h>

//메모리 해제
void free3DArray(int ***ptr,int i,int j,int k){
    for(int a=0;a<i;a++){
        for(int b=0;b<j;b++){
            free(ptr[a][b]);
        }
        free(ptr[a]);
    }
    free(ptr);
}
// 3차원 배열 출력
void print3DArray(int ***ptr,int i,int j,int k){
    for(int a=0;a<i;a++){
        for(int b=0;b<j;b++){
            for(int c=0;c<k;c++){
                printf("A[%d][%d][%d]=%d ",a,b,c,ptr[a][b][c]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main(){
    int i,j,k;
    printf("A[I][J]{k}\n");
    printf("Input I: ");
    scanf("%d",&i);
    printf("Input J: ");
    scanf("%d",&j);
    printf("Input K: ");
    scanf("%d",&k);
    int ***ptr = malloc(sizeof(int**)*i);
    for(int a=0;a<i;a++){
        ptr[a] = malloc(sizeof(int *)*j);
        for(int b=0;b<j;b++){
            ptr[a][b] = malloc(sizeof(int)*k);
            for(int c=0;c<k;c++){
                ptr[a][b][c]= a*100+b*10+c;
            }
        }
    }
    print3DArray(ptr,i,j,k);
    free3DArray(ptr,i,j,k);
}