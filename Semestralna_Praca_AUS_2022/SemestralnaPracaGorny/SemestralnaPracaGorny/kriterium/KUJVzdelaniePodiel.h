#pragma once
#include "Kriterium.h"
//#include "KUJVzdelaniePocet.h"
#include "../EnumVzdelanie.h"
class KUJVzdelaniePodiel
	:public Kriterium<double>
{
public:
	double urobKriterium(UzemnaJednotka* uzemnaJednotka) override;
	Kriterium<double>* nastavKriterium(EnumVzdelanie typVzdelania) {
		this->typVzdelania = typVzdelania;
		return this;
	}
private:
	EnumVzdelanie typVzdelania;

};

double KUJVzdelaniePodiel::urobKriterium(UzemnaJednotka* uzemnaJednotka)  {
	double pocetObyvatelov =	static_cast<double>(uzemnaJednotka->getPocetObyvatelov());
	double pocetObyvatelovVzdelanie = static_cast<double>(uzemnaJednotka->getPocetVzdelanie(typVzdelania));
	return 100.0 * (pocetObyvatelovVzdelanie / pocetObyvatelov);
}