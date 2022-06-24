#pragma once
#include "VyberoveKriterium.h"

template <typename R>
class VyberoveKriteriumMin
	:public VyberoveKriterium<R> {
public:
	VyberoveKriteriumMin(Kriterium<R>* kriterium);
protected:
	bool jeTestovanaHodnotaLepsia(R najlepsiTeraz, R najlepsiTestovany) override;
};

template<typename R>
inline VyberoveKriteriumMin<R>::VyberoveKriteriumMin(Kriterium<R>* kriterium)
	:VyberoveKriterium<R>(kriterium)
{
}

template<typename R>
inline bool VyberoveKriteriumMin<R>::jeTestovanaHodnotaLepsia(R najlepsiTeraz, R najlepsiTestovany)
{
	return najlepsiTestovany < najlepsiTeraz;
}
