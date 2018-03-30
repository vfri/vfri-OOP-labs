#include "stdafx.h"
#include "HTMLDecode.h"

TEST_CASE("HTMLDecode for strings")
{
	
	std::map<std::string, char> substSymbol = { { "&quot;", '\"' },
												{ "&apos;", '\'' },
												{ "&lt;"  , '<'  },
												{ "&gt;"  , '>'  },
												{ "&amp;" , '&'  } };
	
	size_t ampsNum = 0;
	std::string inputStr1  = "s&qouta&&gtsrt dhh   &  fd &";
	std::string str1expRes = "s&qouta&&gtsrt dhh   &  fd &";
	Decode(inputStr1, ampsNum, substSymbol);

	CHECK(inputStr1 == str1expRes);

	std::string inputStr2 = "s&quot;a&&quot;gtsrt dhh   &  fd &";
	std::string str2expRes = "s\"a&\"gtsrt dhh   &  fd &";
	Decode(inputStr2, ampsNum, substSymbol);

	CHECK(inputStr2 == str2expRes);

	std::string inputStr3 = "&&&lt;xyz&gt;&amp;&amp;&&abcd  e f &apos";
	std::string str3expRes = "&&<xyz>&&&&abcd  e f &apos";
	Decode(inputStr3, ampsNum, substSymbol);

	CHECK(inputStr3 == str3expRes);

	std::string inputStr4 = "&lt;3&apos; Hello &gt;&& &amp !&apos;";
	std::string str4expRes = "<3\' Hello >&& &amp !\'";
	Decode(inputStr4, ampsNum, substSymbol);

	CHECK(inputStr4 == str4expRes);

	std::string inputStr5 = "&&&&amp;&&&amp;&&amp;&amp;";
	std::string str5expRes = "&&&&&&&&&&";
	Decode(inputStr5, ampsNum, substSymbol);

	CHECK(inputStr5 == str5expRes);

	std::string inputStr6 = ""; // empty input string
	std::string str6expRes = "";
	Decode(inputStr6, ampsNum, substSymbol);

	CHECK(inputStr6 == str6expRes);

	std::string inputStr7 = "&amp";
	std::string str7expRes = "&amp";
	Decode(inputStr7, ampsNum, substSymbol);

	CHECK(inputStr7 == str7expRes);

}