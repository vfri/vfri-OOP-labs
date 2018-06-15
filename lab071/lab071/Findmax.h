#pragma once
#include "stdafx.h"

template <typename T> 
class CComparator 
{ 
public: 
	bool GreaterThan(T const& a, T const& b) const
	{ 
		return a > b; 
	} 
}; 

template <> 
class CComparator<const char *> 
{ 
public: 
	bool GreaterThan(const char * const& a, const char * const& b) const 
	{ 
		return strcmp(a, b) > 0; 
	} 
};


template < typename T, class Comp>
bool FindMax(std::vector<T> const& arr, T& maxValue, Comp const& comp)
{
	try
	{
		if (arr.empty())
		{
			return false;
		}

		T max = arr[0];

		for (size_t i = 0; i < arr.size(); ++i)
		{
			if (comp.GreaterThan(arr[i], max)) 	max = arr[i];
		}

		maxValue = max;

		return true;
	}
	catch (...)
	{
		throw;
	}
	return false;
}

template <typename T>
void FindAndPrintMax(std::vector<T> const& arr)
{
	T max;
	std::cout << "\n";
	std::copy(arr.begin(), arr.end(), std::ostream_iterator<T>(std::cout, " "));
	std::cout << "\n";
	if (FindMax(arr, max, CComparator<T>()))
	{
		std::cout << "Maximal element is " << max << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}
}
