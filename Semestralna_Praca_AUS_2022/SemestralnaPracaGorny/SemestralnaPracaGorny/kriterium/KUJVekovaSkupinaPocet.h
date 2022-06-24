#pragma once
#include "Kriterium.h"
#include "../EnumVekovaSkupina.h"
class KUJVekovaSkupinaPocet
	:public Kriterium<int>
{
public:
	inline int urobKriterium(UzemnaJednotka* uzemnaJednotka) override;
	Kriterium<int>* nastavKriterium(EnumVekovaSkupina vekovaSkupina) {
		this->vekovaSkupina_ = vekovaSkupina;
		return this;
	}
private:
	EnumVekovaSkupina vekovaSkupina_;
};




inline int KUJVekovaSkupinaPocet::urobKriterium(UzemnaJednotka* uzemnaJednotka) {
	return uzemnaJednotka->getPocetVekovejSkupiny(vekovaSkupina_);
}
