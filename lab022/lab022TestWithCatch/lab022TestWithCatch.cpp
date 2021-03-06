// lab022TestWithCatch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../lab022code/HTMLdecode.h"



static std::map<std::string, char> substSymbol = { { "&quot;", '\"' },  { "&apos;", '\'' }, { "&lt;"  , '<' }, { "&gt;"  , '>' }, { "&amp;" , '&' } };



TEST_CASE("HTMLDecode for strings: empty, nonmodified")
{
	std::string inputStr0 = "";
	std::string str0expRes = "";
	std::string str0realRes = Decode(inputStr0);
	
	CHECK(str0realRes == str0expRes);

	std::string inputStr1 = "s&qouta&&gtsrt dhh   &  fd &";
	std::string str1expRes = "s&qouta&&gtsrt dhh   &  fd &";
	std::string str1realRes = Decode(inputStr1);

	CHECK(str1realRes == str1expRes);
}

TEST_CASE("HTMLDecode for strings: decodings")
{

	std::string inputStr2 = "s&quot;a&&quot;gtsrt dhh   &  fd &";
	std::string str2expRes = "s\"a&\"gtsrt dhh   &  fd &";
	std::string str2realRes = Decode(inputStr2);
	
	CHECK(str2realRes == str2expRes);

	std::string inputStr3 = "&&&lt;xyz&gt;&amp;&amp;&&abcd  e f &apos";
	std::string str3expRes = "&&<xyz>&&&&abcd  e f &apos";
	std::string str3realRes = Decode(inputStr3);
	
	CHECK(str3realRes == str3expRes);

	std::string inputStr4 = "&lt;3&apos; Hello &gt;&& &amp !&apos;";
	std::string str4expRes = "<3\' Hello >&& &amp !\'";
	std::string str4realRes = Decode(inputStr4);
	
	CHECK(str4realRes == str4expRes);

}



TEST_CASE("HTMLDecode for strings: ampersands")
{

	std::string inputStr5 = "&&&&amp;&&&amp;&&amp;&amp;";
	std::string str5expRes = "&&&&&&&&&&";
	std::string str5realRes = Decode(inputStr5);

	CHECK(str5realRes == str5expRes);

	std::string inputStr6 = "&amp";
	std::string str6expRes = "&amp";
	std::string str6realRes = Decode(inputStr6);

	CHECK(inputStr6 == str6expRes);

}



