#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} node;

node *head = NULL;
// node 생성
node* createNode(int data) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->next = NULL;
    newnode->data = data;
    return newnode;
}
// 짝수 삽입
void firstpush(int data) {
    node* newnode = createNode(data);
    newnode->next = head;
    head = newnode;
}
// 홀수 삽입
void lastpush(int data) {
    node* newnode = createNode(data);
    if (head == NULL) {
        head = newnode;
        return;
    }
    node *temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newnode;
}
//삽입
void insert(int data) {
    node *newnode = createNode(data);
    node *temp = head;
    if (head == NULL) {
        head = newnode;
        return;
    }
    while (temp && temp->data % 2 == 0) {
        if (temp->next == NULL || temp->next->data % 2 != 0) {
            newnode->next = temp->next;
            temp->next = newnode;
            return;
        }
        temp = temp->next;
    }
    newnode->next = head;
    head = newnode;
}
// 삭제
int delete(int data) {
    node *temp = head;
    if (head == NULL) {
        return 0;
    }
    if (head->data == data) {
        head = temp->next;
        free(temp);
        return 1;
    }
    while (temp->next && temp->next->data != data) {
        temp = temp->next;
    }
    // 
    if (temp->next == NULL) {
        return 0;
    }
    node *temp2 = temp->next;
    temp->next = temp2->next;
    free(temp2);
    return 1;
}
//노드 출력
void printList() {
    node *temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void input() {
    FILE *fp = fopen("in.txt", "r");
    int n, data;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &data);
        if (data % 2) {
            lastpush(data);
        } else {
            firstpush(data);
        }
    }
    printList();
    fclose(fp);
}

void deleteInsert() {
    FILE *fp = fopen("op.txt", "r");
    int n, num;
    char t;
    int check;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fp, " %c", &t); 
        fscanf(fp, "%d", &num);
        if (t == 'd') {
            printf("Delete %d: ", num);
            check = delete(num);
            if (check) {
                printList();
            } else {
                printf("삭제할 노드 없음.\n");
            }
        } else{
            printf("Insert %d: ", num);
            node *temp = head;
            check = 1;
            while (temp) {
                if (temp->data == num) {
                    printf("중복노드.\n");
                    check = 0;
                    break;
                }
                temp = temp->next;
            }
            if (check) {
                insert(num);
                printList();
            }
        }
    }
    fclose(fp);
}
void freelist(){
    node *temp;
    while(head){
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    input();
    printf("\n");
    deleteInsert();
    freelist();
    return 0;
}