#pragma once
#include "IShape.h"

class CLineSegment : public IShape
{
	public:
		CLineSegment(double startPointX, double startPointY, double endPointX, double endPointY, const std::string& outlineColor);
		double GetArea() const;
		double GetPerimeter() const;
		std::string ToString() const;
		std::string GetOutlineColor() const;
		CPoint GetStartPoint() const;
		CPoint GetEndPoint() const;
		CPoint GetRadVector() const;
		void AppendProperties(std::ostream& ostrm) const;
	private:
		CPoint m_startP;
		CPoint m_endP;
};

