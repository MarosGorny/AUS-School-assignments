#pragma once

#include "structures/table/table.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"
//#include "uzemnaJednotka/EnumTypUzemnejJednotky.h"
#include "uzemnaJednotka/UzemnaJednotka.h"
#include "vyberoveKriterium/VNajmensiaVekovaSkupina.h"
#include "vyberoveKriterium/VNajvacsiaVekovaSkupina.h"

class Kraj;
class Okres;
class Obec;
class Slovensko;

class KNazov;
class KUJNadradena;
class KUJPrislusnost;
class KUJTyp;
class KUJVekovaSkupinaPocet;
class KUJVekovaSkupinaPodiel;
class KUJVekPocet;
class KUJVekPodiel;
class KUJVzdelaniePocet;
class KUJVzdelaniePodiel;

class Filter;
class KompozitnyFilter;
class Filter_OR;
class Filter_AND;

class FilterPrislusnost;
class FilterTyp;
class FilterVekovaSkupinaPocetMedzi;
class FilterVekovaSkupinaPodielMedzi;
class FilterVekPocetMedzi;
class FilterVekPodielMedzi;
class FilterVzdelaniePocetMedzi;
class FilterVzdelaniePodielMedzi;

class VNajvacsiaVekovaSkupina;
class VNajvacsiaVekovaSkupina;

using namespace std;

class Data
{
public:
	Data();
	~Data();

	//VYMAZANIE
	//structures::UnsortedSequenceTable<std::string, Obec*>* spravKopiuObci();
	void vypisObce();
	void vypisOkresy();
	void vypisUnsortedOkresy();
	void vypisKraje();

	Slovensko* dajSlovensko() { return this->slovensko_; };
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* dajObce()  { return this->obceUnsortedCode_; };
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* dajOkresy() { return this->okresyUnsortedCode_; };
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* dajKraje() { return this->krajeUnsortedCode_; };

	UzemnaJednotka* najdi(EnumTypUzemnejJednotky UJ, std::string nazovUJ);
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* spravKopiuPodlaFiltra(structures::Table<std::string, UzemnaJednotka*>* tabulka, Filter* filter);
	//void zoradPodlaNazvu(UzemnaJednotka* uzemnaJednotka, structures::UnsortedSequenceTable<std::string,UzemnaJednotka*>* tabulka,bool vzostupne = true);
	//void zoradPodlaVzdelaniaPocet(UzemnaJednotka* uzemnaJednotka, structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* tabulka, EnumVzdelanie vzdelanie, bool vzostupne = true);

	void vyberUJTyp();





private:
	bool vyberUJ();
	void vyberMoznosti();

	void vyberObec(char vybranyZnak);

	void pridatKriteraAleboVypisatInformacie();

	void vypisatZakladneInfoUJ();
	
	void vyberKraj(char vybranyZnak);

	void vyberOkres(char vybranyZnak);

	void pridatVsetkyKriteriaDoVyberu();

	void pridatKriteriumDoVyberu(char znak);

	void vyberVzdelanie();
	EnumVzdelanie vratEnumVybraneVzdelanie();

	void vyberVekovuSkupinu();
	EnumVekovaSkupina vratEnumVekovuSkupinu();

	void vyberPohlavie();
	EnumPohlavie vratEnumPohlavie();

	void vypisMnozinuSAktivnymKriterium();

	void vypisInfoUJPodlaKriterii(UzemnaJednotka* uzemnaJednotka);

	void vypisInfoUJPodlaFiltrov();

	void pridajObec(Obec* obec);
	void pridajOkres(Okres* okres);
	void pridajKraj(Kraj* kraj);

	void pridajVsetkyObce();
	void pridajVsetkyOkresy();
	void pridajVsetkyKraje();

	void pracaSVybranouMnozinou();

	void vypisTypNazovNadJednotiek(UzemnaJednotka* uj);

	void filtrovanieAZoradenie();

	void pridanieFiltrov();

	void zoraditCezKriteriumMenu();

	void zoraditCezAktivneKriterium();

	void pridatFilterDoVyberu(char znak);

	void zaregistrujFiltre();

	void vyberEnumUJ();

	int dajMinIntHodnotuPreFilter();

	int dajMaxIntHodnotuPreFilter();

	double dajMinDoubleHodnotuPreFilter();

	double dajMaxDoubleHodnotuPreFilter();

	int dajNapisanyVek(bool maximalny);

	void vyberOR_ANDFiltra();


	void prepojObceOkresy();
	void prepojOkresyKraje();
	void prepojKrajeSlovensko();

	void pridajUJ();
	void prepojUJ();

	void vymazObce();
	void vymazOkresy();
	void vymazKraje();

	void vymazVyfiltrovanuMnozinu();

	void vymazUJ();

	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* krajeUnsortedCode_;
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* okresyUnsortedCode_;
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* obceUnsortedCode_;

	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* krajeVsetky_;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* okresyVsetky_;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* obceVsetky_;

	//aktivne kriteria
	structures::Array<bool>* aktivneKriteria_;
	structures::Array<bool>* aktivneFiltre_;
	
	//Kriteria
	KNazov* kriteriumNazov_;
	KUJNadradena* kriteriumNadradena_;
	KUJPrislusnost* kriteriumPrislusnost_;
	KUJTyp* kriteriumTyp_;
	KUJVekovaSkupinaPocet* krtiteriumVekSkupinaPocet_;
	KUJVekovaSkupinaPodiel* kriteriumVekSkupinaPodiel_;
	KUJVekPocet* kriteriumVekPocet_;
	KUJVekPodiel* kriteriumVekPodiel_;
	KUJVzdelaniePocet* kriteriumVzdelaniePocet_;
	KUJVzdelaniePodiel* kriteriumVzdelaniePodiel_;

	//Filter

	Filter_AND* filterAND_;
	bool filterANDZvoleny_;
	Filter_OR* filterOR_;
	bool filterORZvoleny_;
	FilterPrislusnost* filterPrislusnost_;
	FilterTyp* filterTyp_;
	FilterVekovaSkupinaPocetMedzi* filterVekSkupPocet_;
	FilterVekovaSkupinaPodielMedzi* filterVekSkupPodiel_;
	FilterVekPocetMedzi* filterVekPocet_;
	FilterVekPodielMedzi* filterVekPodiel_;
	FilterVzdelaniePocetMedzi* filterVzdelaniePocet_;
	FilterVzdelaniePodielMedzi* filterVzdelaniePodiel_;
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaMnozina_;

	//vyber
	VNajvacsiaVekovaSkupina* vyberNajvacsiaVekSkupina_;
	VNajmensiaVekovaSkupina* vyberNajmensiaVekSkupina_;

	EnumVekovaSkupina enumVekSkupPocet_;
	EnumVekovaSkupina enumVekSkupPodiel_;

	EnumPohlavie enumVekPocetPohlavie_;
	int minVekPocet;
	int maxVekPocet;

	EnumPohlavie enumVekPodielPohlavie_;
	int minVekPodiel;
	int maxVekPodiel;

	EnumVzdelanie enumVzdelaniePocet_;
	EnumVzdelanie enumVzdelaniePodiel_;
	

	Slovensko* slovensko_;

	UzemnaJednotka* vybranaUzemnaJednotka_;
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>* vybranaMnozina_;

	EnumPohlavie vybranePohlave_;
	EnumTypUzemnejJednotky vybranyTypUJ_;
	EnumTypUzemnejJednotky vybranyTypUJFilter_;
	EnumVzdelanie vybraneVzdelanie_;
	EnumVekovaSkupina vybranaVekovaSkupina_;

	//pomocne funkcie
	std::string enumVzdelanieToString(EnumVzdelanie vzdelanie);
	std::string enumTypUJtoString(EnumTypUzemnejJednotky typUJ);
	std::string enumEVStoString(EnumVekovaSkupina typEVS);
	std::string enumPohlavieToString(EnumPohlavie typPohlavia);
};

