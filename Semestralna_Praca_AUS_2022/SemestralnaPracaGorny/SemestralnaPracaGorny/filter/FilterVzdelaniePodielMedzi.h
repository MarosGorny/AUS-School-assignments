#pragma once
#include "FilterVelkeFi.h"
#include "../kriterium/KUJVzdelaniePodiel.h"

class FilterVzdelaniePodielMedzi
	: public FilterVelkeFi<double> {
public:
	FilterVzdelaniePodielMedzi(double minHodnota, double maxHodnota, EnumVzdelanie typVzdelania)
		:FilterVelkeFi((new KUJVzdelaniePodiel())->nastavKriterium(typVzdelania), minHodnota, maxHodnota) {
	}

	void nastavVzdelanie(EnumVzdelanie typVzdelania) {
		reinterpret_cast<KUJVzdelaniePodiel*>(this->dajKriterium())->nastavKriterium(typVzdelania);
	}
};
