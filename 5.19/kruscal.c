#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

int *parent, *rank_arr;

//초기화
void make_set(int n) {
    parent = malloc((n+1) * sizeof(int));
    rank_arr = malloc((n+1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank_arr[i] = 0;
    }
}

// 찾기
int find_set(int x) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank_arr[a] < rank_arr[b]) {
            parent[a] = b;
        } else {
            parent[b] = a;
            if (rank_arr[a] == rank_arr[b])
                rank_arr[a]++;
        }
    }
}

// 간선 비교 함수 (qsort용)
int cmp_edge(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    Edge *edges = malloc(E * sizeof(Edge));
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    // 1) 간선 정렬
    qsort(edges, E, sizeof(Edge), cmp_edge);

    // 2) 유니온–파인드 초기화
    make_set(V);

    int mst_weight = 0, cnt = 0;
    printf("Kruskal MST edges:\n");
    for (int i = 0; i < E && cnt < V-1; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (find_set(u) != find_set(v)) {
            union_set(u, v);
            printf("%d -- %d (w=%d)\n", u, v, w);
            mst_weight += w;
            cnt++;
        }
    }
    printf("Total weight: %d\n", mst_weight);

    free(edges);
    free(parent);
    free(rank_arr);
    return 0;
}
