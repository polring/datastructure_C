#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int front, rear, *arr;
} queue;
// 원형 큐 풀 체크
int isFullCircle(queue *a, int size) {
     return ((a->rear + 1) % size) == a->front; 
}
// 큐가 비었는지 체크
int isEmpty(queue *a){
     return a->front == a->rear; 
}
// 선형 큐 풀 체크
int isFullList(queue *a, int size) {
     return a->rear == size - 1;
}
// 원형 큐 추가
void addCircle(queue *a, int data, int size) {
    if (isFullCircle(a, size)) return;
    a->rear = (a->rear + 1) % size;
    a->arr[a->rear] = data;
}
// 원형 큐 삭제
void deleteCircle(queue *a, int size) {
    if (isEmpty(a)) return;
    a->front = (a->front + 1) % size;
}
// 선형 큐 추가;
void addList(queue *a, int data, int size) {
    a->arr[++(a->rear)] = data;
}
// 선형 큐 삭제
void deleteList(queue *a) {
    if (isEmpty(a)) return;
    a->front++;
}
// 원형 큐 출력;
void printCircle(queue *Circle, int size) {
    int i = (Circle->front + 1) % size;
    while (i != (Circle->rear + 1)%size) {
        printf("%d ", Circle->arr[i]);
        i = (i + 1) % size;
    }
    printf("\n");
}
// 선형 큐 출력
void printList(queue *List, int size) {
    for (int i = List->front + 1; i <= List->rear; i++) {
        printf("%d ", List->arr[i]);
    }
    printf("\n");
}
void scan(char *fileName) {
    FILE *fp = fopen(fileName, "r");
    int size;
    fscanf(fp, "%d", &size);
    queue circle = {0, 0, malloc(sizeof(int) * size)};
    queue list = {-1, -1, malloc(sizeof(int) * size)};
    printf("Queue size: %d\n", size);
    printf("\n");

    char cur;
    char data;
    int number;
    while (fscanf(fp," %c",&cur)==1) {
        if (cur == 'q'){
            break;
        } 
        if (cur == 'a') {
            fscanf(fp, " %c", &data);
            number = data - '0';
            printf("add (%d)\n", number);
            printf("[Cqueue] ");
            if (isFullCircle(&circle, size))
                printf("Full. Not Add.\n");
            else{ 
                addCircle(&circle, number, size); 
                printCircle(&circle, size); 
            }
            printf("[Lqueue] ");
            if(isFullList(&list, size)) 
                printf("Full. Not Add.\n");
            else{
                addList(&list, number, size);
                printList(&list, size); 
            }
        } else {
            printf("Delete\n");
            printf("[Cqueue] ");
            if (isEmpty(&circle)) 
                printf("Empty. Not delete.\n");
            else {
                
                    deleteCircle(&circle, size); 
                    if(isEmpty(&circle)){
                        printf("Empty.\n");
                    }
                    else{
                        printCircle(&circle, size); 
                    }
            }
            printf("[Lqueue] ");
            if (isEmpty(&list)) 
                printf("Empty. not delete. \n");
            else{ 
                deleteList(&list); 
                if(isEmpty(&list)){
                    printf("Empty.\n");
                }
                else{
                    printList(&list, size); 
                }
            }
        }
    }
    fclose(fp);
    free(circle.arr);
    free(list.arr);
}

int main() {
    scan("in1.txt");
    scan("in2.txt");
    scan("in3.txt");
    return 0;
}