#include <stdio.h>
#include <stdlib.h>
#define max 100

typedef struct{
    int id;
    char name[max];
}element;

typedef struct Node{
    element data;
    struct Node* left;
    struct Node* right;
}node;

node* createNode(element data){
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
}

node* insert(node* root, element data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data.id < root->data.id) {
        root->left = insert(root->left, data);  
    } else if (data.id > root->data.id) {
        root->right = insert(root->right, data);  
    } 

    return root;
}
void inorder(node* root){
    if(!root) return;
    inorder(root->left);
    printf("(%d, %s)  ",root->data.id,root->data.name);
    inorder(root->right);
}
node* binarySearch(node* root, int target) {
    if (root == NULL) return NULL;             // 탐색 실패
    if (root->data.id == target) return root;     

    if (target < root->data.id)
        return binarySearch(root->left, target);     
    else
        return binarySearch(root->right, target);    
}
void search(node* root){
    FILE *fp  = fopen("search.txt","r");
    int n;
    int id;
    fscanf(fp,"%d",&n);
    printf("\n\n\n");
    for(int i = 0;i < n; i++){
        fscanf(fp,"%d",&id);
        if(binarySearch(root,id)){
            printf("%d: 있음\n",id);
        }
        else{
            printf("%d: 없음\n",id);
        }
    }
    
}
void ksmall(node* root, int k, int* count, int* result) {
    if (root == NULL || *result) return;

    ksmall(root->left, k, count, result);

    (*count)++;
    if (*count == k) {
        printf("%d번째 노드 : %d, %s\n", k, root->data.id, root->data.name);
        *result = 1;
        return;
    }

    ksmall(root->right, k, count, result);
}

int main(){
    FILE *fp  = fopen("in.txt","r");
    node* root = NULL;
    int n;
    element data;
    fscanf(fp,"%d",&n);
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %s",&data.id,data.name);
        root = insert(root,data);
    }
    printf("[inorder traversal]\n");
    inorder(root);
    fclose(fp);
    search(root);
    int k;
    int count = 0;
    int result = 0;
    printf("\n\nk번쨰 노드 찾기:\n");
    while(1){
        printf("input k: ");
        scanf("%d",&k);
        if(k < 0){
            return 0;
        }
        count = 0;
        result = 0;
        ksmall(root,k,&count,&result);
        

    }
}



