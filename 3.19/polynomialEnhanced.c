#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int coef;
    int expon;
} Polynomial;

typedef struct {
    Polynomial *terms;
    int start;
    int finish;
} PolyRange;

typedef struct {
    Polynomial *terms;
    int avail;
} PolyManager;

int compare(int a, int b) {
    return (a == b) ? 0 : (a > b ? 1 : -1);
}

void attach(PolyManager *pm, int coef, int expon) {
    pm->terms[pm->avail].coef = coef;
    pm->terms[pm->avail].expon = expon;
    pm->avail++;
}

PolyRange minus(PolyManager *pm, PolyRange A, PolyRange B) {
    int coef;
    PolyRange D;
    D.start = pm->avail;

    while (A.start <= A.finish && B.start <= B.finish) {
        switch (compare(pm->terms[A.start].expon, pm->terms[B.start].expon)) {
            case -1:
                attach(pm, -pm->terms[B.start].coef, pm->terms[B.start].expon);
                B.start++;
                break;
            case 0:
                coef = pm->terms[A.start].coef - pm->terms[B.start].coef;
                if (coef != 0) {
                    attach(pm, coef, pm->terms[A.start].expon);
                }
                A.start++;
                B.start++;
                break;
            case 1:
                attach(pm, pm->terms[A.start].coef, pm->terms[A.start].expon);
                A.start++;
                break;
        }
    }

    while (A.start <= A.finish) {
        attach(pm, pm->terms[A.start].coef, pm->terms[A.start].expon);
        A.start++;
    }

    while (B.start <= B.finish) {
        attach(pm, -pm->terms[B.start].coef, pm->terms[B.start].expon);
        B.start++;
    }

    D.finish = pm->avail - 1;
    return D;
}

PolyRange readPoly(FILE *fp, PolyManager *pm) {
    int count;
    fscanf(fp, "%d", &count);
    PolyRange range;
    range.start = pm->avail;
    range.finish = pm->avail + count - 1;

    for (int i = 0; i < count; i++) {
        fscanf(fp, "%d %d", &pm->terms[pm->avail].coef, &pm->terms[pm->avail].expon);
        pm->avail++;
    }
    return range;
}

void printPoly(PolyRange poly, Polynomial *terms) {
    int size = poly.finish - poly.start + 1;
    printf("\n%d ", size);
    for (int i = poly.start; i <= poly.finish; i++) {
        printf("%d %d ", terms[i].coef, terms[i].expon);
    }
}

int main() {
    FILE *fp1 = fopen("./in1.txt", "r");
    FILE *fp2 = fopen("./in2.txt", "r");

    Polynomial *terms = malloc(sizeof(Polynomial) * 200);
    PolyManager pm = { terms, 0 };

    PolyRange A = readPoly(fp1, &pm);
    PolyRange B = readPoly(fp1, &pm);
    PolyRange D = minus(&pm, A, B);

    printPoly(D, pm.terms);

    A = readPoly(fp1, &pm);
    B = readPoly(fp1, &pm);
    D = minus(&pm, A, B);

    printPoly(D, pm.terms);
    fclose(fp1);
    fclose(fp2);
    free(terms);
    return 0;
}
