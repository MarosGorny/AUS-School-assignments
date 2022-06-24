#pragma once
#include "Kriterium.h"
class KUJNadradena
	:public Kriterium<UzemnaJednotka*>
{
public:
	inline UzemnaJednotka* urobKriterium(UzemnaJednotka* uzemnaJednotka) override;
	
};

inline UzemnaJednotka* KUJNadradena::urobKriterium(UzemnaJednotka* uzemnaJednotka) {
	return uzemnaJednotka->getNadJednotku();

}
