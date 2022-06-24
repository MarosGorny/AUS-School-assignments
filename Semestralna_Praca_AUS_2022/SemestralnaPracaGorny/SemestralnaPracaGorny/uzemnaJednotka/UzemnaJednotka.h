#pragma once
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "EnumTypUzemnejJednotky.h"
#include "../pohlavie/EnumPohlavie.h"
#include "../EnumVzdelanie.h"
#include "../EnumVekovaSkupina.h"

using namespace std;


class UzemnaJednotka
{
public:
	
	virtual UzemnaJednotka* getNadJednotku() { return this->nadJednotka_; };
	virtual std::string getNazov() { return this->nazovUJ; };
	virtual std::string getCode() { return this->codeUJ; };
	virtual EnumTypUzemnejJednotky getTyp() { return this->typUzemnejJednotky_; };
	virtual int getPocetObyvatelov() { return this->pocetObyvatelov_; };
	virtual bool getPatriDoVyssiehoCelku() { return this->patriDoVyssiehoCelku_; };

	virtual int getPocetVekovejSkupiny(EnumVekovaSkupina vekovaSkupina) = 0;
	virtual int getPocetVzdelanie(EnumVzdelanie typVzdelania) = 0;
	virtual int getVek(int pocetRokov, EnumPohlavie pohlavie) = 0;
	virtual int getVek(int minRokov, int maxRokov, EnumPohlavie pohlavie) = 0;

	virtual void spocitajObyvatelov() = 0;
	
public:
	UzemnaJednotka(std::string nazov, std::string code);
	~UzemnaJednotka();

protected:
	
	UzemnaJednotka* nadJednotka_;
	std::string nazovUJ;
	std::string codeUJ;
	bool patriDoVyssiehoCelku_;
	int pocetObyvatelov_;
	EnumTypUzemnejJednotky typUzemnejJednotky_;

	
};

inline UzemnaJednotka::UzemnaJednotka(std::string nazov, std::string code) {
		this->nazovUJ = nazov;
		this->codeUJ = code;
}

inline UzemnaJednotka::~UzemnaJednotka()
{
	this->nazovUJ = "";
	this->codeUJ = "";
	this->pocetObyvatelov_ = 0;
	this->nadJednotka_ = nullptr;

}
