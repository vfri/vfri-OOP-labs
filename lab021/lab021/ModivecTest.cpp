#include "stdafx.h"
#include "Modivec.h"

TEST_CASE("Modivec test on values validity")
{
	std::vector<float> v1 = { -1.0, 3.0 };
	std::vector<float> v1expRes = { 3.0, 3.0 };
	Modificate(v1);
	
	CHECK(v1 == v1expRes);

	std::vector<float> v2 = { 4, -1, 3, -2, 5, -3 };
	std::vector<float> v2expRes = { 4, 15, 3, 30, 5, 45 };
	Modificate(v2);

	CHECK(v2 == v2expRes);

	std::vector<float> v3 = { 1, 2, 3, 4, 5, 6 };
	std::vector<float> v3expRes = { 1, 2, 3, 4, 5, 6 };
	Modificate(v3);

	CHECK(v3 == v3expRes);

	std::vector<float> v4 = { -2 };
	std::vector<float> v4expRes = { -8 };
	Modificate(v4);

	CHECK(v4 == v4expRes);

	std::vector<float> v5 = { -3.5, -1, -2.0, 3, 4, 6 };
	std::vector<float> v5expRes = { 73.5, 21, 42, 3, 4, 6 };
	Modificate(v5);

	CHECK(v5 == v5expRes);

}

