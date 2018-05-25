#include "stdafx.h"
#include "CRectangle.h"


CRectangle::CRectangle(double leftTopX, double leftTopY, double width, double height, 
	const std::string& outlineColor, const std::string& fillColor)
	:ISolidShape("Rectangle", outlineColor, fillColor)
	,m_leftTop(CPoint(leftTopX, leftTopY))
{
	m_width = (width > 0) ? width : 0.0;
	m_height = (height > 0) ? height : 0.0;
}

CRectangle::~CRectangle()
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2.0 * (m_width + m_height);
}

std::string CRectangle::GetOutlineColor() const
{
	return IShape::GetOutlineColor();
}


std::string CRectangle::GetFillcolor() const
{
	return ISolidShape::GetFillcolor();
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	double xRB = m_leftTop.GetX() + m_width;
	double yRB = m_leftTop.GetY() + m_height;

	return CPoint(xRB, yRB);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::AppendProperties(std::ostream& ostrm) const
{
	ostrm << "\tLeft top vertex is (" << m_leftTop.GetX() << ", " << m_leftTop.GetY() << ")" << std::endl
		<< "\twidth is " << m_width << std::endl
		<< "\theight is " << m_height << std::endl
		<< "\tPerimeter =  " << GetPerimeter() << std::endl
		<< "\tArea = " << GetArea() << std::endl;
}

std::string CRectangle::ToString() const
{
	ISolidShape::ToString();
	std::ostringstream strm;
	AppendProperties(strm);
	return strm.str();
}




