#include "stdafx.h"
#include "ISolidShape.h"


ISolidShape::ISolidShape(const std::string& type, const std::string& outlineColor, const std::string& fillColor)
	:IShape(type, outlineColor)
	,m_fillColor(fillColor)
{
}

ISolidShape::~ISolidShape()
{
}

std::string ISolidShape::GetFillcolor() const
{
	return m_fillColor;
}

void ISolidShape::AppendProperties(std::ostream& ostrm) const
{
	ostrm << "\tFill Color is " << m_fillColor << std::endl;
}




