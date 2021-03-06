// lab021.cpp: функция преобразования координат вектора вещественных чисел
// умножает отрицательные координаты на произведение наибольшего и наименьшего

#include "stdafx.h"
#include "Modivec.h"


void Modificate(std::vector<float>& values)
{
	if (values.size() != 0)
	{
		auto minMax = std::minmax_element(values.begin(), values.end());
		float negaModifier = (*minMax.first) * (*minMax.second);			// на это число надо умножить отрицательные элементы
		for (auto& f : values)
		{
			f = (f < 0) ? f * negaModifier : f;
		}
	}
}

