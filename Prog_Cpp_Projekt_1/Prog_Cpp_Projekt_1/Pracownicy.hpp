#pragma once
#include <string>
#include <iostream>
#include <variant>
#include "Game.hpp"

using namespace std;

class Pracownik
{
public:
	Pracownik() {};
	Pracownik(string s) { this->Imie = s; };
	Pracownik(string s, double w) { this->Imie = s; this->Wynagrodzenie = w; }

	string getImie() { return this->Imie; }
	double getWynagrodzenie() {return this->Wynagrodzenie;}
	virtual void drukuj() {};
protected:
	string Imie;
	double Wynagrodzenie = 0;

};

class Inzynier : public Pracownik
{
public:
	Inzynier() {}
	Inzynier(string s) : Pracownik(s) {};
	Inzynier(string s, double w) : Pracownik(s, w) {};
	Inzynier(string s, string f) : Pracownik(s) { this->setWydzial(f); this->Wynagrodzenie = W_INZ; }

	~Inzynier() {};

	void drukuj() { cout << "Inzynier " << this->getImie() << ". Skonczyl " << this->getWydzial() << ". Zarabia " << this->getWynagrodzenie() << endl; };

	void setWydzial(string a) { this->wydzial = a; }
	string getWydzial() { return this->wydzial; }

protected:
	string wydzial;
};

class Magazynier : public Pracownik
{
public:
	Magazynier() {}
	Magazynier(string s) : Pracownik(s) {};
	Magazynier(string s, double w) : Pracownik(s, w) {};
	Magazynier(string s, bool f) : Pracownik(s) { this->setWozek(f); this->Wynagrodzenie = W_MAG; }

	~Magazynier() {};

	void drukuj()
	{
		if (this->wozek) {cout << "Magazynier " << this->getImie() << ", umie prowadzic wozek. Zarabia " << this->getWynagrodzenie() << endl;}
		else {cout << "Magazynier " << this->getImie() << ", nie umie prowadzic wozka. Zarabia " << this->getWynagrodzenie() << endl;}
	}

	void setWozek(bool a) { this->wozek = a; }
	bool getWozek() { return this->wozek; }

protected:
	bool wozek;
};

class Marketer : public	Pracownik
{
public:
	Marketer() {}
	Marketer(string s) : Pracownik(s) {};
	Marketer(string s, double w) : Pracownik(s, w) {};
	Marketer(string s, int n) : Pracownik(s) { this->setFollowers(n); this->Wynagrodzenie = W_MKT; }

	~Marketer() {};

	void drukuj() { cout << "Marketer " << this->getImie() << ", posiada " << this->getFollowers() << " followersow, zarabia "<< this->getWynagrodzenie() << endl; };

	void setFollowers(int n) { this->followers = n; }
	int getFollowers() { return this->followers; };

protected:
	int followers;
};

class Robotnik : public Pracownik
{
public:
	Robotnik() {}
	Robotnik(string s) : Pracownik(s) {};
	Robotnik(string s, double w) : Pracownik(s, w) {};
	Robotnik(string s, double size) : Pracownik(s) { setRozmiarButa(size); this->Wynagrodzenie = W_ROB; }

	~Robotnik() { cout << "Destruktor robotnika" << endl; };

	void drukuj() { cout << "Robotnik " << this->getImie() << " o rozmiarze buta " << this->getRozmiarButa() << ". Zarabia " << this->getWynagrodzenie() << endl; };

	void setRozmiarButa(double s) { this->but = s; }
	double getRozmiarButa() { return this->but; }

protected:
	double but;

};

class Pracownicy
{
public:
	Pracownik* pracownicy[200];
	Pracownicy() {};
	
	void push(Pracownik* p) {
		pracownicy[licznik] = p;
		licznik++;
	};

	void pop(int n) {
		delete pracownicy[n];
		licznik--;
	};

	Pracownik* operator[](int n)
	{
		if (n >= licznik) { return nullptr; }

		return pracownicy[n];
	}

	int getLicznik()
	{
		return licznik;
	}

private:
	int licznik = 0;
};

struct DzialHR
{
	void operator()(Inzynier k) { k.drukuj(); }
	void operator()(Marketer k) { k.drukuj(); }
	void operator()(Magazynier k) { k.drukuj(); }
	void operator()(Robotnik k) { k.drukuj(); }
};