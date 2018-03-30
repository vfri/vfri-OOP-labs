#pragma once

#include <iostream>
#include <string>
#include <map>

void SubstCode(std::string& codeString, size_t& pos, std::map<std::string, char>& substSymbol);
void Decode(std::string& codeString, size_t& ampsNum, std::map<std::string, char>& substSymbol);

