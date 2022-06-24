
#pragma once
#include "FilterVelkeFi.h"
#include "../kriterium/KUJVekovaSkupinaPodiel.h"

class FilterVekovaSkupinaPodielMedzi
	: public FilterVelkeFi<double> {
public:
	FilterVekovaSkupinaPodielMedzi(double minHodnota, double maxHodnota, EnumVekovaSkupina typVekovejSkupiny)
		:FilterVelkeFi((new KUJVekovaSkupinaPodiel())->nastavKriterium(typVekovejSkupiny), minHodnota, maxHodnota) {
	}

	void nastavVekovuSkupinu(EnumVekovaSkupina typVekovejSkupiny) {
		reinterpret_cast<KUJVekovaSkupinaPodiel*>(this->dajKriterium())->nastavKriterium(typVekovejSkupiny);
	}
};
