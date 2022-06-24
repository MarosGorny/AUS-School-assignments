#include "Kraj.h"
#include "Okres.h"


Kraj::Kraj(std::string nazov, std::string code)
	:VyssiCelok(nazov, code) {
	this->typUzemnejJednotky_ = KRAJ;
	this->podCelok_ = new structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>();
	this->obce_ = new structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>();
}

Kraj::~Kraj()
{
	delete this->obce_;
	this->obce_ = nullptr;

}



void Kraj::pridajObce()
{
	for (structures::TableItem<std::string, UzemnaJednotka*>* itemOkres : *this->podCelok_) {
		Okres* okres = reinterpret_cast<Okres*>(itemOkres->accessData());
		for (structures::TableItem<std::string, UzemnaJednotka*>* itemObec : *okres->getPodCelok()) {
			Okres* obec = reinterpret_cast<Okres*>(itemObec->accessData());
			this->obce_->insert(obec->getNazov(), obec);
		}
	}
}


void Kraj::pridajOkres(Okres* okres) {
	//novyOkres->pridajObceFOR();
	//cout << "\t" << novyOkres->getNazov() << endl;
	this->podCelok_->insert(okres->getNazov(), okres);
	//this->data_->pridajOkres(novyOkres);
}



void Kraj::vypisOkresy() {
	std::cout << "--------------OKRESY-----------------" << this->getNazov()  << std::endl;
	for (structures::TableItem<std::string, UzemnaJednotka*>* okres : *this->podCelok_) {
		std::cout << "\t" << okres->getKey() << std::endl;
	}
	std::cout << std::endl;
}

