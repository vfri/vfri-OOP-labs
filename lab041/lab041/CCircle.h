#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint const& center, double radius, 
		const std::string& outlineColor, const std::string& fillColor);
	double GetArea() const; // ������� ������
	double GetPerimeter() const; // �������� ������
	std::string ToString() const; // �������� ������
	std::string GetOutlineColor() const; // ���� �������
	std::string GetFillcolor() const; // ���� �������
	CPoint GetCenter() const;
	double GetRadius() const;
private:
	std::string m_type;
	std::string m_outlineColor;
	std::string m_fillColor;
	CPoint m_center;
	double m_radius;
};

