#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int key;
    int item;
}element;
typedef struct Node{
    element data;
    struct Node* left;
    struct Node* right;
}node;


node* createNode(element data){
    node* newnode = malloc(sizeof(node));
    newnode->left = newnode->right = NULL;
    newnode->data = data;
    return newnode;
}


node* minValueNode(node* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

node* delete(node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data.key)
        root->left = delete(root->left, key);
    else if (key > root->data.key)
        root->right = delete(root->right, key);
    else {
        
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }
        
        node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data.key);
    }
    return root;
}

node* search(node* root, int key) {
    if (root == NULL || root->data.key == key) return root;
    if (key < root->data.key)
        return search(root->left, key);
    else
        return search(root->right, key);
}
node* modifiedSearch(node* root, int key){
    if(root->data.key == key){
        return root;
    }
    if(root->data.key > key){
        return modifiedSearch(root->left,key);
    }
    else{
        node* temp = modifiedSearch(root->right,key);
        if(!temp){
            return root;
        }
        else{
            return temp;
        }
    }
    return NULL;
}


node* insert(node* root, element data) {
    if (!root) {
        node* newnode = createNode(data);
        return newnode;
    }
    if (data.key < root->data.key)
        root->left = insert(root->left, data);
    else if (data.key > root->data.key)
        root->right = insert(root->right, data);
    return root;
}

int main(){
    FILE *fp = fopen("","r");
    int n;
    node* root = NULL;
    fscanf(fp,"%d",&n);
    element data;
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d",&data.key,&data.item);
        if(modifiedSearch(root,data.key)){
            root = insert(root,data);
        }
    }
    fclose(fp);

}


