#pragma once
#include "FilterKriterium.h"

template<typename R>
class FilterMaleFi :
    public FilterKriterium<R>
{
public:
    FilterMaleFi(Kriterium<R>* kriterium, R hodnota);
    //toto mozem nastavit cez konstruktor
    void nastavHodnotuFiltru(R hodnota) { this->hodnota_ = hodnota; };
protected:
    bool splnaFilter(R hodnota) override;
private:
    R hodnota_;
};

template<typename R>
inline FilterMaleFi<R>::FilterMaleFi(Kriterium<R>* kriterium, R hodnota)
    :FilterKriterium<R>(kriterium)
{
    this->hodnota_ = hodnota;
}

template<typename R>
bool FilterMaleFi<R>::splnaFilter(R hodnota) {
    return hodnota == hodnota_;

}
