// lab012.cpp: определяет точку входа для консольного приложения.
// преобразует число из записи в позиционной системы с одним основанием в систему с другим. Число должно помещаться в integer

#include "stdafx.h"

void ValidDigit(bool symToNum, char& symbol, int& digit, int radix, int& inValid) 
{   // symToNum -- сделать из цифры однозначное число, !symToNum -- сделать из однозначного числа цифру
	std::string digSetUpper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string digSetLower = "0123456789abcdefghijklmnopqrstuvwxyz";
	std::string digitsUpper = digSetUpper.substr(0, radix);
	std::string digitsLower = digSetLower.substr(0, radix);
	
	int digUppValue = digitsUpper.find(symbol);
	int digLowValue = digitsLower.find(symbol);

	inValid = 0;

	if (symToNum)
	{
		if (digUppValue != std::string::npos)
		{
			digit = digUppValue;
		}
		else if (digLowValue != std::string::npos)
		{
			digit = digLowValue;
		}
		else
		{
			inValid = 1;
		}
	}
	else
	{
		if ((digit >= 0) && (digit < radix))
		{
			symbol = digitsUpper.at(digit);
		}
		else
		{
			inValid = 1;
		}
	}
}

bool WillBeResultInRange(int currResult, bool isNegative, int digValue, int radix)
{
	int bound = std::numeric_limits<int>::max();
	if (isNegative)
	{
		bound = std::numeric_limits<int>::min();
	}
	int quotient = bound / radix;
	int rest = bound - quotient * radix;
	return (currResult <= std::abs(quotient)) && (digValue <= std::abs(rest));
}

int StringToInt(const std::string& str, int radix, int& wasError)
{
	int result = 0;
	bool isNegative = false;
			
	size_t pos = 0;
	
	if (str.at(0) == '-')
	{
		isNegative = true;
		pos++;
	}
		
	int digValue = 0;
			
	while (pos < str.length())
	{
		char symbol = str.at(pos);
		ValidDigit(true, symbol, digValue, radix, wasError); // проверяем, может ли очередной символ быть цифрой
		if (wasError == 1)
		{
			break;
		}
		if (WillBeResultInRange(result, isNegative, digValue, radix))
		{
			result = result * radix + digValue;
		}
		else
		{
			wasError = 2; // переполнение
			break; 
		}
		pos++;
	}
		
	return isNegative ? -result : result;
}

std::string IntToString(int n, int radix, int& wasError)
{
	std::string numberImage = std::string();
	int signum = (n > 0) ? 1 : -1;
	int mediaResult = n;
	int currDigit;
	char nextSymbol = '#';
	
	while (mediaResult != 0)
	{
		currDigit = (signum * mediaResult) % radix;
		mediaResult = (mediaResult - signum * currDigit) / radix;
		
		ValidDigit(false, nextSymbol, currDigit, radix, wasError);
		numberImage.insert(0, 1, nextSymbol);
	}
	if (n == 0)
	{
		numberImage.insert(0, 1, '0');
	}
	if (n < 0)
	{
		numberImage.insert(0, 1, '-');
	}
	numberImage.push_back('\n');
	return numberImage;
}


int main(int argc, char* argv[])
{
	std::cout << "Transform given integer value form one number system to other\n" << std::endl;
	std::cout << "Radices of value from 2 to 36. Digits from 10 to 35 are letters form A to Z\n" << std::endl;

	if (argc < 4)
	{
		std::cout << "The program must have three arguments: 1) present radix; 2) new radix; 3) value to transform" << std::endl;
		return 0; // недостаточно аргументов
	}

	int sourceNotation = std::strtoul(argv[1], nullptr, 10);
	if ((sourceNotation < 2) || (sourceNotation > 36))
	{
		std::cout << "Invalid source notation! Number between 2 and 36 expected" << std::endl;
		return 1;
	}
	int destiNotation = std::strtoul(argv[2], nullptr, 10);
	if ((destiNotation < 2) || (destiNotation > 36))
	{
		std::cout << "Invalid destination notation! Number between 2 and 36 expected" << std::endl;
		return 1;
	}
	
	std::string testString = argv[3];
			
	int error = 0;
	int amount = StringToInt(testString, sourceNotation, error);
	if (error == 1)
	{
		std::cout << "Illegal symbols in number image!" << std::endl;
		return 1;
	}
	if (error == 2)
	{
		std::cout << "Given number " << argv[3] << " is out of integer range!" << std::endl;
		return 1;
	}

	std::string newImage = IntToString(amount, destiNotation, error);
	std::cout << argv[3] << " in radix " << sourceNotation << " will in radix " 
			  << destiNotation << " be " << newImage.c_str() << std::endl;

		
	return 0;
}

