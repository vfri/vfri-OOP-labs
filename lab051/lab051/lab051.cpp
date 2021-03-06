// lab051.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CRational.h"


int main()
{
	CRational test1(20, -15);

	std::cout << test1.GetNumerator() << std::endl;

	CRational test2(4, 7);
	CRational test3(1, 14);
	(test3 += test3) += test2;

	test2.operator+=(test2);

	std::cout << test2.GetNumerator() << "/" << test2.GetDenominator() << std::endl;

	std::cout << test2 << std::endl;

	return 0;
}

