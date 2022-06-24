#pragma once
#include "VyssiCelok.h"

class Okres;

class Kraj :
    public VyssiCelok
{
public:
    Kraj(std::string nazov, std::string code);
    ~Kraj();

    //Vymazat
    void vypisOkresy();
        //Obec* najdiObec(string nazovObce);

    //Funkcne
    void pridajOkres(Okres* okres);
    void pridajObce();
    //Gettre

    structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* getObce() const { return this->obce_; };

    
private:
    structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* obce_;
};
