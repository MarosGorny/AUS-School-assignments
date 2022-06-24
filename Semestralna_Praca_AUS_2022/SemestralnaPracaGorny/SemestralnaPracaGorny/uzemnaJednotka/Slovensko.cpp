#include "Slovensko.h"
#include "Kraj.h"
#include "Obec.h"



Slovensko::Slovensko()
	:VyssiCelok("Slovensko", "0") {
	this->typUzemnejJednotky_ = SLOVENSKO;
	this->podCelok_ = new structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>();
}



void Slovensko::pridajKraj(Kraj* kraj) {
	this->podCelok_->insert(kraj->getNazov(), kraj);
}


/*
void Slovensko::vypisKraje() {
	std::cout << "--------------KRAJE-----------------" << std::endl;
	for (structures::TableItem<std::string, Kraj*>* kraj : *this->kraje_) {
		std::cout << "\t" << kraj->getKey() << std::endl;
	}
	std::cout << std::endl;
}

void Slovensko::vypisUJ() {
	std::cout << "--------------KRAJE-----------------" << std::endl;
	for (structures::TableItem<std::string, Kraj*>* kraj : *this->kraje_) {
		std::cout << "\t" << kraj->getKey() << std::endl;
	}
	std::cout << std::endl;
	
}

*/

