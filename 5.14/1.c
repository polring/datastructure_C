//2022110037 전민제
#include <stdio.h>
#include <stdlib.h>
#define max 100
typedef struct Node{
    int data;
    struct Node* next;
}node;
typedef struct{
    int front;
    int rear;
    int arr[max];
}queue;
void init(queue *a){
    a->rear = a->front = -1;   
}
void enqueue(queue* q, int value) {
    q->arr[++q->rear] = value;
}


int dequeue(queue* q) {
    return q->arr[++q->front];
}

int isEmpty(queue a){
    return a.front == a.rear;
}
node* createNode(int data){
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
void append(node **head,int data){
    node* newnode = createNode(data);
    newnode->next = *head;
    *head = newnode;
}
void graphinit(int *visit,int n){
    for(int i=0;i<n;i++){
        visit[i] = 0;
    }
}
void simplepath(node** head, int *visited, int n, int start, int end) {
    int parent[max];
    for (int i = 0; i < n; i++) parent[i] = -1;
    queue q;
    init(&q);
    graphinit(visited,n);
    visited[start] = 1;
    enqueue(&q, start);

    int found = 0;

    while (!isEmpty(q)) {
        int current = dequeue(&q);
        if (current == end) {
            found = 1;
            break;
        }

        node* temp = head[current];
        while (temp) {
            int next = temp->data;
            if (!visited[next]) {
                visited[next] = 1;
                parent[next] = current;
                enqueue(&q, next);
            }
            temp = temp->next;
        }
    }

    printf("BFS path(%d==>%d):\n", start, end);
    if (!found) {
        printf("No path\n");
        return;
    }
    for (int v = end; v != -1; v = parent[v]) {
        printf("%d ", v);
        if (v == start) break;
    }
    printf("\n");
}

void DFS(node** head,int *visited,int v) {
    visited[v] = 1;
    printf("%3d", v);
    node* temp = head[v];
    while (temp != NULL) {
        int u = temp->data;
        if (!visited[u]) {
            DFS(head,visited, u);
        }
        temp = temp->next;
    }
}

void BFS(node** head, int* visited, int v) {
    queue q;
    init(&q);
    visited[v] = 1;
    enqueue(&q, v);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(&q);
        printf("%3d", currentVertex);

        node* temp = head[currentVertex];
        while (temp) {
            int adj = temp->data;
            if (!visited[adj]) {
                visited[adj] = 1;
                enqueue(&q, adj);
            }
            temp = temp->next;
        }
    }
}
void connectedDfs(node**head,int *visited,int n) {
    int count = 0;
    printf("DFS connected component\n");
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Component %d: ",count);
            DFS(head,visited, i);
            printf("\n");
            count++;
        }
    }
}


void connectedBfs(node** head, int* visited, int n) {
    int count = 0;
    printf("\nBFS connected component\n");
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Component %d: ", count);
            BFS(head, visited, i);
            printf("\n");
            count++;
        }
    }
}


void freelist(node *head){
    node* temp = head;
    while(head){
        temp = head;
        head = head->next;
        free(head);
    }
}

int main(){
    FILE *fp = fopen("in.txt","r");
    int x,y;
    int vertex,edge;
    fscanf(fp,"%d %d",&vertex,&edge);
    node** head = calloc(vertex+1,sizeof(node*));
    int *visit = calloc(vertex + 1,sizeof(int));
    for(int i=0;i<edge;i++){
        fscanf(fp,"%d %d",&x,&y);
        append(head+x,y);
        append(head+y,x);   
    }
    connectedDfs(head,visit,vertex+1);
    graphinit(visit,vertex+1);
    connectedBfs(head,visit,vertex+1);
    int start,end;
    while(1){
        printf("\nInput (from to): ");
        scanf("%d %d",&start,&end);
        if(start == -1 && end == -1){
            return 0;
        }
        simplepath(head,visit,vertex + 1,start,end);
        
    }

    fclose(fp);
    for(int i=0;i<=vertex;i++){
        freelist(head[i]);
    }

    free(head);

}