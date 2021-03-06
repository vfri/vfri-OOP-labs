// lab022.cpp: определяет точку входа для консольного приложения.
// HTML Decode

#include "stdafx.h"


static std::map<std::string, char> substSymbol = { { "&quot;", '\"' },
													{ "&apos;", '\'' },
													{ "&lt;"  , '<' },
													{ "&gt;"  , '>' },
													{ "&amp;" , '&' } };


std::string SubstCode(const std::string& codeString, size_t& pos)
{ // делает замену на месте амперсанда
	std::string result = codeString.substr(0, pos);
	bool found = false;
	for (auto it = substSymbol.begin(); it != substSymbol.end(); ++it)
	{
		if (codeString.compare(pos, (it->first).size(), it->first) == 0)
		{
			found = true;
			result = result + it->second + codeString.substr(pos + (it->first).size());
			break;
		}
	}
	if (!found)
	{
		result = codeString;
	}
	pos++;
	return result;
}


void Decode(std::string& codeString)
{ // декодирует строку	
	size_t currPos;
	currPos = 0;
	while (currPos != std::string::npos)
	{
		currPos = codeString.find_first_of('&', currPos);
		if (currPos != std::string::npos)
		{
			codeString = SubstCode(codeString, currPos);
		}
	}
}






