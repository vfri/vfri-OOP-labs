#pragma once
#include "ISolidShape.h"

class CTriangle : public ISolidShape 
{
	public:
		CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3);
		double GetArea() const; // площадь образа
		double GetPerimeter() const; // периметр образа
		std::string ToString() const; // описание фигуры
		std::string GetOutlineColor() const; // цвет контура
		std::string GetFillcolor() const; // цвет заливки
		CPoint GetVertex1() const;
		CPoint GetVertex2() const;
		CPoint GetVertex3() const;
		void AppendProperties(std::ostream& ostrm) const;
	private:
		CPoint m_vert1;
		CPoint m_vert2;
		CPoint m_vert3;
};

