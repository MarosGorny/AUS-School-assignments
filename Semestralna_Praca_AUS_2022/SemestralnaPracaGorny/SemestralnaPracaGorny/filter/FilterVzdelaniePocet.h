#pragma once
#include "FilterMaleFi.h"
#include "../kriterium/KUJVzdelaniePocet.h"

class FilterVzdelaniePocet 
	: public FilterMaleFi<int> {
public:
	FilterVzdelaniePocet(int pocet,EnumVzdelanie typVzdelania) :
		FilterMaleFi((new KUJVzdelaniePocet())->nastavKriterium(typVzdelania), pocet) {
			
	}

	//void nastavHodnotuFiltru(EnumVzdelanie vzdelanie) { this->};
};
