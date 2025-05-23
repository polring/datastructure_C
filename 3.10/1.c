#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1001
//배열 안에서 스왑을 구현한 함수
void swap(int *arr,int i,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] =temp;
}
// 선택 정렬을 구현한 함수
void selection(int *arr,int size){
    int i,j,min,temp;
    for(i=0;i<size-1;i++){
        min = i;
        for(j=i+1;j<size;j++){
            if(arr[j]<arr[min]){
                min = j;
            }
        }
        swap(arr,i,min);
    }
}
// main
int main(){
    int i,n,step = 10;
    int a[MAX_SIZE];
    double duration;
    clock_t start,end;

    printf("   n      time\n");
    for(n=0;n<=1000;n+=step){
        for(i=0;i<n;i++){
            a[i] = n-i;
        }
        start = clock();
        selection(a,n);
        end = clock();
        duration = ((double)(end-start))/CLOCKS_PER_SEC;
        printf("%6d    %f\n",n,duration);
        if(n==100){
            step = 100;
        }
    }
}