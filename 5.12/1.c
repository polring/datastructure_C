//2022110037 전민제
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}node;

node* createNode(int data){
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
void printlist(node** head,int n,char *name){
    printf("%s\n",name);
    node *temp = NULL;
    for(int i=0;i<=n;i++){
        temp = head[i];
        printf("[ %2d]",i);
        while(temp){
            printf("%4d",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}
int count(node* head){
    int count = 0;
    while(head){
        count++;
        head = head->next;
    }
    return count;
}
void degree(node **head,int n,char *name){
    printf("%s\n",name);
    for(int i=0;i<=n;i++){
        printf("[ %2d] %d\n",i,count(head[i]));
    }
}
void insert(node **head,int data){
    node* newnode = createNode(data);
    node *temp = *head;
    if(!temp){
        *head = newnode;
        return;
    }
    while(temp->next){
        temp = temp->next;
    }
    temp->next = newnode;
}

void append(node **head,int data){
    node* newnode = createNode(data);
    newnode->next = *head;
    *head = newnode;
}
int check(node *head,int n){
    while(head){
        if(head->data == n){
            return 1;
        }
        head = head->next;
    }
    return 0;

}
void nodedelete(node **head,int n){
    node* temp = *head;
    if(temp->data == n){
        *head = (*head)->next;
        free(temp);
        return;
    }
    while(temp->next &&temp->next->data !=n){
        temp = temp->next;
    }
    if(temp->next == NULL){
        return;
    }
    node* temp2 = temp->next;
    temp->next = temp2->next;
    free(temp2);
    
}
void freelist(node *head){
    node* temp = head;
    while(head){
        temp = head;
        head = head->next;
        free(head);
    }
}
int main(){
    int vertex,edge;
    int x,y;
    FILE *fp = fopen("in.txt","r");
    fscanf(fp,"%d %d",&vertex,&edge);
    node** head1 = calloc(vertex+1,sizeof(node*));
    node** head2 = calloc(vertex+1,sizeof(node*));
    for(int i=0;i<edge;i++){
        fscanf(fp,"%d %d",&x,&y);
        append(head1+x,y);
        append(head2+y,x);
    }
    printlist(head1,vertex,"Linked adjacency list");
    printlist(head2,vertex,"Inverse adjacency list");
    degree(head2,vertex,"Indegree");
    degree(head1,vertex,"Outdegree");
    while(1){
        printf("Input (from to): ");
        scanf("%d %d",&x,&y);
        printf("\n");
        if(x < 0 || y< 0){
            return 0;
        }
        if(check(head1[x],y)){
            printf("Delete (%d %d)...\n",x,y);
            nodedelete(head1+x,y);
        }
        else{
            printf("Insert (%d %d)...\n",x,y);
            insert(head1+x,y);
        }
        printlist(head1,vertex,"");
    }
    fclose(fp);
    for(int i=0;i<=vertex;i++){
        freelist(head1[i]);
        freelist(head2[i]);   
    }
    free(head1);
    free(head2);





}