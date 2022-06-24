#pragma once
#include "VyssiCelok.h"

class Obec;
class Kraj;




class Okres :
    public VyssiCelok
{
public:
    Okres(string nazov, string code);
    ~Okres();
    //Vymazat
    void vypisObce();

    //Funkcne
    void pridajObec(Obec* obec);
    void nastavNadKraj(UzemnaJednotka* nadKraj) { this->nadJednotka_ = nadKraj; };


private:
   
};
