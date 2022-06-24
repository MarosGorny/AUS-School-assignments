#pragma once
#include "Filter.h"

template <typename R>
class FilterKriterium 
	:public Filter
{
public:
	~FilterKriterium();
	FilterKriterium<R>(Kriterium<R>* kriterium) { this->kriterium_ = kriterium; };
	bool splna(UzemnaJednotka* uzemnaJednotka) override;
protected:
	Kriterium<R>* dajKriterium() const { return this->kriterium_; };
	virtual bool splnaFilter(R hodnota) = 0;
private:
	Kriterium<R>* kriterium_;
};

template <typename R>
bool FilterKriterium<R>::splna(UzemnaJednotka* uzemnaJednotka) {
	return this->splnaFilter(kriterium_->urobKriterium(uzemnaJednotka));
}

template<typename R>
inline FilterKriterium<R>::~FilterKriterium()
{
	delete this->kriterium_;
	kriterium_ = nullptr;
}
