#ifndef _TABLE_H_
#define _TABLE_H_
#include "io.h"
typedef struct {
    int m;
    int n;
    double** A;
    double* b;
    double* c;
    double* cb;
    double* delta;
    int* B;
} * Table;

Table initializeTable(int n_m, int n_ph);
void setUpTable(Table t, Institutions m, Institutions ph, Connection* c);
#endif
