#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}node;

node* createnode(int data){
    node *newnode = malloc(sizeof(node));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->data = data;
    return newnode;
}

node* headcreate(){
    node *newnode = malloc(sizeof(node));
    newnode->next = newnode;
    newnode->prev = newnode;
    return newnode;
}
void insert(node *ptr,int data){
    node *newnode = createnode(data);
    newnode->prev = ptr;
    newnode->next = ptr->next;
    ptr->next = newnode;
    ptr->next->prev = newnode;
}
int main(){
    node* header = headcreate();


}

