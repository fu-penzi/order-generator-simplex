#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ID 1000
char* names[] = {
    "Jet Networks",
    "Hummingbird",
    "Elvish Media",
    "Rosecurity",
    "Leopardworks",
    "Omegacoustics",
    "Bullimited",
    "Ironstone",
    "Webspace",
    "Gemnite",
    "Phantasm Intelligence",
    "Parable Brews",
    "Phenomenon Intelligence",
    "Moonlightings",
    "Smartechnologies",
    "Lemonetworks",
    "Phantasmedia",
    "Chiefsearch",
    "Nimblehouse",
    "Diamondbit",
    "River Productions"
    "Cyclops Entertainment",
    "Blue Navigations",
    "Butterflyght",
    "Mermedia",
    "Asco",
    "Boarco",
    "Arcaneshow",
    "Wavemobile",
    "Smiletechs",
    "Nemo Records",
    "Loki Foods",
    "Motion Industries",
    "Energence",
    "Moonlightings",
    "Brisco",
    "Luckytronics",
    "Stormpaw",
    "Hatchfly",
    "Nemotube",
    "Hound Systems",
    "Star Records",
    "Slick",
    "Bullimited",
    "Grottolutions",
    "Solsticetems",
    "Elecoms",
    "Lagoontechs",
    "Oceansearch",
    "Marblespace",
    "Hero Security",
    "Aura Acoustics",
    "Orange",
    "Wizardustries",
    "Ansoft",
    "Sunavigations",
    "Cavologies",
    "Fairybridge",
    "Crowware",
    "Micromobile",
    "Gem Corporation",
    "Hound Corporation",
    "Alp Entertainment",
    "Riverecords",
    "Crowares",
    "Lokilutions",
    "Cloverprises",
    "Caverngold",
    "Mermaidsys",
    "Nimblewares",
    "Hammer Entertainment",
    "Bull Productions",
    "Fire",
    "Oystertainment",
    "Hummingbirdustries",
    "Mountainetworks",
    "Energence",
    "Gemcoms",
    "Gnometube",
    "Ocean Enterprises",
    "Apricot Technologies",
    "Bluff Acoustics",
    "Asco",
    "North Starporation",
    "Buckoustics",
    "Nightelligence",
    "Caverncast",
    "Boarworth",
    "Quadking",
    "Jetsun",
    "Hero",
    "Ask Co.",
    "Moonlight Aviation",
    "Summitechnologies",
    "Neroductions",
    "Sunshinetworks",
    "Jupitelligence",
    "Riddledream",
    "Wolfpoly",
    "Wizardshow",
};
int main(int argc, char** argv)
{
    FILE* out = fopen("output/data_in/d7-dane_losowe_50x50.txt", "w");
    int totalProduced = 200000;
    int totalNeeded = 10000;
    int nm = 50;
    int nph = 50;
    int dailyProduction[MAX_ID];
    int dailyNeed[MAX_ID];
    int dailyMax[MAX_ID][MAX_ID];
    srand(time(NULL));
    fprintf(out, "# Producenci szczepionek (id | nazwa | dzienna produkcja)\n");
    int namesId = 0;
    for (int i = 0; i < nm - 1; i++) {
        dailyProduction[i] = rand() % totalProduced * 2 / (nm - i);
        if (dailyProduction[i] >= totalProduced) {
            dailyProduction[i] = totalProduced / 2;
        }
        totalProduced -= dailyProduction[i];
        if (namesId > 49) {
            namesId = 0;
        }
        fprintf(out, "%d | %s | %d\n", i, names[namesId], dailyProduction[i]);
        namesId++;
    }
    dailyProduction[nm - 1] = totalProduced;
    fprintf(out, "%d | %s | %d\n", nm - 1, names[namesId - 1], dailyProduction[nm - 1]);

    fprintf(out, "# Apteki (id | nazwa | dzienne zapotrzebowanie)\n");
    namesId = 50;
    for (int i = 0; i < nph - 1; i++) {
        dailyNeed[i] = rand() % totalNeeded * 2 / (nph - i);
        if (dailyNeed[i] >= totalNeeded) {
            dailyNeed[i] = totalNeeded / 2;
        }
        totalNeeded -= dailyNeed[i];
        fprintf(out, "%d | %s | %d\n", i, names[namesId], dailyNeed[i]);
        if (namesId > 99) {
            namesId = 51;
        }
        namesId++;
    }
    dailyNeed[nph - 1] = totalNeeded;
    fprintf(out, "%d | %s | %d\n", nph - 1, names[namesId - 1], totalNeeded);

    fprintf(out, "# Połączenia producentów i aptek (id producenta | id apteki | dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [zł] )\n");
    for (int i = 0; i < nm; i++) {
        for (int j = 0; j < nph; j++) {
            int tmp = rand() % (dailyProduction[i] / 2) + dailyProduction[i] / 2;
            fprintf(out, "%d | %d | %d | %.2lf\n", i, j, tmp, ((double)rand() * (170.20 - 66.11)) / (double)RAND_MAX + 66.11);
        }
    }
    return 0;
}
