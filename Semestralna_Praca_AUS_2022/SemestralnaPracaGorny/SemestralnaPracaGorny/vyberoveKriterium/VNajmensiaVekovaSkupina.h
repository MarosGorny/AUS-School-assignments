#pragma once
#include "VyberoveKriteriumMin.h"
#include "kriterium/KUJVekovaSkupinaPocet.h"
#include "kriterium/Kriterium.h"


class VNajmensiaVekovaSkupina : public VyberoveKriteriumMin<int> {
public:
	VNajmensiaVekovaSkupina(EnumVekovaSkupina vekovaSkupina_) :
		VyberoveKriteriumMin<int>((new KUJVekovaSkupinaPocet())->nastavKriterium(vekovaSkupina_)) {
	}

	void nastavVekSkupinu(EnumVekovaSkupina vekovaSkupina) {
		reinterpret_cast<KUJVekovaSkupinaPocet*>(this->kriterium_)->nastavKriterium(vekovaSkupina);
	}
	

};