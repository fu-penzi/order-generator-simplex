#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* progname = "orders";
void err(char* error, int line, char* buf)
{
    if (line == -1) {
        fprintf(stderr, "%s:%s\n\n", progname, error);
    } else {
        fprintf(stderr, "%s:%s %d :\n\t%s\n\n", progname, error, line, buf);
    }
    exit(EXIT_FAILURE);
}
void setInstitution(Institutions* institutions, int id, char* name, int dailyAmount)
{
    institutions->id[id] = id;
    strcpy(institutions->name[id], name);
    institutions->dailyAmount[id] = dailyAmount;
}
void setConnection(Connection* connection, int i, int j, int maxAmount, double price)
{
    connection->i = i;
    connection->j = j;
    connection->maxAmount = maxAmount;
    connection->price = price;
}
Input readFile(char* fname)
{
    char buf[MAX_BUF];

    Institutions manufacturers;
    int nm = 0;
    for (int i = 0; i < MAX_ID; i++) {
        manufacturers.id[i] = -1;
    }
    manufacturers.n = 0;

    Institutions pharmacies;
    int nph = 0;
    for (int i = 0; i < MAX_ID; i++) {
        pharmacies.id[i] = -1;
    }
    pharmacies.n = 0;

    Connection* connections;
    int nc = 0;

    FILE* in = fopen(fname, "r");
    if (in == NULL) {
        err("Nie udalo sie otworzyc pliku wejsciowego", -1, NULL);
    }
    int line = 1;
    if (fgets(buf, MAX_BUF, in) == NULL) {
        err("Pusty plik wejsciowy.", -1, "");
    }
    if (buf[0] != '#') {
        err("Bledny format danych wejsciowych w linii #", line, buf);
    }
    line++;
    while (fgets(buf, MAX_BUF, in) != NULL && buf[0] != '#') {
        int id;
        char name[MAX_NAME_LENGTH];
        int dailyAmount;
        if (sscanf(buf, " %d | %[^|] | %d ", &id, name, &dailyAmount) == 3) {
            if (id < 0 || dailyAmount < 0) {
                err("Wczytano ujemna wartosc w linii #", line, buf);
            }
            if (manufacturers.id[id] != -1) {
                err("Wczytano powtarzajacy sie indeks w linii #", line, buf);
            }
            if (id + 1 > manufacturers.n) {
                manufacturers.n = id + 1;
            }
            setInstitution(&manufacturers, id, name, dailyAmount);
            nm++;
            line++;
        } else {
            err("Bledny format danych wejsciowych w linii #", line, buf);
        }
    }
    if (manufacturers.n != nm) {
        err("Brakuje producentow.", -1, NULL);
    }

    while (fgets(buf, MAX_BUF, in) != NULL && buf[0] != '#') {
        int id;
        char name[MAX_NAME_LENGTH];
        int dailyAmount;
        if (sscanf(buf, " %d | %[^|] | %d ", &id, name, &dailyAmount) == 3) {
            if (id < 0 || dailyAmount < 0) {
                err("Wczytano ujemna wartosc w linii #", line, buf);
            }
            if (pharmacies.id[id] != -1) {
                err("Wczytano powtarzajacy sie indeks w linii #", line, buf);
            }
            if (id + 1 > pharmacies.n) {
                pharmacies.n = id + 1;
            }
            setInstitution(&pharmacies, id, name, dailyAmount);
            nph++;
            line++;

        } else {
            err("Bledny format danych wejsciowych w linii #", line, buf);
        }
    }
    if (pharmacies.n != nph) {
        err("Brakuje aptek.", -1, NULL);
    }
    if (manufacturers.n == 0 || pharmacies.n == 0) {
        err("Wejsciowy plik nie zawiera niezbednych danych.", -1, NULL);
    }
    connections = malloc(nm * nph * sizeof *connections);
    for (int i = 0; i < nm; i++) {
        for (int j = 0; j < nph; j++) {
            connections[nph * i + j].i = -1;
            connections[nph * i + j].j = -1;
        }
    }
    while (fgets(buf, MAX_BUF, in) != NULL) {
        int i;
        int j;
        int maxAmount;
        double price;
        if (buf[0] == '#') {
            err("Bledny format danych wejsciowych w linii #", line, buf);
        }
        if (sscanf(buf, " %d | %d | %d | %lf ", &i, &j, &maxAmount, &price) == 4) {
            if (i < 0 || j < 0 || maxAmount < 0 || price < 0) {
                err("Wczytano ujemna wartosc w linii #", line, buf);
            }
            if (i + 1 > manufacturers.n || j + 1 > pharmacies.n) {
                err("Wczytano indeks nieistniejacej instytucji w linii #", line, buf);
            }
            if (connections[nph * i + j].i != -1 || connections[nph * i + j].j != -1) {
                err("Wczytano powtarzajacy sie indeks w linii #", line, buf);
            }
            setConnection(&connections[nph * i + j], i, j, maxAmount, price);
            nc++;
            line++;
        } else {
            err("Bledny format danych wejsciowych w linii #", line, buf);
        }
    }
    if (nc != manufacturers.n * pharmacies.n) {
        err("Brakuje polaczen.", -1, NULL);
    }
    Input i = malloc(sizeof *i);
    i->manufacturers = manufacturers;
    i->pharmacies = pharmacies;
    i->connections = connections;
    return i;
}
void resultsToFile(char* fname, double totalCost, int* amount, Institutions manufacturers, Institutions pharmacies, Connection* connections)
{
    FILE* out = fopen(fname, "w");
    if (out == NULL) {
        err("Nie udalo sie utworzyc pliku wyjsciowego", -1, NULL);
    }
    for (int i = 0; i < manufacturers.n; i++) {
        for (int j = 0; j < pharmacies.n; j++) {
            int index = pharmacies.n * i + j;
            double cost = amount[index] * connections[index].price;
            fprintf(out, "%s -> %s [Koszt = %d * %.2lf = %.2lf]\n", manufacturers.name[i], pharmacies.name[j], amount[index], connections[index].price, cost);
        }
    }
    fprintf(out, "Oplaty całkowite: %.2lf", totalCost);
}