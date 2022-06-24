#pragma once
#include "FilterVelkeFi.h"
#include "../kriterium/KUJVekovaSkupinaPocet.h"

class FilterVekovaSkupinaPocetMedzi
	: public FilterVelkeFi<int> {
public:
	FilterVekovaSkupinaPocetMedzi(int minHodnota, int maxHodnota, EnumVekovaSkupina typVekovejSkupiny)
		:FilterVelkeFi((new KUJVekovaSkupinaPocet())->nastavKriterium(typVekovejSkupiny), minHodnota, maxHodnota) {
	}

	void nastavVekovuSkupinu(EnumVekovaSkupina typVekovejSkupiny) {
		reinterpret_cast<KUJVekovaSkupinaPocet*>(this->dajKriterium())->nastavKriterium(typVekovejSkupiny);
	}
};
