#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int coef;
    int expon;
    struct Node* next;
}node;

node* createNode(int coef,int expon){
    node* newnode = malloc(sizeof(node));
    newnode->next = NULL;
    newnode->coef = coef;
    newnode->expon = expon;
    return newnode;
}
void append(node **head,int coef,int expon){
    node* newnode = createNode(coef,expon);
    node *temp = *head;
    if(*head == NULL){
        *head = newnode;
        return;
    }
    while(temp->next){
        temp = temp->next;
    }
    temp->next = newnode;
}

void sortedinsert(node **head,int coef,int expon){
    node *newnode= createNode(coef,expon);
    if(*head == NULL){
        *head = newnode;
        return;
    }
    if((*head)->expon < expon){
        newnode->next = *head;
        *head = newnode;
        return;
    }
    node *temp = *head;
    while(temp->next && temp->next->expon > expon){
        temp = temp->next;
    }
    if(temp->next == NULL){
        temp->next = newnode;
        return;
    }
    node *temp3 = temp->next;
    if(temp->next->expon == expon){
        temp->next->coef += coef;
        if(temp->next->coef == 0){
            temp->next = temp->next->next;
            free(temp3);
        }
        free(newnode);
        return;
    }
    newnode->next = temp->next;
    temp->next = newnode;
}

void multiply(node** head){
    node* trail1 = head[0];
    node* trail2 = head[1];
    int coef,expon;
    while(trail1){
        trail2 = head[1];
        while(trail2){
            coef = trail2->coef * trail1->coef;
            expon = trail2->expon + trail1->expon;
            sortedinsert(head + 2,coef,expon);
            trail2 = trail2->next;
        }
        trail1 = trail1 ->next;
    }
}
void printlist(node *head){
    while(head){
        printf("[%d %d] ",head->coef,head->expon);
        head = head->next;
    }
    printf("\n");
}
void freeList(node **head){
    node *temp = *head;
    while(*head){
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}
void execute(const char* name1,const char* name2){
    FILE *fp = fopen(name1,"r");
    FILE *fp2 = fopen(name2,"r");
    node *head[3] = {NULL,NULL,NULL};
    int n;
    int coef,expon;
    fscanf(fp,"%d",&n);
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d",&coef,&expon);
        append(head,coef,expon);
    }
    fscanf(fp2,"%d",&n);
    for(int i=0;i<n;i++){
        fscanf(fp2,"%d %d",&coef,&expon);
        append(head+1,coef,expon);
    }
    multiply(head);
    printf("poly:\n");
    printlist(head[0]);
    printf("poly2:\n");
    printlist(head[1]);
    printf("poly1 * poly2:\n");
    printlist(head[2]);
    fclose(fp);
    fclose(fp2);
    freeList(head);
    freeList(head + 1);
    freeList(head + 2);
    
}

int main(){
    execute("in1.txt","in2.txt");
    execute("in3.txt","in4.txt");
}