#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define Error -100000
typedef struct{
    int vert;
    int horiz;
}offsets;
typedef struct{
    int row;
    int col;
    int dir;
}element;
typedef struct{
    element *stack;
    int top;
    int capacity;
}Stack;
int isEmpty(Stack *a){
    if(a->top<=-1){
        return 1;
    }
    return 0;
}
int isFull(Stack *a){
    if(a->top>=a->capacity){
        return 1;
    }
    return 0;
}
void push(Stack *a,element b){

    if(isFull(a)){
        a->capacity *=2;
        a->stack = realloc(a->stack,sizeof(int)*a->capacity);
    }
    a->stack[++(a->top)] = b;
}
element pop(Stack *a){
    return a->stack[(a->top)--];
}
int path(int (*mark)[MAX],int (*maze)[MAX],Stack *a,offsets *move,int cols,int rows){
    int i,row,col,next_row,next_col,dir,found = 0;
    element position;
    const int start_x = 1;
    const int start_y = 1;
    const int final_x = rows;
    const int final_y = cols;
    mark[start_x][start_y] = 1;
    a->top = 0;
    a->stack[0].row = start_x;
    a->stack[0].col = start_y;
    a->stack[0].dir = 1;
    while(a->top>-1 && !found){
        position = pop(a);
        row = position.row;
        col = position.col;
        dir = position.dir;
        while(dir < 8 && !found){
            next_row = row + move[dir].vert;
            next_col = col + move[dir].horiz;
            if(next_row == final_x  && next_col == final_y){
                found = 1;
            }
            else if(!maze[next_row][next_col] && !mark[next_row][next_col]){
                mark[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(a,position);
                row = next_row;
                col = next_col;
                dir = 0; 
            }
            else{
                dir++;
            }
        }

    }
    return found;

    
    
}

int main(){
    Stack a;
    element b;
    int rows,cols;
    int mark[MAX][MAX] = {0};
    int maze[MAX][MAX] = {0};
    scanf("%d %d",&rows,&cols);
    a.stack = malloc(sizeof(element));
    a.top = -1;
    a.capacity = 1;
    printf("%d\n",a.capacity);
    offsets move[8]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
    printf("Enter maze (0 for path, 1 for wall):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    int found = path(mark,maze,&a,move,cols,rows);
    if (found) {
        printf("Path found!\n");
        printf("Solution:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (mark[i][j]) printf("* ");
                else printf("%d ", maze[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("No path found!\n");
    }

}