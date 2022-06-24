#pragma once
#include "KompozitnyFilter.h"

class Filter_OR
	: public KompozitnyFilter {
public:
	bool splna(UzemnaJednotka* uzemnaJednotka);
};

bool Filter_OR::splna(UzemnaJednotka* uzemnaJednotka) {
	for (Filter* filter : *this->filtre_) {
		if (filter->splna(uzemnaJednotka)) {
			return true;
		}
	}

	return false;
}