#pragma once

class CPoint
{
private:
	double x;
	double y;
};


class IShape // ��������� "������� ������"
{
	public:
	
		IShape();
		double GetArea() const; // ������� ������
		double GetPerimeter() const; // �������� ������
		std::string ToString() const; // �������� ������
		std::string GetOutlineColor() const; // ���� �������

};



