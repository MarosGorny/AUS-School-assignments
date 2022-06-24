#pragma once
#include "FilterVelkeFi.h"
#include "../kriterium/KUJVekPodiel.h"

class FilterVekPodielMedzi
	: public FilterVelkeFi<double> {
public:
	FilterVekPodielMedzi(int minHodnota, int maxHodnota, int minimalnyVek, int maximalnyVek, EnumPohlavie pohlavie)
		:FilterVelkeFi((new KUJVekPodiel())->nastavKriterium(minimalnyVek,maximalnyVek, pohlavie), minHodnota, maxHodnota) {
	}

	void nastavVekPohlavie(int minimalnyVek, int maximalnyVek, EnumPohlavie pohlavie) {
		reinterpret_cast<KUJVekPodiel*>(this->dajKriterium())->nastavKriterium(minimalnyVek,maximalnyVek,pohlavie);
	}
};
