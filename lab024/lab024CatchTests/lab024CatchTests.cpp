// lab024CatchTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../lab024/GeneratePrimes.h"


TEST_CASE("Upper bound ab, -1, 0, 1 -- wrong bound")
{
	constexpr unsigned int maxBound = 100000000;
	int numArg1 = 2; char boundStr1[] = "ab";
	unsigned int upperBound1 = maxBound;
	if (numArg1 > 1)
	{
		upperBound1 = ((isdigit(boundStr1[0]) && (std::stoi(boundStr1) >= 0))) ? std::stoi(boundStr1) : maxBound;
	}
	
	CHECK(upperBound1 == 100000000);

	int numArg2 = 2; char boundStr2[] = "-1";
	unsigned int upperBound2 = maxBound;
	if (numArg2 > 1)
	{
		upperBound2 = ((isdigit(boundStr2[0]) && (std::stoi(boundStr2) >= 0))) ? std::stoi(boundStr2) : maxBound;
	}

	CHECK(upperBound2 == 100000000);

	unsigned int primesAmountFor0;
	GeneratePrimeNumbersSet(0, primesAmountFor0);

	CHECK(primesAmountFor0 == 0);

	unsigned int primesAmountFor1;
	GeneratePrimeNumbersSet(1, primesAmountFor1);

	CHECK(primesAmountFor1 == 0);

}


TEST_CASE("Upper bound 20, 100, 99999999, 1000000000")
{
	unsigned int primesAmountFor20;
	GeneratePrimeNumbersSet(20, primesAmountFor20);

	CHECK(primesAmountFor20 == 8);

	unsigned int primesAmountFor100;
	GeneratePrimeNumbersSet(100, primesAmountFor100);

	CHECK(primesAmountFor100 == 25);

	unsigned int primesAmountForEightNines;
	GeneratePrimeNumbersSet(99999999, primesAmountForEightNines);

	CHECK(primesAmountForEightNines == 5761455);

	unsigned int primesAmountForHuge;
	GeneratePrimeNumbersSet(1000000000, primesAmountForHuge);

	CHECK(primesAmountForHuge == 5761455);

}




