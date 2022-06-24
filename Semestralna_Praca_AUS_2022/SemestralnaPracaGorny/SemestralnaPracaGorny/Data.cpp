#include "Data.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

#include "uzemnaJednotka/Slovensko.h"
#include "uzemnaJednotka/Kraj.h"
#include "uzemnaJednotka/Okres.h"
#include "uzemnaJednotka/Obec.h"

#include "kriterium/KNazov.h"
#include "kriterium/KUJNadradena.h"
#include "kriterium/KUJPrislusnost.h"
#include "kriterium/KUJTyp.h"
#include "kriterium/KUJVekovaSkupinaPocet.h"
#include "kriterium/KUJVekovaSkupinaPodiel.h"
#include "kriterium/KUJVekPocet.h"
#include "kriterium/KUJVekPodiel.h"
#include "kriterium/KUJVzdelaniePocet.h"
#include "kriterium/KUJVzdelaniePodiel.h"

#include "filter/KompozitnyFilter.h"
#include "filter/Filter_AND.h"
#include "filter/Filter_OR.h"
#include "filter/Filter.h"
#include "filter/FilterPrislusnost.h"
#include "filter/FilterTyp.h"
#include "filter/FilterVekovaSkupinaPocetMedzi.h"
#include "filter/FilterVekovaSkupinaPodielMedzi.h"
#include "filter/FilterVekPocetMedzi.h"
#include "filter/FilterVekPodielMedzi.h"
#include "filter/FilterVzdelaniePocetMedzi.h"
#include "filter/FilterVzdelaniePodielMedzi.h"

#include"triedenie/quick_sort.h"





Data::Data()
{
	this->krajeVsetky_ = new structures::SortedSequenceTable<std::string, UzemnaJednotka*>();
	this->okresyVsetky_= new structures::SortedSequenceTable<std::string, UzemnaJednotka*>();
	this->obceVsetky_ = new structures::SortedSequenceTable<std::string, UzemnaJednotka*>();

	this->krajeUnsortedCode_ = new structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>();
	this->okresyUnsortedCode_ = new structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>();
	this->obceUnsortedCode_ = new structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>();

	this->slovensko_ = new Slovensko();
	
	this->aktivneKriteria_ = new structures::Array<bool>(10);
	this->aktivneFiltre_ = new structures::Array<bool>(8);

	this->kriteriumNazov_ = new KNazov();
	this->kriteriumNadradena_ = new KUJNadradena();
	this->kriteriumPrislusnost_ = new KUJPrislusnost();
	this->kriteriumTyp_ = new KUJTyp();
	this->krtiteriumVekSkupinaPocet_ = new KUJVekovaSkupinaPocet();
	this->kriteriumVekSkupinaPodiel_ = new KUJVekovaSkupinaPodiel();
	this->kriteriumVekPocet_ = new KUJVekPocet();
	this->kriteriumVekPodiel_ = new KUJVekPodiel();
	this->kriteriumVzdelaniePocet_ = new KUJVzdelaniePocet();
	this->kriteriumVzdelaniePodiel_ = new KUJVzdelaniePodiel();

	this->vyfiltrovanaMnozina_ = nullptr;
	this->filterAND_ = new Filter_AND();
	this->filterOR_ = new Filter_OR();
	this->filterANDZvoleny_ = false;
	this->filterORZvoleny_ = false;
	this->filterPrislusnost_ = new FilterPrislusnost(nullptr, false);
	this->filterTyp_ = new FilterTyp(nullptr, NULL_ENUM_UJ);
	this->filterVekSkupPocet_ = new FilterVekovaSkupinaPocetMedzi(0, 0, NULL_ENUM_VEKOVA_SKUPINA);
	this->filterVekSkupPodiel_ = new FilterVekovaSkupinaPodielMedzi(0, 0, NULL_ENUM_VEKOVA_SKUPINA);
	this->filterVekPocet_ = new FilterVekPocetMedzi(0,0, 0, -1, NULL_ENUM_POHLAVE);
	this->filterVekPodiel_ = new FilterVekPodielMedzi(0,0, 0, -1, NULL_ENUM_POHLAVE);
	this->filterVzdelaniePocet_ = new FilterVzdelaniePocetMedzi(0, 0, NULL_ENUM_VZDELANIE);
	this->filterVzdelaniePodiel_ = new FilterVzdelaniePodielMedzi(0, 0, NULL_ENUM_VZDELANIE);

	//vyber
	this->vyberNajvacsiaVekSkupina_ = new VNajvacsiaVekovaSkupina(NULL_ENUM_VEKOVA_SKUPINA);
	this->vyberNajmensiaVekSkupina_ = new VNajmensiaVekovaSkupina(NULL_ENUM_VEKOVA_SKUPINA);
	
	this->pridajUJ();
	this->prepojUJ();

}

Data::~Data()
{
	
	

	//vymazanie pomocnych arrayov pre interface
	delete this->aktivneFiltre_;
	delete this->aktivneKriteria_;
	this->aktivneKriteria_ = nullptr;
	this->aktivneFiltre_ = nullptr;

	//vymazanieKriterii
	delete this->kriteriumNazov_;
	delete this->kriteriumNadradena_;
	delete this->kriteriumPrislusnost_;
	delete this->kriteriumTyp_;
	delete this->krtiteriumVekSkupinaPocet_;
	delete this->kriteriumVekSkupinaPodiel_;
	delete this->kriteriumVekPocet_;
	delete this->kriteriumVekPodiel_;
	delete this->kriteriumVzdelaniePocet_;
	delete this->kriteriumVzdelaniePodiel_;
	this->kriteriumNazov_ = nullptr;
	this->kriteriumNadradena_ = nullptr;
	this->kriteriumPrislusnost_ = nullptr;
	this->kriteriumTyp_ = nullptr;
	this->krtiteriumVekSkupinaPocet_ = nullptr;
	this->kriteriumVekSkupinaPodiel_ = nullptr;
	this->kriteriumVekPocet_ = nullptr;
	this->kriteriumVekPodiel_ = nullptr;
	this->kriteriumVzdelaniePocet_ = nullptr;
	this->kriteriumVzdelaniePodiel_ = nullptr;

	//vymazanie filtrov
	delete this->filterAND_;
	delete this->filterOR_;
	delete this->filterPrislusnost_;
	delete this->filterTyp_;
	delete this->filterVekSkupPocet_;
	delete this->filterVekSkupPodiel_;
	delete this->filterVekPocet_;
	delete this->filterVekPodiel_;
	delete this->filterVzdelaniePocet_;
	delete this->filterVzdelaniePodiel_;
	if(vyfiltrovanaMnozina_ != nullptr)
		delete this->vyfiltrovanaMnozina_;

	this->filterAND_ = nullptr;
	this->filterOR_ = nullptr;
	this->filterPrislusnost_ = nullptr;
	this->filterTyp_ = nullptr;
	this->filterVekSkupPocet_ = nullptr;
	this->filterVekSkupPodiel_ = nullptr;
	this->filterVekPocet_ = nullptr;
	this->filterVekPodiel_ = nullptr;
	this->filterVzdelaniePocet_ = nullptr;
	this->filterVzdelaniePodiel_ = nullptr;
	this->vyfiltrovanaMnozina_ = nullptr;

	//vyber
	delete this->vyberNajvacsiaVekSkupina_;
	delete this->vyberNajmensiaVekSkupina_;
	this->vyberNajvacsiaVekSkupina_ = nullptr;
	this->vyberNajmensiaVekSkupina_ = nullptr;

	this->vymazUJ();
	delete this->krajeVsetky_;
	delete this->okresyVsetky_;
	delete this->obceVsetky_;
	delete this->slovensko_;

	this->krajeVsetky_ = nullptr;
	this->okresyVsetky_ = nullptr;
	this->obceVsetky_ = nullptr;
	this->slovensko_ = nullptr;

	//Vymazanie pomocnych struktur
	delete this->krajeUnsortedCode_;
	delete this->okresyUnsortedCode_;
	delete this->obceUnsortedCode_;
	this->krajeUnsortedCode_ = nullptr;
	this->okresyUnsortedCode_ = nullptr;
	this->obceUnsortedCode_ = nullptr;

	
}



void Data::prepojObceOkresy()
{
	Okres* okres = nullptr;
	std::string codeOkresu{};

	Obec* obec = nullptr;
	std::string skratenyCodeObce{};

	int counter = 0;

	for (structures::TableItem<std::string, UzemnaJednotka*>* obecItem : *this->obceUnsortedCode_) {


		obec = reinterpret_cast<Obec*>(obecItem->accessData());
		skratenyCodeObce = obec->getCode().substr(0, 6);

		if (counter == 0) {
			okres = reinterpret_cast<Okres*>(this->okresyUnsortedCode_->find(skratenyCodeObce));
			codeOkresu = okres->getCode();
			counter++;
		} else if (skratenyCodeObce != codeOkresu) {
			okres->spocitajObyvatelov();
			okres = reinterpret_cast<Okres*>(this->okresyUnsortedCode_->find(skratenyCodeObce));
			codeOkresu = okres->getCode();
		}
		obec->nastavNadOkres(okres);
		okres->pridajObec(obec);
		
	}
	okres->spocitajObyvatelov(); //na posledny prvok
}

void Data::prepojOkresyKraje()
{
	Kraj* kraj = nullptr;
	std::string codeKraju{};

	Okres* okres = nullptr;
	std::string skratenyCodeOkresu{};

	int counter = 0;

	for (structures::TableItem<std::string, UzemnaJednotka*>* okresItem : *this->okresyUnsortedCode_) {
		okres = reinterpret_cast<Okres*>(okresItem->accessData());
		skratenyCodeOkresu = okres->getCode().substr(0, 5);

		if (counter == 0) {
			kraj = reinterpret_cast<Kraj*>(this->krajeUnsortedCode_->find(skratenyCodeOkresu));
			codeKraju = kraj->getCode();
			counter++;
		}
		else if (skratenyCodeOkresu != codeKraju) {
			kraj->spocitajObyvatelov();
			kraj = reinterpret_cast<Kraj*>(this->krajeUnsortedCode_->find(skratenyCodeOkresu));
			codeKraju = kraj->getCode();
		}

		okres->nastavNadKraj(kraj);
		kraj->pridajOkres(okres);

	}
	kraj->spocitajObyvatelov();
}

void Data::prepojKrajeSlovensko()
{

	for (structures::TableItem<std::string, UzemnaJednotka*>* okresItem : *this->krajeUnsortedCode_) {
		Kraj* kraj = reinterpret_cast<Kraj*>(okresItem->accessData());
		slovensko_->pridajKraj(kraj);
		kraj->pridajObce();
	}
	slovensko_->spocitajObyvatelov();
}

void Data::pridajUJ()
{
	this->pridajVsetkyObce();
	this->pridajVsetkyOkresy();
	this->pridajVsetkyKraje();
}

void Data::prepojUJ()
{
	this->prepojObceOkresy();
	this->prepojOkresyKraje();
	this->prepojKrajeSlovensko();
}

void Data::vymazObce()
{
	for (structures::TableItem<std::string, UzemnaJednotka*>* obecItem : *this->obceVsetky_) {
		Obec* obec = reinterpret_cast<Obec*>(obecItem->accessData());
		delete obec;
		obec = nullptr;

	}
}

void Data::vymazOkresy()
{
	for (structures::TableItem<std::string, UzemnaJednotka*>* okresItem : *this->okresyVsetky_) {
		Okres* okres = reinterpret_cast<Okres*>(okresItem->accessData());
		delete okres;
		okres = nullptr;
	}
}

void Data::vymazKraje()
{
	for (structures::TableItem<std::string, UzemnaJednotka*>* krajItem : *this->krajeVsetky_) {
		Kraj* kraj = reinterpret_cast<Kraj*>(krajItem->accessData());
		delete kraj;
		kraj = nullptr;
	}
}



void Data::vymazUJ()
{
	this->vymazObce();
	this->vymazOkresy();
	this->vymazKraje();
	
}


UzemnaJednotka* Data::najdi(EnumTypUzemnejJednotky UJ, std::string nazovUJ)
{
	UzemnaJednotka* hladanaUJ = nullptr;
	switch (UJ)
	{
	case SLOVENSKO:
		return this->slovensko_;
	case KRAJ:
		
		if (this->krajeVsetky_->tryFind(nazovUJ, hladanaUJ)) {
			return hladanaUJ;
			
		}
		break;
	case OKRES:
		
		if (this->okresyVsetky_->tryFind(nazovUJ, hladanaUJ)) {
			return hladanaUJ;
		}
		break;
	case OBEC:
		
		if (this->obceVsetky_->tryFind(nazovUJ, hladanaUJ)) {
			return hladanaUJ;
		}
		break;
	default:
		return nullptr;
		break;
	}
	return nullptr;
}

structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* Data::spravKopiuPodlaFiltra(structures::Table<std::string, UzemnaJednotka*>* tabulka, Filter* filter)
{
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* novaTabulka = new structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>();

	for (structures::TableItem<std::string, UzemnaJednotka*>* ujItem : *tabulka) {
		if (filter->splna(ujItem->accessData())) {
			novaTabulka->insert(ujItem->accessData()->getNazov(), ujItem->accessData());
		}
	}
	return novaTabulka;
}

void Data::vyberUJTyp()
{

	char znak{};
	string line{};
	do {
		this->vybranaMnozina_ = nullptr;
		this->vybranaUzemnaJednotka_ = nullptr;
		this->vybraneVzdelanie_ = NULL_ENUM_VZDELANIE;
		this->vybranyTypUJ_ = NULL_ENUM_UJ;
		this->vybranaVekovaSkupina_ = NULL_ENUM_VEKOVA_SKUPINA;
		this->vybranePohlave_ = NULL_ENUM_POHLAVE;
		this->vybranyTypUJFilter_ = NULL_ENUM_UJ;

		std::cout << "\n---------------------------------" << endl;
		std::cout << "Aku uzemnu jednotku chces vyhladat?" << endl;
		std::cout << "0 - Slovensko" << endl;
		std::cout << "1 - Kraj alebo vsetky kraje" << endl;
		std::cout << "2 - Okres alebo vsetky okresy" << endl;
		std::cout << "3 - Obec alebo vsetky obce" << endl;
		std::cout << "q - Koniec" << endl;
		std::cout << "---------------------------------" << endl;
		std::cout << "Vyber:\t";

		//cin.ignore();
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];
		char key_press;

		switch (znak)
		{
		case '0': {
			bool nepokracuj = true;
			do
			{
				vybranyTypUJ_ = SLOVENSKO;
				vybranaUzemnaJednotka_ = this->slovensko_;
				std::cout << "Ak chces vypisat pocet obyvatelov, stlac 'o'." << endl;
				std::cout << "Ak chces pocet obyvatelov podla EVS, stlac 'e'." << endl;
				std::cout << "Ak chces vypisat pocet obyvatelov podla vzdelania, stlac 'v'." << endl;
				std::cout << "Ak sa chces vratit, stlac 'q'." << endl;
				key_press = _getch();
				if (key_press == 111) {//o
					std::cout << endl;
					std::cout << "Pocet obyvatelov: " << this->slovensko_->getPocetObyvatelov() << std::endl;
				}
				else if (key_press == 101) { //e
					this->vyberVekovuSkupinu();
					std::cout << endl;
					std::cout << this->enumEVStoString(this->vybranaVekovaSkupina_) << std::endl;
					std::cout << "Pocet obyvatelov v danej skupine: ";
					std::cout << this->slovensko_->getPocetVekovejSkupiny(vybranaVekovaSkupina_) << std::endl;
				}
				else if (key_press == 118) { //v 
					this->vyberVzdelanie();
					std::cout << endl;
					std::cout << this->enumVzdelanieToString(this->vybraneVzdelanie_) << std::endl;
					std::cout << "Pocet obyvatelov podla vzdelania: ";
					std::cout << this->slovensko_->getPocetVzdelanie(vybraneVzdelanie_) << std::endl;
				}
				else if (key_press == 113) {
					nepokracuj = false;
				}
				
			} while (nepokracuj);

		} 
				break;
		case '1':
			vybranyTypUJ_ = KRAJ;
			std::cout << "Ak chces vypisat zoznam krajov, stlac 'v'." << endl;
			key_press = _getch();
			if(key_press == 118) 
				this->vypisKraje();

			std::cout << "Ak chces vybrat vsetky kraje, stlac 'x'" << endl;
			key_press = _getch();
			if (key_press == 120 || key_press == 88) {
				std::cout << "Zvolil si vsetky kraje" << endl;
				this->vybranaMnozina_ = this->krajeUnsortedCode_;
				this->pracaSVybranouMnozinou();
			}
			else {
				std::cout << "Vyber kraj:\t";
				if (this->vyberUJ()) {
					this->vyberMoznosti();
				}
				else {
					std::cout << "Uzemna jednotka sa nenasla - skus to znova" << endl << endl;
				}
			}
			break;
		case '2':
			vybranyTypUJ_ = OKRES;
			std::cout << "Ak chces vypisat zoznam okresov, stlac 'v'." << endl;
			key_press = _getch();
			if (key_press == 118)
				this->vypisOkresy();
			
			std::cout << "Ak chces vybrat vsetky okresy, stlac 'x'" << endl;
			key_press = _getch();
			if (key_press == 120 || key_press == 88) {
				std::cout << "Zvolil si vsetky okresy" << endl;
				this->vybranaMnozina_ = this->okresyUnsortedCode_;
				this->pracaSVybranouMnozinou();
			}
			else {
				std::cout << "Vyber okres:\t";
				if (this->vyberUJ()) {
					this->vyberMoznosti();
				}
				else {
					std::cout << "Uzemna jednotka sa nenasla - skus to znova" << endl << endl;
				}
			}
			break;
		case '3':
			vybranyTypUJ_ = OBEC;
			std::cout << "Ak chces vypisat zoznam obci, stlac 'v'." << endl;
			key_press = _getch();
			if (key_press == 118 || key_press == 86)
				this->vypisObce();
			std::cout << "Ak chces vybrat vsetky obce, stlac 'x'" << endl;
			key_press = _getch();
			if (key_press == 120 || key_press == 88) {
				std::cout << "Zvolil si vsetky obce" << endl;
				this->vybranaMnozina_ = this->obceUnsortedCode_;
				this->pracaSVybranouMnozinou();
			}   else {
				std::cout << "Vyber obec:\t";
				if (this->vyberUJ()) {
					this->vyberMoznosti();
				}
				else {
					std::cout << "Uzemna jednotka sa nenasla - skus to znova" << endl << endl;
				}
			}
			break;
		case 'q':
		case 'Q':
			std::cout << endl;
			std::cout << "Program sa uspesne vypol." << endl;
			break;
		default:
			std::cout << "Neznamy vyber, prosim skus znova!" << endl;
			
			break;
		}
	} while (znak != 'q' && znak != 'Q');
	
}

bool Data::vyberUJ()
{
	string line{};
	char znak{};
	Kraj* kraj = nullptr;
	Okres* okres = nullptr;
	Obec* obec = nullptr;

	getline(cin, line);
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	znak = line[0];

		switch (vybranyTypUJ_)
		{
		case KRAJ:
			kraj = reinterpret_cast<Kraj*>(this->najdi(vybranyTypUJ_, line));
			if (kraj != nullptr) {
				vybranaUzemnaJednotka_ = kraj;
				return true;
			}
			break;
		case OKRES:
			okres = reinterpret_cast<Okres*>(this->najdi(vybranyTypUJ_, line));
			if (okres != nullptr) {
				vybranaUzemnaJednotka_ = okres;
				return true;
			}
			break;
		case OBEC:
			obec = reinterpret_cast<Obec*>(this->najdi(vybranyTypUJ_, line));
			if (obec != nullptr) {
				vybranaUzemnaJednotka_ = obec;
				return true;
			}
			break;
		default:
			break;
		}
		return false;

		
	
}

void Data::vyberMoznosti()
{

	if (vybranyTypUJ_ == KRAJ) {
		std::cout << "Zaujimaju ta:" << endl;
		std::cout << "0 - Vsetky obce daneho kraja" << endl;
		std::cout << "1 - Vsetky okresy daneho kraja" << endl;
		std::cout << "2 - Dany kraj - pridat kriteria" << endl;
		std::cout << "3 - Dany kraj - vypisat zakladne informacie o UJ" << endl;
		std::cout << "q - Vratit sa spat" << endl;
		std::cout << "---------------------------------" << endl;
		std::cout << "Vyber:\t";
	}
	else if (vybranyTypUJ_ == OKRES) {
		std::cout << "Co chces robit?" << endl;
		std::cout << "0 - Filtrovat vsetky obce pod okresom" << endl;
		std::cout << "1 - Zoradit vsetky obce pod okresom" << endl;
		std::cout << "2 - Filtrovat a zoradit vsetky obce pod okresom" << endl;
		std::cout << "3 - Najst UJ s najmensou EVS z obci pod okresom" << endl;
		std::cout << "4 - Najst UJ s najvacsou EVS z obci pod okresom" << endl;
		std::cout << "5 - Pridat kriteria" << endl;
		std::cout << "6 - Vypisat zakladne informacie o uzemnej jednotke" << endl;
		std::cout << "q - Vratit sa spat" << endl;	//?????? ASI
		std::cout << "---------------------------------" << endl;
		std::cout << "Vyber:\t";
	}
	else if (vybranyTypUJ_ == OBEC) {
		std::cout << "Co chces robit?" << endl;
		std::cout << "1 - Pridat kriteria" << endl;
		std::cout << "2 - Vypisat zakladne informacie o uzemnej jednotke" << endl;
		std::cout << "q - Vratit sa spat" << endl;	//?????? ASI
		std::cout << "---------------------------------" << endl;
		std::cout << "Vyber:\t";
	}

	string line{};
	char znak{};
	getline(cin, line);
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	znak = line[0];

	if (znak == 'Q' || znak == 'q') {
		return;
	}

	switch (vybranyTypUJ_)
	{

	case KRAJ:
		vyberKraj(znak);
		break;
	case OKRES:
		vyberOkres(znak);
		break;
	case OBEC:
		vyberObec(znak);
		break;
	case NULL_ENUM_VZDELANIE:
		break;
	default:
		break;
	}

}
void Data::vyberKraj(char vybranyZnak) {
	Kraj* kraj = reinterpret_cast<Kraj*>(this->vybranaUzemnaJednotka_);
	switch (vybranyZnak)
	{
	case '0':
		this->vybranaMnozina_ = kraj->getObce();
		this->pracaSVybranouMnozinou();
		break;
	case '1':
		this->vybranaMnozina_ = kraj->getPodCelok();
		this->zoraditCezKriteriumMenu();
		break;
	case '2':
		this->pridatKriteraAleboVypisatInformacie();
		break;
	case '3':
		this->vypisatZakladneInfoUJ();
		break;
	case 'Q':
	case 'q':
		break;
	default:
		std::cout << "Neznamy vyber, vraciam sa spat" << endl;
		break;
	}
}

void Data::vyberOkres(char vybranyZnak) {
	string line{};
	char znak{};
	Okres* okres = reinterpret_cast<Okres*>(this->vybranaUzemnaJednotka_);

		switch (vybranyZnak)
		{
		case '0':

			this->vybranaMnozina_ = okres->getPodCelok();
			this->vyberOR_ANDFiltra();
			this->pridanieFiltrov();

		case '1':

			this->vybranaMnozina_ = okres->getPodCelok();
			this->zoraditCezKriteriumMenu();
			break;
		case '2':
			this->vybranaMnozina_ = okres->getPodCelok();
			this->vyberVekovuSkupinu();
			this->vyberNajmensiaVekSkupina_->nastavVekSkupinu(this->vybranaVekovaSkupina_);
			this->vypisTypNazovNadJednotiek(this->vyberNajmensiaVekSkupina_->vyberNajelspieho(this->vybranaMnozina_));
		case '3':
			this->vybranaMnozina_ = okres->getPodCelok();
			this->vyberVekovuSkupinu();
			this->vyberNajmensiaVekSkupina_->nastavVekSkupinu(this->vybranaVekovaSkupina_);
			this->vypisTypNazovNadJednotiek(this->vyberNajmensiaVekSkupina_->vyberNajelspieho(this->vybranaMnozina_));
			break;

		case '4':
			this->vybranaMnozina_ = okres->getPodCelok();
			this->vyberVekovuSkupinu();
			this->vyberNajvacsiaVekSkupina_->nastavVekSkupinu(this->vybranaVekovaSkupina_);
			this->vypisTypNazovNadJednotiek(this->vyberNajvacsiaVekSkupina_->vyberNajelspieho(this->vybranaMnozina_));
			break;
		case '5':
			this->pridatKriteraAleboVypisatInformacie();
			break;
		case '6':
			this->vypisatZakladneInfoUJ();
			break;
		case 'Q':
		case 'q':
			break;
		default:
			std::cout << "Neznamy vyber, vraciam sa spat" << endl;
			break;
		}
	
}

void Data::vyberObec(char vybranyZnak) {
	string line{};
	char znak{};
	switch (vybranyZnak)
	{
	case '1':
		this->pridatKriteraAleboVypisatInformacie();
		break;
	case '2':
		this->vypisatZakladneInfoUJ();
		break;
	case 'Q':
	case 'q':
		break;
	default:
		std::cout << "Neznamy vyber, vraciam sa spat" << endl;
		break;
	}
}

void Data::vypisatZakladneInfoUJ() {
	int width = 55;
	std::cout << setw(width) << "Nazov uzemnej jednotky: " << kriteriumNazov_->urobKriterium(vybranaUzemnaJednotka_) << endl;
	std::cout << setw(width) << "Nadradena uzemna jednotka: "; {
		if (kriteriumNadradena_->urobKriterium(vybranaUzemnaJednotka_) == nullptr) {
			std::cout << "Slovensko";
		}
		else {
			std::cout << kriteriumNadradena_->urobKriterium(vybranaUzemnaJednotka_)->getNazov();
		}
		std::cout << endl;

	} 
	std::cout << setw(width) << "Prislusnost vo vyssom celku: ";
	if (kriteriumPrislusnost_->urobKriterium(vybranaUzemnaJednotka_))
		std::cout << "Ano";
	else
		std::cout << "Nie";
	std::cout << endl;
	std::cout << setw(width) << "Typ uzemnej jednotky: " << this->enumTypUJtoString(kriteriumTyp_->urobKriterium(vybranaUzemnaJednotka_)) << endl;
}

void Data::pridatKriteraAleboVypisatInformacie() {
	std::string line;
	char key_press;
	char znak;
	do {
		std::cout << "Pridat kriterium, alebo vypisat informacie?" << endl;
		std::cout << "0 - Kriterium: Nazov" << endl;
		std::cout << "1 - Kriterium: Nadradena uzemna jednotka" << endl;
		std::cout << "2 - Kriterium: Prislusnost vo vyssom celku" << endl;
		std::cout << "3 - Kriterium: Typ uzemnej jednotky" << endl;
		std::cout << "4 - Kriterium: Ekonomicka vekova skupina pocet" << endl;
		std::cout << "5 - Kriterium: Ekonomicka vekova skupina podiel" << endl;
		std::cout << "6 - Kriterium: Vek pocet" << endl;
		std::cout << "7 - Kriterium: Vek podiel" << endl;
		std::cout << "8 - Kriterium: Vzdelanie pocet" << endl;
		std::cout << "9 - Kriterium: Vzdelanie podiel" << endl;
		std::cout << "v - Vypisanie informacii o UJ" << endl;
		std::cout << "q - Vratit sa spat" << endl;	//?????? ASI
		std::cout << "---------------------------------" << endl;
		std::cout << "Ak chces pridat/odobrat vsetky kriteria, stlac 'a'." << endl;
		key_press = _getch();
		if (key_press == 97)
		{
			this->pridatVsetkyKriteriaDoVyberu();
		}
		std::cout << "Vyber:\t";


		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		if (znak >= '0' && znak <= '9') {
			this->pridatKriteriumDoVyberu(znak);
		}
		else if (znak == 'v' || znak == 'V') {
			this->vypisInfoUJPodlaKriterii(this->vybranaUzemnaJednotka_);
		}
	} while (znak != 'q' && znak != 'Q');
}

void Data::pridatVsetkyKriteriaDoVyberu() {


	char key_press;
	bool nespravnyVstup = true;
	int minimalnyVek{};
	int maximalnyVek{};
	do
	{
		std::cout << "Ak chces pridat vsetky kriteria, stlac 'p'." << endl;
		std::cout << "Ak chces odobrat vsetky kriteria, stlac 'o'." << endl;
		key_press = _getch();
		if (key_press == 112 || key_press == 111) {
			nespravnyVstup = false;
		}
		else {
			std::cout << "Neznamy vyber, prosim skus znova" << endl;
		}
	} while (nespravnyVstup);
	
	if (key_press == 112) //p
	{
		
		this->vyberVekovuSkupinu();
		this->vyberPohlavie();
		int minimalnyVek = this->dajNapisanyVek(false);
		int maximalnyVek = this->dajNapisanyVek(true);
		

		this->vyberVzdelanie();

		for (int i = 0; i < aktivneKriteria_->size(); i++)
		{
			this->aktivneKriteria_->at(i) = true;
		}

		this->krtiteriumVekSkupinaPocet_->nastavKriterium(vybranaVekovaSkupina_);
		this->kriteriumVekPocet_->nastavKriterium(minimalnyVek,maximalnyVek, this->vybranePohlave_);
		this->kriteriumVzdelaniePocet_->nastavKriterium(vybraneVzdelanie_);
		std::cout << "Vsetky kriteria boli pridane!" << endl;

	} else if (key_press == 111) { //o 
		for (int i = 0; i < aktivneKriteria_->size(); i++)
		{
			this->aktivneKriteria_->at(i) = false;
		}
		std::cout << "Vsetky kriteria boli odobrane!" << endl;
	}

	std::cout << "Pridat kriterium, alebo vypisat informacie?" << endl;
	std::cout << "0 - Kriterium: Nazov" << endl;
	std::cout << "1 - Kriterium: Nadradena uzemna jednotka" << endl;
	std::cout << "2 - Kriterium: Prislusnost vo vyssom celku" << endl;
	std::cout << "3 - Kriterium: Typ uzemnej jednotky" << endl;
	std::cout << "4 - Kriterium: Ekonomicka vekova skupina pocet" << endl;
	std::cout << "5 - Kriterium: Ekonomicka vekova skupina podiel" << endl;
	std::cout << "6 - Kriterium: Vek pocet" << endl;
	std::cout << "7 - Kriterium: Vek podiel" << endl;
	std::cout << "8 - Kriterium: Vzdelanie pocet" << endl;
	std::cout << "9 - Kriterium: Vzdelanie podiel" << endl;
	std::cout << "v - Vypisanie informacii o UJ" << endl;
	std::cout << "q - Vratit sa spat" << endl;	
	std::cout << "---------------------------------" << endl;



}

void Data::pridatKriteriumDoVyberu(char znak) {
	//SAFE VSTUP, osetrene
	int vyber = (int(znak)) - 48; // 48 je v ASCII a
	bool& vybraneKriterium = this->aktivneKriteria_->at(vyber);
	switch (znak)
	{
	case '0':
		std::cout << "Kriterium: Nazov ";
		break;
	case'1': 	
		std::cout << "Kriterium: Nadradena uzemna jednotka ";
		break;
	case'2': 
		std::cout << "Kriterium: Prislusnost vo vyssom celku ";
		break;
	case'3':
		std::cout << "Kriterium: Typ uzemnej jednotky ";
		break;
	case'4':
		this->vyberVekovuSkupinu();
		std::cout << "Kriterium: Ekonomicka vekova skupina pocet ";
		if (vybraneKriterium)
			this->vybranaVekovaSkupina_ = NULL_ENUM_VEKOVA_SKUPINA;
		else
			this->krtiteriumVekSkupinaPocet_->nastavKriterium(vybranaVekovaSkupina_);
		break;
	case'5':
		this->vyberVekovuSkupinu();
		std::cout << "Kriterium: Ekonomicka vekova skupina podiel ";
		if (vybraneKriterium)
			this->vybranaVekovaSkupina_ = NULL_ENUM_VEKOVA_SKUPINA;
		else
			this->krtiteriumVekSkupinaPocet_->nastavKriterium(vybranaVekovaSkupina_);
		break;
	case'6': 
	{
		this->vyberPohlavie();
		int minimalnyVek = this->dajNapisanyVek(false);
		int maximalnyVek = this->dajNapisanyVek(true);
		bool nespravnyVstup = true;


		std::cout << "Kriterium: Vek pocet ";
		if (vybraneKriterium)
			this->vybranePohlave_ = NULL_ENUM_POHLAVE;
		else
			this->kriteriumVekPocet_->nastavKriterium(minimalnyVek,maximalnyVek,this->vybranePohlave_);
		break;
	}
	case'7':
	{
		this->vyberPohlavie();
		bool nespravnyVstup = true;
		int minimalnyVek = this->dajNapisanyVek(false);
		int maximalnyVek = this->dajNapisanyVek(true);

		std::cout << "Kriterium: Vek podiel ";
		if (vybraneKriterium)
			this->vybranePohlave_ = NULL_ENUM_POHLAVE;
		else
			this->kriteriumVekPodiel_->nastavKriterium(minimalnyVek,maximalnyVek, this->vybranePohlave_);
		break;
	}
	case '8':
	{
		this->vyberVzdelanie();

		std::cout << "Kriterium: Vzdelanie pocet ";
		if (vybraneKriterium) 
			this->vybraneVzdelanie_ = NULL_ENUM_VZDELANIE;
		else 
			this->kriteriumVzdelaniePocet_->nastavKriterium(vybraneVzdelanie_);
		break;
	}
	case'9':
	{
		this->vyberVzdelanie();

		std::cout << "Kriterium: Vzdelanie podiel ";
		if (vybraneKriterium)
			this->vybraneVzdelanie_ = NULL_ENUM_VZDELANIE;
		else
			this->kriteriumVzdelaniePodiel_->nastavKriterium(vybraneVzdelanie_);
		break;
	}
	default:
		std::cout << "SPADLO DO DEFAULTU: Data::pridatKriteriumDoVyberu(char znak) " << endl;
		break;
	}

	if (vybraneKriterium) {
		vybraneKriterium = false;
		std::cout << "bolo odobrane" << endl;
	}
	else {
		vybraneKriterium = true;
		std::cout << "bolo pridane" << endl;
	}




}

void Data::vyberVzdelanie() {
	bool opakuj = false;
	do {
		opakuj = false;
		std::cout << std::endl;
		std::cout << "Vyber vzdelanie:" << endl;
		std::cout << "1 - Bez ukonceneho vzdelania - osoby vo veku 0-14 rokov" << std::endl;
		std::cout << "2 - Zakladne vzdelanie" << std::endl;
		std::cout << "3 - Stredne odborne (ucnovske) vzdelanie (bez maturity)" << std::endl;
		std::cout << "4 - Uplne stredne vzdelanie (s maturitou)" << std::endl;
		std::cout << "5 - Vyssie odborne vzdelanie" << std::endl;
		std::cout << "6 - Vysokoskolske vzdelanie" << std::endl;
		std::cout << "7 - Bez skolskeho vzdelania - osoby vo veku 15 rokov a viac" << std::endl;
		std::cout << "8 - Nezistene" << std::endl;
		std::cout << "Vyber:\t";

	
		string line{};
		char znak{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		switch (znak)
		{
		case '1':
			this->vybraneVzdelanie_ = BEZ_UKONCENEHO_VZDELANIA_0_14_ROKOV;
			break;
		case '2':
			this->vybraneVzdelanie_ = ZAKLADNE_VZDELANIE;
			break;
		case '3':
			this->vybraneVzdelanie_ = STREDNE_ODBORNE_VZDELANIE;
			break;
		case '4':
			this->vybraneVzdelanie_ = UPLNE_STREDNE_VZDELANIE;
			break;
		case '5':
			this->vybraneVzdelanie_ = VYSSIE_ODBORNE_VZDELANIE;
			break;
		case '6':
			this->vybraneVzdelanie_ = VYSOKOSKOLSKE_VZDELANIE;
			break;
		case '7':
			this->vybraneVzdelanie_ = BEZ_SKOLSKEHO_VZDELANIA_15_A_VIAC_ROKOV;
			break;
		case '8':
			this->vybraneVzdelanie_ = NEZISTENE;
			break;
		default:
			this->vybraneVzdelanie_ = NULL_ENUM_VZDELANIE;
			opakuj = true;
			std::cout << "Neznamy vyber, prosim skus znova!" << endl;
			break;
		}
	} while (opakuj);
}

EnumVzdelanie Data::vratEnumVybraneVzdelanie()
{
	bool opakuj = false;
	do {
		opakuj = false;
		std::cout << std::endl;
		std::cout << "Vyber vzdelanie:" << endl;
		std::cout << "1 - Bez ukonceneho vzdelania - osoby vo veku 0-14 rokov" << std::endl;
		std::cout << "2 - Zakladne vzdelanie" << std::endl;
		std::cout << "3 - Stredne odborne (ucnovske) vzdelanie (bez maturity)" << std::endl;
		std::cout << "4 - Uplne stredne vzdelanie (s maturitou)" << std::endl;
		std::cout << "5 - Vyssie odborne vzdelanie" << std::endl;
		std::cout << "6 - Vysokoskolske vzdelanie" << std::endl;
		std::cout << "7 - Bez skolskeho vzdelania - osoby vo veku 15 rokov a viac" << std::endl;
		std::cout << "8 - Nezistene" << std::endl;
		std::cout << "Vyber:\t";


		string line{};
		char znak{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		switch (znak)
		{
		case '1':
			return BEZ_UKONCENEHO_VZDELANIA_0_14_ROKOV;
			break;
		case '2':
			return ZAKLADNE_VZDELANIE;
			break;
		case '3':
			return STREDNE_ODBORNE_VZDELANIE;
			break;
		case '4':
			return UPLNE_STREDNE_VZDELANIE;
			break;
		case '5':
			return VYSSIE_ODBORNE_VZDELANIE;
			break;
		case '6':
			return VYSOKOSKOLSKE_VZDELANIE;
			break;
		case '7':
			return BEZ_SKOLSKEHO_VZDELANIA_15_A_VIAC_ROKOV;
			break;
		case '8':
			return NEZISTENE;
			break;
		default:
			return NULL_ENUM_VZDELANIE;
			opakuj = true;
			std::cout << "Neznamy vyber, prosim skus znova!" << endl;
			break;
		}
	} while (opakuj);
}

void Data::vyberVekovuSkupinu() {
	bool opakuj = false;
	do {
		opakuj = false;
		std::cout << std::endl;
		std::cout << "Vyber ekonomicku vekovu skupinu" << endl;
		std::cout << "1 - Predproduktivni: 0-14 rokov" << std::endl;
		std::cout << "2 - Produktivni: 15-64 rokov" << std::endl;
		std::cout << "3 - Poproduktivni: 65-100+ rokov" << std::endl;
		std::cout << "Vyber:\t";

		string line{};
		char znak{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		switch (znak)
		{
		case '1':
			this->vybranaVekovaSkupina_ = PREDPRODUKTIVNI;
			break;
		case '2':
			this->vybranaVekovaSkupina_ = PRODUKTIVNI;
			break;
		case '3':
			this->vybranaVekovaSkupina_ = POPRODUKTIVNI;
			break;
		default:
			this->vybranaVekovaSkupina_ = NULL_ENUM_VEKOVA_SKUPINA;
			opakuj = true;
			std::cout << "Neznamy vyber, prosim skus znova!" << endl;
			break;
		}
	} while (opakuj);

}

EnumVekovaSkupina Data::vratEnumVekovuSkupinu()
{
	bool opakuj = false;
	do {
		opakuj = false;
		std::cout << std::endl;
		std::cout << "Vyber ekonomicku vekovu skupinu" << endl;
		std::cout << "1 - Predproduktivni: 0-14 rokov" << std::endl;
		std::cout << "2 - Produktivni: 15-64 rokov" << std::endl;
		std::cout << "3 - Poproduktivni: 65-100+ rokov" << std::endl;
		std::cout << "Vyber:\t";

		string line{};
		char znak{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		switch (znak)
		{
		case '1':
			return PREDPRODUKTIVNI;
			break;
		case '2':
			return PRODUKTIVNI;
			break;
		case '3':
			return POPRODUKTIVNI;
			break;
		default:
			return NULL_ENUM_VEKOVA_SKUPINA;
			opakuj = true;
			std::cout << "Neznamy vyber, prosim skus znova!" << endl;
			break;
		}
	} while (opakuj);
}

void Data::vyberPohlavie() {
	bool opakuj = false;
	do {
		opakuj = false;
		std::cout << std::endl;
		std::cout << "Vyber pohlavie" << endl;
		std::cout << "1 - Zena" << std::endl;
		std::cout << "2 - Muz" << std::endl;
		std::cout << "3 - Obidve pohlavia" << std::endl;
		std::cout << "Vyber:\t";

		string line{};
		char znak{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		switch (znak)
		{
		case '1':
			this->vybranePohlave_ = ZENA;
			break;
		case '2':
			this->vybranePohlave_ = MUZ;
			break;
		case '3':
			this->vybranePohlave_ = OBIDVE_POHLAVIA;
			break;
		default:
			this->vybranePohlave_ = NULL_ENUM_POHLAVE;
			opakuj = true;
			std::cout << "Neznamy vyber, prosim skus znova!" << endl;
			break;
		}
	} while (opakuj);

}

EnumPohlavie Data::vratEnumPohlavie()
{
	bool opakuj = false;
	do {
		opakuj = false;
		std::cout << std::endl;
		std::cout << "Vyber pohlavie" << endl;
		std::cout << "1 - Zena" << std::endl;
		std::cout << "2 - Muz" << std::endl;
		std::cout << "3 - Obidve pohlavia" << std::endl;
		std::cout << "Vyber:\t";

		string line{};
		char znak{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		switch (znak)
		{
		case '1':
			return ZENA;
			break;
		case '2':
			return MUZ;
			break;
		case '3':
			return OBIDVE_POHLAVIA;
			break;
		default:
			return NULL_ENUM_POHLAVE;
			opakuj = true;
			std::cout << "Neznamy vyber, prosim skus znova!" << endl;
			break;
		}
	} while (opakuj);
}

void Data::vypisInfoUJPodlaKriterii(UzemnaJednotka* uzemnaJednotka) {
	int width = 55;
	for (int i = 0; i < aktivneKriteria_->size(); i++)
	{
		if (aktivneKriteria_->at(i)) {
			switch (i) {
			case 0:
				std::cout << setw(width) << "Nazov uzemnej jednotky: " << kriteriumNazov_->urobKriterium(uzemnaJednotka) << endl;
				break;
			case 1:
				std::cout << setw(width) << "Nadradena uzemna jednotka: "; {
					if (kriteriumNadradena_->urobKriterium(uzemnaJednotka) == nullptr) {
						std::cout << "Slovensko";
					}
					else {
						std::cout << kriteriumNadradena_->urobKriterium(uzemnaJednotka)->getNazov();
					}
					std::cout << endl;

				}
				break;
			case 2:
				std::cout << setw(width) << "Prislusnost vo vyssom celku: ";
				if (kriteriumPrislusnost_->urobKriterium(uzemnaJednotka)) 
					std::cout << "Ano";
				else
					std::cout << "Nie";
				std::cout << endl;
				break;
			case 3:
				std::cout << setw(width) << "Typ uzemnej jednotky: " << this->enumTypUJtoString(kriteriumTyp_->urobKriterium(uzemnaJednotka)) << endl;
				break;
			case 4:
				std::cout << setw(width) << ("EVS: " + this->enumEVStoString(this->vybranaVekovaSkupina_)) << endl;
				std::cout << setw(width) << "Ekonomicka vekova skupina pocet: " << krtiteriumVekSkupinaPocet_->urobKriterium(uzemnaJednotka) << endl;
				break;
			case 5:
				std::cout << setw(width) << ("EVS: " + this->enumEVStoString(this->vybranaVekovaSkupina_)) << endl;
				std::cout << setw(width) << "Ekonomicka vekova skupina podiel: " << kriteriumVekSkupinaPodiel_->urobKriterium(uzemnaJednotka) << endl;
				break;
			case 6:
				std::cout << setw(width) << ("POHLAVIE: " + this->enumPohlavieToString(this->vybranePohlave_)) << endl;
				std::cout << setw(width) << "Dany vek - pocet ludi: " << kriteriumVekPocet_->urobKriterium(uzemnaJednotka) << endl;
				break;
			case 7:
				std::cout << setw(width) << ("POHLAVIE: " + this->enumPohlavieToString(this->vybranePohlave_)) << endl;
				std::cout << setw(width) << "Dany vek - podiel ludi: " << kriteriumVekPodiel_->urobKriterium(uzemnaJednotka) << endl;
				break;
			case 8:
				std::cout << setw(width) << ("VZDELANIE SKUPINA: " + this->enumVzdelanieToString(this->vybraneVzdelanie_)) << endl;
				std::cout << setw(width) << "Pocet: " << kriteriumVzdelaniePocet_->urobKriterium(uzemnaJednotka) << endl;
				break;
			case 9:
				std::cout << setw(width) << ("VZDELANIE SKUPINA: " + this->enumVzdelanieToString(this->vybraneVzdelanie_)) << endl;
				std::cout << setw(width) << "Podiel: " << kriteriumVzdelaniePodiel_->urobKriterium(uzemnaJednotka) << endl;
				break;
			default:
				break;
			}
		}


	}
	for (int i = 0; i < aktivneKriteria_->size(); i++)
	{
		this->aktivneKriteria_->at(i) = false;
	}


	std::cout << "--------------------------------" << endl;
	std::cout << endl;
}

void Data::vypisMnozinuSAktivnymKriterium() {
	int width = 55;

	std::cout << setw(width) << "Nazov uzemnej jednotky";
	for (int i = 0; i < aktivneKriteria_->size(); i++)
	{

		//NADPIS
		if (aktivneKriteria_->at(i)) {
			switch (i) {
			case 0:
				std::cout << setw(width) << "Nazov";
				break;
			case 1:
				std::cout << setw(width) << "Nadradena UJ";
				break;
			case 2:
				std::cout << setw(20) << "Prislusnost-Vyssi celok";
				break;
			case 3:
				std::cout << setw(15) << "Typ UJ";
				break;
			case 4:
				std::cout << setw(20) << "EVS - pocet";
				break;
			case 5:
				std::cout << setw(20) << "EVS - podiel";
				break;
			case 6:
				std::cout << setw(20) << "Vek pocet";
				break;
			case 7:
				std::cout << setw(20) << "Vek podiel";
				break;
			case 8:
				std::cout << setw(25) << "Vzdelanie pocet";
				break;
			case 9:
				std::cout << setw(25) << "Vzdelanie podiel";
				break;
			default:
				break;
			}
		}

	}
	std::cout << endl;


	//VYPISANIE VYSLEDKOV
	for (structures::TableItem<std::string, UzemnaJednotka*>* item : *this->vybranaMnozina_) {
		std::cout << setw(width) << item->accessData()->getNazov();
		for (int i = 0; i < aktivneKriteria_->size(); i++)
		{
			if (aktivneKriteria_->at(i)) {
				switch (i) {
				case 0:
					std::cout << setw(width) << item->accessData()->getNazov();
					break;
				case 1:
					std::cout << setw(width) << this->kriteriumNadradena_->urobKriterium(item->accessData())->getNazov();
					std::cout << setw(width); {
						if (kriteriumNadradena_->urobKriterium(item->accessData()) == nullptr) {
							std::cout << "Slovensko";
						}
						else {
							std::cout << kriteriumNadradena_->urobKriterium(item->accessData())->getNazov();
						}
						std::cout << endl;

					}

					break;
				case 2:
					if (kriteriumPrislusnost_->urobKriterium(item->accessData())) {
						std::cout << setw(20) << "Ano";
					}
					else {
						std::cout << setw(20) << "Nie";
					}
					std::cout << endl;
					break;
				case 3:
					std::cout << setw(15) << this->enumTypUJtoString(kriteriumTyp_->urobKriterium(item->accessData()));
					break;
				case 4:
					std::cout << setw(20) << krtiteriumVekSkupinaPocet_->urobKriterium(item->accessData());
					break;
				case 5:
					std::cout << setw(20) << kriteriumVekSkupinaPodiel_->urobKriterium(item->accessData());
					break;
				case 6:
					std::cout << setw(20) << kriteriumVekPocet_->urobKriterium(item->accessData());
					break;
				case 7:
					std::cout << setw(20) << kriteriumVekPodiel_->urobKriterium(item->accessData());
					break;
				case 8:
					std::cout << setw(25) << kriteriumVzdelaniePocet_->urobKriterium(item->accessData());
					break;
				case 9:
					std::cout << setw(25) << kriteriumVzdelaniePodiel_->urobKriterium(item->accessData());
					break;
				default:
					break;
				}
			}

		}

		std::cout << endl;
	}

	for (int i = 0; i < aktivneKriteria_->size(); i++)
	{
		this->aktivneKriteria_->at(i) = false;
	}


	std::cout << "--------------------------------" << endl;
	std::cout << endl;
}
void Data::vypisInfoUJPodlaFiltrov() {
	int width = 55;

	std::cout << setw(width) << "Nazov uzemnej jednotky";
	for (int i = 0; i < aktivneFiltre_->size(); i++)
	{
		
		//NADPIS
		if (aktivneFiltre_->at(i)) {
			switch (i) {
			case 0:
				std::cout << setw(25) << "Prislusnost-Vyssi celok";
				break;
			case 1:
				std::cout << setw(25) << "Typ uzemnej jednotky";
				break;
			case 2:
				std::cout << setw(20) << "EVS pocet ludi";
				break;
			case 3:
				std::cout << setw(20) << "EVS podiel ludi";
				break;
			case 4:
				std::cout << setw(25) << "Dany vek - pocet ludi";
				break;
			case 5:
				std::cout << setw(25) << "Dany vek - podiel ludi";
				break;
			case 6:
				std::cout << setw(30) << "Dane vzdelanie - pocet ludi";
				break;
			case 7:
				std::cout << setw(30) << "Dane vzdelanie - podiel ludi";
				break;
			default:
				break;
			}
		}
		
	}
	std::cout << endl;


	//VYPISANIE VYSLEDKOV
	for (structures::TableItem<std::string, UzemnaJednotka*>* item : *this->vyfiltrovanaMnozina_) {
		std::cout << setw(width) << item->accessData()->getNazov();
		for (int i = 0; i < aktivneFiltre_->size(); i++)
		{
			if (aktivneFiltre_->at(i)) {
				switch (i) {
				case 0:
					if (kriteriumPrislusnost_->urobKriterium(item->accessData())) {
						std::cout << setw(25) << "Ano";
					}
					else {
						std::cout << setw(25) << "Nie";
					}
					std::cout << endl;
					break;
				case 1:
					std::cout << setw(25) << this->enumTypUJtoString(kriteriumTyp_->urobKriterium(item->accessData()));
					break;
				case 2:
					std::cout << setw(20) << krtiteriumVekSkupinaPocet_->urobKriterium(item->accessData());
					break;
				case 3:
					std::cout << setw(20) << kriteriumVekSkupinaPodiel_->urobKriterium(item->accessData());
					break;
				case 4:
					std::cout << setw(25) << kriteriumVekPocet_->urobKriterium(item->accessData());
					break;
				case 5:
					std::cout << setw(25) << kriteriumVekPodiel_->urobKriterium(item->accessData());
					break;
				case 6:
					std::cout << setw(30) << kriteriumVzdelaniePocet_->urobKriterium(item->accessData());
					break;
				case 7:
					std::cout << setw(30) << kriteriumVzdelaniePodiel_->urobKriterium(item->accessData());
					break;
				default:
					break;
				}
			}

			
		}

		std::cout << endl;
	}

	for (int i = 0; i < aktivneFiltre_->size(); i++)
	{
		this->aktivneFiltre_->at(i) = false;
	}

	

	if (filterANDZvoleny_) {
		this->filterAND_->vynulujFiltre();
	} 

	if (filterORZvoleny_) {
		this->filterOR_->vynulujFiltre();
	}
	
	this->vyfiltrovanaMnozina_->clear();
	delete this->vyfiltrovanaMnozina_;
	this->vyfiltrovanaMnozina_ = nullptr;

	std::cout << "--------------------------------" << endl;
	std::cout << endl;
}

void Data::pridajObec(Obec* obec)
{
	this->obceVsetky_->insert(obec->getNazov(), obec);
}

void Data::pridajOkres(Okres* okres)
{
	this->okresyVsetky_->insert(okres->getNazov(),okres);
}

void Data::pridajKraj(Kraj* kraj)
{
	this->krajeVsetky_->insert(kraj->getNazov(), kraj);
}

void Data::vypisObce()
{
	int fieldWith = 45;
	std::cout << "ZOZNAM OBCI:" << std::endl << endl;;
	int counter = 0;
	for (structures::TableItem<std::string, UzemnaJednotka*>* obec : *this->obceVsetky_) {
		std::cout << std::setw(fieldWith) << left << obec->getKey();

		counter++;

		if (counter == 3) {
			std::cout << endl;
			counter = 0;
		}
	}
	std::cout << endl << endl;
}


void Data::vypisOkresy()
{
	int fieldWith = 45;
	std::cout << "ZOZNAM OKRESOV:" << std::endl << endl;;
	int counter = 0;
	for (structures::TableItem<std::string, UzemnaJednotka*>* obec : *this->okresyVsetky_) {
		std::cout << std::setw(fieldWith) << left << obec->getKey();

		counter++;

		if (counter == 3) {
			std::cout << endl;
			counter = 0;
		}
	}
	std::cout << endl << endl;
}

void Data::vypisUnsortedOkresy()
{
	std::cout << "--------------OKRESY UNSORTED-----------------" << std::endl;
	for (structures::TableItem<std::string, UzemnaJednotka*>* okres : *this->okresyUnsortedCode_) {
		std::cout << "\t" << okres->accessData()->getNazov() << " - " << okres->accessData()->getPocetVzdelanie(NEZISTENE) << std::endl;
	}
	std::cout << std::endl;
}

void Data::vypisKraje()
{
	int fieldWith = 45;
	std::cout << "ZOZNAM KRAJOV:" << std::endl << endl;;
	int counter = 0;
	for (structures::TableItem<std::string, UzemnaJednotka*>* obec : *this->krajeVsetky_) {
		std::cout << std::setw(fieldWith) << left << obec->getKey() << endl;

	}
	std::cout << endl;
}

void Data::pridajVsetkyObce()
{
	ifstream filename;
	filename.open("vek.csv");
	if (filename.good())
	{
		string line;
		getline(filename, line);
		stringstream s(line);
	}

	int counter;

	if (filename.good())
	{
		string line;
		std::string codeObce;
		std::string nazovObce;
		std::string okresCode;
		int counterArray = 0;
		while (getline(filename, line)) {   // get a whole line
			std::stringstream ss(line);
			counter = 0;
			Obec* novaObec = nullptr;

			while (getline(ss, line, ';')) {
				if (counter == 0)
					codeObce = line;
				else if (counter == 1) {
					nazovObce = line;
					novaObec = new Obec(nazovObce, codeObce); //vytvori sa nova Obec
					
				}					
				else if (counter >= 2 && counter <= 102) {
					int pozicia = counter - 2;
					novaObec->pridajVek(pozicia, stoi(line));
				}
				else if (counter >= 103 && counter <= 203) {
					int pozicia = counter - 2;
					novaObec->pridajVek(pozicia, stoi(line));
				}
				else if (counter >= 204) {
					int pozicia = counter - 204;
					novaObec->pridajVzdelanie(pozicia, stoi(line));
				}

				counter++;
			}
			novaObec->spocitajObyvatelov();
			this->pridajObec(novaObec);
			this->obceUnsortedCode_->insert(novaObec->getCode(), novaObec);
			counterArray++;
		}
	}
}

void Data::pridajVsetkyOkresy()
{
	ifstream filename;
	filename.open("okresy.csv");
	if (filename.good())
	{
		string line;
		getline(filename, line);
		stringstream s(line);
	}

	int counter;

	if (filename.good())
	{
		string line;
		std::string okresCode;
		std::string mediumTitle;
		int counterArray = 0;
		while (getline(filename, line)) {   // get a whole line
			std::stringstream ss(line);
			counter = 0;
			Okres* novyOkres = nullptr;
			while (getline(ss, line, ';')) {
				// You now have separate entites here
				switch (counter)
				{
				case 1:
					//cout << "code " << line << endl;
					okresCode = line;
					break;
				case 3:
					//cout << "shortTitle " << line << endl;
					mediumTitle = line;
					novyOkres = new Okres(mediumTitle, okresCode);
					break;
				default:
					break;
				}
				
				counter++;
			}
			this->pridajOkres(novyOkres);
			this->okresyUnsortedCode_->insert(novyOkres->getCode(), novyOkres);
			counterArray++;
		}
	}
}

void Data::pridajVsetkyKraje()
{
	ifstream filename;
	filename.open("kraje.csv");
	if (filename.good())
	{
		string line;
		getline(filename, line);
		stringstream s(line);
	}

	int counter;

	if (filename.good())
	{
		string line;
		std::string code;
		std::string shortTitle;
		while (getline(filename, line)) {   // get a whole line
			std::stringstream ss(line);
			counter = 0;
			Kraj* novyKraj = nullptr;
			while (getline(ss, line, ';')) {
				// You now have separate entites here
				switch (counter)
				{
				case 4:
					shortTitle = line;
					break;
				case 5:
					code = line.substr(5, 5);
					novyKraj = new Kraj(shortTitle, code);
					break;
				default:
					break;
				}

				counter++;
			}
			
			this->pridajKraj(novyKraj);
			this->krajeUnsortedCode_->insert(novyKraj->getCode(), novyKraj);
		}
	}
}

void Data::pracaSVybranouMnozinou() {
	string line{};
	char znak{};

	do {


		std::cout << "\nCo chces robit?" << endl;
		std::cout << "0 - Filtrovat" << endl;
		std::cout << "1 - Zoradit" << endl;
		std::cout << "2 - Zoradit a filtrovat" << endl;
		std::cout << "3 - Najst UJ s najmensou ekonomickou vekovu skupinu" << endl;
		std::cout << "4 - Najst UJ s najvacsou ekonomickou vekovu skupinu" << endl;
		std::cout << "q - Vratit sa spat" << endl;	
		std::cout << "---------------------------------" << endl;
		std::cout << "Vyber:\t";
	
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		switch (znak)
		{
		case '0':
			this->vyberOR_ANDFiltra();
			this->pridanieFiltrov();
			break;
		case '1':
		{
			this->zoraditCezKriteriumMenu();
			break;
		}
		case '2':
			this->vyberOR_ANDFiltra();
			this->filtrovanieAZoradenie();
			break;
		case '3':
			this->vyberVekovuSkupinu();
			this->vyberNajmensiaVekSkupina_->nastavVekSkupinu(this->vybranaVekovaSkupina_);
			this->vypisTypNazovNadJednotiek(this->vyberNajmensiaVekSkupina_->vyberNajelspieho(this->vybranaMnozina_));
			break;
	
		case '4':
			this->vyberVekovuSkupinu();
			this->vyberNajvacsiaVekSkupina_->nastavVekSkupinu(this->vybranaVekovaSkupina_);
			this->vypisTypNazovNadJednotiek(this->vyberNajvacsiaVekSkupina_->vyberNajelspieho(this->vybranaMnozina_));
			break;
		case 'q':
		case 'Q':
			break;
		default:
			std::cout << "Neznamy vyber, prosim skus znova!" << endl;
			break;
		}
	} while (znak != 'q' && znak != 'Q');
}

void Data::vypisTypNazovNadJednotiek(UzemnaJednotka* uj) {
	int width = 55;
	UzemnaJednotka* ujNad;
	UzemnaJednotka* ujNadNad;

	cout << setw(10) << "UJ Typ" << setw(width) << "Nazov" << endl;
	cout << setw(10) << this->enumTypUJtoString(uj->getTyp()) << setw(width) << uj->getNazov() << endl;

	switch (uj->getTyp())
	{
	case OBEC:
		ujNad = uj->getNadJednotku();
		cout << setw(10) << this->enumTypUJtoString(ujNad->getTyp()) << setw(width) << ujNad->getNazov() << endl;
		ujNadNad = ujNad->getNadJednotku();
		cout << setw(10) << this->enumTypUJtoString(ujNadNad->getTyp()) << setw(width) << ujNadNad->getNazov() << endl;
		break;

	case OKRES:
		ujNad = uj->getNadJednotku();
		cout << setw(10) << this->enumTypUJtoString(ujNad->getTyp()) << setw(width) << ujNad->getNazov() << endl;
	case KRAJ:
		break;
	case NULL_ENUM_UJ:
		break;
	default:
		break;
	}
}

void Data::zoraditCezKriteriumMenu() {
	string line{};
	char znak{};
	bool nespravnyVyber = true;

	do {


		std::cout << "Pouzit kriterium, na zoredenie" << endl;
		std::cout << "0 - Kriterium: Nazov" << endl;
		std::cout << "1 - Kriterium: Ekonomicka vekova skupina pocet" << endl;
		std::cout << "2 - Kriterium: Vek podiel" << endl;
		std::cout << "3 - Kriterium: Vzdelanie pocet" << endl;
		std::cout << "4 - Kriterium: Vzdelanie podiel" << endl;
		std::cout << "q - Vratit sa spat" << endl;	
		std::cout << "---------------------------------" << endl;
		std::cout << "Vyber:\t";
		do {
			getline(cin, line);
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			znak = line[0];

			switch (znak)
			{
			case '0':
				this->pridatKriteriumDoVyberu(znak);
				zoraditCezAktivneKriterium();
				vypisMnozinuSAktivnymKriterium();
				nespravnyVyber = false;
				break;
			case '1':
			{
				znak = '4';
				this->pridatKriteriumDoVyberu(znak);
				std::cout << "******************************************" << std::endl;
				std::cout << "** Prosim este raz zadaj tie iste udaje **" << std::endl;
				std::cout << "******************************************" << std::endl;
				this->pridatKriteriumDoVyberu('5');
				this->aktivneFiltre_->at(5) = false;
				zoraditCezAktivneKriterium();
				this->aktivneFiltre_->at(5) = true;
				vypisMnozinuSAktivnymKriterium();
				nespravnyVyber = false;
				break;
			}
			case '2':
				znak = '7';
				this->pridatKriteriumDoVyberu(znak);
				std::cout << "******************************************" << std::endl;
				std::cout << "** Prosim este raz zadaj tie iste udaje **" << std::endl;
				std::cout << "******************************************" << std::endl;
				this->pridatKriteriumDoVyberu('6');
				this->aktivneKriteria_->at(6) = false;
				zoraditCezAktivneKriterium();
				this->aktivneKriteria_->at(6) = true;
				vypisMnozinuSAktivnymKriterium();
				nespravnyVyber = false;
				break;
			case '3':
				znak = '8';
				this->pridatKriteriumDoVyberu(znak);
				zoraditCezAktivneKriterium();
				
				vypisMnozinuSAktivnymKriterium();
				nespravnyVyber = false;
				break;
			case '4':
				znak = '9';
				this->pridatKriteriumDoVyberu(znak);
				zoraditCezAktivneKriterium();
				vypisMnozinuSAktivnymKriterium();
				nespravnyVyber = false;
				break;
			case'q':
			case'Q':
				nespravnyVyber = false;
				break;
			default:
				std::cout << "Neznamy vyber, prosim skus znova!" << endl;
				break;
			}
		} while (nespravnyVyber);
		
	} while (znak != 'q' && znak != 'Q');
}

void Data::zoraditCezAktivneKriterium() {
	bool nespravnyVstup = true;
	char key_press;
	bool vzostupne;
	
	do {
		std::cout << "\nAk chces triedit vzostupne, stlac sipku hore" << endl;
		std::cout << "Ak chces tried zostupne, stlac sipku dole" << endl;
		key_press = _getch();
		if (key_press == 72) {
			vzostupne = true;
			nespravnyVstup = false;
		}
		else if (key_press == 80) {
			vzostupne = false;
			nespravnyVstup = false;
		}
		else {
			std::cout << "Stlacil si nespravne tlacidlo, skus znova!" << endl;
		}
	} while (nespravnyVstup);


	for (int i = 0; i < this->aktivneKriteria_->size(); i++)
	{
		if (this->aktivneKriteria_->at(i)) {
			if (i == 0) {
				QuickSort<std::string, UzemnaJednotka*, std::string>* quickSortNazov = new QuickSort<std::string, UzemnaJednotka*, std::string>();
				quickSortNazov->utriedCezKriterium(*(this->vybranaMnozina_), *(this->kriteriumNazov_), vzostupne);
				delete quickSortNazov;
			}
			else if (i == 4) {
				QuickSort<std::string, UzemnaJednotka*, int>* quickSortVekSkupPocet = new QuickSort<std::string, UzemnaJednotka*, int>();
				quickSortVekSkupPocet->utriedCezKriterium(*(this->vybranaMnozina_), *(this->krtiteriumVekSkupinaPocet_), vzostupne);
				delete quickSortVekSkupPocet;
			}
			else if (i == 7) {
				QuickSort<std::string, UzemnaJednotka*, double>* quickSortVekPodiel = new QuickSort<std::string, UzemnaJednotka*, double>();
				quickSortVekPodiel->utriedCezKriterium(*(this->vybranaMnozina_), *(this->kriteriumVekPodiel_), vzostupne);
				delete quickSortVekPodiel;
			}
			else if (i == 8) {
				QuickSort<std::string, UzemnaJednotka*, int>* quickSortVzdelaniePocet = new QuickSort<std::string, UzemnaJednotka*, int>();
				quickSortVzdelaniePocet->utriedCezKriterium(*(this->vybranaMnozina_), *(this->kriteriumVzdelaniePocet_), vzostupne);
				delete quickSortVzdelaniePocet;
			}
			else if (i == 9) {
				QuickSort<std::string, UzemnaJednotka*, double>* quickSortVzdelaniePodiel = new QuickSort<std::string, UzemnaJednotka*, double>();
				quickSortVzdelaniePodiel->utriedCezKriterium(*(this->vybranaMnozina_), *(this->kriteriumVzdelaniePodiel_), vzostupne);
				delete quickSortVzdelaniePodiel;
			}

		}
	}
}

void Data::filtrovanieAZoradenie() {
	string line{};
	char znak{};
	do
	{
		std::cout << "\nPridat/odobrat filter" << endl;
		std::cout << "0 - Filter: Prislusnost vo vyssom celku" << endl;
		std::cout << "1 - Filter: Typ uzemnej jednotky" << endl;
		std::cout << "2 - Filter: Ekonomicka vekova skupina pocet - interval" << endl;
		std::cout << "3 - Filter: Ekonomicka vekova skupina podiel - interval" << endl;
		std::cout << "4 - Filter: Vek pocet - interval" << endl;
		std::cout << "5 - Filter: Vek podiel - interval" << endl;
		std::cout << "6 - Filter: Vzdelanie pocet - interval" << endl;
		std::cout << "7 - Filter: Vzdelanie podiel - interval" << endl;
		std::cout << "z - Zoradit podla kriteria" << endl;
		std::cout << "q - Vratit sa spat" << endl;
		std::cout << "---------------------------------" << endl;
		std::cout << "Vyber:\t";

		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		if (znak >= '0' && znak <= '7') {
			this->pridatFilterDoVyberu(znak);
		}
		else if (znak == 'z' || znak == 'Z') {
			this->zaregistrujFiltre();
			if (this->filterANDZvoleny_) {
				this->vybranaMnozina_ = this->spravKopiuPodlaFiltra(this->vybranaMnozina_, this->filterAND_);
				this->zoraditCezKriteriumMenu();
			}
			else if (this->filterORZvoleny_) {
				this->vybranaMnozina_ = this->spravKopiuPodlaFiltra(this->vybranaMnozina_, this->filterOR_);
				this->zoraditCezKriteriumMenu();
			}

			this->vybranaMnozina_->clear();
			delete this->vybranaMnozina_;
			this->vybranaMnozina_ = nullptr;
		}

		else if (znak == 'q' || znak == 'q') {
			break;
		}

	} while (true);
}

void Data::pridanieFiltrov() {
	string line{};
	char znak{};
	do
	{
		std::cout << "\nPridat/odobrat filter" << endl;
		std::cout << "0 - Filter: Prislusnost vo vyssom celku" << endl;
		std::cout << "1 - Filter: Typ uzemnej jednotky" << endl;
		std::cout << "2 - Filter: Ekonomicka vekova skupina pocet - interval" << endl;
		std::cout << "3 - Filter: Ekonomicka vekova skupina podiel - interval" << endl;
		std::cout << "4 - Filter: Vek pocet - interval" << endl;
		std::cout << "5 - Filter: Vek podiel - interval" << endl;
		std::cout << "6 - Filter: Vzdelanie pocet - interval" << endl;
		std::cout << "7 - Filter: Vzdelanie podiel - interval" << endl;
		std::cout << "f - vyfiltrovat podla pridanych filtrov a vypisat informacie" << endl;
		std::cout << "q - Vratit sa spat" << endl;
		std::cout << "---------------------------------" << endl;
		std::cout << "Vyber:\t";

		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		if (znak >= '0' && znak <= '7') {
			this->pridatFilterDoVyberu(znak);
		}
		else if (znak == 'f' || znak == 'F') {
			std::cout << "\nFiltrovanie prebehlo uspesne" << endl;
			this->zaregistrujFiltre();
			if (this->filterANDZvoleny_) {
				this->vyfiltrovanaMnozina_ = this->spravKopiuPodlaFiltra(this->vybranaMnozina_, this->filterAND_);
				this->vypisInfoUJPodlaFiltrov(); 
			}
			else if (this->filterORZvoleny_) {
				this->vyfiltrovanaMnozina_ = this->spravKopiuPodlaFiltra(this->vybranaMnozina_, this->filterOR_);
				this->vypisInfoUJPodlaFiltrov(); 
			}
		}
			
		else if (znak == 'q' || znak == 'q') {
			break;
		}

	} while (true);



}

void Data::pridatFilterDoVyberu(char znak) {
	//SAFE VSTUP, osetrene
	int vyber = (int(znak)) - 48; // 48 je v ASCII a
	bool& vybranyFilter = this->aktivneFiltre_->at(vyber);
	char key_press;
	switch (znak)
	{
	case '0':
		if (vybranyFilter) {
			//// DO NOTHING
		}
		else {
			bool nespravnyVstup = true;
			do{
				std::cout << "\nAk chces vybrat uzemne jednotky z vyssieho celku, stlac 'a'" << endl;
				std::cout << "Ak chces vybrat uzemne jednotky z vyssieho celku, stlac 'n'" << endl;
				key_press = _getch();
				if (key_press == 97) {
					this->filterPrislusnost_->nastavHodnotuFiltru(true);
					nespravnyVstup = false;
				}
				else if (key_press == 110) {
					this->filterPrislusnost_->nastavHodnotuFiltru(false);
					nespravnyVstup = false;
				}
				else {
					std::cout << "Stlacil si nespravne tlacidlo, skus znova!" << endl;
				}
			} while (nespravnyVstup);
		}
		std::cout << "Filter: Prislusnost vo vyssom celku ";
		break;
	case'1':
		if (vybranyFilter) {
			this->vybranyTypUJ_ = NULL_ENUM_UJ;
		}
		else {
			this->vyberEnumUJ();
			this->filterTyp_->nastavHodnotuFiltru(this->vybranyTypUJFilter_);
		}
		std::cout << "Filter: Typ uzemnej jednotky ";
		break;
	case'2':
		if (vybranyFilter) {
			this->enumVekSkupPocet_ = NULL_ENUM_VEKOVA_SKUPINA;
		}
		else {
			this-> enumVekSkupPocet_ = this->vratEnumVekovuSkupinu();
			this->krtiteriumVekSkupinaPocet_->nastavKriterium(this->enumVekSkupPocet_);
			this->filterVekSkupPocet_->nastavVekovuSkupinu(this->enumVekSkupPocet_);
			std::cout << "\nZadaj obmedzujuci interval pre pocet ludi v danej vekovej skupine:" << endl;
			this->filterVekSkupPocet_->nastavHodnotuFiltru(dajMinIntHodnotuPreFilter(), dajMaxIntHodnotuPreFilter());
			
		}
		std::cout << "Filter: Ekonomicka vekova skupina pocet ";
		break;
	case'3':
		if (vybranyFilter) {
			this->enumVekSkupPodiel_ = NULL_ENUM_VEKOVA_SKUPINA;
		}
		else {
			this->enumVekSkupPodiel_ = this->vratEnumVekovuSkupinu();
			std::cout << "\nZadaj obmedzujuci interval pre podiel ludi v danej vekovej skupine:" << endl;
			this->kriteriumVekSkupinaPodiel_->nastavKriterium(this->enumVekSkupPodiel_);
			this->filterVekSkupPodiel_->nastavVekovuSkupinu(this->enumVekSkupPodiel_);
			this->filterVekSkupPodiel_->nastavHodnotuFiltru(dajMinDoubleHodnotuPreFilter(), dajMaxDoubleHodnotuPreFilter());
		}
		std::cout << "Filter: Ekonomicka vekova skupina podiel ";
		break;
	case'4':
		if (vybranyFilter) {
			this->enumVekPocetPohlavie_ = NULL_ENUM_POHLAVE;
		}
		else {
			this->enumVekPocetPohlavie_ = this->vratEnumPohlavie();
			this->minVekPocet = this->dajNapisanyVek(false);
			this->maxVekPocet = this->dajNapisanyVek(true);
			this->filterVekPocet_->nastavVekPohlavie(this->minVekPocet, this->maxVekPocet, this->enumVekPocetPohlavie_);
			this->kriteriumVekPocet_->nastavKriterium(this->minVekPocet, this->maxVekPocet, this->enumVekPocetPohlavie_);

			std::cout << "\nZadaj obmedzujuci interval pre pocet ludi s danym vekom:" << endl;
			this->filterVekPocet_->nastavHodnotuFiltru(dajMinIntHodnotuPreFilter(), dajMaxIntHodnotuPreFilter());
		}
		std::cout << "Filter: Vek pocet ";
		break;
	case'5':
		if (vybranyFilter) {
			this->enumVekPodielPohlavie_ = NULL_ENUM_POHLAVE;
		}
		else {
			this->enumVekPodielPohlavie_ = this->vratEnumPohlavie();
			this->minVekPodiel = this->dajNapisanyVek(false);
			this->maxVekPodiel = this->dajNapisanyVek(true);
			this->filterVekPodiel_->nastavVekPohlavie(this->minVekPodiel, this->maxVekPodiel, this->enumVekPodielPohlavie_);
			this->kriteriumVekPodiel_->nastavKriterium(this->minVekPodiel, this->maxVekPodiel, this->enumVekPodielPohlavie_);
			std::cout << "\nZadaj obmedzujuci interval pre podiel ludi s danym vekom:" << endl;
			this->filterVekPodiel_->nastavHodnotuFiltru(dajMinDoubleHodnotuPreFilter(), dajMaxDoubleHodnotuPreFilter());
		}
		std::cout << "Filter: Vek podiel ";
		break;
	case'6':
	{
		if (vybranyFilter) {
			this->enumVzdelaniePocet_ = NULL_ENUM_VZDELANIE;
		}
		else {
			this->enumVzdelaniePocet_ = vratEnumVybraneVzdelanie();
			this->filterVzdelaniePocet_->nastavVzdelanie(this->enumVzdelaniePocet_);
			this->kriteriumVzdelaniePocet_->nastavKriterium(this->enumVzdelaniePocet_);
			std::cout << "\nZadaj obmedzujuci interval pre pocet ludi s danym vzdelanim:" << endl;
			this->filterVzdelaniePocet_->nastavHodnotuFiltru(dajMinIntHodnotuPreFilter(), dajMaxIntHodnotuPreFilter());
		}
		std::cout << "Filter: Vzdelanie pocet ";
		break;
	}
	case'7':
	{
		if (vybranyFilter) {
			this->enumVzdelaniePodiel_ = NULL_ENUM_VZDELANIE;
		}
		else {
			this->enumVzdelaniePodiel_ =  vratEnumVybraneVzdelanie();
			this->filterVzdelaniePodiel_->nastavVzdelanie(this->enumVzdelaniePodiel_);
			this->kriteriumVzdelaniePodiel_->nastavKriterium(this->enumVzdelaniePodiel_);
			std::cout << "\nZadaj obmedzujuci interval pre podiel ludi s danym vzdelanim:" << endl;
			this->filterVzdelaniePodiel_->nastavHodnotuFiltru(dajMinDoubleHodnotuPreFilter(), dajMaxDoubleHodnotuPreFilter());
		}
		std::cout << "Filter: Vzdelanie podiel ";
		break;
	}
	default:
		std::cout << "SPADLO DO DEFAULTU: Data::pridatFiltreDoVyberu(char znak) " << endl;
		break;
	}

	if (vybranyFilter) {
		vybranyFilter = false;
		std::cout << "bol odobrany" << endl;
	}
	else {
		vybranyFilter = true;
		std::cout << "bol pridany" << endl;
	}

}

void Data::zaregistrujFiltre() {

	for (int i = 0; i < this->aktivneFiltre_->size(); i++)
	{
		if (filterANDZvoleny_) {
			if (this->aktivneFiltre_->at(i)) {
				switch (i) {
				case 0:
					filterAND_->zaregistrujFilter(this->filterPrislusnost_);
					break;
				case 1:
					filterAND_->zaregistrujFilter(this->filterTyp_);
					break;
				case 2:
					filterAND_->zaregistrujFilter(this->filterVekSkupPocet_);
					break;
				case 3:
					filterAND_->zaregistrujFilter(this->filterVekPodiel_);
					break;
				case 4:
					filterAND_->zaregistrujFilter(this->filterVekPocet_);
					break;
				case 5:
					filterAND_->zaregistrujFilter(this->filterVekPodiel_);
					break;
				case 6:
					filterAND_->zaregistrujFilter(this->filterVzdelaniePocet_);
					break;
				case 7:
					filterAND_->zaregistrujFilter(this->filterVzdelaniePodiel_);
					break;
				default:
					break;
				}
			}
			
		}	else if (filterOR_) {
			if (this->aktivneFiltre_->at(i)) {
				switch (i) {
				case 0:
					filterOR_->zaregistrujFilter(this->filterPrislusnost_);
					break;
				case 1:
					filterOR_->zaregistrujFilter(this->filterTyp_);
					break;
				case 2:
					filterOR_->zaregistrujFilter(this->filterVekSkupPocet_);
					break;
				case 3:
					filterOR_->zaregistrujFilter(this->filterVekPodiel_);
					break;
				case 4:
					filterOR_->zaregistrujFilter(this->filterVekPocet_);
					break;
				case 5:
					filterOR_->zaregistrujFilter(this->filterVekPodiel_);
					break;
				case 6:
					filterOR_->zaregistrujFilter(this->filterVzdelaniePocet_);
					break;
				case 7:
					filterOR_->zaregistrujFilter(this->filterVzdelaniePodiel_);
					break;
				default:
					break;
				}
			}
			
		}

	}
}

void Data::vyberEnumUJ() {
	bool opakuj = false;
	do {
		opakuj = false;
		std::cout << std::endl;
		std::cout << "Vyber uzemnu jednotku" << endl;
		std::cout << "1 - Kraj" << std::endl;
		std::cout << "2 - Okres" << std::endl;
		std::cout << "3 - Obec" << std::endl;
		std::cout << "Vyber:\t";

		string line{};
		char znak{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		znak = line[0];

		switch (znak)
		{
		case '1':
			this->vybranyTypUJFilter_ = KRAJ;
			break;
		case '2':
			this->vybranyTypUJFilter_ = OKRES;
			break;
		case '3':
			this->vybranyTypUJFilter_ = OBEC;
			break;
		default:
			this->vybranyTypUJFilter_ = NULL_ENUM_UJ;
			opakuj = true;
			std::cout << "Neznamy vyber, prosim skus znova!" << endl;
			break;
		}
	} while (opakuj);
}

int Data::dajMinIntHodnotuPreFilter() {
	bool nespravnyVstup = true;
	int minHodnota{};
	char key_press;
	do
	{	
		std::cout << "Ak chces neobmedzenu dolnu hranicu stlac 'n'." << endl;
		key_press = _getch();
		if (key_press == 110 || key_press == 78)
			return INT_MIN;
		std::cout << "Zadaj minimalnu hodnotu: ";
		string line{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		try {
			minHodnota = stoi(line);
			nespravnyVstup = false;
			if (minHodnota < 0)
				std::cout << "Minimalna hodnota bola nastavena na 0" << endl;
		}
		catch (...) {
			std::cout << "Zadal si nespravny vstup, skus znova!" << endl;
		}
	} while (nespravnyVstup);

	return minHodnota;
}

int Data::dajMaxIntHodnotuPreFilter() {
	bool nespravnyVstup = true;
	int maxHodnota{};
	char key_press;
	do
	{
		std::cout << "Ak chces neobmedzenu hornu hranicu stlac 'n'." << endl;
		key_press = _getch();
		if (key_press == 110 || key_press == 78)
			return INT_MAX;
		std::cout << "Zadaj maximalnu hodnotu: ";
		string line{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		try {
			maxHodnota = stoi(line);
			nespravnyVstup = false;
		}
		catch (...) {
			std::cout << "Zadal si nespravny vstup, skus znova!" << endl;
		}
	} while (nespravnyVstup);

	return maxHodnota;
}

double Data::dajMinDoubleHodnotuPreFilter() {
	bool nespravnyVstup = true;
	double minHodnota{};
	char key_press;
	do
	{
		std::cout << "Ak chces neobmedzenu dolnu hranicu stlac 'n'." << endl;
		key_press = _getch();
		if (key_press == 110 || key_press == 78)
			return -DBL_MAX;
		std::cout << "Zadaj minimalnu hodnotu: ";
		string line{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		try {
			minHodnota = stod(line);
			nespravnyVstup = false;
			if (minHodnota < 0.0)
				std::cout << "Minimalna hodnota bola nastavena na 0.0" << endl;
		}
		catch (...) {
			std::cout << "Zadal si nespravny vstup, skus znova!" << endl;
		}
	} while (nespravnyVstup);

	return minHodnota;
}

double Data::dajMaxDoubleHodnotuPreFilter() {
	bool nespravnyVstup = true;
	double maxHodnota{};
	char key_press;
	do
	{
		std::cout << "Ak chces neobmedzenu hornu hranicu stlac 'n'." << endl;
		key_press = _getch();
		if (key_press == 110 || key_press == 78)
			return DBL_MAX;
		std::cout << "Zadaj maximalnu hodnotu: ";
		string line{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		try {
			maxHodnota = stod(line);
			nespravnyVstup = false;
		}
		catch (...) {
			std::cout << "Zadal si nespravny vstup, skus znova!" << endl;
		}
	} while (nespravnyVstup);

	return maxHodnota;
}

int Data::dajNapisanyVek(bool maximalny) {
	bool nespravnyVstup;
	int vek;
	nespravnyVstup = true;
	do
	{
		if(maximalny)
			std::cout << "Zadaj maximalny vek(vratane): ";
		else 
			std::cout << "Zadaj minimalny vek(vratane): ";
		string line{};
		getline(cin, line);
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		try {
			vek = stoi(line);
			nespravnyVstup = false;
			if (maximalny && vek > 100)
				std::cout << "Maximalny vek bol nastaveny na 100+" << endl;
			if(!maximalny && vek < 0)
				std::cout << "Minimalny vek bol nastaveny na 0" << endl;
		}
		catch (...) {
			std::cout << "Zadal si nespravny vstup, skus znova!" << endl;
		}
	} while (nespravnyVstup);
	return vek;
}

void Data::vyberOR_ANDFiltra() {
	char key_press;
	bool nespravnyVstup = true;
	this->filterORZvoleny_ = false;
	this->filterANDZvoleny_ = false;
	do
	{
		std::cout << "Ak chces vybrat filter_AND , stlac 'a'." << endl;
		std::cout << "Ak chces vybrat filter_OR, stlac 'o'." << endl;
		key_press = _getch();
		if (key_press == 97 ) { //a
			this->filterANDZvoleny_ = true;
			this->filterORZvoleny_ = false;
			nespravnyVstup = false;
		}
		else if(key_press == 111) {	//o
			nespravnyVstup = false;
			this->filterORZvoleny_ = true;
			this->filterANDZvoleny_ = false;
		}
		else {
			std::cout << "Neznamy vyber, prosim skus znova" << endl;
		}
	} while (nespravnyVstup);
}

std::string Data::enumVzdelanieToString(EnumVzdelanie vzdelanie) {
	switch (vzdelanie)
	{
	case BEZ_UKONCENEHO_VZDELANIA_0_14_ROKOV:
		return "Bez ukonceneho vzdelania - osoby vo veku 0-14 rokov";
		break;
	case ZAKLADNE_VZDELANIE:
		return "Zakladne vzdelanie";
		break;
	case STREDNE_ODBORNE_VZDELANIE:
		return "Stredne odborne (ucnovske) vzdelanie (bez maturity)";
		break;
	case UPLNE_STREDNE_VZDELANIE:
		return "Uplne stredne vzdelanie (s maturitou)";
		break;
	case VYSSIE_ODBORNE_VZDELANIE:
		return "Vyssie odborne vzdelanie";
		break;
	case VYSOKOSKOLSKE_VZDELANIE:
		return "Vysokoskolske vzdelanie";
		break;
	case BEZ_SKOLSKEHO_VZDELANIA_15_A_VIAC_ROKOV:
		return "Bez skolskeho vzdelania - osoby vo veku 15 rokov a viac";
		break;
	case NEZISTENE:
		return "Nezistene";
		break;
	case NULL_ENUM_VZDELANIE:
		return "NEZNAME VZDELANIE";
		break;
	default:
		return "NEZNAME VZDELANIE";
		break;
	}
}

std::string Data::enumTypUJtoString(EnumTypUzemnejJednotky typUJ) {
	switch (typUJ)
	{
	case SLOVENSKO:
		return "Slovensko";
		break;
	case KRAJ:
		return "Kraj";
		break;
	case OKRES:
		return "Okres";
		break;
	case OBEC:
		return "Obec";
		break;
	case NULL_ENUM_UJ:
		return "NEZNAMA UZEMNA JEDNOTKA";
		break;
	default:
		return "SPADLO DO DEFAULTU: Data::enumTypUJtoString";
		break;
	}
}

std::string Data::enumEVStoString(EnumVekovaSkupina typEVS) {
	switch (typEVS)
	{
	case PREDPRODUKTIVNI:
		return "Predproduktivni";
		break;
	case PRODUKTIVNI:
		return "Produktivni";
		break;
	case POPRODUKTIVNI:
		return "Poproduktivni";
		break;
	case NULL_ENUM_VEKOVA_SKUPINA:
		return "NEZNAMA EVS";
		break;
	default:
		return "SPADLO DO DEFAULTU: Data::enumEVStoString";
		break;
	}
}

std::string Data::enumPohlavieToString(EnumPohlavie typPohlavia) {
	switch (typPohlavia)
	{
	case ZENA:
		return "Zeny";
		break;
	case MUZ:
		return "Muzi";
		break;
	case OBIDVE_POHLAVIA:
		return "Muzi a zeny";
		break;
	case NULL_ENUM_POHLAVE:
		return "NEZNAME POHAVIE";
		break;
	default:
		return "SPADLO DO DEFAULTU: Data::enumPohlavieToString";
		break;
	}
}

