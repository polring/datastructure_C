#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int coef;
    int expon;
    struct Node* next;
}node;

int compare(int a,int b){
    if(a== b){
        return 0;
    }
    return a>b ? 1 : -1;
}
node* createNode(int expon,int coef){
    node* newnode = malloc(sizeof(node));
    newnode->next = NULL;
    newnode->coef = coef;
    newnode->expon = expon;
    return newnode;
}
void attach(int expon,int coef,node** c){
    node* newnode = createNode(expon,coef);
    if(*c == NULL){
        *c = newnode;
        return;
        
    }
    node *temp = *c;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = newnode;
}

void poly(node **head){
    int coef;
    while(head[0]&&head[1]){
        switch (compare(head[0]->expon,head[1]->expon))
        {
        case 1:
            attach(head[0]->expon,head[0]->coef,&head[2]);
            head[0] = head[0]->next;
            break;
        
        case 0:
            coef = head[0]->coef + head[1]->coef;
            attach(head[0]->expon,coef,&head[2]);
            head[0] = head[0]->next;
            head[1] = head[1]->next;
            break;
        
        default:
            attach(head[1]->expon,head[1]->coef,&head[2]);
            head[1] = head[1]->next;
        }
    }
    while(head[0]){
        attach(head[0]->expon,head[0]->coef,&head[2]);
        head[0] = head[0]->next;
    }
    while(head[1]){
        attach(head[1]->expon,head[1]->coef,&head[2]);
        head[1] = head[1]->next;
    }
}
void printlist(node* a){
    while(a){
        printf("%d %d ",a->coef,a->expon);
        a = a->next;
    }
}
int main(){
    node* head[3] = {NULL,NULL,NULL};
    FILE *fp = fopen("polynomial.txt","r");
    int n;
    fscanf(fp,"%d",&n);
    int coef,expon;
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d",&coef,&expon);
        attach(expon,coef,head);
    }
    fscanf(fp,"%d",&n);
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d",&coef,&expon);
        attach(expon,coef,head+1);
    }
    poly(head);
    printlist(head[2]);

    
    
    

}