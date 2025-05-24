//2022110037 전민제
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student{
    char name[10];
    int score;
}student;
void insertionSorting(student *arr,int n){
    student temp;
    int j;
    for(int i = 1; i < n;i++){
        temp = arr[i];
        for(j = i-1;j>=0;j--){
            if(temp.score > arr[j].score){
                arr[j+1] = arr[j];
            }
            else{
                break;
            }
        }
        arr[j+1] = temp;
    }
}
void quickSort(student *arr,int left,int right){
    int pivot,i,j;
    student tmp;
    if(left < right){
        i = left-1, j = right;
        pivot = arr[right].score;
        printf("Pivot: %d\n",pivot);
        do{
            do{
                i++;
            }while(arr[i].score > pivot);
            do{
                j--;
            }while(arr[j].score < pivot);
            if(i < j){
                tmp = arr[i], arr[i] = arr[j], arr[j] = tmp;
            }

        }while(i < j);
        tmp = arr[right], arr[right] = arr[i],arr[i] = tmp;
        quickSort(arr,left,i-1);
        quickSort(arr,i+1,right);

    }
}
void printInsertionSorting(student *arr,int n){
    printf("[Insert sort]\n");
    insertionSorting(arr,n);
    for(int i = 0; i < n; i++){
        printf("%8s:%4d\n",arr[i].name,arr[i].score);
    }
}
void printQuickSorting(student *arr, int n){
    printf("[Quick sort]\n");
    quickSort(arr,0,n-1);
     for(int i = 0; i < n; i++){
        printf("%8s:%4d\n",arr[i].name,arr[i].score);
    }
}

int main(){
    FILE *fp = fopen("in.txt","r");
    student *students1,*students2;
    int n;
    fscanf(fp,"%d",&n);
    students1 = malloc(sizeof(student)*n);
    students2 = malloc(sizeof(student)*n);
    for(int i = 0 ;i<n;i++){
        fscanf(fp,"%s %d",students1[i].name,&students1[i].score);
        strcpy(students2[i].name,students1[i].name);
        students2[i].score = students1[i].score;

    }
    printInsertionSorting(students1,n);
    printQuickSorting(students2,n);
    free(students1);
    free(students2);
    fclose(fp);


}