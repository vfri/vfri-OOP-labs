// lab07arrCatchTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../lab07arr/MyArray.h"

TEST_CASE("Appended to empty CMyArray can be got by back()")
{
	arrayenv::CMyArray<std::string> strArr1;
	strArr1.push_back(std::string("first"));
	strArr1.push_back(std::string("second"));
	std::string last1 = strArr1.back();
	std::string expLast1 = std::string("second");
	CHECK(last1 == expLast1);
}


TEST_CASE("Copiing ctor keeps on emptyness and keeps on nonempty content of array")
{
	arrayenv::CMyArray<std::string> strArr2;
	arrayenv::CMyArray<std::string> strArr2copy(strArr2);

	CHECK(strArr2copy.empty());

	strArr2.resize(6);
	strArr2[0] = std::string("This ");
	strArr2[1] = std::string("is the ");
	strArr2[2] = std::string("house ");
	strArr2[3] = std::string("that ");
	strArr2[4] = std::string("Jack ");
	strArr2[5] = std::string("built");

	arrayenv::CMyArray<std::string> strArr2copy2(strArr2);
	std::string hjb = strArr2copy2[0];
	
	for (size_t i = 1; i < strArr2copy2.size(); ++i)
	{
		hjb += strArr2copy2[i];
	}

	std::string expPhrase = "This is the house that Jack built";
	CHECK(hjb == expPhrase);


}

TEST_CASE("Copiing interval marked by iterators is possible")
{
	arrayenv::CMyArray<std::string> strArr2;
	
	strArr2.push_back(std::string("This "));
	strArr2.push_back(std::string("is the "));
	strArr2.push_back(std::string("house "));
	strArr2.push_back(std::string("that "));
	strArr2.push_back(std::string("Jack "));
	strArr2.push_back(std::string("built"));

	arrayenv::CMyArray<std::string>::const_iterator houseIter = strArr2.begin();
	houseIter++;
	houseIter++;
	CHECK(*houseIter == std::string("house "));
	arrayenv::CMyArray<std::string>::const_iterator jackIter = strArr2.end();
	jackIter--;
	CHECK(*jackIter == std::string("built"));

	arrayenv::CMyArray<std::string> htj(houseIter, jackIter);
	CHECK(htj[1] == std::string("that "));

	arrayenv::CMyArray<std::string>::iterator dataIter = htj.data();
	CHECK(htj.size() == 3);
	CHECK(*dataIter == std::string("house "));

	
	*dataIter = std::string("mouse ");
	
	std::string transformedHtj = htj[0] + htj[1] + htj[2];
	CHECK(transformedHtj == std::string("mouse that Jack "));
	
}

TEST_CASE("Filling ctor can fill array by many equal values")
{
	std::vector<int> sixSeven = { 6, 7 };
	arrayenv::CMyArray<std::vector<int> > fiveTimesSixSeven(5, sixSeven);

	CHECK(fiveTimesSixSeven[4][0] == 6);
	CHECK(fiveTimesSixSeven[3][1] == 7);
}


TEST_CASE("Copiing assignment for T = std::vector<int> works right")
{
	arrayenv::CMyArray<std::vector<int>> vecintArr1;
	vecintArr1.push_back(std::vector<int>({ 5, 3, 1 }));
	vecintArr1.push_back(std::vector<int>({ 16, 18, 20, 22 }));
	int lastInFirst = vecintArr1.back()[2];
	int expLastInFirst = 20;
	CHECK(expLastInFirst == lastInFirst);

	arrayenv::CMyArray<std::vector<int>> vecintArr2;
	vecintArr2.push_back(std::vector<int>({ 117, 771 }));
	CHECK(vecintArr2.back()[0] == 117);

	vecintArr2 = vecintArr1;
	CHECK(vecintArr2.back()[1] == 18);

}





