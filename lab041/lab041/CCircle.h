#pragma once
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
	public:
		CCircle(double centerX, double centerY, double radius);
		double GetArea() const; // ������� ������
		double GetPerimeter() const; // �������� ������
		std::string ToString() const; // �������� ������
		std::string GetOutlineColor() const; // ���� �������
		std::string GetFillcolor() const; // ���� �������
		CPoint GetCenter() const;
		double GetRadius() const;
		void AppendProperties(std::ostream& ostrm) const;
	private:
		CPoint m_center;
		double m_radius;
};

