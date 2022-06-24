#pragma once
#include "Kriterium.h"
#include "../EnumVekovaSkupina.h"

class KUJVekovaSkupinaPodiel
	:public Kriterium<double>
{
public:
	double urobKriterium(UzemnaJednotka* uzemnaJednotka) override;
	Kriterium<double>* nastavKriterium(EnumVekovaSkupina vekovaSkupina) {
		this->vekovaSkupina_ = vekovaSkupina;
		return this;
	}
private:
	EnumVekovaSkupina vekovaSkupina_;

};

double KUJVekovaSkupinaPodiel::urobKriterium(UzemnaJednotka* uzemnaJednotka) {
	double pocetObyvatelov = static_cast<double>(uzemnaJednotka->getPocetObyvatelov());
	double pocetObyvatelovVekovejSkupiny = static_cast<double>(uzemnaJednotka->getPocetVekovejSkupiny(vekovaSkupina_));
	return 100.0 * (pocetObyvatelovVekovejSkupiny / pocetObyvatelov);
}