#pragma once

#include <iostream>
#include <variant>
#include <string>
#include "Pracownicy.hpp"
#include "Firma.hpp"
#include "Game.hpp"


class Kredyt
{
public:
	Kredyt() {};
	Kredyt(double d, int r) { this->rata = d;  this->dlug = d*(double)r; this->pozostale_raty = r; };
	~Kredyt() { cout << "Splacono Kredyt" << endl; };

	double splac_rate() 
	{
		this->dlug -= this->rata;
		this->pozostale_raty--; 
	};

private:
	double dlug;
	double rata;
	int pozostale_raty;

};