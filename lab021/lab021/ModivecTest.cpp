#include "stdafx.h"
#include "Modivec.h"

TEST_CASE("Modivec test")
{
	CHECK(TrimBlanks("") == "");
	CHECK(TrimBlanks("Hello") == "Hello");
	CHECK(TrimBlanks("   Hello") == "Hello");
	CHECK(TrimBlanks("Hello   ") == "Hello");
	CHECK(TrimBlanks("    Hello   ") == "Hello");
	CHECK(TrimBlanks("    ") == "");
	CHECK(TrimBlanks("A") == "A");
}