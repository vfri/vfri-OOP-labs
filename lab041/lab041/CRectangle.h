#pragma once
#include "ISolidShape.h"

class CRectangle : 	public ISolidShape
{
	public:
		CRectangle(double leftTopX, double leftTopY, double width, double height);
		double GetArea() const; // ������� ������
		double GetPerimeter() const; // �������� ������
		std::string ToString() const; // �������� ������
		std::string GetOutlineColor() const; // ���� �������
		std::string GetFillcolor() const; // ���� �������
		CPoint GetLeftTop() const; // ����� ������� �������
		CPoint GetRightBottom() const; // ������ ������ �������
		double GetWidth() const; // ������
		double GetHeight() const; // ������
		void AppendProperties(std::ostream& ostrm) const;
	private:
		CPoint m_leftTop;
		double m_width;
		double m_height;
};

