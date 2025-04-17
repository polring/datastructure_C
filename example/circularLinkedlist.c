#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}node;


node* createNode(int data){
    node* newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void insert(node **head,int position,int data){
    node *newnode = createNode(data);
    node *temp = *head;
    if(*head == NULL){
        *head = newnode;
        newnode->next = *head;
    }
    else if(position == 1){
        while(temp->next!=*head){
            temp = temp->next;
        }
        newnode->next = *head;
        temp->next = newnode;
        *head = newnode;
    }
    else{
        for(int i=1;i<position-1&&temp->next!=*head;i++){
            temp = temp->next;
        }
        if(temp->next == *head){
            printf("position을 벗어남");
            free(newnode);
            return;
        }
        newnode->next = temp->next;
        temp->next = newnode;


    }
}
void printlist(node *head){
    node *temp = head;
    if(head == NULL){
        return;
    }
    do{
        printf("%d ",temp->data);
        temp =temp->next;
    }while(temp!=head);
}
void freelist(node **head){
    node *temp = *head;
    node *trail = *head;
    do{
        temp = trail;
        trail = trail ->next;
        free(temp);
    }while(trail!=*head);
    *head = NULL;
}
int main(){
    node *head = NULL;
    insert(&head,1,1);
    insert(&head,2,3);  
    printlist(head);
    freelist(&head);
    printlist(head);

}
