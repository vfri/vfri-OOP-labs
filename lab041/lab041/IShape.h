#pragma once

class CPoint
{
public:
	CPoint(double x, double y);
	double GetX() const;
	double GetY() const;
private:
	double m_x;
	double m_y;
};


class IShape // интерфейс "плоская фигура"
{
public:
	virtual ~IShape() {};
	virtual double GetArea() const = 0; // площадь образа
	virtual double GetPerimeter() const = 0; // периметр образа
	virtual std::string ToString() const = 0; // описание фигуры
	virtual std::string GetOutlineColor() const = 0; // цвет контура
};



