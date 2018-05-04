#include "stdafx.h"
#include "../lab024/GeneratePrimes.h"

std::vector<bool> SieveResult(unsigned int bound) // ���������� ������� �� ������ ������ ����������,
{	// �������� 1 �� �������� ������� �����
	std::vector<bool> result(bound + 1, 1);
	result[0] = result[1] = 0;

	size_t lastPrime = 2;
	while (lastPrime * lastPrime <= bound)
	{
		for (size_t i = lastPrime * lastPrime; i <= bound; i += lastPrime)
		{
			result[i] = false;
		}
		std::vector<bool>::iterator startFindNextPrime = result.begin() + lastPrime + 1;
		std::vector<bool>::iterator itPrimes = std::find(startFindNextPrime, result.end(), true);
		lastPrime += std::distance(startFindNextPrime, itPrimes) + 1;
	}
	return result;
}

std::set<int> GeneratePrimeNumbersSet(unsigned int upperBound)
{
	std::vector<bool> primesPositions = SieveResult(upperBound);
	std::set<int> result;
	int number = 0;
	for (auto it = primesPositions.begin(); it != primesPositions.end(); ++it)
	{
		if (*it)
		{
			result.insert(result.end(), number);
		}
		++number;		
	}
	return result;
}
