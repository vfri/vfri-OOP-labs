#include "stdafx.h"
#include "CLineSegment.h"


CLineSegment::CLineSegment(double startPointX, double startPointY, double endPointX, double endPointY, const std::string& outlineColor)
	:m_type(std::string("LineSegment"))
	,m_outlineColor(outlineColor)
	,m_startP(CPoint(startPointX, startPointY))
	,m_endP(CPoint(endPointX, endPointY))
{
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startP;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endP;
}

std::string CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	double x1 = m_startP.GetX();
	double y1 = m_startP.GetY();
	double x2 = m_endP.GetX();
	double y2 = m_endP.GetY();

	return pow( pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);
}

std::string CLineSegment::ToString() const
{
	std::ostringstream strm;

	strm << "\tShape type is Line segment" << std::endl
		<< "\tColor is " << m_outlineColor << std::endl
		<< "\tEndpoint 1 is (" << m_startP.GetX() << ", " << m_startP.GetY() << ")" << std::endl
		<< "\tEndpoint 2 is (" << m_endP.GetX() << ", " << m_endP.GetY() << ")" << std::endl
		<< "\tPerimeter = " << GetPerimeter() << std::endl
		<< "\tArea = " << GetArea() << std::endl;
	
	return strm.str();
}


CPoint CLineSegment::GetRadVector() const
{
	double xRad = m_endP.GetX() - m_startP.GetX();
	double yRad = m_endP.GetY() - m_startP.GetY();
	return CPoint(xRad, yRad);
}