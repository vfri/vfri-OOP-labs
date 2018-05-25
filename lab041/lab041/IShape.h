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
		IShape(const std::string& type, const std::string& outlineColor);
		virtual double GetArea() const = 0; // площадь образа
		virtual double GetPerimeter() const = 0; // периметр образа
		std::string ToString() const; // описание фигуры
		std::string GetOutlineColor() const; // цвет контура
	protected:
		std::string m_type;				// тип фигуры
		std::string m_outlineColor;		// цвет контура
		virtual void AppendProperties(std::ostream& ostrm) const = 0;
};



