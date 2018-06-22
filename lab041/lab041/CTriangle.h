#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : public ISolidShape 
{
public:
	CTriangle(CPoint const& vert1, CPoint const& vert2, CPoint const& vert3,
	const std::string& outlineColor, const std::string& fillColor);
	double GetArea() const; // ������� ������
	double GetPerimeter() const; // �������� ������
	std::string ToString() const; // �������� ������
	std::string GetOutlineColor() const; // ���� �������
	std::string GetFillcolor() const; // ���� �������
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
private:
	std::string m_type;
	std::string m_outlineColor;
	std::string m_fillColor;
	CPoint m_vert1;
	CPoint m_vert2;
	CPoint m_vert3;
};

