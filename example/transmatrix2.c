#include <stdio.h>
#define MAX_COL 101 //

typedef struct {
    int row;    // 행 번호
    int col;    // 열 번호
    int value;  // 값
} Term;

void fastTranspose(Term a[], Term b[]) {
    int rowTerms[MAX_COL], startingPos[MAX_COL];
    int i, j, numCols = a[0].col, numTerms = a[0].value;
    
    // 전치 행렬의 기본 정보 설정
    b[0].row = numCols;       // 원래 열 수 -> 전치 행렬의 행 수
    b[0].col = a[0].row;      // 원래 행 수 -> 전치 행렬의 열 수
    b[0].value = numTerms;    // 값의 개수는 동일
    
    if (numTerms > 0) { // 0이 아닌 요소가 있는 경우
        // 1. 각 열에 있는 요소 개수 계산
        for (i = 0; i < numCols; i++) {
            rowTerms[i] = 0;
        }
        for (i = 1; i <= numTerms; i++) {
            rowTerms[a[i].col]++;
        }
        
        // 2. 각 열의 시작 위치 계산
        startingPos[0] = 1;
        for (i = 1; i < numCols; i++) {
            startingPos[i] = startingPos[i-1] + rowTerms[i-1];
        }
        
        // 3. 전치 행렬 생성
        for (i = 1; i <= numTerms; i++) {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;    // 원래 열 -> 전치 행
            b[j].col = a[i].row;    // 원래 행 -> 전치 열
            b[j].value = a[i].value;// 값 복사
        }
    }
}

// 행렬 출력 함수
void printMatrix(Term matrix[]) {
    printf("row\tcol\tvalue\n");
    for (int i = 0; i <= matrix[0].value; i++) {
        printf("%d\t%d\t%d\n", matrix[i].row, matrix[i].col, matrix[i].value);
    }
}

int main() {
    // 예시 희소 행렬 
    Term a[] = {
        {6, 6, 8},  // 행 수, 열 수, 값 개수
        {0, 0, 15},
        {0, 3, 22},
        {0, 5, -15},
        {1, 1, 11},
        {1, 2, 3},
        {2, 3, -6},
        {4, 0, 91},
        {5, 2, 28}
    };
    Term b[9]; // 전치 행렬을 저장할 배열
    
    printf("원래 행렬:\n");
    printMatrix(a);
    
    fastTranspose(a, b);
    
    printf("\n전치 행렬:\n");
    printMatrix(b);
    
    return 0;
}