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

	std::vector<const char*> cstrVec = { "red", "orange", "yellow", "green", "white", "black", "cian" };

	FindAndPrintMax(intVec);
	FindAndPrintMax(doubleVec);
	FindAndPrintMax(strVec);
	FindAndPrintMax(cstrVec);
	
	return 0;
}
/*	
	int max = 0;
	std::copy(intVec.begin(), intVec.end(), std::ostream_iterator<int>(std::cout, " "));
	if (FindMax(intVec, max, CComparator<int>()))
	{
		std::cout << "Maximal element is " << max << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}

	double doubleMax = 0;
	if (FindMax(doubleVec, doubleMax, CComparator<double>()))
	{
		std::cout << "Maximal element is " << doubleMax << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}
	
	std::string maxStr;
		if (FindMax(strVec, maxStr, CComparator<std::string>()))
	{
		std::cout << "Maximal element is " << maxStr << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}
	
	const char* maxCstr = { '\0' };
	if (FindMax(cstrVec, maxCstr, CComparator<const char*>()))
	{
		std::cout << "Maximal element is " << maxCstr << std::endl;
	}
	else
	{
		std::cout << "Vector is empty!" << std::endl;
	}

	return 0;
}

*/