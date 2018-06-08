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
	virtual ~IShape() {};
	virtual double GetArea() const = 0; // ������� ������
	virtual double GetPerimeter() const = 0; // �������� ������
	virtual std::string ToString() const = 0; // �������� ������
	virtual std::string GetOutlineColor() const = 0; // ���� �������
};



