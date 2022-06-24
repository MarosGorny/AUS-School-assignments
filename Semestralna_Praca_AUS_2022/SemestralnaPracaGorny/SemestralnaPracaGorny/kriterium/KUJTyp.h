#pragma once
#include "Kriterium.h"
#include "../EnumVzdelanie.h"

class KUJTyp
	:public Kriterium<EnumTypUzemnejJednotky>
{
public:
	inline EnumTypUzemnejJednotky urobKriterium(UzemnaJednotka* uzemnaJednotka) override;
};

inline EnumTypUzemnejJednotky KUJTyp::urobKriterium(UzemnaJednotka* uzemnaJednotka) {
	return uzemnaJednotka->getTyp();
}
