#pragma once
#include "Kriterium.h"
#include "../EnumVzdelanie.h"
class KUJVzdelaniePocet
	:public Kriterium<int>
{
public:
	inline int urobKriterium(UzemnaJednotka* uzemnaJednotka) override;
	Kriterium<int>* nastavKriterium(EnumVzdelanie typVzdelania) {
		this->typVzdelania = typVzdelania;
		return this;
	}
private:
	EnumVzdelanie typVzdelania;
};

inline int KUJVzdelaniePocet::urobKriterium(UzemnaJednotka* uzemnaJednotka) {
	return uzemnaJednotka->getPocetVzdelanie(typVzdelania);
}