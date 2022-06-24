#pragma once
#include <iostream>
#include "../uzemnaJednotka/UzemnaJednotka.h"
#include "../kriterium/Kriterium.h"


class Filter
{
public:
	virtual ~Filter() = default;
	virtual bool splna(UzemnaJednotka* uzemnaJednotka) = 0;
protected:
};
