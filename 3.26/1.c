// 무식한 버전
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int vert;
    int horiz;
} offsets;

typedef struct {
    int x;
    int y;
} coordinate;

typedef struct {
    int row;
    int col;
    int dir;
} element;

typedef struct {
    element *stack;
    int top;
    int capacity;
} Stack;

int isEmpty(Stack *a) {
    return a->top == -1;
}

int isFull(Stack *a) {
    return a->top == a->capacity - 1;
}

void push(Stack *a, element b) {
    if (isFull(a)) {
        a->capacity *= 2;
        a->stack = realloc(a->stack, sizeof(element) * a->capacity);
    }
    a->stack[++(a->top)] = b;
}

element pop(Stack *a) {
    return a->stack[(a->top)--];
}
int path(int (*mark)[MAX], int (*maze)[MAX], Stack *a, offsets *move, int cols, int rows, coordinate start, coordinate final) {
    int row, col, next_row, next_col, dir, found = 0;
    element position;

    mark[start.x + 1][start.y + 1] = 1;
    position.row = start.x + 1;
    position.col = start.y + 1;
    position.dir = 0;
    push(a, position);

    while (!isEmpty(a) && !found) {
        position = pop(a);
        row = position.row;
        col = position.col;
        dir = position.dir;

        while (dir < 8 && !found) {
            next_row = row + move[dir].vert;
            next_col = col + move[dir].horiz;

            if (next_row == (final.x + 1) && next_col == (final.y + 1)) {
                found = 1;
                push(a,(element){row,col,dir});
            }
            else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
                mark[next_row][next_col] = 1;
                position.row = row;
                position.col = col;
                position.dir = dir + 1;
                push(a, position);
                row = next_row;
                col = next_col;
                dir = 0;
            } else {
                dir++;
            }
        }
    }
    
    return found;
}


void scan(FILE *fp, int (*maze)[MAX], int *rows, int *cols, coordinate *start, coordinate *final) {
    fscanf(fp, "%d %d", rows, cols);
    for (int i = 1; i <= *rows; i++) {
        for (int j = 1; j <= *cols; j++) {
            fscanf(fp, "%d", &maze[i][j]);
        }
    }
    fscanf(fp, "%d %d %d %d", &(start->x), &(start->y), &(final->x), &(final->y));
}

void print(Stack *a, int rows, int cols, int (*mark)[MAX], int (*maze)[MAX], int (*paths)[MAX], offsets *move, coordinate start, coordinate final) {
    printf("[MAZE]\n");
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if (i == start.x + 1 && j == start.y + 1) {
                printf("S ");
            }
            else if (i == final.x + 1 && j == final.y + 1) {
                printf("F ");
            }
            else {
                printf("%d ", maze[i][j]);
            }
        }
        printf("\n");
    }
    int found = path(mark, maze, a, move, cols, rows, start, final);
    
    if (found) {
        while (!isEmpty(a)) {
            element e = pop(a);
            paths[e.row][e.col] = 1;
        }
        paths[final.x + 1][final.y + 1] = 1;
    }

    if(found){
        printf("[PATH]\n");
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                if (i == start.x + 1 && j == start.y + 1)
                    printf("S ");
                else if (i == final.x + 1 && j == final.y + 1)
                    printf("F ");
                else if (paths[i][j])
                    printf("X ");
                else
                    printf("%d ", maze[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("No path.");
    }
}

int main() {
    Stack a;
    int rows, cols;
    int mark[MAX][MAX] = {0};
    int maze[MAX][MAX] = {1};
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            maze[i][j] = 1; 
        }
    }
    int paths[MAX][MAX] = {0};
    coordinate start;
    coordinate final;
    FILE *fp = fopen("maze1.txt", "r");
    
    a.top = -1;
    a.capacity = 10;
    a.stack = malloc(sizeof(element) * a.capacity);
    
    offsets move[8] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}}; 
    scan(fp, maze, &rows, &cols, &start, &final);
    print(&a, rows, cols, mark, maze, paths, move, start, final);
    
    fclose(fp);
    free(a.stack);
    fp = fopen("maze2.txt", "r");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            maze[i][j] = 1;
            mark[i][j] = 0;
            paths[i][j] = 0; 
        }
    }
    a.top = -1;
    a.capacity = 10;
    a.stack = malloc(sizeof(element) * a.capacity);
    scan(fp, maze, &rows, &cols, &start, &final);
    print(&a, rows, cols, mark, maze, paths, move, start, final);
    fclose(fp);
    free(a.stack);
    fp = fopen("maze3.txt","r");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            maze[i][j] = 1;
            mark[i][j] = 0;
            paths[i][j] = 0; 
        }
    }
    a.top = -1;
    a.capacity = 10;
    a.stack = malloc(sizeof(element) * a.capacity);
    scan(fp, maze, &rows, &cols, &start, &final);
    print(&a, rows, cols, mark, maze, paths, move, start, final);
    fclose(fp);
    free(a.stack);
    return 0;
}