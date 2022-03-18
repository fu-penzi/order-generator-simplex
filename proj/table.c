#include "table.h"
#include <stdio.h>
#include <stdlib.h>
Table initializeTable(int nm, int nph)
{
    int n = nm * nph;
    int m = nm + nph + n + 1;

    Table t = malloc(sizeof *t);
    t->m = m;
    t->n = n;
    t->A = malloc(m * sizeof(double*));
    for (int i = 0; i < m; i++) {
        t->A[i] = malloc((m + n) * sizeof(double));
    }
    t->b = malloc(m * sizeof(double));
    t->c = malloc((n + m) * sizeof(double));
    t->cb = malloc(m * sizeof(double));

    t->delta = malloc((n + m) * sizeof(double));
    t->B = malloc(m * sizeof(int));
    return t;
}
void setManufacturerConditions(Table t, Institutions mn, int nph)
{
    for (int i = 0; i < mn.n; i++) {
        for (int j = 0; j < nph; j++) {
            int index = nph * i + j;
            t->A[i][index] = 1;
        }
    }
    for (int i = 0; i < mn.n; i++) {
        t->b[i] = mn.dailyAmount[i];
    }
}
void setPharmacyConditions(Table t, Institutions ph, int nm)
{
    for (int j = 0; j < ph.n; j++) {
        for (int i = 0; i < nm; i++) {
            int index = ph.n * i + j;
            t->A[nm + j][index] = 1;
        }
    }
    for (int i = 0; i < ph.n; i++) {
        t->b[nm + i] = ph.dailyAmount[i];
    }
}
void setConnectionConditions(Table t, Connection* c, int nm, int nph)
{
    for (int i = 0; i < nm; i++) {
        for (int j = 0; j < nph; j++) {
            int index = nph * i + j;
            t->A[nm + nph + index][index] = 1;
        }
    }
    for (int i = 0; i < t->n; i++) {
        t->b[nm + nph + i] = c[i].maxAmount;
    }
}
void setUpTable(Table t, Institutions mn, Institutions ph, Connection* c)
{
    setManufacturerConditions(t, mn, ph.n);
    setPharmacyConditions(t, ph, mn.n);
    setConnectionConditions(t, c, mn.n, ph.n);

    int n = mn.n * ph.n;
    for (int i = 0; i < mn.n; i++) {
        for (int j = 0; j < ph.n; j++) {
            int index = ph.n * i + j;
            t->A[mn.n + ph.n + n][index] = -1;
        }
    }
    for (int i = 0; i < ph.n; i++) {
        t->b[mn.n + ph.n + t->n] -= ph.dailyAmount[i];
    }

    for (int i = 0; i < t->m; i++) {
        t->A[i][n + i] = 1;
    }
    for (int i = 0; i < t->n; i++) {
        t->c[i] = -c[i].price;
    }
    for (int i = 0; i < t->m; i++) {
        t->c[t->n + i] = 0;
    }
    for (int i = 0; i < t->m; i++) {
        t->cb[i] = 0;
    }
    for (int i = 0; i < t->n + t->m; i++) {
        t->delta[i] = -t->c[i];
    }
    for (int i = 0; i < t->m; i++) {
        t->B[i] = n + i;
    }
}
