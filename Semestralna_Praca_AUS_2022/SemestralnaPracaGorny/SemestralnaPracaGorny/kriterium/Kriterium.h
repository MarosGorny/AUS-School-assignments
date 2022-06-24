#pragma once
#include "../uzemnaJednotka/UzemnaJednotka.h"


/// <summary> Kriterium. </summary>
/// <typeparam name = "R"> Navratovy typ. </typepram>
template <typename R>
class Kriterium
{
public:
	Kriterium() = default;
	virtual ~Kriterium() = default;
	virtual R urobKriterium(UzemnaJednotka* uzemnaJednotka) = 0;
};

