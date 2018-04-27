#pragma once

class CRectangle
{
	public:
		CRectangle(int left, int top, int width, int height); // конструктор
		// прямоугольник с левой верхней вершиной (left, top), шириной width, высотой height 

		~CRectangle(); // деструктор

		int GetLeft(); // получить левую границу
		int GetRight(); // получить правую границу
		int GetTop(); // получить верхнюю границу
		int GetBottom(); // получить нижнюю границу

		int GetWidth(); // получить ширину
		int GetHeight(); // получить высоту

		int GetArea(); // получить площадь прмоугольника
		int GetPerimeter(); // получить периметр

		void SetLeft(int newLeft); // задать левую границу
		void SetRight(int newRight); // задать правую границу
		void SetTop(int newTop); // задать верхнюю границу
		void SetBottom(int newBottom); // задать нижнюю границу

		void SetWidth(); // задать ширину
		void SetHeight(); // задать высоту

		void Move(int dx, int dy); // переместить прямоугольник на вектор (dx, dy)
		void Scale(int sx, int sy); // масшиабировать sx по x, sy gо y
		bool Intersect(CRectangle const& other); // найти пересечение с прямоугольником other
	private:
		int m_left; // левая граница
		int m_top; // верхняя граница
		int m_width; // ширина
		int m_height; // высота		
};

