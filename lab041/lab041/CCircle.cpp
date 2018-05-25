#include "stdafx.h"
#include "CCircle.h"


CCircle::CCircle(double centerX, double centerY, double radius)
	:ISolidShape("Circle", m_outlineColor, m_fillColor)
	,m_center(CPoint(centerX, centerY))
{
	m_radius = (radius > 0) ? radius : 0.0;
}

double CCircle::GetArea() const
{
	return atan(1.0) * 4.0 * pow(m_radius, 2);
}


double CCircle::GetPerimeter() const
{
	return atan(1.0) * 8.0 * m_radius;
}

std::string CCircle::GetOutlineColor() const
{
	return IShape::GetOutlineColor();
}

std::string CCircle::GetFillcolor() const
{
	return ISolidShape::GetFillcolor();
}


CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::AppendProperties(std::ostream& ostrm) const
{
	ostrm << "\tcenter is at point (" << m_center.GetX() << ", " << m_center.GetY() << ")" << std::endl
		<< "\tradius is " << m_radius << std::endl
		<< "\tPerimeter =  " << GetPerimeter() << std::endl
		<< "\tArea = " << GetArea() << std::endl;
}

std::string CCircle::ToString() const
{
	ISolidShape::ToString();
	std::ostringstream strm;
	AppendProperties(strm);
	return strm.str();
}






