// lab051.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CRational.h"


int main()
{
	CRational test1(20, -15);

	std::cout << test1.GetNumerator() << std::endl;

	return 0;
}

