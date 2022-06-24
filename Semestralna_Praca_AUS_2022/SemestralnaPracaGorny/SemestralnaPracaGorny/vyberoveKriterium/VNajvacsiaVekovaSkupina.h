#pragma once
#include "VyberoveKriteriumMax.h"
#include "kriterium/KUJVekovaSkupinaPocet.h"


class VNajvacsiaVekovaSkupina : public VyberoveKriteriumMax<int> {
public:
	VNajvacsiaVekovaSkupina(EnumVekovaSkupina vekovaSkupina_) :
		VyberoveKriteriumMax<int>((new KUJVekovaSkupinaPocet())->nastavKriterium(vekovaSkupina_)) {
	}
	void nastavVekSkupinu(EnumVekovaSkupina vekovaSkupina) {
		reinterpret_cast<KUJVekovaSkupinaPocet*>(this->kriterium_)->nastavKriterium(vekovaSkupina);
	}

};