#pragma once
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
	public:
		CCircle();
		double GetArea() const; // площадь образа
		double GetPerimeter() const; // периметр образа
		std::string ToString() const; // описание фигуры
		std::string GetOutlineColor() const; // цвет контура
		std::string GetFillcolor() const; // цвет заливки
	private:
		CPoint GetCenter() const;
		double GetRadius() const;
};

