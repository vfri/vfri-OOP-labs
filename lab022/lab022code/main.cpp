#include "stdafx.h"
#include "HTMLdecode.h"


int main()
{
	std::cout << "Enter some strings with &quot; , &apos; , &lt; , &gt; , &amp; macroses to decode:\n";
	std::string codeString;

	while (std::getline(std::cin, codeString))
	{
		Decode(codeString);
		std::cout << codeString << "\n";
	}

	return 0;
}
