#pragma once

#include <iostream>
#include <variant>
#include <string>
#include "Pracownicy.hpp"
#include "Firma.hpp"
#include "Kredyt.hpp"

const double W_INZ = 5000;
const double W_MAG = 3000;
const double W_MKT = 4000;
const double W_ROB = 3000;

class Game
{
public:
	void akcja_gracza() {};
	bool get_stan() {};

	void tick() {};

private:
	bool stan;
	std::unique_ptr<Firma> firma;
};