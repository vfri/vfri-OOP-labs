#pragma once
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
	public:
		CCircle();
		double GetArea() const; // ������� ������
		double GetPerimeter() const; // �������� ������
		std::string ToString() const; // �������� ������
		std::string GetOutlineColor() const; // ���� �������
		std::string GetFillcolor() const; // ���� �������
	private:
		CPoint GetCenter() const;
		double GetRadius() const;
};

