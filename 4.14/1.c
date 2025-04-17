#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int coef;
    int expon;
} polynomial;

typedef struct Node {
    polynomial data;
    struct Node* next;
} node;
// 노드 생성 함수
node* createNode(polynomial data) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
// 노드 오름차순으로 삽입
void insertSorted(node** head, polynomial data) {
    node* newnode = createNode(data);
    node* current = *head;
    node* prev = NULL;

    while (current && current->data.expon > data.expon) {
        prev = current;
        current = current->next;
    }

    if (current && current->data.expon == data.expon) {
        current->data.coef += data.coef;
        free(newnode); 
        if (current->data.coef == 0) { 
            if (prev) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            free(current);
        }
        return;
    }


    newnode->next = current;
    if (prev) {
        prev->next = newnode;
    } else {
        *head = newnode;
    }
}

// 방정식 입력
void scan(const char* name, node** head) {
    FILE* fp = fopen(name, "r");
    polynomial data;
    int n;
    fscanf(fp, "%d", &n);
    for(int i = 0; i < n; i++) {
        fscanf(fp, "%d %d", &data.coef, &data.expon);
        if (data.coef != 0) { 
            insertSorted(head, data);
        }
    }
    fclose(fp);
}
// 노드 리스트 출력
void printlist(node* head) {
    while (head) {
        printf("[%d, %d] ", head->data.coef, head->data.expon);
        head = head->next;
    }
    printf("\n");
}
// 곱한후 새로운 노드 생성
void multiply(node** head) {
    node* trail = head[0];
    node* trail2 = head[1];
    polynomial data;

    while (trail) {
        trail2 = head[1];
        while (trail2) {
            data.coef = trail->data.coef * trail2->data.coef;
            data.expon = trail->data.expon + trail2->data.expon;
            if (data.coef != 0){
                insertSorted(&head[2], data);
            }
            trail2 = trail2->next;
        }
        trail = trail->next;
    }
}
//리스트 노드 메모리 해제
void freeList(node** head) {
    node* current = *head;
    while (current) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}
// 결과 출력및 해제
void print(node **head){
    for(int i=0;i<2;i++){
        printf("poly%d: \n",i);
        printlist(head[i]);
    }
    printf("poly1 * poly2:\n");
    printlist(head[2]);
    freeList(head);
    freeList(head+1);
    freeList(head+2);
}

int main() {
    node* head[3] = {NULL, NULL, NULL};
    scan("in1.txt", &head[0]);
    scan("in2.txt", &head[1]);
    multiply(head);
    print(head);
    scan("in3.txt", &head[0]);
    scan("in4.txt", &head[1]);
    multiply(head);
    print(head);

    
    return 0;
}