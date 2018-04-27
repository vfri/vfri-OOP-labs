#pragma once

#include <vector>
#include <set>

std::vector<bool> SieveResult(unsigned int bound); // позиции простых по решету Эратосфена
std::set<int> GeneratePrimeNumbersSet(unsigned int upperBound); // множество простых, не больших upperBound
