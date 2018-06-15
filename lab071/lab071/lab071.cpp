// lab071.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Findmax.h"


int main()
{
	std::vector<int> intVec = { 12, 2, 31, 5, 21, 7, 82, 13, 24 };
	std::vector<double> doubleVec = { 1e-2, .23, 1.204, 0.23, -4.32, 1.8e-1 };
	std::vector <std::string> strVec = { std::string("cat"), std::string("dog"), std::string("catalog"), 
		std::string("door"), std::string("ifelse"), std::string("ace"), std::string("arcus") };

	std::vector<const char*> cstrVec= { "red", "orange", "yellow", "green", "white", "black", "cian" };

	int max = 0;
	if (FindMax(intVec, max))
	{
		std::cout << "Maximal element is " << max << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}

	double doubleMax = 0;
	if (FindMax(doubleVec, doubleMax))
	{
		std::cout << "Maximal element is " << doubleMax << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}
	
	std::string maxStr;
		if (FindMax(strVec, maxStr))
	{
		std::cout << "Maximal element is " << maxStr << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}
	
	const char* maxCstr = { '\0' };
	if (FindMax(cstrVec, maxCstr))
	{
		std::cout << "Maximal element is " << maxCstr << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}

	return 0;
}

