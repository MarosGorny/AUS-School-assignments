#pragma once


#include "VyssiCelok.h"

class Kraj;


class Slovensko :
    public VyssiCelok
{
public:
    Slovensko();

public:
	//Funkcne
	void pridajKraj(Kraj* kraj);
	
};
