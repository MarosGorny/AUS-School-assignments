#pragma once
// bez intervalu

#include "FilterMaleFi.h"
#include "../kriterium/KUJTyp.h"
#include "../uzemnaJednotka/EnumTypUzemnejJednotky.h"




class FilterTyp
	: public FilterMaleFi<EnumTypUzemnejJednotky> {
public:
	FilterTyp(UzemnaJednotka* uzemnaJednotka, EnumTypUzemnejJednotky typ) :
		FilterMaleFi(new KUJTyp(), typ) {
	}
};
