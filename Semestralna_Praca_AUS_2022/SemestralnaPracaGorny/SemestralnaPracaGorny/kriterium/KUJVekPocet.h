#pragma once
#include "Kriterium.h"
#include "../pohlavie/EnumPohlavie.h"



class KUJVekPocet
	:public Kriterium<int>
{
public:
	inline int urobKriterium(UzemnaJednotka* uzemnaJednotka) override;
	Kriterium<int>* nastavKriterium(int minVek,int maxVek, EnumPohlavie typPohlavia) {
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



inline int KUJVekPocet::urobKriterium(UzemnaJednotka* uzemnaJednotka) {
	return uzemnaJednotka->getVek(this->minVek_, this->maxVek_ , this->typPohlavia_);
}
