#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} node;

// 더미 노드 생성
node* headcreate() {
    node* head = malloc(sizeof(node));
    head->next = head;
    head->prev = head;
    return head;
}

// 데이터 노드 생성
node* createNode(int data) {
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

// 정렬하면서 삽입(해당 노드까지 접근후 처리)
void sortedinsert(node* head, int data) {
    node* newnode = createNode(data);
    node* temp = head->next;

    while (temp != head && temp->data > data) {
        temp = temp->next;
    }

    newnode->next = temp;
    newnode->prev = temp->prev;
    temp->prev->next = newnode;
    temp->prev = newnode;
}

// 리스트 출력
void printlist(node* head) {
    node* temp = head->next;
    while (temp != head) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 우측 기준 리스트 출력
void rightlist(node* head, int data) {
    node* start = head->next;


    while (start != head && start->data != data) {
        start = start->next;
    }


    node* temp = start;
    printf("%d 기준 우측 리스트 출력: \n",data);
    do {
        if(temp !=head){
            printf("%d ", temp->data);
        }
        temp = temp->next;
    } while (temp != start);
    printf("\n");
}
// 좌측 기준 리스트 출력
void leftlist(node* head, int data) {
    node* start = head->next;
    while (start != head && start->data != data) {
        start = start->next;
    }


    node* temp = start;
    printf("%d 기준 좌측 리스트 출력: \n",data);
    do {
        if(temp != head){
            printf("%d ", temp->data);
        }
        temp = temp->prev;
    } while (temp != start);
    printf("\n");
}
// 노드 삭제
int deleted(node *head,int data){
    if (head->next == head) return 2; 

    node *start = head->next;

    while (start != head && start->data != data) {
        start = start->next;
    }

    if (start == head){
        return 1;
    }

    start->prev->next = start->next;
    start->next->prev = start->prev;

    free(start);
    return 0;
}
    
// 노드 삭제하는 프로그램
void deletelist(node *head){
    int n = 0;
    int bool;
    while(1){
        printf("삭제할 숫자 입력: ");
        scanf("%d",&n);
        if(n<0){
            printf("Quit");
            return;
        }
        bool = deleted(head,n);
        if(bool){
            printf("삭제할 노드%d 없음\n",n);
        }
        printlist(head);
        
    }
}
// 노드들 free
void freelist(node *head){
    node* curr = head->next;
    node* next;

    while (curr != head) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    free(head);
}



int main() {
    FILE* fp = fopen("in.txt", "r");

    int n, num, standard;
    node* head = headcreate();

    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &num);
        sortedinsert(head, num);  
    }

    fclose(fp);

    printlist(head);

    printf("Left/Right 출력 위한 숫자 입력: ");
    scanf("%d", &standard);

    leftlist(head, standard);
    rightlist(head, standard);
    deletelist(head);
    freelist(head);
    return 0;
}
