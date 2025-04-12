#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int coef;
    int expon;
}polynomial;
// 차수를 비교하기 위한 함수
int compare(int a,int b){
    if(a==b){
        return 0;
    }
    return a>b ? 1:-1;
}
// polynomial 배열에 구한 값 넣기 
void attach(polynomial *terms,int coefficient,int exponent,int *avail){
    terms[*avail].coef = coefficient;
    terms[(*avail)++].expon = exponent;
}
void minus(int *avail,polynomial *terms,int starta,int finisha,int startb,int finishb,int *startd,int *finishd){
    int coefficient;
    *startd = *avail;
    while((starta<=finisha)&&(startb<=finishb)){
        switch (compare(terms[starta].expon,terms[startb].expon))
    {
        case -1:
            attach(terms,-(terms[startb].coef),terms[startb].expon,avail);
            startb++;
            break;
    
        case 0:
            coefficient = terms[starta].coef - terms[startb].coef;
            if(coefficient!=0){
                attach(terms,coefficient,terms[starta].expon,avail);
            }
            starta++;
            startb++;
            break;
        case 1:
            attach(terms,terms[starta].coef,terms[starta].expon,avail);
            starta++;
            break;
    }


    }
    for(;starta<=finisha;starta++){
        attach(terms,terms[starta].coef,terms[starta].expon,avail);
    }

    for(;startb<=finishb;startb++){ 
        attach(terms,-(terms[startb].coef),terms[startb].expon,avail);
    }
    *finishd = *avail-1;
    

}
void print(FILE *fp){
    int a,b;
    fscanf(fp,"%d",&a);
    polynomial *terms = malloc(sizeof(polynomial)*a);
    int starta = 0,finisha = a-1;
    for(int i=starta;i<=finisha;i++){
        fscanf(fp,"%d %d",&(terms[i].coef),&(terms[i].expon));
    }
    fscanf(fp,"%d",&b);
    terms = realloc(terms,sizeof(polynomial)*2*(a+b));
    int startb = a,finishb = a+b-1;
    int avail = a+b;
    for(int i=a;i<a+b;i++){
        fscanf(fp,"%d %d",&(terms[i].coef),&(terms[i].expon));
    }
    int startd,finishd;
    minus(&avail,terms,starta,finisha,startb,finishb,&startd,&finishd);
    int size = finishd-startd +1;
    printf("\n%d ",size);
    for(;startd<=finishd;startd++){
        printf("%d %d ",terms[startd].coef,terms[startd].expon);
    }
    free(terms);
}
int main(){
    FILE *fp = fopen("./in1.txt","r");
    FILE *fp2 = fopen("./in2.txt","r");
    print(fp);
    print(fp2);
    fclose(fp);
    fclose(fp2);
}