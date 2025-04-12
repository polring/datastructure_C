#include <stdio.h>
#define max 100
typedef struct{
    int col;
    int row;
    int value;
}Term;
//전치 행렬 구현
void transpos(Term *a,Term *b){
    int rowTerms[max];
    int startingpos[max];
    int i,j;
    int numcols=a[0].col;
    int numTerms = a[0].value;
    b[0].row = numcols;
    b[0].col = a[0].row;
    b[0].value = numTerms;
        for(i=0;i<numcols;i++){
            rowTerms[i] = 0;
        }
        for(i=1;i<=numTerms;i++){
            rowTerms[a[i].col]++;
        }
        startingpos[0] = 1;
        for(i=1;i<numcols;i++){
            startingpos[i] = startingpos[i-1] + rowTerms[i-1];
        }
        for(i=1;i<=numTerms;i++){
            j = startingpos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value; 
        }
}
int main(){
    Term a[max];
    Term b[max];
    int row,col,i,j;
    int value;
    FILE * fp = fopen("./in.txt","r");
    fscanf(fp,"%d",&a[0].row);
    fscanf(fp,"%d",&a[0].col);
    row = a[0].row;
    col = a[0].col;
    int current = 1;
    for(i=0;i<row*col;i++){
        fscanf(fp,"%d",&value);
        if(value==1){
            a[current].value = 1;
            a[current].row = i/row;
            a[current].col = i%row;
            current++;
        }
    }
    a[0].value = current-1;
    printf("[Before Transpose]\n   ROW COL VAL\n");
    for(i=0;i<=a[0].value;i++){
        printf("%5d%5d%5d\n",a[i].row,a[i].col,a[i].value);
    }
    int cnt = 1;
    transpos(a,b);
    // 2차원을 1차원으로 생각할 때 i를 row로 나누었을때 몫은 row고 나머지는 col이다
    for(i=0;i<row*col;i++){
        if(a[cnt].row == i/row&&a[cnt].col == i%row){
            printf("* ");
            cnt++;
        }
        else{
            printf("  ");
        }
        if(i%col == col-1){
            printf("\n");
        }
        
    }
    printf("[After Transpose]\n   ROW COL VAL\n");
    for(i=0;i<=a[0].value;i++){
        printf("%5d%5d%5d\n",b[i].row,b[i].col,b[i].value);
    }
    cnt  =1;
    for(i=0;i<row*col;i++){
        if(b[cnt].row == i/col&&b[cnt].col == i%col){
            printf("* ");
            cnt++;
        }
        else{
            printf("  ");
        }
        if(i%col == row-1){
            printf("\n");
        }
    
        
    }

    



}