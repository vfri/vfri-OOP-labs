#pragma once
#include "ISolidShape.h"

class CTriangle : public ISolidShape 
{
	public:
		CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3);
		double GetArea() const; // ������� ������
		double GetPerimeter() const; // �������� ������
		std::string ToString() const; // �������� ������
		std::string GetOutlineColor() const; // ���� �������
		std::string GetFillcolor() const; // ���� �������
		CPoint GetVertex1() const;
		CPoint GetVertex2() const;
		CPoint GetVertex3() const;
		void AppendProperties(std::ostream& ostrm) const;
	private:
		CPoint m_vert1;
		CPoint m_vert2;
		CPoint m_vert3;
};

