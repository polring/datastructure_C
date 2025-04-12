#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {     
    lparen,    
    rparen,    
    plus,      
    minus,     
    times,     
    divide,   
    mod,
    at,
    shap,
    eos,      
    operand    
} precedence;

#define MAX 100
int error = 1;
precedence stack[MAX];
int top = -1;
// 스택에서 우선순위
static int isp[] = {0, 19, 12, 12, 13, 13, 13, 14, 11, 0}; 
// 입력에서 우선순위
static int icp[] = {20, 19, 12, 12, 13, 13, 13, 14, 11, 0};

// 스택 연산 함수
void push(precedence token) {
    if (top >= MAX - 1){
        return;
    }
    stack[++top] = token;
}

precedence pop() {
    if (top == -1) {
        exit(0);
    }
    return stack[top--];
}

char returnToken(precedence token) {
    switch (token) {
        case plus:   return '+';
        case minus:  return '-';
        case times:  return '*';
        case divide: return '/';
        case mod:    return '%';
        case at:     return '@';
        case shap:   return '#';
        case rparen: return ')';
        case lparen: return '(';
        default:     return '\0';
    }
}

// 토큰을 가져오는 함수
precedence getToken(char *symbol, int *n,char *expression) {
    *symbol = expression[(*n)++];
    switch (*symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '*': return times;
        case '/': return divide;
        case '%': return mod;
        case '@': return at;
        case '#': return shap;
        case '\0': return eos;
        default: return operand; 
    }
}


// 중위 -> 후위 변환 함수
char * postfix(char *expression) {
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;
    int cnt = 0;
    error = 1;
    char *str = malloc(sizeof(char)*MAX);
    for (token = getToken(&symbol, &n,expression); token != eos; token = getToken(&symbol, &n,expression)) {
        if (token == operand) {
            str[cnt++] = symbol; 
        } else if (token == rparen) {
            while (stack[top] != lparen&&stack[top]!=eos) {
                str[cnt++] = returnToken(pop());
            }
            if(stack[top]==lparen){
                pop();
            } 
            else{
                error = 0;
                return str;
            }
        } else {
            while (isp[stack[top]] >= icp[token]) {
                str[cnt++] = returnToken(pop());
            }
            push(token); 
        }
    }
    while ((token = pop()) != eos) {
        str[cnt++] = returnToken(token);
        if(token == lparen || token == rparen){
            error = 0;
            return str;
        }
    }
    return str;
}

int main() {
    FILE *fp = fopen("infix.txt","r");
    int n;
    fscanf(fp,"%d",&n);
    char *expression = malloc(sizeof(char)*MAX);
    char *str;
    for(int i=0;i<n;i++){
        str = NULL;
        fscanf(fp,"%s",expression);
        printf("infix: %s\n",expression);
        str = postfix(expression);
        printf("Postfix: %s\n",str);
        if(!error){
            printf("괄호 오류\n");
        }
        
        printf("\n");
        
        free(str);
        
    }
    
}
