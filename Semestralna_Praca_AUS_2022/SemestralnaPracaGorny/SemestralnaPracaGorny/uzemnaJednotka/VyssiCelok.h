#pragma once
#include "UzemnaJednotka.h"
//#include "../kriterium/Kriterium.h"
#include "../triedenie/sort.h"
#include "../structures/table/table.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "Obec.h"

class VyssiCelok :
    public UzemnaJednotka
{
public:
    VyssiCelok(string nazov,string code);
    ~VyssiCelok();
    //virtual structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* getPodcelok() const = 0;
    //virtual structures::UnsortedSequenceTable<std::string, VyssiCelok*>* getPodCelky() const = 0;
    //virtual Obec* najdiObec(string nazovObce) = 0;
public:
    structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* getPodCelok() const { return this->podCelok_; };

public:
    int getPocetVekovejSkupiny(EnumVekovaSkupina vekovaSkupina) override;
    int getPocetVzdelanie(EnumVzdelanie typVzdelania) override;
    int getVek(int pocetRokov, EnumPohlavie pohlavie) override;
    int getVek(int minRokov, int maxRokov, EnumPohlavie pohlavie) override;
    void spocitajObyvatelov() override;


protected:
    structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* podCelok_;
};

inline VyssiCelok::VyssiCelok(string nazov, string code)
    :UzemnaJednotka(nazov,code)
{
    this->patriDoVyssiehoCelku_ = true;
}

inline VyssiCelok::~VyssiCelok()
{
    delete this->podCelok_;
    this->podCelok_ = nullptr;
}


inline int VyssiCelok::getPocetVekovejSkupiny(EnumVekovaSkupina vekovaSkupina)
{
    int pocet = 0;
    for (structures::TableItem<std::string, UzemnaJednotka*>* item : *podCelok_) {
        pocet += item->accessData()->getPocetVekovejSkupiny(vekovaSkupina);
    }

    return pocet;
}

inline int VyssiCelok::getPocetVzdelanie(EnumVzdelanie typVzdelania)
{
    int pocet = 0;
    for (structures::TableItem<std::string, UzemnaJednotka*>* item : *podCelok_) {
        pocet += item->accessData()->getPocetVzdelanie(typVzdelania);
    }

    return pocet;
}

inline int VyssiCelok::getVek(int pocetRokov, EnumPohlavie pohlavie)
{
    int pocet = 0;
    for (structures::TableItem<std::string, UzemnaJednotka*>* item : *podCelok_) {
        pocet += item->accessData()->getVek(pocetRokov, pohlavie);
    }

    return pocet;
}

inline int VyssiCelok::getVek(int minRokov, int maxRokov, EnumPohlavie pohlavie)
{
    int pocet = 0;
    for (structures::TableItem<std::string, UzemnaJednotka*>* item : *podCelok_) {
        pocet += item->accessData()->getVek(minRokov,maxRokov, pohlavie);
    }

    return pocet;
}

inline void VyssiCelok::spocitajObyvatelov()
{
    for (structures::TableItem<string, UzemnaJednotka*>* ujItem : *this->podCelok_) {
        this->pocetObyvatelov_ += ujItem->accessData()->getPocetObyvatelov();
    }
}


