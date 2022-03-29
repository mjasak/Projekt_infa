#pragma once

#include <string>
#include <iostream>

using namespace std;

// Klasa Karta posiada prywatne pola: PIN, type-typ karty (kredytowa, debetowa) oraz stan czyli ilosc srodkow na koncie, do ktorego przypisana jest karta
// posiada metody:
// wyplac(kwota) - sprawdza, czy z karty mozna wyplacic dana kwote oraz odejmuje z konta wartosc kwoty, jesli mozna
// gettery: pinu, typu oraz stanu konta
// setter - mozna konto "doladowac"
// karta posiada takze id - czyli swoj rodzaj (visa, mastercard etc.) - uzywany jest tylko do metody druk() sluzacej bardziej do debugowania niz do obslugi karty
// klasy Visa, Mastercard, AmericanExpress, VisaElectron dziedzicza po klasie Karta

class Karta
{
public:
	string id = "Nieznana Karta";
	unsigned long long number;

	Karta() {};
	Karta(int p) : pin(p) {};
	Karta(int p, string t) : pin(p), type(t) {};
	Karta(int p, string t, unsigned long long n) : Karta(p, t) { this->number = n; };
	Karta(int p, string t, unsigned long long n, double s) : Karta(p, t,n) { this->stanKarty = s; };


	void druk() { cout << "to jest " << this->id << " o numerze: " << this->number << endl; }

	string getType() { return this->type; };
	void setStan(double s) { this->stanKarty = s; }
	double getStan() { return this->stanKarty; }
	int getPin() { return this->pin; }

	 bool wyplac(int kwota) { 
		if (this->type == "D" && this->stanKarty < kwota) {
			cout << "Nie mozna wyplacic takiej kwoty" << endl;
			return false;
		}
		else { this->stanKarty -= kwota; return true; }
	}

protected:
	int pin;
	string type; // C - credit, D- debit
	double stanKarty = 1000;
};


class Visa : public Karta
{
public:
	Visa() {};
	Visa(int p) : Karta(p) { this->id = "Visa"; };
	Visa(int p, string t) : Karta(p,t) { this->id = "Visa"; };
	Visa(int p, string t, unsigned long long n) : Karta(p, t, n) { this->id = "Visa"; };
	Visa(int p, string t, unsigned long long n, double s) : Karta(p, t, n, s) { this->id = "Visa"; };

};

class Mastercard : public Karta
{
public:
	Mastercard() {};
	Mastercard(int p) : Karta(p) { this->id = "Visa"; };
	Mastercard(int p, string t) : Karta(p, t) { this->id = "Mastercard"; };
	Mastercard(int p, string t, unsigned long long n) : Karta(p, t, n) { this->id = "Mastercard";}
	Mastercard(int p, string t, unsigned long long n,double s) : Karta(p, t, n,s) { this->id = "Mastercard"; }
};

class AmericanExpress : public Karta
{
public:
	AmericanExpress() {};
	AmericanExpress(int p) : Karta(p) { this->id = "AmericanExpress"; };
	AmericanExpress(int p, string t) : Karta(p, t) { this->id = "AmericanExpress"; };
	AmericanExpress(int p, string t, unsigned long long n) : Karta(p, t, n) { this->id = "AmericanExpress"; }
	AmericanExpress(int p, string t, unsigned long long n, double s) : Karta(p, t, n, s) { this->id = "AmericanExpress"; }
};

class VisaElectron : public Karta
{
public:
	VisaElectron() {};
	VisaElectron(int p) : Karta(p) { this->id = "VisaElectron"; };
	VisaElectron(int p, string t) : Karta(p, t) { this->id = "VisaElectron"; };
	VisaElectron(int p, string t, unsigned long long n) : Karta(p, t, n) { this->id = "VisaElectron"; }
	VisaElectron(int p, string t, unsigned long long n, double s) : Karta(p, t, n,s) { this->id = "VisaElectron"; }
};
