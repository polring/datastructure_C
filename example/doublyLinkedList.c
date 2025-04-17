#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}node;

node* creaetNode(int data){
    node* newnode = malloc(sizeof(node));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->data = data;
    return newnode;
}

void insert(node **head,int position, int data){
    node* newnode = creaetNode(data);
    if(position == 1 || *head == NULL){
        newnode->next = *head;
        *head = newnode;
        
    }
    else{
        node *temp = *head;
        for(int i=1;i<position-1&&temp;i++){
            temp  = temp->next;
        }
        if(temp ==NULL){
            printf("position 범위를 벗어남");
            return;
        }
        newnode->next = temp->next;
        temp->next = newnode;
        newnode->prev = temp;
    }
}

void deletedata(node **head,int data){
    node* temp = *head;
    if((*head)->data == data){
        *head = (*head)->next;
        free(temp);
        return;
    }
    while(temp->next && temp->next->data !=data){
        temp = temp->next;
    }
    if(temp->next == NULL){
        printf("삭제할 데이터 없음");
        return;
    }
    node *temp2 = temp->next;
    temp->next->prev = temp;
    temp->next = temp->next->next;
    free(temp2);
}
void printlist(node* head){
    while(head){
        printf("%d ",head->data);
        head = head->next;
    }
}
void freeList(node *head){
    node *temp;
    while(head){
        temp = head;
        head = head->next;
        free(temp);
    }
}
int main(){
    node* head = NULL;
    insert(&head,1,1);
    insert(&head,2,2);
    deletedata(&head,2);
    printlist(head);


}