#pragma once
#include "Filter.h"
#include "../structures/list/array_list.h"

class KompozitnyFilter
	:public Filter
{
public:
	inline KompozitnyFilter();
	inline ~KompozitnyFilter();
	void zaregistrujFilter(Filter* filter);
	void vynulujFiltre();
protected:
	structures::ArrayList<Filter*>* filtre_;
};

inline KompozitnyFilter::KompozitnyFilter() {
	this->filtre_ = new structures::ArrayList<Filter*>();
}

inline KompozitnyFilter::~KompozitnyFilter() {
	delete this->filtre_;
	this->filtre_ = nullptr;
}

inline void KompozitnyFilter::zaregistrujFilter(Filter* filter)
{
	this->filtre_->add(filter);
}

inline void KompozitnyFilter::vynulujFiltre()
{
	this->filtre_->clear();
}

