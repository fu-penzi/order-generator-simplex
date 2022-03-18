#include "../../io.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    char* in = argc > 1 ? argv[1] : NULL;
    FILE* out = argc > 2 ? fopen(argv[2], "r") : NULL;
    if (in == NULL || out == NULL) {
        fprintf(stderr, "Podaj poprawne pliki wejsciowe");
        exit(EXIT_FAILURE);
    }

    Input d = readFile(in);
    int nm = d->manufacturers.n;
    int nph = d->pharmacies.n;

    int* amount = malloc(nm * nph * sizeof(int));
    double* vaccinePrice = malloc(nm * nph * sizeof(double));
    double* orderPrice = malloc(nm * nph * sizeof(double));
    double totalCost;
    int n = 0;
    char buf[MAX_BUF];
    while (fgets(buf, MAX_BUF, out) != NULL) {
        char str[MAX_NAME_LENGTH * 3];
        if (sscanf(buf, "%[^[] [Koszt = %d * %lf = %lf]", str, &amount[n], &vaccinePrice[n], &orderPrice[n]) == 4) {
            n++;
        } else if (sscanf(buf, "Oplaty całkowite: %lf", &totalCost) == 1) {
        } else {
            err("Bledny format pliku z wynikami.", n, buf);
        }
    }
    if (n != nm * nph) {
        fprintf(stderr, "Bledny format pliku z wynikami.\nn = %d nm = %d nph = %d\n", n, nm, nph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nm * nph; i++) {
        if (vaccinePrice[i] != d->connections[i].price) {
            err("Bledne koszty.", -1, NULL);
        }
        if (amount[i] > d->connections[i].maxAmount) {
            err("Bledna ilosc zamowionych szczepionek.", -1, NULL);
        }
    }

    int* boughtByPharmacy = malloc(nph * sizeof(int));
    for (int j = 0; j < nph; j++) {
        for (int i = 0; i < nm; i++) {
            boughtByPharmacy[j] += amount[nph * i + j];
        }
        if (boughtByPharmacy[j] != d->pharmacies.dailyAmount[j]) {
            err("Bledna ilosc zakupionych szczepionek.", -1, buf);
        }
    }

    int* soldByManufacurer = malloc(nm * sizeof(int));
    for (int i = 0; i < nm; i++) {
        for (int j = 0; j < nph; j++) {
            soldByManufacurer[i] += amount[nph * i + j];
        }
        if (soldByManufacurer[i] > d->manufacturers.dailyAmount[i]) {
            err("Bledna ilosc sprzedanych szczepionek.\n", -1, buf);
        }
    }
    printf("Pozytywny wynik testu dla danych %s\n\n", argv[1]);
    return 0;
}