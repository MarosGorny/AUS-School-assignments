

#include "structures/heap_monitor.h"
#include "Data.h"
#include<conio.h>




int main()
{
	initHeapMonitor();

	std::cout << "Ak do 10 sekund nenabehne menu, stlac enter." << std::endl;
	Data* data = new Data();

	data->vyberUJTyp();


	delete data;
	data = nullptr;
}


