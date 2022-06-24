#pragma once
#include "FilterKriterium.h"
template<typename R>
class FilterVelkeFi :
    public FilterKriterium<R>
{
public:
    FilterVelkeFi(Kriterium<R>* kriterium, R minHodnota, R maxHodnota);
    //toto mozem nastavit cez konstruktor
    //void nastavMinHodnotu(R minHodnota) { this->minHodnota_ = minHodnota; };
    //void nastavMaxHodnotu(R maxHodnota) { this->maxHodnota_ = maxHodnota; };
    
    void nastavHodnotuFiltru(R minHodnota, R maxHodnota) { this->minHodnota_ = minHodnota; this->maxHodnota_ = maxHodnota; };
protected:
    bool splnaFilter(R hodnota) override;
private:

    R minHodnota_;
    R maxHodnota_;
};

template<typename R>
inline FilterVelkeFi<R>::FilterVelkeFi(Kriterium<R>* kriterium, R minHodnota, R maxHodnota)
    :FilterKriterium<R>(kriterium)
{
    this->minHodnota_ = minHodnota;
    this->maxHodnota_ = maxHodnota;
}

template<typename R>
bool FilterVelkeFi<R>::splnaFilter(R hodnota) {
    return hodnota >= minHodnota_ && hodnota <= maxHodnota_;
}
