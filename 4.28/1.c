//2022110037 전민제
#include <stdio.h>
#include <stdlib.h>
int count = 0;
int countleaf = 0;
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
// bfs를 이용한 출력
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
}
// postorder
void postorder(node* root){
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("(%d) ",root->data);
}
// 노드 개수 카운트 
void nodecount(node* root){
    if(!root) return;
    nodecount(root->left);
    nodecount(root->right);
    count++;
}
// 높이 찾는 함수
int height(node *root){
    if(!root) return 0;
    
    int heightleft = height(root->left);
    int heightright = height(root->right);
    return (heightleft > heightright ? heightleft : heightright) + 1; 
}
// 리프노드 찾는 함수
void leafcount(node *root){
    if(!root){
        return;
    }
    if(root->left == NULL && root->right == NULL){
        countleaf++;
    }
    leafcount(root->left);
    leafcount(root->right);
    
}
// 특정 레벨의 노드 출력
void printlevel(node* root,int level){
    if (!root) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else {
        printlevel(root->left, level - 1);
        printlevel(root->right, level - 1);
    }
}

void maketree(node **root,int data){
    if(data > 100) return;
    node * newnode = createNode(data);
    *root = newnode;
    maketree((&(*root)->left),2*data);    
    maketree(&((*root)->right),3*data);
}

int main(){
    int n;
    printf("input number: ");
    scanf("%d",&n);
    node *root;
    maketree(&root,n);
    printf("\n");
    printf("height : %d\n",height(root));
    nodecount(root);
    printf("Node 개수: %d\n",count);
    leafcount(root);
    printf("Leaf node개수: %d\n",countleaf);
    printf("\n");

    printf("input level: ");
    int level;
    scanf("%d",&level);
    printlevel(root,level);
    printf("\n");
    printf("\nPostorder traversal: ");
    postorder(root);
    printf("\nLevelorder traversal: ");
    levelorder(root,100);
    


    
}

