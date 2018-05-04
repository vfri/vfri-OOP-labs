#include "stdafx.h"
#include "../lab024/GeneratePrimes.h"

std::vector<bool> SieveResult(unsigned int bound) // просеивает позиции по методу решета Ёратосфена,
{	// оставл€€ 1 на позици€х простых чисел
	std::vector<bool> result(bound + 1, 1);
	result[0] = result[1] = 0;

	unsigned int lastPrime = 2;
	while (lastPrime * lastPrime <= bound)
	{
		for (unsigned int i = lastPrime * lastPrime; i <= bound; i += lastPrime)
		{
			result[i] = false;
		}
		std::vector<bool>::iterator startFindNextPrime = result.begin() + lastPrime + 1;
		std::vector<bool>::iterator itPrimes = std::find(startFindNextPrime, result.end(), true);
		lastPrime += std::distance(startFindNextPrime, itPrimes) + 1;
	}
	// std::copy(result.begin(), result.end(), std::ostream_iterator<bool>(std::cout, " "));
	std::cout << std::endl;
	return result;
}

std::set<int> GeneratePrimeNumbersSet(unsigned int upperBound, unsigned int& primesAmount)
{
	std::vector<bool> primesPositions = SieveResult(upperBound);
	std::vector<bool>::iterator it = primesPositions.begin();
	std::set<int> result;
	primesAmount = 0;
	while ((it = std::find(++it, primesPositions.end(), true)) != primesPositions.end())
	{
		primesAmount++;
		result.insert(std::distance(primesPositions.begin(), it));
	}
	std::cout << primesAmount << " primary numbers up to " << upperBound << " overall" << std::endl;
	return result;
}
