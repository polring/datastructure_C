//2022110037 전민제
#include <stdio.h>
#include <string.h>
// 홀수만 출력
void oddprint(char *str,int i){
    if(str[i]=='\0'){
        return;
    }
    printf("%c",str[i]);
    oddprint(str,i+2);
    
}
//거꾸로 출력
void reverse(char *str,int i){
    if(str[i]=='\0'){
        return;
    }
    reverse(str,i+1);
    printf("%c",str[i]);
    
}



int main(){
    char str[100] = {'\0'};
    printf("%s","input str: ");
    scanf("%s",str);
    printf("홀수번째 문자 출력: ");
    oddprint(str,0);
    printf("\n문자열 거꾸로 출력: ");
    reverse(str,0);

}