#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// 인접 리스트용 노드
typedef struct AdjNode {
    int v, w;
    struct AdjNode *next;
} AdjNode;

// 최소 힙용 요소
typedef struct {
    int v, key;
} HeapNode;

// 최소 힙 구조체
typedef struct {
    HeapNode *harr;
    int size;
    int capacity;
    int *pos;  // vertex → heap index
} MinHeap;

// 새로운 인접 리스트 노드 생성
AdjNode* newAdjNode(int v, int w) {
    AdjNode* node = malloc(sizeof(AdjNode));
    node->v = v;
    node->w = w;
    node->next = NULL;
    return node;
}

// 그래프 (인접 리스트)
typedef struct {
    int V;
    AdjNode **array;
} Graph;

// 그래프 생성
Graph* createGraph(int V) {
    Graph* g = malloc(sizeof(Graph));
    g->V = V;
    g->array = malloc((V+1) * sizeof(AdjNode*));
    for (int i = 1; i <= V; i++)
        g->array[i] = NULL;
    return g;
}

// 무향 그래프에 간선 추가
void addEdge(Graph* g, int u, int v, int w) {
    AdjNode* node = newAdjNode(v, w);
    node->next = g->array[u];
    g->array[u] = node;
    node = newAdjNode(u, w);
    node->next = g->array[v];
    g->array[v] = node;
}

// 최소 힙 생성
MinHeap* createMinHeap(int capacity) {
    MinHeap* mh = malloc(sizeof(MinHeap));
    mh->pos = malloc((capacity+1) * sizeof(int));
    mh->size = 0;
    mh->capacity = capacity;
    mh->harr = malloc((capacity+1) * sizeof(HeapNode));
    return mh;
}

// 힙 노드 교환
void swapHeapNode(HeapNode *a, HeapNode *b) {
    HeapNode t = *a; *a = *b; *b = t;
}

// heapify (상향)
void minHeapify(MinHeap* mh, int idx) {
    int smallest = idx;
    int left = 2*idx, right = 2*idx+1;
    if (left <= mh->size && 
        mh->harr[left].key < mh->harr[smallest].key)
        smallest = left;
    if (right <= mh->size && 
        mh->harr[right].key < mh->harr[smallest].key)
        smallest = right;
    if (smallest != idx) {
        // pos 업데이트
        mh->pos[mh->harr[smallest].v] = idx;
        mh->pos[mh->harr[idx].v]      = smallest;
        // 교환 후 재귀 호출
        swapHeapNode(&mh->harr[smallest], &mh->harr[idx]);
        minHeapify(mh, smallest);
    }
}

// 힙에 삽입 또는 key 감소
void decreaseKey(MinHeap* mh, int v, int key) {
    int i = mh->pos[v];
    mh->harr[i].key = key;
    while (i > 1 && mh->harr[i].key < mh->harr[i/2].key) {
        // pos 교환
        mh->pos[mh->harr[i].v]   = i/2;
        mh->pos[mh->harr[i/2].v] = i;
        swapHeapNode(&mh->harr[i], &mh->harr[i/2]);
        i = i/2;
    }
}

// 최소 키를 가진 노드 추출
HeapNode extractMin(MinHeap* mh) {
    HeapNode root = mh->harr[1];
    HeapNode last = mh->harr[mh->size--];
    mh->harr[1] = last;
    mh->pos[root.v] = mh->pos[last.v] = 1;
    minHeapify(mh, 1);
    return root;
}

// 힙에 아직 있는지 확인
int isInMinHeap(MinHeap *mh, int v) {
    return mh->pos[v] <= mh->size;
}

// Prim 수행
void primMST(Graph* g) {
    int V = g->V;
    int *parent = malloc((V+1)*sizeof(int));
    int *key    = malloc((V+1)*sizeof(int));
    MinHeap *mh = createMinHeap(V);

    // 초기화
    for (int v = 1; v <= V; v++) {
        key[v] = INF;
        mh->harr[v] = (HeapNode){v, key[v]};
        mh->pos[v]  = v;
    }
    key[1] = 0;
    decreaseKey(mh, 1, 0);
    mh->size = V;

    while (mh->size) {
        HeapNode hn = extractMin(mh);
        int u = hn.v;

        // u의 인접 리스트 순회
        for (AdjNode *p = g->array[u]; p; p = p->next) {
            int v = p->v;
            if (isInMinHeap(mh, v) && p->w < key[v]) {
                key[v]    = p->w;
                parent[v] = u;
                decreaseKey(mh, v, key[v]);
            }
        }
    }

    printf("Prim MST edges:\n");
    int total = 0;
    for (int v = 2; v <= V; v++) {
        printf("%d -- %d (w=%d)\n", parent[v], v, key[v]);
        total += key[v];
    }
    printf("Total weight: %d\n", total);

    free(parent);
    free(key);
    free(mh->harr);
    free(mh->pos);
    free(mh);
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    Graph* g = createGraph(V);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(g, u, v, w);
    }

    primMST(g);

    // 인접 리스트 메모리 해제
    for (int i = 1; i <= V; i++) {
        AdjNode *p = g->array[i], *next;
        while (p) {
            next = p->next;
            free(p);
            p = next;
        }
    }
    free(g->array);
    free(g);
    return 0;
}
