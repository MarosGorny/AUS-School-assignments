#pragma once
#include "../kriterium/Kriterium.h"
#include <string>

class KNazov
	:public Kriterium<std::string>
{
public:
	inline std::string urobKriterium(UzemnaJednotka* uzemnaJednotka) override;
private:
	EnumVzdelanie typVzdelania;
};

inline std::string KNazov::urobKriterium(UzemnaJednotka* uzemnaJednotka) {
	return uzemnaJednotka->getNazov();
}