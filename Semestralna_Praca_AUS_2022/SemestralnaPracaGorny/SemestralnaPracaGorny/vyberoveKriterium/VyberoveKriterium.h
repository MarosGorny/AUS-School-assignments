#pragma once
#include "structures/table/table.h"
#include "uzemnaJednotka/UzemnaJednotka.h"
#include "kriterium/Kriterium.h"

template<typename R>
class VyberoveKriterium {
public:
	VyberoveKriterium(Kriterium<R>* kriterium);
	~VyberoveKriterium();
	UzemnaJednotka* vyberNajelspieho(structures::Table<std::string, UzemnaJednotka*>* tabulka);
protected:
	virtual bool jeTestovanaHodnotaLepsia(R najlepsiTeraz, R najlepsiTestovany) = 0;
	Kriterium<R>* kriterium_;
	
};

template<typename R>
inline VyberoveKriterium<R>::VyberoveKriterium(Kriterium<R>* kriterium)
{
	this->kriterium_ = kriterium;
}

template<typename R>
inline VyberoveKriterium<R>::~VyberoveKriterium()
{
	delete this->kriterium_;
}

template<typename R>
inline UzemnaJednotka* VyberoveKriterium<R>::vyberNajelspieho(structures::Table<std::string, UzemnaJednotka*>* tabulka)
{
	int counter = 0;
	R bestValue{};
	UzemnaJednotka* bestObject = nullptr;

	for (structures::TableItem<std::string, UzemnaJednotka*>* item : *tabulka) {
		
		UzemnaJednotka* testovanaUJ = item->accessData();
		R testovanaHodnota = kriterium_->urobKriterium(testovanaUJ);

		if (counter == 0) {
			bestValue = kriterium_->urobKriterium(testovanaUJ);
			bestObject = item->accessData();
			counter++;
		}

		if (jeTestovanaHodnotaLepsia(bestValue, testovanaHodnota)) {
			bestValue = testovanaHodnota;
			bestObject = testovanaUJ;
		}

	}
	return bestObject;
}
