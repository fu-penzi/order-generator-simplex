#ifndef _IO_H_
#define _IO_H_
#define MAX_BUF 8192
#define MAX_ID 1000
#define MAX_NAME_LENGTH 512

typedef struct {
    int i;
    int j;
    int maxAmount;
    double price;
} Connection;

typedef struct {
    int n;
    int id[MAX_ID];
    char name[MAX_ID][MAX_NAME_LENGTH];
    int dailyAmount[MAX_ID];
} Institutions;

typedef struct {
    Institutions manufacturers;
    Institutions pharmacies;
    Connection* connections;
} * Input;
void err(char* error, int line, char* buf);
Input readFile(char* fname);
void resultsToFile(char* fname, double totalCost, int* amount, Institutions manufacturers, Institutions pharmacies, Connection* connections);
#endif
