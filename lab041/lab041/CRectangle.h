#pragma once
#include "ISolidShape.h"

class CRectangle : 	public ISolidShape
{
public:
	CRectangle(double leftTopX, double leftTopY, double width, double height, 
		const std::string& outlineColor, const std::string& fillColor);
	double GetArea() const; // ������� ������
	double GetPerimeter() const; // �������� ������
	std::string ToString() const; // �������� ������
	std::string GetOutlineColor() const; // ���� �������
	std::string GetFillcolor() const; // ���� �������
	CPoint GetLeftTop() const; // ����� ������� �������
	CPoint GetRightBottom() const; // ������ ������ �������
	double GetWidth() const; // ������
	double GetHeight() const; // ������
private:
	std::string m_type;
	std::string m_outlineColor;
	std::string m_fillColor;
	CPoint m_leftTop;
	double m_width;
	double m_height;
};

