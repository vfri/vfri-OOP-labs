// lab072CatchTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../lab072/CMyArray.h"


TEST_CASE("Trivial")
{
	std::cout << "Trueism" << std::endl;
	CHECK((1 > 0) == true);
}

