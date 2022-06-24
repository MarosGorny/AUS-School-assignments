#pragma once
#include "KompozitnyFilter.h"

class Filter_AND
	: public KompozitnyFilter{
public:
	bool splna(UzemnaJednotka* uzemnaJednotka);
};

bool Filter_AND::splna(UzemnaJednotka* uzemnaJednotka) {
	for (Filter* filter : *this->filtre_) {
		if (!filter->splna(uzemnaJednotka)) {
			return false;
		}
	}

	return true;
}