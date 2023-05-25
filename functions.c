#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include "dataType.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int brojLijekova = 0; // 1. 5.

void kreiranjeDatoteke(const char* ime) { // 4.
	FILE* fp = fopen(ime, "rb"); // 16.

	if (fp == NULL) {
		fp = fopen(ime, "wb");
		fwrite(&brojLijekova, sizeof(int), 1, fp);
		fclose(fp);
	}
	else {
		fclose(fp);
	}
}

void dodajLijek(const char* ime) {
	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje lijeka u datoteku lijekovi.bin"); // 19.
		exit(EXIT_FAILURE);
	}

	fread(&brojLijekova, sizeof(int), 1, fp);
	//printf("Broj lijekova: %d\n\n", brojLijekova);

	LIJEK temp = { 0 };
	temp.id = brojLijekova + 1;
	//getchar();

	printf("Unesite ime lijeka: ");
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite proizvodaca lijeka: ");
	scanf("%39[^\n]", temp.proizvodac);
	getchar();

	printf("Unesite kolicinu lijeka: ");
	scanf("%d", &temp.kolicina);

	printf("Unesite cijenu lijeka: ");
	scanf("%lf", &temp.cijena);

	fseek(fp, 0, SEEK_END);
	fwrite(&temp, sizeof(LIJEK), 1, fp);

	brojLijekova++;
	fseek(fp, 0, SEEK_SET);
	fwrite(&brojLijekova, sizeof(int), 1, fp);
	rewind(fp); // 17.

	fclose(fp);
}

void* ucitajLijekove(const char* ime) {
	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje lijekova iz datoteke lijekovi.bin");
		exit(EXIT_FAILURE);
	}

	fread(&brojLijekova, sizeof(int), 1, fp);

	LIJEK* polje = malloc(brojLijekova * sizeof(LIJEK)); // 14.

	if (polje == NULL) {
		fclose(fp);
		fprintf(stderr, "Alokacija memorije za polje lijekova: Not enough space\n");
		exit(EXIT_FAILURE);
	}

	fread(polje, sizeof(LIJEK), brojLijekova, fp);

	fclose(fp);

	return polje;
}

void ispisiSveLijekove(const void* polje) {
	const LIJEK* lijekovi = (const LIJEK*)polje;

	printf("%-12s | %-20s | %-19s | %-8s | %-6s\n", "ID", "Ime lijeka", "Proizvodac", "Kolicina", "Cijena");
	printf("------------+-----------------------+---------------------+----------+-------\n");
	for (int i = 0; i < brojLijekova; i++) {
		printf("%-12d | %-20s | %-19s | %-8d | %.2lfkn \n", lijekovi[i].id, lijekovi[i].ime, lijekovi[i].proizvodac, lijekovi[i].kolicina, lijekovi[i].cijena);
	}
}

void* pretraziLijekove(const void* polje) {
	const LIJEK* lijekovi = (const LIJEK*)polje;
	char ime[25];
	printf("Unesite ime lijeka za pretragu: ");
	scanf("%24[^\n]", ime);
	getchar();

	for (int i = 0; i < brojLijekova; i++) {
		if (strcmp(lijekovi[i].ime, ime) == 0) {
			return (void*)&lijekovi[i];
		}
	}

	return NULL;
}

void uredivanjeLijekova(void* polje, const char* ime) {
	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Uredivanje lijekova u datoteci lijekovi.bin");
		exit(EXIT_FAILURE);
	}

	LIJEK* lijekovi = (LIJEK*)polje;
	char trazeniLijek[25];
	printf("Unesite ime lijeka za uredivanje: ");
	scanf("%24[^\n]", trazeniLijek);
	getchar();

	int pronadjen = 0;
	for (int i = 0; i < brojLijekova; i++) {
		if (strcmp(lijekovi[i].ime, trazeniLijek) == 0) {
			pronadjen = 1;

			printf("Unesite novo ime lijeka: ");
			scanf("%s", lijekovi[i].ime);

			printf("Unesite novog proizvodaca lijeka: ");
			scanf("%s", lijekovi[i].proizvodac);

			printf("Unesite novu kolicinu lijeka: ");
			scanf("%d", &lijekovi[i].kolicina);
			getchar();

			printf("Unesite novu cijenu lijeka: ");
			scanf("%lf", &lijekovi[i].cijena);
			getchar();

			fseek(fp, sizeof(int) + i * sizeof(LIJEK), SEEK_SET);
			fwrite(&lijekovi[i], sizeof(LIJEK), 1, fp);

			break;
		}
	}

	if (!pronadjen) {
		printf("Lijek '%s' nije pronadjen.\n", trazeniLijek);
	}

	fclose(fp);
}

void brisanjeLijeka(void* polje, const char* ime) {
	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Brisanje lijeka iz datoteke lijekovi.bin");
		exit(EXIT_FAILURE);
	}

	LIJEK* lijekovi = (LIJEK*)polje;
	char trazeniLijek[25];
	printf("Unesite ime lijeka za brisanje: ");
	scanf("%24[^\n]", trazeniLijek);
	getchar();

	int pronadjen = 0;
	for (int i = 0; i < brojLijekova; i++) {
		if (strcmp(lijekovi[i].proizvodac, trazeniLijek) == 0) {
			pronadjen = 1;

			for (int j = i; j < brojLijekova - 1; j++) {
				lijekovi[j] = lijekovi[j + 1];
			}

			brojLijekova--;
			fseek(fp, 0, SEEK_SET);
			fwrite(&brojLijekova, sizeof(int), 1, fp);

			fseek(fp, sizeof(int) + brojLijekova * sizeof(LIJEK), SEEK_SET); // 17.
			fwrite(NULL, sizeof(LIJEK), 1, fp);

			break;
		}
	}

	if (!pronadjen) {
		printf("Lijek '%s' nije pronadjen.\n", trazeniLijek);
	}

	fclose(fp);
}

void sortirajPoCijeni(void* polje) {
	LIJEK* lijekovi = (LIJEK*)polje;

	for (int i = 0; i < brojLijekova - 1; i++) {
		for (int j = 0; j < brojLijekova - i - 1; j++) {
			if (lijekovi[j].cijena > lijekovi[j + 1].cijena) {
				LIJEK temp = lijekovi[j];
				lijekovi[j] = lijekovi[j + 1];
				lijekovi[j + 1] = temp;
			}
		}
	}
}

void ispisPoCijeni(const void* polje) {
	const LIJEK* lijekovi = (const LIJEK*)polje;

	printf("%-12s | %-20s | %-19s | %-8s | %-6s\n", "ID", "Ime lijeka", "Proizvodac", "Kolicina", "Cijena");
	printf("------------+-----------------------+---------------------+----------+-------\n");
	for (int i = 0; i < brojLijekova; i++) {
		printf("%-12d | %-20s | %-19s | %-8d | %.2lf\n", lijekovi[i].id, lijekovi[i].ime, lijekovi[i].proizvodac, lijekovi[i].kolicina, lijekovi[i].cijena);
	}
}

int izlazIzPrograma(void* polje) {
	LIJEK* lijekovi = (LIJEK*)polje;

	FILE* fp = fopen("lijekovi.bin", "rb+");

	if (fp == NULL) {
		perror("Brisanje lijekova iz datoteke lijekovi.bin");
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_SET);
	fwrite(&brojLijekova, sizeof(int), 1, fp);

	fwrite(lijekovi, sizeof(LIJEK), brojLijekova, fp);

	fclose(fp);

	free(lijekovi); // oslobadanje memorije

	return 0;
}

int izbornik(const char* ime) { // 8. 
	int izbor;
	void* polje = NULL;

	kreiranjeDatoteke(ime);

	while (1) {
		printf("\n");
		printf("1. Dodaj lijek\n");
		printf("2. Ispisi sve lijekove\n");
		printf("3. Pretrazi lijekove\n");
		printf("4. Uredi lijek\n");
		printf("5. Izbrisi lijek\n");
		printf("6. Sortiraj lijekove po cijeni\n");
		printf("7. Ispis lijekova sortiranih po cijeni\n");
		printf("8. Izlaz iz programa\n");
		printf("\n");
		printf("Unesite broj opcije: ");
		scanf("%d", &izbor);
		getchar();

		switch (izbor) {
		case 1:
			dodajLijek(ime);
			break;
		case 2:
			polje = ucitajLijekove(ime);
			ispisiSveLijekove(polje);
			free(polje);
			break;
		case 3:
			polje = ucitajLijekove(ime);
			pretraziLijekove(polje);
			free(polje);
			break;
		case 4:
			polje = ucitajLijekove(ime);
			uredivanjeLijekova(polje, ime);
			free(polje);
			break;
		case 5:
			polje = ucitajLijekove(ime);
			brisanjeLijeka(polje, ime);
			free(polje);
			break;
		case 6:
			polje = ucitajLijekove(ime);
			sortirajPoCijeni(polje);
			printf("Lijekovi su sortirani po cijeni.\n");
			polje = ucitajLijekove(ime);
			break;
		case 7:
			polje = ucitajLijekove(ime);
			ispisPoCijeni(polje);
			free(polje);
			break;
		case 8:
			return izlazIzPrograma(polje);
		default:
			printf("Pogresan unos. Molimo unesite ponovno.\n");
			break;
		}
	}
}