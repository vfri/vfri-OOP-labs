#pragma once
#include "ISolidShape.h"

class CTriangle : public ISolidShape 
{
public:
	CTriangle(double vert1X, double vert1Y, double vert2X, double vert2Y, double vert3X, double vert3Y,
	const std::string& outlineColor, const std::string& fillColor);
	double GetArea() const; // площадь образа
	double GetPerimeter() const; // периметр образа
	std::string ToString() const; // описание фигуры
	std::string GetOutlineColor() const; // цвет контура
	std::string GetFillcolor() const; // цвет заливки
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
private:
	std::string m_type;
	std::string m_outlineColor;
	std::string m_fillColor;
	CPoint m_vert1;
	CPoint m_vert2;
	CPoint m_vert3;
};

