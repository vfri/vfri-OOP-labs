#pragma once

class CPoint
{
	public:
		CPoint(double x, double y);
		double GetX() const;
		double GetY() const;
	private:
		double m_x;
		double m_y;
};


class IShape // ��������� "������� ������"
{
	public:
		IShape(const std::string& type, const std::string& outlineColor);
		virtual double GetArea() const = 0; // ������� ������
		virtual double GetPerimeter() const = 0; // �������� ������
		std::string ToString() const; // �������� ������
		std::string GetOutlineColor() const; // ���� �������
	protected:
		std::string m_type;				// ��� ������
		std::string m_outlineColor;		// ���� �������
		virtual void AppendProperties(std::ostream& ostrm) const = 0;
};



