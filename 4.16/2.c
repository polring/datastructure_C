#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}node;

node* headcreate(){
    node* newnode = malloc(sizeof(node));
    newnode->next = newnode;
    newnode->prev = newnode;
    return newnode;
}
node* createNode(int data){
    node* newnode = malloc(sizeof(node));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->data = data;
    return newnode;
}
//head부터 시작해서 head->next탐색후 삽입하고 싶은 위치 앞까지 도달후 삽입
void sortedinsert(node *head,int data){
    node *newnode = createNode(data);
    node *temp = head;
    while(temp->next!=head&&temp->next->data > data){
        temp = temp->next;
    }
    newnode->next = temp->next;
    newnode->prev = temp;
    temp->next->prev = newnode;
    temp->next = newnode;
    

}
// 좌측 리스트 출력
void leftprint(node *head,int data){
    printf("\n%d 기준 좌측 리스트 출력: \n",data);
    node *temp = head->next;
    while(temp->data !=data){
        temp = temp->next;
    }
    node *temp2 = temp;
    while(temp2!=head){
        printf("%d ",temp2->data);
        temp2 = temp2->prev;
    }
    temp2 = temp2->prev;
    while(temp2!=temp){
        printf("%d ",temp2->data);
        temp2 = temp2->prev;
    }
    printf("\n");
}
//기준 우측 리스트 출력
void rightprint(node *head, int data){
    printf("\n%d 기준 우측 리스트 출력: \n",data);
    node *temp = head->next;
    while(temp->data !=data){
        temp = temp->next;
    }
    node *temp2 = temp;
    while(temp2!=head){
        printf("%d ",temp2->data);
        temp2 = temp2->next;
    }
    temp2 = temp2->next;
    while(temp2!=temp){
        printf("%d ",temp2->data);
        temp2 = temp2->next;
    }
    printf("\n");

}
//노드 삭제 
void deletenode(node* head,int data){
    node *temp = head;
    while(temp->next !=head && temp->next->data !=data){
        temp = temp->next; 
    }
    if(temp->next == head){
        printf("삭제할 노드%d 없음.\n",data);
        return;
    }
    node *temp2 = temp->next;
    temp->next= temp->next->next;
    temp2->prev = temp;
    free(temp2);
}
//노드들 출력
void printlist(node *head){
    node *temp = head->next;
    while(temp!=head){
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void freeList(node *head){
    node *temp = head->next;
    while(temp!=head){
        
    }
}
//노드 삭제 수행하는 함수
void deletefunction(node* head){
    int n;
    int bool;
    while(1){
        printf("삭제할 숫자 입력: ");
        scanf("%d",&n);
        if(n<0){
            printf("Quit");
            return;
        }
        deletenode(head,n);
        printlist(head);
    }
}

int main(){
    node* head = headcreate();
    int n,num;
    FILE *fp = fopen("in.txt","r");
    fscanf(fp,"%d",&n);
    for(int i=0;i<n;i++){
        fscanf(fp,"%d",&num);
        sortedinsert(head,num);
    }
    printf("리스트 출력: ");
    printlist(head);
    int standard;
    printf("\nLeft/Right 출력 위한 숫자 입력: ");
    scanf("%d",&standard);
    leftprint(head,standard);
    rightprint(head,standard);
    deletefunction(head);


}
