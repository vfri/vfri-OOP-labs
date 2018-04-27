// lab024.cpp: определяет точку входа для консольного приложения.
// поиск простых чисел в пределах upperBound

#include "stdafx.h"
#include "GeneratePrimes.h"



int main(int argc, char* argv[])
{
	unsigned int upperBound = 100000000;
	if (argc > 1) 
	{
		upperBound = std::stoi(argv[1]);
	}
	std::cout << "Finds set of prime numbers below " << upperBound << std::endl;
		
	std::set<int> primes(GeneratePrimeNumbersSet(upperBound));
	std::copy(primes.begin(), primes.end(), std::ostream_iterator<unsigned int>(std::cout, " "));
		
	return 0;
}

