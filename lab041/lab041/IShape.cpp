#include "stdafx.h"
#include "IShape.h"


CPoint::CPoint(double x = 0, double y = 0)
	:m_x(x)
	,m_y(y)
{
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}

IShape::IShape(const std::string& type = "LineSegment", const std::string& outlineColor = "ff0000")
	:m_type(type)
	,m_outlineColor(outlineColor)
{
}

IShape::~IShape()
{
}

std::string IShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string IShape::ToString() const
{
	std::ostringstream sstrm;
	sstrm << m_type << ":" << std::endl << "\tOutline Color is " << GetOutlineColor() << std::endl;
	AppendProperties(sstrm);
	return sstrm.str();
}



