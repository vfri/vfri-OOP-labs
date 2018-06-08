#include "stdafx.h"
#include "CTriangle.h"
#include "CLineSegment.h"



CTriangle::CTriangle(double vert1X, double vert1Y, double vert2X, double vert2Y, double vert3X, double vert3Y,
	const std::string& outlineColor, const std::string& fillColor)
	:m_type(std::string("Triangle"))
	,m_outlineColor(outlineColor)
	,m_fillColor(fillColor)
	,m_vert1(CPoint(vert1X, vert1Y))
	,m_vert2(CPoint(vert2X, vert2Y))
	,m_vert3(CPoint(vert3X, vert3Y))
{
}

CPoint CTriangle::GetVertex1() const
{
	return m_vert1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vert2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vert3;
}

std::string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CTriangle::GetFillcolor() const
{
	return m_fillColor;
}

double CTriangle::GetPerimeter() const
{
	CLineSegment side1(m_vert1.GetX(), m_vert1.GetY(), m_vert2.GetX(), m_vert2.GetY(), m_outlineColor);
	CLineSegment side2(m_vert2.GetX(), m_vert2.GetY(), m_vert3.GetX(), m_vert3.GetY(), m_outlineColor);
	CLineSegment side3(m_vert3.GetX(), m_vert3.GetY(), m_vert1.GetX(), m_vert1.GetY(), m_outlineColor);

	return side1.GetPerimeter() + side2.GetPerimeter() + side3.GetPerimeter();
}

double CTriangle::GetArea() const
{
	CLineSegment side2(m_vert1.GetX(), m_vert1.GetY(), m_vert2.GetX(), m_vert2.GetY(), m_outlineColor);
	CLineSegment side3(m_vert1.GetX(), m_vert1.GetY(), m_vert3.GetX(), m_vert3.GetY(), m_outlineColor);
	CPoint side2Rad = side2.GetRadVector();
	CPoint side3Rad = side3.GetRadVector();

	return 0.5 * abs(side2Rad.GetX() * side3Rad.GetY() - side2Rad.GetY() * side3Rad.GetX());
}

std::string CTriangle::ToString() const
{
	std::ostringstream strm;

	strm << "\tShape type is Triangle" << std::endl
		<< "\tOutline color is " << m_outlineColor << std::endl
		<< "\tFill color is " << m_fillColor << std::endl
		<< "\tVertex 1 is (" << m_vert1.GetX() << ", " << m_vert1.GetY() << ")" << std::endl
		<< "\tVertex 2 is (" << m_vert2.GetX() << ", " << m_vert2.GetY() << ")" << std::endl
		<< "\tVertex 3 is (" << m_vert3.GetX() << ", " << m_vert3.GetY() << ")" << std::endl
		<< "\tPerimeter =  " << GetPerimeter() << std::endl
		<< "\tArea = " << GetArea() << std::endl;
	
	return strm.str();
}
