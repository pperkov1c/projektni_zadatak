#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void kreiranjeDatoteke(const char* ime);
void dodajLijek(const char* ime);
void* ucitajLijekove(const char* ime);
void ispisiSveLijekove(const void* polje);
void* pretraziLijekove(const void* polje);
void uredivanjeLijekova(void* polje, const char* ime);
void brisanjeLijeka(void* polje, const char* ime);
void sortirajPoCijeni(void* polje);
void ispisPoCijeni(const void* polje);
int izlazIzPrograma(void* polje);
int izbornik(const char* ime);
#endif