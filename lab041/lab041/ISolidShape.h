#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
	public:
		ISolidShape();
		std::string GetFillcolor() const; // цвет заливки
};

