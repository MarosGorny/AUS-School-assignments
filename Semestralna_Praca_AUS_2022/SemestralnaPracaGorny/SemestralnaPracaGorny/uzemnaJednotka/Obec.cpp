#include "Obec.h"
#include "Okres.h"

Obec::Obec(std::string nazov, std::string code)
	:UzemnaJednotka(nazov, code) {

	this->typUzemnejJednotky_ = OBEC;
	this->patriDoVyssiehoCelku_ = false;

	this->typyVzdelania_ = new structures::Array<int>(8);
	this->vek_ = new structures::Array<int>(202);
}

Obec::~Obec()
{
	
	delete this->typyVzdelania_;
	delete this->vek_;
	this->typyVzdelania_ = nullptr;
	this->vek_ = nullptr;
}

int Obec::getPocetVekovejSkupiny(EnumVekovaSkupina vekovaSkupina)
{
	int pocet = 0;
	switch (vekovaSkupina)
	{
	case PREDPRODUKTIVNI:
		for (int i = 0; i <= 14; i++)
		{
			pocet += this->getVek(i, OBIDVE_POHLAVIA);
		}
		break;
	case PRODUKTIVNI:
		for (int i = 15; i <= 64; i++)
		{
			pocet += this->getVek(i, OBIDVE_POHLAVIA);
		}
		break;
	case POPRODUKTIVNI:
		for (int i = 65; i <= 100; i++)
		{
			pocet += this->getVek(i, OBIDVE_POHLAVIA);
		}
		break;
	default:
		break;
	}
	return pocet;
}

int Obec::getPocetVzdelanie(EnumVzdelanie typVzdelania) {
	return this->typyVzdelania_->at(typVzdelania);
}

int Obec::getVek(int pocetRokov, EnumPohlavie pohlavie)
{
	if (pocetRokov < 0)
		pocetRokov = 0;
	else if (pocetRokov > 100)
		pocetRokov = 100;

	switch (pohlavie)
	{
	case ZENA:
		return this->vek_->at(pocetRokov + 101);
		break;
	case MUZ:
		return this->vek_->at(pocetRokov);
		break;
	case OBIDVE_POHLAVIA:
		return this->vek_->at(pocetRokov) + this->vek_->at(pocetRokov + 101);
		break;
	default:
		break;
	}
	return -1;
}

int Obec::getVek(int minRokov,int maxRokov, EnumPohlavie pohlavie)
{
	int suma = 0;
	if (minRokov < 0)
		minRokov = 0;
	if (maxRokov > 100)
		maxRokov = 100;

	switch (pohlavie)
	{
	case ZENA:
		for (int i = minRokov; i <= maxRokov; i++)
		{
			suma += this->vek_->at(i+101);
		}
		return suma;
		break;
	case MUZ:
		for (int i = minRokov; i <= maxRokov; i++)
		{
			suma += this->vek_->at(i);
		}
		return suma;
		break;
	case OBIDVE_POHLAVIA:
		for (int i = minRokov; i <= maxRokov; i++)
		{
			suma += this->vek_->at(i);
			suma += this->vek_->at(i + 101);
		}
		return suma;
		break;
	default:
		break;
	}
	return -1;
}

void Obec::pridajVek(int pozicia, int pocet)
{
	this->vek_->at(pozicia) = pocet;
}

void Obec::pridajVzdelanie(int pozicia, int pocet)
{
	this->typyVzdelania_->at(pozicia) = pocet;
}

void Obec::vypisVzdelanie() {
	cout << "\t----Vzdelanie obce " << this->nazovUJ << " ----" << endl;

	for (int i = 0; i < typyVzdelania_->size(); i++)
	{
		cout << typyVzdelania_->at(i) << endl;
	}
}

void Obec::spocitajObyvatelov()
{
	for (int i = 0; i < this->vek_->size(); i++)
	{
		this->pocetObyvatelov_ += this->vek_->at(i);
	}
}




