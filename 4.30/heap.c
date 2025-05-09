#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct PriorityQueue {
    int heap[MAX_SIZE];
    int size;
} PriorityQueue;

// 초기화
void init(PriorityQueue *pq) {
    pq->size = 0;
}

// swap 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(PriorityQueue *pq, int value) {
    if (pq->size >= MAX_SIZE - 1) {
        printf("힙이 가득 찼습니다.\n");
        return;
    }

    pq->size++;
    int i = pq->size;
    pq->heap[i] = value;

    
    while (i > 1 && pq->heap[i] > pq->heap[i / 2]) {
        swap(&pq->heap[i], &pq->heap[i / 2]);
        i = i / 2;
    }
}
void printheap(PriorityQueue pq){
    for(int i=1;i<=pq.size;i++){
        printf("%d ",pq.heap[i]);
    }
    printf("\n");
}

int deleteMax(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("힙이 비어 있습니다.\n");
        return -1;
    }

    int maxValue = pq->heap[1]; 
    pq->heap[1] = pq->heap[pq->size--];  
    int i = 1;

    // 자식 중 더 큰 값과 비교하면서 아래로 내림
    while (i * 2 <= pq->size) {
        int left = i * 2;
        int right = i * 2 + 1;
        int larger = left;

        if (right <= pq->size && pq->heap[right] > pq->heap[left]) {
            larger = right;
        }

        if (pq->heap[i] >= pq->heap[larger]) break;

        swap(&pq->heap[i], &pq->heap[larger]);
        i = larger;
    }

    return maxValue;
}

// 루트 확인
int peek(PriorityQueue *pq) {
    if (pq->size == 0) return -1;
    return pq->heap[1];
}

// 테스트
int main() {
    PriorityQueue pq;
    init(&pq);

    insert(&pq, 30);
    insert(&pq, 50);
    insert(&pq, 40);
    insert(&pq, 10);
    insert(&pq, 60);

    printf("최대값: %d\n", peek(&pq));  // 60
    printf("삭제된 값: %d\n", deleteMax(&pq));  // 60
    printf("최대값: %d\n", peek(&pq));  // 50

    return 0;
}
