#pragma once
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
	public:
		CCircle(double centerX, double centerY, double radius);
		double GetArea() const; // площадь образа
		double GetPerimeter() const; // периметр образа
		std::string ToString() const; // описание фигуры
		std::string GetOutlineColor() const; // цвет контура
		std::string GetFillcolor() const; // цвет заливки
		CPoint GetCenter() const;
		double GetRadius() const;
		void AppendProperties(std::ostream& ostrm) const;
	private:
		CPoint m_center;
		double m_radius;
};

