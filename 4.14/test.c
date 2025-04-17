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


node* createNode(polynomial data){
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void insert(polynomial data,node **head,node *ptr){
    node *newnode = createNode(data);
    if(*head == NULL || ptr == NULL){
        newnode->next = *head;
        *head = newnode;
        return;
    }
    newnode->next = ptr->next;
    ptr->next = newnode;
}
node *last(node *head){
    if(head == NULL){
        return NULL;
    }
    while(head->next){
        head = head->next;
    }
    return head;
}
void scan(const char* name,node **head){
    FILE *fp = fopen(name,"r");
    polynomial data;
    int n;
    fscanf(fp,"%d",&n);
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d",&data.coef,&data.expon);
        insert(data,head,last(*head));
    }
    
}
void print(node *head){
    while(head){
        printf("[%d, %d] ",head->data.coef,head->data.expon);
        head = head->next;
    }
    printf("\n");
}
node *compare(node *head,int expon){
    if(head == NULL){
        return NULL;
    }
    while(head->next && head->next->data.expon >= expon ){
        if(head->next->data.expon == expon ){
            return head->next;
        }
        head = head->next;
        
    }
    
    return head;
}

void multiply(node **head){
    polynomial data;
    node *ptr;
    node *trail = head[0];
    node *trail2 = head[1];
    while(trail){
        trail2 = head[1];
        while(trail2){
            data.coef = trail->data.coef * trail2->data.coef;
            data.expon = trail->data.expon + trail2->data.expon;
            ptr = compare(head[2],data.expon);
            if(ptr->data.expon == data.expon){
                ptr->data.coef +=data.coef;
            }
            insert(data,head+2,ptr);
            trail2 = trail2->next;
        }
        trail = trail->next;
    }
}

int main(){
    node *head[3] = {NULL,NULL,NULL};
    scan("in1.txt",head);
    scan("in2.txt",head+1);
    multiply(head);
    print(head[2]);


}

