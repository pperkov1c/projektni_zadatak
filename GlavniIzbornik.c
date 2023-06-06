#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include "Strukture.h"
#include "Header.h"

int izbornik(const char* const lijekoviDat, const char* const racuniDat) { //8.

	static LIJEK* poljeLijekova = NULL; //9.
	static LIJEK* pronadjeniLijek = NULL;

	int odabir = 0;



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

	switch (odabir) {

	case 1:
		dodajLijek(lijekoviDat);
		break;

	case 2:

		if (poljeLijekova != NULL) {
			free(poljeLijekova); //15.
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
