#pragma once
#include "stdafx.h"

template < typename T >
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (arr.empty())
	{
		return false;
	}
	
	T max = arr[0];
	
	for (size_t i = 0; i < arr.size(); ++i)
	{
		std::cout << arr[i] << " vs " << max << std::endl;
		if (arr[i] > max)
		{
			max = arr[i];
			std::cout << "New max\n";
		}

	}

	maxValue =  max;

	return true;
}

template <>
bool FindMax<const char*>(std::vector<const char*> const& arr, 	const char * & maxValue)
{
	if (arr.empty())
	{
		return false;
	}

	const char* max = arr[0];

	for (size_t i = 0; i < arr.size(); ++i)
	{
		std::cout << arr[i] << " vs " << max << std::endl;
		if (strcmp(arr[i], max) > 0)
		{
			max = arr[i];
			std::cout << "New max\n";
		}

	}

	maxValue = max;

	return true;
}