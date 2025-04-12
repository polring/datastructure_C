// 최대한 효율성 생각하면서 구현 매개변수도 최소한으로 줄임
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int row, col, dir;
} element;
typedef struct {
    int vert;
    int horiz;
} offsets;
typedef struct {
    element *stack;
    int top, capacity;
} Stack;

typedef struct {
    int rows, cols;
    int maze[MAX][MAX];
} Maze;

const offsets move[8] = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};

int isEmpty(Stack *s) { return s->top == -1; }
int isFull(Stack *s) { return s->top == s->capacity - 1; }

void push(Stack *s, element p) {
    if (isFull(s)) {
        s->capacity *= 2;
        s->stack = realloc(s->stack, sizeof(element) * s->capacity);
    }
    s->stack[++s->top] = p;
}

element pop(Stack *s) { return s->stack[s->top--]; }
// 따로 배열을 사용하지 않고 방문한 곳은 -1로 표시
int path(Maze *m, Stack *s, element start, element end) {
    int found = 0;
    element pos = {start.row + 1, start.col + 1, 0};
    m->maze[pos.row][pos.col] = -1;
    push(s, pos);

    while (!isEmpty(s) && !found) {
        pos = pop(s);
        int row = pos.row, col = pos.col, dir = pos.dir;

        while (dir < 8 && !found) {
            int next_row = row + move[dir].vert;
            int next_col = col + move[dir].horiz;

            if (next_row == end.row + 1 && next_col == end.col + 1) {
                found = 1;
                push(s, (element){row, col, dir});
            } else if (!m->maze[next_row][next_col]) {
                m->maze[next_row][next_col] = -1; 
                push(s, (element){row, col, dir + 1});
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

void scan(FILE *fp, Maze *m, element *start, element *end) {
    fscanf(fp, "%d %d", &m->rows, &m->cols);
    for (int i = 1; i <= m->rows; i++)
        for (int j = 1; j <= m->cols; j++)
            fscanf(fp, "%d", &m->maze[i][j]);
    fscanf(fp, "%d %d %d %d", &start->row, &start->col, &end->row, &end->col);
}

void print(Maze *m, Stack *s, element start, element end) {
    printf("[MAZE]\n");
    for (int i = 1; i <= m->rows; i++) {
        for (int j = 1; j <= m->cols; j++) {
            if (i == start.row + 1 && j == start.col + 1) printf("S ");
            else if (i == end.row + 1 && j == end.col + 1) printf("F ");
            else printf("%d ", m->maze[i][j]);
        }
        printf("\n");
    }

    int found = path(m, s, start, end);
    element data;
    if (found) {
        while(!isEmpty(s)){
            data = pop(s);
            m->maze[data.row][data.col] = 2;
        }
        printf("[PATH]\n");
        for (int i = 1; i <= m->rows; i++) {
            for (int j = 1; j <= m->cols; j++) {
                if (i == start.row + 1 && j == start.col + 1) printf("S ");
                else if (i == end.row + 1 && j == end.col + 1) printf("F ");
                // stack에 남아 있는 좌표(탈출 경로)는 2로 표시
                else if (m->maze[i][j] == 2) printf("X ");
                //한번이라도 간 경우 -1로 표시
                else if (m->maze[i][j] == -1) printf("0 ");
                else printf("%d ",m->maze[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("No path.\n");
    }
}

void init_maze(Maze *m) {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++) {
            m->maze[i][j] = 1;
        }
}

int main() {
    Maze m = {0};
    Stack s = {NULL,-1,10};
    element start, end;
    s.stack = malloc(sizeof(element) * s.capacity);

    const char *files[] = {"maze1.txt", "maze2.txt", "maze3.txt"};
    for (int i = 0; i < 3; i++) {
        FILE *fp = fopen(files[i], "r");
        init_maze(&m);
        s.top = -1;
        scan(fp, &m, &start, &end);
        print(&m, &s, start, end);
        fclose(fp);
    }

    free(s.stack);
    return 0;
}