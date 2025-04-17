#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int coef;
    int expon;
}polynomial;

typedef struct Node{
    polynomial data;
    struct Node* next;
}node;

node *createNode(polynomial data){
    node* newnode = malloc(sizeof(node));
    newnode->next = NULL;
    newnode->data = data;
    return newnode;
}

void append(polynomial data,node **head){
    node *newnode = createNode(data);
    if(*head == NULL){
        *head = newnode;
    }
    node *temp = *head;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = newnode;
}
int sizing(node *head){
    int count = 0;
    while(head){
        count++;
        head = head->next;
    }
    return count;
}

void swap(node *a,node *b,node **head){
    
    polynomial temp = a->data;
    a->data = b->data;
    b->data = temp;

}

void sorting(node **head){
    int size = sizing(*head);
    node* prev = *head;
    node* current = *head;
    int min = prev->data.expon;
    node* minpointer = NULL;
    while(prev->next){
        current = prev;
        while(current){
            if(min>current->data.expon){
                min = current->data.expon;
                minpointer = current;
            }
            current = current->next;
        }
        swap(prev,minpointer,head);

        prev = prev->next;
    }
}
int main(){
    node *head = NULL;
    FILE *Fp = fopen("polynomial.txt","r");
    
}

