#pragma once
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
	public:
		CTriangle();
		double GetArea() const; // ������� ������
		double GetPerimeter() const; // �������� ������
		std::string ToString() const; // �������� ������
		std::string GetOutlineColor() const; // ���� �������
		std::string GetFillcolor() const; // ���� �������
	private:
		CPoint GetVertex1() const;
		CPoint GetVertex2() const;
		CPoint GetVertex3() const;
};

