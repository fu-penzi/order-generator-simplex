#include "simplex.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
void calculateDelta(Table t)
{
    for (int j = 0; j < t->n + t->m; j++) {
        double tmp = 0;
        for (int i = 0; i < t->m; i++) {
            if (t->cb[i] != 0 && t->A[i][j] != 0) {
                tmp += t->cb[i] * t->A[i][j];
            }
        }
        t->delta[j] = tmp - t->c[j];
    }
}
bool isFeasible(Table t)
{
    calculateDelta(t);

    for (int j = 0; j < t->m + t->n; j++) {
        if (t->delta[j] < 0) {
            err("Niewlasciwe dane wejsciowe.", -1, NULL);
        }
    }

    for (int i = 0; i < t->m; i++) {
        if (t->b[i] < 0) {
            return false;
        }
    }
    return true;
}
void pivot(Table t, int x, int y)
{
    double pivot = t->A[x][y];
    t->b[x] /= pivot;
    for (int j = 0; j < t->n + t->m; j++) {
        if (t->A[x][j] != 0) {
            t->A[x][j] /= pivot;
        }
    }
    for (int i = 0; i < t->m; i++) {
        if (t->A[i][y] != 0 && i != x) {
            double tmp = -t->A[i][y];
            t->b[i] += tmp * t->b[x];
            for (int j = 0; j < t->m + t->n; j++) {
                t->A[i][j] += tmp * t->A[x][j];
            }
        }
    }
    t->B[x] = y;
    t->cb[x] = t->c[y];
}
int findRow(Table t)
{
    int x = 0;
    double minb = t->b[0];
    for (int i = 1; i < t->m; i++) {
        if (t->b[i] < minb) {
            x = i;
            minb = t->b[i];
        }
    }
    return x;
}
int findColumn(Table t, int x)
{
    int y = -1;
    double maxRatio = -1;
    for (int j = 0; j < t->n + t->m; j++) {
        if (t->A[x][j] < 0) {
            double ratio = t->delta[j] / t->A[x][j];
            if (y == -1 || maxRatio < ratio) {
                maxRatio = ratio;
                y = j;
            }
        }
    }
    return y;
}
int* dualSimplex(Table t)
{
    while (!isFeasible(t)) {

        int pivotRow = findRow(t);
        int pivotColumn = findColumn(t, pivotRow);

        if (pivotColumn == -1) {
            err("Niewystarczajaca ilosc szczepionek aby zaspokoic dzienne zapotrzebowanie wszystkich aptek.", -1, NULL);
        }

        pivot(t, pivotRow, pivotColumn);
    }

    int* result = malloc(t->m * sizeof(int));
    for (int j = 0; j < t->m; j++) {
        result[j] = 0;
    }
    for (int i = 0; i < t->m; i++) {
        if (t->B[i] < t->n) {
            result[t->B[i]] = t->b[i];
        }
    }
    return result;
}