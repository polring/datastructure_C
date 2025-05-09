#include <stdio.h>
#include <stdlib.h>

// 스레드 노드 정의
typedef struct ThreadedNode {
    int data;
    struct ThreadedNode* left;
    struct ThreadedNode* right;
    int isLeftThread;
    int isRightThread;
} ThreadedNode;

// 노드 생성
ThreadedNode* createNode(int data) {
    ThreadedNode* newNode = (ThreadedNode*)malloc(sizeof(ThreadedNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->isLeftThread = 1;
    newNode->isRightThread = 1;
    return newNode;
}

// 노드 삽입 (중위 기준)
void insert(ThreadedNode** rootRef, int data) {
    ThreadedNode* parent = NULL;
    ThreadedNode* curr = *rootRef;

    while (curr != NULL) {
        if (data == curr->data) {
            return; // 중복은 삽입 안함
        }
        parent = curr;
        if (data < curr->data) {
            if (!curr->isLeftThread)
                curr = curr->left;
            else
                break;
        } else {
            if (!curr->isRightThread)
                curr = curr->right;
            else
                break;
        }
    }

    ThreadedNode* newNode = createNode(data);

    if (parent == NULL) {
        *rootRef = newNode;
    } else if (data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->isLeftThread = 0;
        parent->left = newNode;
    } else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->isRightThread = 0;
        parent->right = newNode;
    }
}

// 중위 순회를 위한 가장 왼쪽 노드 찾기
ThreadedNode* leftmost(ThreadedNode* node) {
    if (node == NULL) return NULL;
    while (!node->isLeftThread)
        node = node->left;
    return node;
}
ThreadedNode* insucc(ThreadedNode * node){
    ThreadedNode* temp = node->right;
    if(!node->right){
        while(!temp->isRightThread){
            temp = temp->left;
        }
    }
    return temp;
}


// 중위 순회
void inorderTraversal(ThreadedNode* root) {
    ThreadedNode* curr = leftmost(root);
    while (curr != NULL) {
        printf("%d ", curr->data);
        if (curr->isRightThread) {
            curr = curr->right;
        } else {
            curr = leftmost(curr->right);
        }
    }
}

// 테스트용 메인
int main() {
    ThreadedNode* root = NULL;
    insert(&root, 40);
    insert(&root, 20);
    insert(&root, 60);
    insert(&root, 10);
    insert(&root, 30);
    insert(&root, 50);
    insert(&root, 70);

    printf("중위 순회 결과 (Threaded Binary Tree): ");
    inorderTraversal(root);  // 10 20 30 40 50 60 70
    printf("\n");

    return 0;
}
