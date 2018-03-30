// lab021.cpp: определяет точку входа для консольного приложения.
// преобразование последовательности вещественных чисел методами vector

#include "stdafx.h"
#include "Modivec.h"


std::vector<float> LoadSeriesToVector(std::istream& input)
{
	std::vector<float> values;

	std::copy(std::istream_iterator<float>(input), std::istream_iterator<float>(), std::back_inserter(values));
	std::cin.clear();

	return values;
}

void LoadVectorToSeries(const std::vector<float>& values, std::ostream& output)
{
	std::copy(values.begin(), values.end(), std::ostream_iterator<float>(output, " "));
}

void Modificate(std::vector<float>& values)
{
	std::vector<float> result;
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
}


void ModifyFloatSeries()
{
	std::vector<float> values = LoadSeriesToVector(std::cin);

	Modificate(values);	
	
	LoadVectorToSeries(values, std::cout);
}

