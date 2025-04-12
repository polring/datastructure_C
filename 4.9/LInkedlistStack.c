//2022110037 전민제
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int data;
    struct Node* next;
}node;
// 스택의 top즉 head와 용량을 저장할 구조체
typedef struct{
    node* top;
    int capacity;
}stack;
node *createnode(int data){
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
// 스택이 비어있는지 확인
int isEmpty(stack a){
    return a.top==NULL;
}
//스택이 차있는지 확인
int isFull(stack a){
    return a.capacity == 4;
}
//스택에 push 스택은 push할때 top에 넣기 떄문에 top을 변경해야한다.
void push(stack *a,int data){
    node* newnode = createnode(data);
    newnode->next = a->top;
    a->top = newnode;
    a->capacity++;
}
//스택에 pop 
void pop(stack *a){
    node *temp = a->top;
    a->top = a->top->next;
    free(temp);
    a->capacity--;

}
//linkedlist 출력(이렇게 구현하면 a.top은 변경되지 않는다) call by value;
void printlist(stack a,char alph){
    printf("[%c] ",alph);
    while(a.top){
        printf("%d ",a.top->data);
        a.top = a.top->next;
    }
    printf("\n");
}
// 노드 해제
void freelist(stack a){
    node *temp = a.top;
    while(a.top){
        temp = a.top;
        a.top = a.top->next;
        free(temp);
    }
}
int main(){
    char c = 0;
    char alph;
    int num;
    int index = 0;
    FILE *fp = fopen("in.txt","r");
    stack stacks[3] = {{NULL,0},{NULL,0},{NULL,0}};
    while(1){
        fscanf(fp," %c",&c);
        if(c == 'q'){
            break;
        }
        else if(c == 'a'){
            fscanf(fp," %c %d",&alph,&num);
            printf("(%c %c%3d)",c,alph,num);
            index = alph-'A';
            if(isFull(stacks[index])){
                printf("보관함%c가 가득 찼음: 보관불가\n",alph);
            }
            else{
                push(stacks+index,num);
                printlist(stacks[index],alph);
            }
        }
        else{
            fscanf(fp," %c",&alph);
            index = alph-'A';
            printf("(%c %c)   ",c,alph);
            if(isEmpty(stacks[index])){
                printf("보관함%c가 비어있음: 반환불가\n",alph);
            }
            else{
                pop(stacks+index);
                printlist(stacks[index],alph); 
            }
        }
    }
    fclose(fp);

    freelist(stacks[0]);
    freelist(stacks[1]);
    freelist(stacks[2]);  
}
