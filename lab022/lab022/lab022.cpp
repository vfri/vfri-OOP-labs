// lab022.cpp: определяет точку входа для консольного приложения.
// HTML Decode

#include "stdafx.h"


void SubstCode(std::string& codeString, size_t& pos, std::map<std::string, char>& substSymbol) 
{ // делает замену на месте амперсанда
	for (std::map<std::string, char>::iterator it = substSymbol.begin(); it != substSymbol.end(); ++it)
	{
		if (codeString.find(it->first, pos) == pos)
		{
			codeString.replace(pos, (it->first).size(), 1, it->second);
			break;
		}
	}
	pos++;
}


void Decode(std::string& codeString, size_t& ampsNum, std::map<std::string, char>& substSymbol)
{ // декодирует строку	
	size_t currPos;
	currPos = 0;
	while (currPos != std::string::npos)
	{
		currPos = codeString.find_first_of('&', currPos);
		if (currPos != std::string::npos)
		{
			SubstCode(codeString, currPos, substSymbol);
			ampsNum++;
		}
	}
}


int main()
{
	std::map<std::string, char> substSymbol = {	{"&quot;", '\"'},
												{"&apos;", '\''},
												{"&lt;", '<'},
												{"&gt;", '>'},
												{"&amp;", '&'} };

			
	std::string codeString;
	size_t ampsNum = 0;
		
	while (std::getline(std::cin, codeString))
	{
		Decode(codeString, ampsNum, substSymbol);
		std::cout << codeString;
		printf("\n");
	}
	printf("%d ampersands!\n", ampsNum);
	
	return 0;
}

