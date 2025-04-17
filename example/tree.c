#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node * right;
}node;

node* createNode(int data){
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

node* insertnode(node* root,int data){
    if(root == NULL){
        return createNode(data);
    }
    if(data<root->data){
        root->left = insertnode(root->left,data);

    } else if(data>root->data){
        root->right = insertnode(root->right,data);
    }
    return root;
}
void preorderTraversal(node* root){
    if(root){
        printf("%d ",root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}
void inorderTraversal(node *root){
    if(root){
        inorderTraversal(root->left);
        printf("%d ",root->data);
        inorderTraversal(root->right);
    }
}
void postorderTraversal(node *root){
    if(root){
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ",root->data);
    }
}
int main(){
    node *root = NULL;
    root = insertnode(root,50);
    root = insertnode(root,30);
    root = insertnode(root,70);
    root = insertnode(root,20);
    root = insertnode(root,40);
    root = insertnode(root,60);
    root = insertnode(root,80);
    printf("전위 순회(Preorder): ");
    preorderTraversal(root);
    printf("\n");
    printf("inorder : ");
    inorderTraversal(root);
    printf("\n");
    printf("postorder : ");
    postorderTraversal(root);


}