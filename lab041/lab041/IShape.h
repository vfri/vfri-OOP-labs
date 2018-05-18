#pragma once

class CPoint
{
private:
	double x;
	double y;
};


class IShape // интерфейс "плоская фигура"
{
	public:
	
		IShape();
		double GetArea() const; // площадь образа
		double GetPerimeter() const; // периметр образа
		std::string ToString() const; // описание фигуры
		std::string GetOutlineColor() const; // цвет контура

};



