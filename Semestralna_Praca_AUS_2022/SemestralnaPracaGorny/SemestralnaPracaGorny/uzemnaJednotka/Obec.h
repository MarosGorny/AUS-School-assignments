#pragma once
#include "UzemnaJednotka.h"
#include "../structures/array/array.h"


class Okres;

class Obec :
    public UzemnaJednotka
{
public:
	Obec(std::string nazov,std::string code);
	~Obec();
	//Na VYMAZANIE
	void vypisVzdelanie();
	
	
	//Funkcne 
	
	int getPocetVekovejSkupiny(EnumVekovaSkupina vekovaSkupina);
	int getPocetVzdelanie(EnumVzdelanie typVzdelania);
	int getVek(int pocetRokov, EnumPohlavie pohlavie) override;
	int getVek(int minRokov, int maxRokov, EnumPohlavie pohlavie) override;

	void pridajVek(int pozicia, int pocet);
	void pridajVzdelanie(int pozicia, int pocet);
	
	void nastavNadOkres(UzemnaJednotka* nadOkres) { this->nadJednotka_ = nadOkres; };
	void spocitajObyvatelov();
private:

	//Funkcne
	

	structures::Array<int>* typyVzdelania_;
	structures::Array<int>* vek_;
};

