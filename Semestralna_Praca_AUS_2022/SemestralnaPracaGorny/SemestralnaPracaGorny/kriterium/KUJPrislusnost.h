#pragma once
#include "Kriterium.h"
class KUJPrislusnost
	:public Kriterium<bool>
{
public:
	inline bool urobKriterium(UzemnaJednotka* uzemnaJednotka) override;

};

inline bool KUJPrislusnost::urobKriterium(UzemnaJednotka* uzemnaJednotka) {
	return uzemnaJednotka->getPatriDoVyssiehoCelku();
}
