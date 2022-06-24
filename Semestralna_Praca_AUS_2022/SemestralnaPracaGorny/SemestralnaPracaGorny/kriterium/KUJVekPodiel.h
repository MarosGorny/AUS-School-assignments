#pragma once
#include "Kriterium.h"

class KUJVekPodiel
	:public Kriterium<double>
{
public:
	double urobKriterium(UzemnaJednotka* uzemnaJednotka) override;
	Kriterium<double>* nastavKriterium(int minVek, int maxVek, EnumPohlavie typPohlavia) {
		this->minVek_ = minVek;
		this->maxVek_ = maxVek_;
		this->typPohlavia_ = typPohlavia;
		return this;
	}
private:
	int minVek_;
	int maxVek_;
	EnumPohlavie typPohlavia_;
};

inline double KUJVekPodiel::urobKriterium(UzemnaJednotka* uzemnaJednotka) {
	double pocetObyvatelov = static_cast<double>(uzemnaJednotka->getPocetObyvatelov());
	double pocetVek = static_cast<double>(uzemnaJednotka->getVek(this->minVek_, this->maxVek_, this->typPohlavia_));
	return 100.0 * (pocetVek / pocetObyvatelov);
}