#pragma once
#include "../pohlavie/Muz.h"
#include "../pohlavie/Zena.h"
#include "../uzemnaJednotka/UzemnaJednotka.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "../pohlavie/EnumPohlavie.h"
class EVS
{
public:
	structures::UnsortedSequenceTable<int, int> dajPredproduktivnych();
	structures::UnsortedSequenceTable<int, int> dajProduktivnych();
	structures::UnsortedSequenceTable<int, int> dajPoproduktivnych();
	EVS(UzemnaJednotka uzemnaJednotka);
	void nastavEVS(EnumPohlavie pohlavie);
private:
	Muz* muzi;
	Zena* zeny;
};

