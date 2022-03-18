#ifndef _SIMPLEX_H_
#define _SIMPLEX_H_
#include <stdbool.h>
#include "table.h"
void calculateDelta(Table t);
bool isFeasible(Table t);
void pivot(Table t ,int x, int y);
int findRow(Table t);
int findColumn(Table t, int x);
int* dualSimplex(Table t);
#endif
