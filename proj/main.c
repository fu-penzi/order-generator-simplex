#include "io.h"
#include "simplex.h"
#include "table.h"
#include <stdio.h>
#include <getopt.h>
char* usage = "Uzycie:\n\t-i  -  plik wejściowy\n\t-o  -  plik wyjściowy\n";
int main(int argc, char** argv)
{
    int opt;
    char* in = NULL;
    char* out = NULL;
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
        case 'o':
            out = optarg;
            break;
        case 'i':
            in = optarg;
            break;
        default:
            err(usage,-1,NULL);
        }
    }
    if (in == NULL ) {
        fprintf(stderr, "%s", usage);
        err("Brak nazwy pliku wejsciowego.", -1, NULL);
    }
    if (out == NULL) {
        fprintf(stderr, "%s", usage);
        err("Brak nazwy pliku wyjsciowego.", -1, NULL);
    }
    
    Input i = readFile(in);
    Table t = initializeTable(i->manufacturers.n, i->pharmacies.n);
    setUpTable(t, i->manufacturers, i->pharmacies, i->connections);
    int* amount = dualSimplex(t);
    double totalCost = 0;
    for (int i = 0; i < t->m; i++) {
        totalCost -= t->cb[i] * t->b[i];
    }
    resultsToFile(out, totalCost, amount, i->manufacturers, i->pharmacies, i->connections);

    return 0;
}
