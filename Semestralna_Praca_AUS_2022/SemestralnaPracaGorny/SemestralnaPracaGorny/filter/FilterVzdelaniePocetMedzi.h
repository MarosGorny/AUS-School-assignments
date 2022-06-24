#pragma once
#include "FilterVelkeFi.h"
#include "../kriterium/KUJVzdelaniePocet.h"

class FilterVzdelaniePocetMedzi
	: public FilterVelkeFi<int> {
public:
	FilterVzdelaniePocetMedzi(int minHodnota, int maxHodnota, EnumVzdelanie typVzdelania)
		:FilterVelkeFi((new KUJVzdelaniePocet())->nastavKriterium(typVzdelania), minHodnota, maxHodnota) {

	}

	void nastavVzdelanie(EnumVzdelanie typVzdelania) {
		reinterpret_cast<KUJVzdelaniePocet*>(this->dajKriterium())->nastavKriterium(typVzdelania);
	}

	
};
