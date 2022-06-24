#pragma once
#include "VyberoveKriterium.h"

template <typename R>
class VyberoveKriteriumMax 
	:public VyberoveKriterium<R>{
public:
	VyberoveKriteriumMax(Kriterium<R>* kriterium);
protected:
	bool jeTestovanaHodnotaLepsia(R najlepsiTeraz, R najlepsiTestovany) override;
};

template<typename R>
inline VyberoveKriteriumMax<R>::VyberoveKriteriumMax(Kriterium<R>* kriterium)
	:VyberoveKriterium<R>(kriterium)
{
}

template<typename R>
inline bool VyberoveKriteriumMax<R>::jeTestovanaHodnotaLepsia(R najlepsiTeraz, R najlepsiTestovany)
{
	return najlepsiTestovany > najlepsiTeraz;
}
