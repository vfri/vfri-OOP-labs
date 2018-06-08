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










