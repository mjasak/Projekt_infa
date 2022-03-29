
#include<iostream>
#include "Bankomat.hpp"
#include<variant>


int main()
{
	Bankomat b; // tworzy bankomat
	// b.listuj_karty(); //listuje dostepne karty
	b.dodaj_karte(new card(Visa(1234, "C", 9999999999999999,12000))); //dodaje nowa karte kredytowa o pinie 1234, numerze 16x9 i dostepnej kwocie 12 000
	//b.instaluj(); // instalacja bankomatu
	b.klient(); // operacja wyplaty
}
