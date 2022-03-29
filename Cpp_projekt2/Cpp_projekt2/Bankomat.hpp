#pragma once
#include <memory>
#include <iostream>
#include <algorithm>
#include <variant>
#include "Karty.hpp"

//klasa bankomat posiada pola prywatne :
//balance - ilosc pieniedzy w bankomacie
//karty - tablica kart zapisanych w systemie(imitacja bazy danych banku z informacjami o kartach) alokowana statycznie o maksymalnym rozmiarze 1000 (na potrzeby tego programu mysle, ze wystarczy)
//n_cards - ilosc kart zapisanych w systemie
//zmienne logiczne :
//visa, mastercard, americanexpress, visaelectron - informujace o tym czy dana karta jest obslugiwana przez bankomat
//prywatne metody :
//initialize - wstepne dodanie kilku kart do 'systemu'
//weryfikuj_rodzaj - funkcja zwracajaca informacje, czy rodzaj 'wlozonej' karty jest zgodny z wymaganiami bankomatu
//weryfikuj_pin - zwraca false jesli pin jest bledny, true jesli poprawny
//wyplac - odejmuja wyplacana kwote z puli bankomatu(jesli jest to mozliwe)
//wyplac_z_karty - informuje, czy zadana kwota jest mozliwa do wyplacenia z karty
//publiczne metody :
//getBalance - getter ilosci pieniedzy w bankomacie
//doladuj - sluzy do uzupelniania pieniedzy w bankomacie
//dodaj_karte - dodaje karte do systemu' bankowego
//listuj_karty - wypisuje karty w 'systemie' - bardziej do debugowania
//instaluj - pozwala na wybor dostepnych w bankomacie kart oraz ustalic ilosc srodkow w bankomacie
//klient - funkcja sluzaca do obslugi klienta, tzn wyplaceniu pieniedzy po wpisaniu numeru karty
//znajdz - szuka karty o podanym numerze w systemie i zwraca jej indeks
//wypisz_stan - wypisuje ilosc srodkow na karcie o zadanaym indeksie


using namespace std;
using card = variant<Visa, Mastercard, AmericanExpress, VisaElectron>;
const int MAX_CARDS = 1000;
const int INITIAL_BALANCE = 200000;

class Bankomat
{
public:
	Bankomat()
	{
		karty = unique_ptr<card[]>(new card[MAX_CARDS]);
		initialize_cards();
	}

	int getBalance() { return balance; }
	void doladuj(int kwota) { balance += kwota; }

	void dodaj_karte(card* c)
	{
		if (n_cards < MAX_CARDS)
		{
			karty[n_cards] = *c;
			n_cards++;
		}
	}

	void listuj_karty()
	{
		for (int i=0; i < n_cards; i++)
		{
			unsigned int index = karty[i].index();
			if (index == 0) { get<0>(karty[i]).druk(); }
			else if (index == 1) { get<1>(karty[i]).druk(); }
			else if (index == 2) { get<2>(karty[i]).druk(); }
			else if (index == 3) { get<3>(karty[i]).druk(); }
			else { cout << "Niezidentyfikowana karta"; }
		}
	}

	void instaluj()
	{
		bool k;
		cout << "Ktore karty ma obslugiwac bankomat? Wpisz 1/0" << endl;
		cout << "Visa?" << endl;
		cin >> k;
		visa = k;
		cout << "Mastercard?" << endl;
		cin >> k;
		mastercard = k;
		cout << "AmericanExpress?" << endl;
		cin >> k;
		americanexpress = k;
		cout << "VisaElectron?" << endl;
		cin >> k;
		visaelectron = k;

		int kwota;
		cout << "Podaj kwote poczatkowa bankomatu" << endl;
		cin >> kwota;
		this->balance = kwota;
	}

	void klient()
	{
		unsigned long long num;
		cout << "Podaj 16-cyfrowy numer karty" << endl;
		cin >> num;
		int index = znajdz(num);
		if (index < 0)
		{
			cout << "Nie znaleziono karty w systemie" << endl;
		}
		else 
		{
			bool a;
			a = weryfikuj_rodzaj(index);
			if (a)
			{
				int pin;
				cout << "Podaj PIN" << endl;
				cin >> pin;
				bool b = weryfikuj_pin(index, pin);
				int licznik = 0;
				
				if (!b)
				{
					for (int licznik = 0; licznik < 2; licznik++)
					{
						cout << "PIN nieprawidlowy, wpisz ponownie. Pozostalo prob: " << 2-licznik << endl;
						cin >> pin;
						if (weryfikuj_pin(index, pin)) { b = true; break; }
						if(licznik==1) cout << "PIN trzykrotnie bledny, operacja odrzucona" << endl;
					}
				}

				if (b)
				{
					//wyplacanie hajsiwa
					cout << "PIN poprawny" << endl;
					wypisz_stan(index);
					cout << "Podaj kwote. Mozna wyplacac jedynie wielokrotnosci liczby 10." << endl;
					bool koniec = false;
					while (!koniec) 
					{
						int kwota;
						cin >> kwota;

						bool w_karta = wyplac_z_karty(index, kwota);

						if (w_karta)
						{
							this->wyplac(kwota);
							cout << "Pomyslnie wyplacono. Prosze wyjac karte" << endl;
							wypisz_stan(index);
							koniec = true;
						}
						else { cout << "Nie mozna wyplacic takiej kwoty. Podaj inna kwote" << endl; }

					}
				}

			}
			else
			{
				cout << "Nie obslugujemy takiej karty" << endl;
			}
		}
		
	}

	int znajdz(unsigned long long num)
	{
		for (int i = 0; i < n_cards; i++)
		{
			unsigned int index = karty[i].index();
			if (index == 0) { if (num == get<0>(karty[i]).number) return i; }
			else if (index == 1) { if (num == get<1>(karty[i]).number) return i; }
			else if (index == 2) { if (num == get<2>(karty[i]).number) return i; }
			else if (index == 3) { if (num == get<3>(karty[i]).number) return i; }
			else { cout << "Niezidentyfikowana karta"; return -1; }
		}
		return -1;
	}
	void wypisz_stan(int ind)
	{
		unsigned int index = karty[ind].index();
		if (index == 0)
		{
			//obsluga karty visa
			cout << "Stan konta: " << get<0>(karty[ind]).getStan() << endl;;
		}
		else if (index == 1)
		{
			//obsluga karty visa
			cout << "Stan konta: " << get<1>(karty[ind]).getStan() << endl;;
		}
		else if (index == 2)
		{
			//obsluga karty visa
			cout << "Stan konta: " << get<2>(karty[ind]).getStan() << endl;;
		}
		else if (index == 3)
		{
			//obsluga karty visa
			cout << "Stan konta: " << get<3>(karty[ind]).getStan() << endl;;
		}
	}

private:
	unsigned int balance = INITIAL_BALANCE;
	unique_ptr<card[]> karty;
	int n_cards;
	bool visa = true;
	bool mastercard = true;
	bool americanexpress = true;
	bool visaelectron = true;

	void initialize_cards()
	{
		dodaj_karte(new card(Visa(1234, "C", 1234123412341234)));
		dodaj_karte(new card(VisaElectron(1235, "C", 1234123412341235)));
		dodaj_karte(new card(Mastercard(1236, "D", 1234123412341236)));
		dodaj_karte(new card(Visa(1237, "C", 1234123412341237)));
		dodaj_karte(new card(AmericanExpress(1238, "D", 1234123412341238)));
	}

	bool weryfikuj_rodzaj(int i)
	{
		cout << i << endl;
		if (i >= 0){
			unsigned int index = karty[i].index();
			// weryfikacja rodzajow karty
			if (index == 0 && visa)
			{
				//obsluga karty visa
				return true;
			}
			else if (index == 1 && mastercard)
			{
				//obsluga mastercard
				return true;
			}
			else if (index == 2 && americanexpress)
			{
				//obsluga AE
				return true;
			}
			else if (index == 3 && visaelectron)
			{
				//obsluga visaelectron
				return true;
			}
			else
			{
				// cout << "Bankomat nie obsluguje takiej karty" << endl;
				return false;
			}
		}
		else return false;

		// weryfikacja pinu

	}

	bool weryfikuj_pin(int ind, int pin)
	{
		unsigned int index = karty[ind].index();
		// weryfikacja rodzajow karty
		if (index == 0)
		{
			//obsluga karty visa
			if (pin == get<0>(karty[ind]).getPin()) return true;
			else return false;
		}
		else if (index == 1)
		{
			//obsluga mastercard
			if (pin == get<1>(karty[ind]).getPin()) return true;
			else return false;
		}
		else if (index == 2)
		{
			//obsluga AE
			if (pin == get<2>(karty[ind]).getPin()) return true;
			else return false;
		}
		else if (index == 3)
		{
			//obsluga visaelectron
			if (pin == get<3>(karty[ind]).getPin()) return true;
			else return false;
		}
		else return false;
	}

	void wyplac(int kwota)
	{
		if (balance > kwota) {
			this->balance -= kwota;
		}
		else
		{
			cout << "Nie mozna wyplacic takiej kwoty" << endl;
		}
	}

	bool wyplac_z_karty(int ind, int kwota)
	{
		unsigned int index = karty[ind].index();
		if (index == 0)
		{
			//obsluga karty visa
			return get<0>(karty[ind]).wyplac(kwota);
		}
		else if (index == 1)
		{
			//obsluga karty visa
			return get<1>(karty[ind]).wyplac(kwota);
		}
		else if (index == 2)
		{
			//obsluga karty visa
			return get<2>(karty[ind]).wyplac(kwota);
		}
		else if (index == 3)
		{
			//obsluga karty visa
			return get<3>(karty[ind]).wyplac(kwota);
		}
	}

};