#pragma once

#include "FilterMaleFi.h"
#include "../uzemnaJednotka/UzemnaJednotka.h"
#include "../kriterium/KUJPrislusnost.h"

class FilterPrislusnost
	: public FilterMaleFi<bool> {
public:
	FilterPrislusnost(UzemnaJednotka* uzemnaJednotka, bool patriDoVyssiehoCelku) :
		FilterMaleFi(new KUJPrislusnost(),patriDoVyssiehoCelku) {
	}
};
