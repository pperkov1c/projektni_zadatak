#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include "Strukture.h"
#include "Header.h"

int izbornik(const char* const lijekoviDat) {

    static LIJEK* poljeLijekova = NULL;
    static LIJEK* pronadjeniLijek = NULL;

    int odabir = 0;
    int tocanUnos = 0;

    do {
        printf("***************************************\n");
        printf("       ~ BAZA PODATAKA LIJEKOVA ~          \n");
        printf("***************************************\n");
        printf("1. Unos novog lijeka             \n");
        printf("2. Stanje svih lijekova u ljekarni  \n");
        printf("3. Pretrazivanje lijeka po imenu       \n");
        printf("4. Pretrazivanje lijeka po ID-u	       \n");
        printf("5. Sortiranje lijekova po cijeni	       \n");
        printf("6. Azuriranje lijeka           \n");
        printf("7. Brisanje lijeka iz ljekarne	       \n");
        printf("8. Promjena imena datoteke	       \n");
        printf("9. Brisanje datoteke      \n");
        printf("10. Izlaz iz programa         \n");

        scanf("%d", &odabir);
        char unos[10];
        do {
            printf("\nUnesite broj od 1 do 10: ");
            scanf("%9s", unos);

            if (sscanf(unos, "%d", &odabir) != 1 || odabir < 1 || odabir > 10) {
                printf("Nevazeci unos. Molimo unesite broj od 1 do 10.\n");
                odabir = 0;
                while (getchar() != '\n');
            }

        } while (odabir == 0);

        if (odabir >= 1 && odabir <= 10) {
            tocanUnos = 1;
        }
        else {
            printf("Neispravan unos. Molimo odaberite broj izmedu 1 i 10.\n");
        }
    } while (!tocanUnos);

    switch (odabir) {
    case 1:
        dodajLijek(lijekoviDat);
        break;

    case 2:

        if (poljeLijekova != NULL) {
            free(poljeLijekova);
            poljeLijekova = NULL;
        }

        poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

        stanjeLijekova(poljeLijekova);

        break;

    case 3:

        if (poljeLijekova != NULL) {
            free(poljeLijekova);
            poljeLijekova = NULL;
        }

        poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

        pretrazivnajeLijekaIme(poljeLijekova);
        break;


    case 4:

        if (poljeLijekova != NULL) {
            free(poljeLijekova);
            poljeLijekova = NULL;
        }

        poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

        pretrazivnajeLijeka(poljeLijekova);

        break;

    case 5:

        if (poljeLijekova != NULL) {
            free(poljeLijekova);
            poljeLijekova = NULL;
        }

        poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

        sortiranjeLijekova(poljeLijekova);

        break;

    case 6:
        if (poljeLijekova != NULL) {
            free(poljeLijekova);
            poljeLijekova = NULL;
        }

        poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

        azuriranjeLijeka(poljeLijekova, lijekoviDat);

        break;

    case 7:

        if (poljeLijekova != NULL) {
            free(poljeLijekova);
            poljeLijekova = NULL;
        }

        poljeLijekova = (LIJEK*)ucitajLijekove(lijekoviDat);

        brisanjeLijeka(poljeLijekova, lijekoviDat);

        break;

    case 8:
        promjenaImenaDatoteci(lijekoviDat);
        break;

    case 9:
        brisanjeDatoteke(lijekoviDat);
        break;

    case 10:
        odabir = izlazIzPrograma(poljeLijekova);
        break;

    default:
        odabir = 0;
    }

    return odabir;
}