#include <stdio.h>

typedef struct {
    int row;    // 행 번호
    int col;    // 열 번호
    int value;  // 값
} Term;

void fastTranspose(Term a[], Term b[]) {
    int num,i,j,currentb;
    num = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num;
    if(num>0){
        currentb = 1;
        for(i=0;i<a[0].col;i++){
            for(j=1;j<=num;j++){
                if(a[j].col == i){
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
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