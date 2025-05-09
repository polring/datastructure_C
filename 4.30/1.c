//2022110037
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
typedef struct{
    int key;
    int time;
}element;
typedef struct{
    element heap[MAX_SIZE];
    int size;
} PriorityQueue;
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(PriorityQueue *pq, element vlaue) {
    int i = ++pq->size;
    pq->heap[i].key = vlaue.key;
    pq->heap[i].time = vlaue.time;

    while (i > 1 && pq->heap[i].time < pq->heap[i / 2].time) {
        swap(&(pq->heap[i].key), &(pq->heap[i / 2].key));
        swap(&(pq->heap[i].time), &(pq->heap[i / 2].time));
        i /= 2;
    }
}

int pop(PriorityQueue *pq) {
    int minvalue = pq->heap[1].key;  
    pq->heap[1] = pq->heap[pq->size--];  
    int i = 1;

    while (i * 2 <= pq->size) {
        int left = i * 2;
        int right = i * 2 + 1;
        int smaller = left;

        if (right <= pq->size && pq->heap[right].time < pq->heap[left].time) {
            smaller = right;
        }

        if (pq->heap[i].time <= pq->heap[smaller].time) break;
        swap(&(pq->heap[i].key), &(pq->heap[smaller].key));
        swap(&(pq->heap[i].time), &(pq->heap[smaller].time));
        
        i = smaller;
    }

    return minvalue;
}
void changeValue(PriorityQueue* pq, int id, int newTime) {
    int index = -1;
    int oldTime;

    for (int i = 1; i <= pq->size; i++) {
        if (pq->heap[i].key == id) {
            index = i;
            oldTime = pq->heap[i].time;
            pq->heap[i].time = newTime;
            break;
        }
    }


    if (newTime < oldTime) {
        int i = index;
        while (i > 1 && pq->heap[i].time < pq->heap[i / 2].time) {
            swap(&pq->heap[i].key, &pq->heap[i / 2].key);
            swap(&pq->heap[i].time, &pq->heap[i / 2].time);
            i /= 2;
        }
    }
    else if (newTime > oldTime) {
        int i = index;
        while (i * 2 <= pq->size) {
            int left = i * 2;
            int right = i * 2 + 1;
            int smallest = left;

            if (right <= pq->size && pq->heap[right].time < pq->heap[left].time) {
                smallest = right;
            }
            if (pq->heap[i].time <= pq->heap[smallest].time) break;
            swap(&pq->heap[i].key, &pq->heap[smallest].key);
            swap(&pq->heap[i].time, &pq->heap[smallest].time);
            i = smallest;
        }
    }
}

void printheap(PriorityQueue pq){
    for(int i=1;i<=pq.size;i++){
        printf("%d ",pq.heap[i].key);
    }
    printf("\n");
}



int main() {
    PriorityQueue pq;
    pq.size = 0;
    for(int i=0;i<MAX_SIZE;i++){
        pq.heap[i].time = 0;
    }
    FILE *fp = fopen("in.txt","r");
    int n;
    element data;
    fscanf(fp,"%d",&n);
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d",&data.key,&data.time);
        insert(&pq,data);
    }

    printf("Min heap level order traversal:\n");
    printheap(pq);
    printf("\n연속으로 2번 pop: (%d, %d) (%d, %d)\n",pq.heap[1].key,pq.heap[1].time,pq.heap[2].key,pq.heap[2].time);
    
    pop(&pq);
    pop(&pq);
    printheap(pq);
    int id,time;
    while(1){
        printf("\n변경할 task ID, time 입려: ");
        scanf("%d %d",&id,&time);
        if(id < 0){
            return 0;
        }
        changeValue(&pq,id,time);
        printf("\ntask %d의 time을 %d로 변경 후 heap:\n",id,time);
        printheap(pq);
    }



    
}
