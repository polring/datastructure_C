#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}node;
typedef struct{
    node** pointer;
    int rear;
    int front;
}Queue;
node* createNode(int data){
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
void init(Queue *a,int k){
    a->pointer = malloc(sizeof(node*)*k);
    a->front = -1;
    a->rear = -1;
}
int isEmpty(Queue a){
    return a.front == a.rear;
}
void enqueue(Queue *a ,node *pointer){
    a->pointer[++(a->rear)] = pointer;
}

node* dequeue(Queue *a){
    return a->pointer[++(a->front)];
}
//트리 생성하는 함수
void maketree(node **root,int data){
    if(data > 100) return;
    node * newnode = createNode(data);
    *root = newnode;
    maketree((&(*root)->left),2*data);    
    maketree(&((*root)->right),3*data);
}
// bfs를 이용한 level order 출력
void levelorder(node* root,int k){
    Queue a;
    init(&a,k);
    node* temp = NULL;
    if(root){
        enqueue(&a,root);
    }
    while(!isEmpty(a)){
        temp = dequeue(&a);
        printf("(%d) ",temp->data);
        if(temp->left != NULL){
            enqueue(&a,temp->left);
        }
        if(temp->right != NULL){
            enqueue(&a,temp->right);
        }
    }
}//postorder 순회
void postorder(node* root){
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("(%d) ",root->data);
}
//node 개수 세기
int countNodes(node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}
// 트리 height 측정
int height(node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
// 리프 노드는 자식이 없는 노드를 의미함
int countLeafNodes(node* root) {
    if (root == NULL) {
        return 0;
    }
    // 리프 노드 조건: 왼쪽, 오른쪽 자식이 모두 NULL
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}
void printNodesAtLevel(node* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else {
        printNodesAtLevel(root->left, level - 1);
        printNodesAtLevel(root->right, level - 1);
    }
}

int main(){
    int n;
    printf("input number: ");
    scanf("%d",&n);
    node *root;
    maketree(&root,n);
    printf("\nheight : %d\n",height(root));
    printf("Node 개수: %d\n",countNodes(root));
    printf("Leaf node개수: %d\n",countLeafNodes(root));
    printf("\n");
    printf("input level: ");
    int level;
    scanf("%d",&level);
    printNodesAtLevel(root,level);
    printf("\n");
    printf("\nPostorder traversal: ");
    postorder(root);
    printf("\nLevelorder traversal: ");
    levelorder(root,100);
}
