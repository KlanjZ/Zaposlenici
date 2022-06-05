#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>

typedef struct zaposlenik {
    char korisnickoIme[15];
    char sifra[16];
	char ime[20];
	char prezime[30];
	int ID;
	float placa;
}ZAPOSLENIK;

int izbornik(void);
int getch(void);
char* sifra(void);
void kreirajZaposlenika(void);
int brojZap(void);
void ispisZap(int z);
void login(int k);
int izbornikZaposlenik(int z);
void promjenaSifre(int s, int z);
void obirisiZaposlenika(int z);
int sortiraj(int z);
void sortirajPlacaVeca(int z);
void sortirajPlacaManja(int z);
void zamjena(ZAPOSLENIK *veci, ZAPOSLENIK *manji);
void sortirajIme(int z);
void stvoriBiljesku(char *ime);
void citajBiljesku(char *ime);
void trazenjeID(int k);
int provjeraKorisnika(int k, char *korisnik);
int provjeraID(int k, int ID);
#endif // HEADER_H
