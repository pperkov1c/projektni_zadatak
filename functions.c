#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Header.h"

static int brojLijekova = 0;

void kreiranjeDatoteke(const char* const dat) {

	FILE* fp = fopen(dat, "rb");

	// ako ne postoji stvaramo novu datoteku sa wb, ako postoji samo zatvaramo
	if (fp == NULL) {

		fp = fopen(dat, "wb");

		if (strcmp(dat, "lijekovi.bin") == 0) {
			fwrite(&brojLijekova, sizeof(int), 1, fp);
		}

		fclose(fp);
	}
	else {
		fclose(fp);
	}
}

void dodajLijek(const char* const dat) {

	system("CLS");

	//otvaramo datoteku, dajemo joj rb+ permisiju
	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Dodavanje lijeka");
		exit(EXIT_FAILURE);
	}

	fread(&brojLijekova, sizeof(int), 1, fp);

	printf("Broj lijekova: %d\n\n", brojLijekova);

	//upis lijeka u datoteku

	LIJEK temp = { 0 };

	temp.id = brojLijekova + 1;
	getchar();

	printf("Unesite ime lijeka: ");
	scanf("%29[^\n]", temp.naziv);
	getchar();

	printf("Unesite proizvodaca: ");
	scanf("%29[^\n]", temp.proizvodac);
	getchar();

	printf("Unesite kolicinu lijeka: ");
	scanf("%d", &temp.kolicina);
	getchar();

	printf("Unesite cijenu lijeka: ");
	scanf("%f", &temp.cijena);

	//postavljanje pokazivaca

	fseek(fp, sizeof(LIJEK) * brojLijekova, SEEK_CUR);
	fwrite(&temp, sizeof(LIJEK), 1, fp);

	printf("Novi lijek dodan\n");

	rewind(fp);
	brojLijekova++;

	fwrite(&brojLijekova, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajLijekove(const char* const dat) {

	//otvaranje datoteke

	FILE* fp = fopen(dat, "rb");

	if (fp == NULL) {
		perror("Ucitavanje");
		return NULL;
		exit(EXIT_FAILURE);
	}

	//ocitavanje broja lijekova

	fread(&brojLijekova, sizeof(int), 1, fp);

	LIJEK* poljeLijekova = (LIJEK*)calloc(brojLijekova, sizeof(LIJEK));

	if (poljeLijekova == NULL) {
		printf("Zauzimanje memorije");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeLijekova, sizeof(LIJEK), brojLijekova, fp);

	//vracanje poljaLijekova

	return poljeLijekova;
}

void stanjeLijekova(const LIJEK* const poljeLijekova) {
	system("CLS");

	//provjeravanje poljaLijekova

	if (brojLijekova == NULL) {
		printf("Polje lijekova je prazno");
		return;
	}

	//ispis lijekova iz niza brojLijekova

	for (int i = 0; i < brojLijekova; i++) {
		printf("ID: %d  Naziv: %s  Proizvodac: %s  Kolicina na stanju: %d  Cijena: %.2fkn\n\n",
			(poljeLijekova + i)->id,
			(poljeLijekova + i)->naziv,
			(poljeLijekova + i)->proizvodac,
			(poljeLijekova + i)->kolicina,
			(poljeLijekova + i)->cijena);
	}
}

void* pretrazivanjeLijekova(LIJEK* const poljeLijekova) {

	system("CLS");
	//provjera polja

	if (poljeLijekova == NULL) {
		printf("Polje lijekova prazno\n");
		return NULL;
	}

	int trazeniLijek = 0;
	int temp = 0;

	printf("Unesite ID lijeka: ");
	scanf("%d", &trazeniLijek);

	//petlja kojom idemo kroz polje, usporedjujemo trazeni id, s id-evima u polju

	for (int i = 0; i < brojLijekova; i++) {

		if (trazeniLijek == (poljeLijekova + i)->id) {

			printf("ID: %d  Naziv: %s  Proizvodac: %s  Kolicina na stanju: %d.  Cijena: %f\n\n",
				(poljeLijekova + i)->id,
				(poljeLijekova + i)->naziv,
				(poljeLijekova + i)->proizvodac,
				(poljeLijekova + i)->kolicina,
				(poljeLijekova + i)->cijena);

			temp++;
		}

	}

	for (int i = 0; i < brojLijekova; i++) {

		if (trazeniLijek == (poljeLijekova + i)->id) {
			printf("Clan pronaden\n");

			return (poljeLijekova + i);
		}
	}

	if (temp == 0) {
		printf("Nema lijeka pod tim imenom\n");
		return;
	}

	return NULL;
}

void pretrazivnajeLijekaIme(LIJEK* const poljeLijekova) {

	system("CLS");

	//provjera polja lijekova
	if (brojLijekova == 0) {
		printf("Polje lijekova prazno\n");
		return;
	}

	char trazeniLijek[25];
	int temp = 0;

	printf("Unesite ime lijeka: ");
	getchar();
	scanf("%29[^\n]", trazeniLijek);


	//petlja kojom prolazimo kroz polje i usporedujemo trazeno ime

	for (int i = 0; i < brojLijekova; i++) {

		if (strcmp(trazeniLijek, (poljeLijekova + i)->naziv) == 0) {

			printf("ID: %d  Naziv: %s  Proizvodac: %s  Kolicina na stanju: %d.  Cijena: %f\n\n",
				(poljeLijekova + i)->id,
				(poljeLijekova + i)->naziv,
				(poljeLijekova + i)->proizvodac,
				(poljeLijekova + i)->kolicina,
				(poljeLijekova + i)->cijena);

			temp++;
		}

	}

	if (temp == 0) {
		printf("Nema lijeka pod tim imenom\n");
		return;
	}
}

void zamjena(LIJEK* const high, LIJEK* const low) {
	LIJEK temp = { 0 };

	temp = *low;
	*low = *high;
	*high = temp;

}

void sortiranjeLijekova(const LIJEK* poljeLijekova) {

	system("CLS");

	int min = -1;

	for (int i = 0; i < brojLijekova - 1; i++)
	{
		min = i;

		for (int j = i + 1; j < brojLijekova; j++)
		{
			if ((poljeLijekova + j)->cijena < (poljeLijekova + min)->cijena) {
				min = j;
			}
		}
		zamjena((poljeLijekova + i), (poljeLijekova + min));
	}

	stanjeLijekova(poljeLijekova);
}

void azuriranjeLijeka(LIJEK* poljeLijekova, const char* const dat) {

	system("CLS");

	//provjera poljaLijekova

	if (poljeLijekova == NULL) {
		printf("Polje prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	//provjera datoteke

	if (fp == NULL) {
		printf("Azuriranje korisnika");
		return 1;
	}

	int trazeniId;

	printf("Unesite ID lijeka kojeg zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojLijekova) {
			printf("Lijek s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojLijekova);


	//Azuriranje datoteke

	LIJEK temp = { 0 };

	temp.id = trazeniId;

	getchar();

	printf("Unesite novi naziv lijeka (trenutno: %s): ", (poljeLijekova + trazeniId - 1)->naziv);
	scanf("%24[^\n]", temp.naziv);
	getchar();

	printf("Unesite novog proizvodaca lijeka (trenutno %s): ", (poljeLijekova + trazeniId - 1)->proizvodac);
	scanf("%24[^\n]", temp.proizvodac);
	getchar();

	printf("Unesite novu kolicinu lijeka (trenutno %d): ", (poljeLijekova + trazeniId - 1)->kolicina);
	scanf("%d", &temp.kolicina);


	printf("Unesite novu cijenu lijeka (trenutno %f): ", (poljeLijekova + trazeniId - 1)->cijena);
	scanf("%f", &temp.cijena);


	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(LIJEK) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(LIJEK), 1, fp);

	printf("Lijek uspjesno azuriran\n");

	fclose(fp);

}

void brisanjeLijeka(LIJEK* const poljeLijekova, const char* const dat) {

	system("CLS");

	//provjera polja

	if (poljeLijekova == NULL) {
		printf("Polje je prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	//provjera datoteke

	if (fp == NULL) {
		printf("Brisanje lijeka");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int trazeniId;

	printf("Unesite ID lijeka kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojLijekova) {
			printf("Lijek s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojLijekova);

	int counter = 0;

	//petlja kojom prolazimo kroz polje te brisemo zeljeni lijek

	for (int i = 0; i < brojLijekova; i++) {

		if (trazeniId != (poljeLijekova + i)->id) {

			fwrite((poljeLijekova + i), sizeof(LIJEK), 1, fp);
			counter++;
		}
	}

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);

	fclose(fp);

	printf("Lijek je uspjesno obrisan\n");

}
void brisanjeBaze(LIJEK* polje) {
	printf("Zelite li pri izlasku programa izbrisati datoteku ili ju ipak zelite zadrzati?\n");
	printf("Ako zelite izbrisati datoteku napisite obrisi, ako ne zelite napisite zadrzi\n");

	char uvjet[7] = { '\0' };
	scanf("%6s", uvjet);
	if (!strcmp("obrisi", uvjet)) {
		remove("lijekovi.bin") == 0 ? printf("Izbrisali ste datoteku lijekovi.bin.\n") : printf("Datoteka neuspjesno izbrisana ili ona ne postoji.\n");
		printf("\nIzlaz iz programa.\n");
		free(polje);
	}
	else printf("\nZadrzali ste datoteku.\nIzlaz iz programa\n");
}


