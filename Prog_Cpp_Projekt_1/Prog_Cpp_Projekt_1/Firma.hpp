#pragma once

#include <iostream>
#include <variant>
#include <string>
#include "Pracownicy.hpp"
#include "Game.hpp"
#include "Kredyt.hpp"

const int N = 100; // N - ilosc ostatnich miesiecy liczona do rozgrywki
const int M = 10; // mnoznik zdolnosci kredytowej firmy


using pracownik_t = std::variant<Inzynier, Magazynier, Marketer, Robotnik>;


class Firma
{
public:
	Firma() {};

	void drukuj_pracownikow() {/* DRUKOWANIE PRACOWNIKOW*/};
	void wez_kredyt(double kwota, int czas_splaty) 
	{
		if (kwota > M*wartosc_firmy()) { cout << "Nie mozna wziac takiego kredytu";  }
		else { /* NOWE KREDYTY*/  }
	};
	void zatrudnij(const pracownik_t& p) 
	{
		// NOWI PRACOWNICY
	};
	void zaplac_wynagrodzenie() { this->stan_konta -= oblicz_wartosc_wynagrodzen(); };
	void otrzymaj_przychod() 
	{
		this->stan_konta += this->oblicz_przychod();
	};
	void splac_raty() { /* SPLACANIE RAT*/};
	double get_stan_konta() { return this->stan_konta; };
	double wartosc_firmy() {/* WARTOSC FIRMY */};
	double oblicz_przychod() { /* PRZYCHOD */};
	double oblicz_wartosc_wynagrodzen() { /* WARTOSC WYNAGRODZEN*/};


private:
	double stan_konta;
	int n_kredytow;
	unique_ptr<Kredyt[]> kredyty;

	int n_prac=0;
	unique_ptr<pracownik_t[]> pracownicy;

	double historia_przych[N];

};

