#pragma once
#include "FilterVelkeFi.h"
#include "../kriterium/KUJVekPocet.h"

class FilterVekPocetMedzi
	: public FilterVelkeFi<int> {
public:
	FilterVekPocetMedzi(int minHodnota, int maxHodnota,int minimalnyVek,int maximalnyVek, EnumPohlavie pohlavie)
		:FilterVelkeFi((new KUJVekPocet())->nastavKriterium(minimalnyVek,maximalnyVek,pohlavie), minHodnota, maxHodnota) {
	}

	void nastavVekPohlavie(int minimalnyVek, int maximalnyVek, EnumPohlavie pohlavie) {
		reinterpret_cast<KUJVekPocet*>(this->dajKriterium())->nastavKriterium(minimalnyVek,maximalnyVek, pohlavie);
	}
};
