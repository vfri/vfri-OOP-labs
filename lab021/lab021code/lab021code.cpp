// lab021code.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include "../lab021code/Modivec.h"


std::vector<float> LoadSeriesToVector(std::istream& input)
{
	std::vector<float> values;

	std::copy(std::istream_iterator<float>(input), std::istream_iterator<float>(), std::back_inserter(values));
	input.clear();

	return values;
}

void LoadVectorToSeries(const std::vector<float>& values, std::ostream& output)
{
	std::copy(values.begin(), values.end(), std::ostream_iterator<float>(output, " "));
}


void Modificate(std::vector<float>& values)
{
	if (values.size() != 0)
	{
		auto minMax = std::minmax_element(values.begin(), values.end());
		float negaModifier = (*minMax.first) * (*minMax.second);
		for (auto& f : values)
		{
			f = (f < 0) ? f * negaModifier : f;
		}
	}
}





