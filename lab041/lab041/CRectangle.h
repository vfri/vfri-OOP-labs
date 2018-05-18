#pragma once
#include "ISolidShape.h"

class CRectangle : 	public ISolidShape
{
	public:
		CRectangle();
		double GetArea() const; // ������� ������
		double GetPerimeter() const; // �������� ������
		std::string ToString() const; // �������� ������
		std::string GetOutlineColor() const; // ���� �������
		std::string GetFillcolor() const; // ���� �������
	private:
		CPoint GetLeftTop() const; // ����� ������� �������
		CPoint GetRightBottom() const; // ������ ������ �������
		double GetWidth() const; // ������
		double GetHeight() const; // ������

};

