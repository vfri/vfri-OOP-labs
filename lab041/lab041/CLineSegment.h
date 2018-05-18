#pragma once
#include "IShape.h"

class CLineSegment : public IShape
{
	public:
		CLineSegment();
		double GetArea() const;
		double GetPerimrter() const;
		std::string ToString() const;
		std::string GetOutlineColor() const;
	private:	
		CPoint GetStartPoint() const;
		CPoint GetEndPoint() const;
};

