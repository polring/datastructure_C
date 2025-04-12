#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
typedef struct{
    float coef;
    int expon;
}polynomial;

int compare(int a,int b){
    if(a==b){
        return 0;
    }
    return a>b ? 1:-1;
}
void attach(polynomial*terms,int coefficient,int exponent,int *avail){
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void add(int *avail,polynomial *terms,int starta,int finisha,int startb,int finishb,int *startd,int *finishd){
    float coefficient;
    *startd = avail;
    while((starta<=finisha)&&(startb<=finishb)){
        switch (compare(terms[starta].expon,terms[startb].expon))
        {
        case -1:
            attach(terms,terms[startb].coef,terms[startb].expon,avail);
            startb++;
            break;
        
        case 0:
        coefficient = terms[starta].coef + terms[startb].coef;
        if(coefficient){
            attach(terms,coefficient,terms[starta].expon,avail);
        }
            starta++;
            startb++;
            break;

        case 1:
            attach(terms,terms[starta].coef,terms[starta].expon,avail);
            starta++;
        }
    }
    for(;starta<=finisha;starta++){
        attach(terms,terms[starta].coef,terms[starta].expon,avail);
    }
    for(;startb<=finishb;startb++){
        attach(terms,terms[startb].coef,terms[startb].expon,avail);
    }
    *finishd = avail-1;
}


int main(){
    polynomial *temrs = malloc(sizeof(polynomial)*MAX);
    int avail = 0;
    int starta,finisha,startb,finishb,startd,finishd;
    starta = 0;
    finisha = 3;
    startb = 4;
    finishb = 7;
    add(&avail,starta,finishb,startb,finishb,&startd,&startd);

    


}