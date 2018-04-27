#pragma once

class CRectangle
{
	public:
		CRectangle(int left, int top, int width, int height); // �����������
		// ������������� � ����� ������� �������� (left, top), ������� width, ������� height 

		~CRectangle(); // ����������

		int GetLeft(); // �������� ����� �������
		int GetRight(); // �������� ������ �������
		int GetTop(); // �������� ������� �������
		int GetBottom(); // �������� ������ �������

		int GetWidth(); // �������� ������
		int GetHeight(); // �������� ������

		int GetArea(); // �������� ������� �������������
		int GetPerimeter(); // �������� ��������

		void SetLeft(int newLeft); // ������ ����� �������
		void SetRight(int newRight); // ������ ������ �������
		void SetTop(int newTop); // ������ ������� �������
		void SetBottom(int newBottom); // ������ ������ �������

		void SetWidth(); // ������ ������
		void SetHeight(); // ������ ������

		void Move(int dx, int dy); // ����������� ������������� �� ������ (dx, dy)
		void Scale(int sx, int sy); // �������������� sx �� x, sy g� y
		bool Intersect(CRectangle const& other); // ����� ����������� � ��������������� other
	private:
		int m_left; // ����� �������
		int m_top; // ������� �������
		int m_width; // ������
		int m_height; // ������		
};

