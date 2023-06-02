#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include "Strukture.h"

int main(void) {

	int odgovor = 1;


	char* datotekaLijekovi = "lijekovi.bin";

	kreiranjeDatoteke(datotekaLijekovi);

	while (odgovor) {
		odgovor = izbornik(datotekaLijekovi);
	}

	printf("\nKraj programa");

	return 0;
}