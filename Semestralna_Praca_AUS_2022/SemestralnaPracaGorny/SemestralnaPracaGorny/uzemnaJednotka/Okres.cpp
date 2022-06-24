#include "Okres.h"
#include "Obec.h"
#include "Kraj.h"
#include "../kriterium/Kriterium.h"
#include "../triedenie/sort.h"


Okres::Okres(std::string nazov, std::string code)
	:VyssiCelok(nazov, code) {

	this->typUzemnejJednotky_ = OKRES;
	this->podCelok_ = new structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>();
}

Okres::~Okres()
{

}



void Okres::vypisObce() {
	std::cout << "--------------OBCE----------------- " << this->getNazov() << std::endl;
	for (structures::TableItem<std::string, UzemnaJednotka*>* obec : *this->podCelok_) {
		std::cout << "\t" << obec->getKey() << std::endl;
	}
	std::cout << std::endl;
}

void Okres::pridajObec(Obec* obec) {
	//Obec* novaObec = new Obec(nazovObce, codeObce);
	//cout << novaObec->getNazov() << endl;
	this->podCelok_->insert(obec->getNazov(),obec);
	//this->data_->pridajObec(novaObec);
	
}



