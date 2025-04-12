//2022110037 전민제
#include <stdio.h>
#define max 100
typedef struct{
    int row;
    int col;
    int value;
}Term;
//행렬을 90도 돌리는 함수
void trans(Term *a,Term *b){
    int col  = a[0].col;
    int value  = a[0].value;
    int endingpos[max],cnt[max];
    int i,j;
    b[0].col = a[0].row;
    b[0].row = col;
    b[0].value  = value;
    for(i=0;i<value;i++){
        cnt[i] = 0;
    }
    for(i=1;i<=value;i++){
        cnt[a[i].col]++;
    }
    endingpos[0] = cnt[0];
    for(i=1;i<col;i++){
        endingpos[i]= endingpos[i-1] + cnt[i];
    }
    for(i=1;i<=value;i++){
        j = endingpos[a[i].col]--;
        b[j].col = (col-1)-a[i].row;
        b[j].row = a[i].col;
        b[j].value = a[i].value;
    }

}
//파일에서 데이터 입력 받고 배열에 저장하는 함수
void datascan(FILE *fp,Term *a){
    int row,col,i,value;
    int cnt = 1;
    fscanf(fp,"%d %d",&row,&col);
    for(i=0;i<col*row;i++){
        fscanf(fp,"%d",&value);
        if(value==1){
            a[cnt].col = i%row;
            a[cnt].row = i/row;
            a[cnt].value  = value;
            cnt++;
        }
    }
    a[0].col = col;
    a[0].row  = row;
    a[0].value  = --cnt;
}
// 결과를 출력하는 함수
void print(Term *a,Term *b){
    int row = a[0].row;
    int col = a[0].col;
    int cnt = a[0].value;
    int i;
    printf("[90도 회전하기 전]\n   ROW COL VAL\n");
    for(i=0;i<=cnt;i++){
        printf("%5d%4d%4d\n",a[i].row,a[i].col,a[i].value);
    }
    int idx = 1;
    for(i=0;i<a[0].col*a[0].row;i++){
        if(a[idx].row ==i/row && a[idx].col == i%row){
            printf("* ");
            idx++;
        }
        else{
            printf("  ");
        }
        if(i%row == col - 1){
            printf("\n");
        }
    }
    trans(a,b);
    printf("[90도 회전한 후]\n   ROW COL VAL\n");

    for(i=0;i<=cnt;i++){
        printf("%5d%4d%4d\n",b[i].row,b[i].col,b[i].value);
    }
    idx = 1;
    for(i=0;i<col*row;i++){
        if(b[idx].row ==i/col && b[idx].col == i%col){
            printf("* ");
            idx++;
        }
        else{
            printf("  ");
        }
        if(i%col == row- 1){
            printf("\n");
        }
    }
    
}
int main(){
    Term a[max];
    Term b[max];
    FILE *fp = fopen("./sparse1.txt","r");
    datascan(fp,a);
    fclose(fp);
    print(a,b);
    fp = fopen("./sparse2.txt","r");
    datascan(fp,a);
    fclose(fp);
    print(a,b);
    

    
}