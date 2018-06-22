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
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Comp const& comp)
{
	if (arr.empty())
	{
		return false;
	}
	
	auto maxIt = arr.begin();
	
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (comp.GreaterThan(*it, *maxIt)) maxIt = it;
	}

	maxValue = *maxIt;

	return true;
}

template <typename T>
void FindAndPrintMax(std::vector<T> const& arr)
{
	T max;
	std::cout << "\n";
	std::copy(arr.begin(), arr.end(), std::ostream_iterator<T>(std::cout, " "));
	std::cout << "\n";
	if (FindMaxEx(arr, max, CComparator<T>()))
	{
		std::cout << "Maximal element is " << max << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}
}
