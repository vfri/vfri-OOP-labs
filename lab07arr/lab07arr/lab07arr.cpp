// lab07arr.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "MyArray.h"


int main(int argc, char* argv[])
{
	arrayenv::CMyArray<std::vector<int>> arrVecint1;
	std::vector<int> firstElem1 = { 1, 3, 5 };
	arrVecint1.push_back(firstElem1);
	std::cout << arrVecint1[0][1] << std::endl;
	
	return 0;
}