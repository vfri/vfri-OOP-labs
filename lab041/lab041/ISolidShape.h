#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
	public:
		ISolidShape(const std::string& type, const std::string& outlineColor, const std::string& fillColor);
		virtual double GetArea() const = 0; // площадь образа
		virtual double GetPerimeter() const = 0; // периметр образа
		std::string GetFillcolor() const;
	protected:
		std::string m_fillColor;	// цвет заливки
		void AppendProperties(std::ostream& ostrm) const override;
};

