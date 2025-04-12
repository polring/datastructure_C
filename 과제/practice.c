#include <stdio.h>


void reverse(char *str,int n){
    if(str[n]== '\0'){
        return;
    }
    reverse(str,n+1);
    printf("%c ",str[n]);
}
int main(){
    char str[100];
    scanf("%s",str);
    reverse(str,0);
    
}