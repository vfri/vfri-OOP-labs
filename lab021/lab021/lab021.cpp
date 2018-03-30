// lab021.cpp: определяет точку входа для консольного приложения.
// преобразование последовательности вещественных чисел методами vector

#include "stdafx.h"



int main()
{
	std::vector<float> values;

	std::copy(std::istream_iterator<float>(std::cin), std::istream_iterator<float>(), std::back_inserter(values));
	std::cin.clear();

	std::copy(values.begin(), values.end(), std::ostream_iterator<float>(std::cout, " "));
		
	float maxValue = *max_element(values.begin(), values.end());
	float minValue = *min_element(values.begin(), values.end());
	float negaModifier = minValue * maxValue;

	for (std::vector<float>::iterator it = values.begin(); it != values.end(); ++it)
	{
		if (*it < 0)
		{
			*it = *it * negaModifier;
		}
	}
	
	std::copy(values.begin(), values.end(), std::ostream_iterator<float>(std::cout, " "));
	
	return 0;
}

