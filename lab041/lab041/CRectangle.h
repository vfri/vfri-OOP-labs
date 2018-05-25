#pragma once
#include "ISolidShape.h"

class CRectangle : 	public ISolidShape
{
	public:
		CRectangle(double leftTopX, double leftTopY, double width, double height);
		double GetArea() const; // площадь образа
		double GetPerimeter() const; // периметр образа
		std::string ToString() const; // описание фигуры
		std::string GetOutlineColor() const; // цвет контура
		std::string GetFillcolor() const; // цвет заливки
		CPoint GetLeftTop() const; // левая верхняя вершина
		CPoint GetRightBottom() const; // правая нижняя вершина
		double GetWidth() const; // ширина
		double GetHeight() const; // высота
		void AppendProperties(std::ostream& ostrm) const;
	private:
		CPoint m_leftTop;
		double m_width;
		double m_height;
};

