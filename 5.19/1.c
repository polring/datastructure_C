//2022110037 전민제
#include <stdio.h>
#include <stdlib.h>
#define MAX 200

typedef struct{
    int i,j,min;
}edge;
// setFInd 함수 구현 
int setFind(int *parent,int a){
    if(parent[a]!=a){
        parent[a] = setFind(parent,parent[a]);
    }
    return parent[a];
}
//노드 a,b 각각 찾은다음 한쪽을 다른 쪽 부모로 만든다.
void setUnion(int *parent,int a,int b){
    a = setFind(parent,a);
    b = setFind(parent,b);
    if(a!=b){
        parent[a] = b;
    }
}
// 크루스칼 알고리즘 실행
void kruskal(int **arr,int n){
    int visited[MAX][MAX] = {0,};
    int *parent = malloc(sizeof(int)*n);
    for(int i = 0;i<n;i++){
        parent[i] = i;
    }
    edge data[MAX];
    edge value;
    int cnt = 0;
    while(cnt < n-1){
        value.i = -1;
        value.j = -1;
        value.min = MAX;
        for(int i =0;i<n;i++){
            for(int j = i+1;j<n;j++){
                if(!visited[i][j]&&arr[i][j]>0&&arr[i][j] < value.min){
                    value.min = arr[i][j];
                    value.i = i;
                    value.j = j;
                }
            }
        }
        visited[value.i][value.j] = visited[value.j][value.i] = 1;
        printf("try (%d, %d, %d)==> ",value.i,value.j,value.min);
        
        if(setFind(parent,value.i)!=setFind(parent,value.j)){
            setUnion(parent,value.i,value.j);
            printf("OK\n");
            data[cnt++] = value;
        }
        else{
            printf("cycle\n");
        }
    }
    printf("\n(edge):weight\n");
    for(int i =0;i<cnt;i++){
        printf("(%2d,%3d): %d\n",data[i].i,data[i].j,data[i].min);
    }
    free(parent);
}

int main(){
    int n;
    FILE *fp = fopen("in.txt","r");
    fscanf(fp,"%d",&n);
    int **arr = malloc(sizeof(int*)*n);
    for(int i =0;i<n;i++){
        arr[i] = calloc(n,sizeof(int));
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fscanf(fp,"%d",&arr[i][j]);
        }
    }

    fclose(fp);
    kruskal(arr,n);
    for(int i=0;i<n;i++){
        free(arr[i]);
    }
    free(arr);
}