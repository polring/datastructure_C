//2022110037 전민제
#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char name[20];
    int year;
    int price;
}book;

int main(){
    FILE *fp = fopen("in.txt","r");
    int n,i;
    fscanf(fp,"%d",&n);
    book *ptr = (book *)malloc(sizeof(book)*n);
    for(i=0;i<n;i++){
        fscanf(fp,"%s %d %d",ptr[i].name,&(ptr[i].year),&(ptr[i].price));
    }
    fclose(fp);
    int maxvalue,minvalue;
    maxvalue = ptr[0].price;
    minvalue = ptr[0].price;
    // 최대,최소가격 구하기
    for(i=0;i<n;i++){
        if(maxvalue<ptr[i].price){
            maxvalue = ptr[i].price;
        }
        if(minvalue>ptr[i].price){
            minvalue = ptr[i].price;
        }
    }
    printf("Max price:\n");
    //최대,최소가 하나가 아닐 수도 있기 때문에 최대 최소랑 같은 값을 가지는 책 출력
    for(i=0;i<n;i++){
        if(ptr[i].price == maxvalue){
            printf("%s\n",ptr[i].name);
        }
    }
    printf("\n\nMin price:\n");
    for(i=0;i<n;i++){
        if(ptr[i].price == minvalue){
            printf("%s\n",ptr[i].name);
        }
    }
    // 2023~2024년 사이에 출판된 책 파일에 출력
    FILE *fp2 = fopen("out.txt","w");
    fprintf(fp2,"%s\n","Book list in 2023~2024");
    for(i=0;i<n;i++){
        if(ptr[i].year<=2024 && ptr[i].year>=2023){
            fprintf(fp2,"%s\n",ptr[i].name);
        }
    }
    fclose(fp2);



}