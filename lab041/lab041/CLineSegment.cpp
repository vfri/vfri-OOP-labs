#include "stdafx.h"
#include "CLineSegment.h"


CLineSegment::CLineSegment(CPoint const& startPoint, CPoint const& endPoint, 
	const std::string& outlineColor = std::string("000fff"))
	:m_type(std::string("LineSegment"))
	,m_outlineColor(outlineColor)
	,m_startP(startPoint)
	,m_endP(endPoint)
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
	return CalcDistance(m_startP, m_endP);
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