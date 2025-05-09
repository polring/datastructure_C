#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}node;
typedef struct ThreadNode{
    int data;
    struct ThreadNode* left;
    struct ThreadNode* right;
    int isLeft;
    int isRight;
}ThreadNode;
node* createNode(int data){
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
}
node* copy(node *root){
    if(root){
        node * temp = createNode(0);
        temp->left = root->left;
        temp->right = root->right;
        temp->data =   root->data;
        return temp;
    }
    return NULL;
}
int equal(node *root1,node *root2){
    return (!root1 && !root2) || (root1 && root2 && (root1->data == root2->data) && equal(root1->left,root2->left) && equal(root1->right,root2->right));
}
