// lab012.cpp: определяет точку входа для консольного приложения.
// преобразует число из записи в позиционной системы с одним основанием в систему с другим. Число должно помещаться в integer

#include "stdafx.h"

enum errorType { NoError = 0, IllegalSymbol, OutOfRange };

std::string digSetUpper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string digSetLower = "0123456789abcdefghijklmnopqrstuvwxyz";

int DigitFromZifra(const char symbol, const std::string& digitsUpper, const std::string& digitsLower, errorType& wasError)
{
	
	int digUppValue = digitsUpper.find(symbol);
	int digLowValue = digitsLower.find(symbol);

	wasError = NoError;
	int digit = -1;

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
		wasError = IllegalSymbol;
	}
	
	return digit;
}

char ZifraFromDigit(const int digit, const int radix, const std::string& digitsUpper, errorType& wasError)
{
			
	wasError = NoError;
	char zifra = '#'; 

	if ((digit >= 0) && (digit < radix))
	{
		zifra = digitsUpper[digit];
	}
	else
	{
		wasError = IllegalSymbol;
	}
	
	return zifra;
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
	return ((currResult < std::abs(quotient)) || ((currResult == std::abs(quotient)) && (digValue <= std::abs(rest))));
}

int StringToInt(const std::string& str, int radix, errorType& wasError)
{
	std::string digitsUpper = digSetUpper.substr(0, radix);
	std::string digitsLower = digSetLower.substr(0, radix);
	
	int result = 0;
	bool isNegative = false;
			
	size_t pos = 0;
	
	if (str[0] == '-')
	{
		isNegative = true;
		pos++;
	}
		
	int digValue = 0;
			
	while (pos < str.length())
	{
		char symbol = str[pos];
		digValue = DigitFromZifra(symbol, digitsUpper, digitsLower, wasError); // проверяем, может ли очередной символ быть цифрой
		if (wasError == IllegalSymbol)
		{
			break;
		}
		if (WillBeResultInRange(result, isNegative, digValue, radix))
		{
			result = result * radix + digValue;
		}
		else
		{
			wasError = OutOfRange; // переполнение
			break; 
		}
		pos++;
	}
		
	return isNegative ? -result : result;
}

std::string IntToString(int n, int radix, errorType& wasError)
{
	std::string digitsUpper = digSetUpper.substr(0, radix);
	std::string numberImage;
	int signum = (n > 0) ? 1 : -1;
	int numberRest = n;
		
	while (numberRest != 0)
	{
		int currDigit = (signum * numberRest) % radix;
		numberRest = (numberRest - signum * currDigit) / radix;
		
		char nextSymbol = ZifraFromDigit(currDigit, radix, digitsUpper, wasError);
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


bool NoEnoughArgs(const int argcount)
{
	if (argcount < 4)
	{
		std::cout << "The program must have three arguments: 1) present radix; 2) new radix; 3) value to transform" << std::endl;
	}
	return (argcount < 4);
}

int whatNotation(const char* notationStr, const bool whatOfTwo) // whatOfTwo == 0 -- source, == 1 -- destination
{
	const unsigned int notation = std::strtoul(notationStr, nullptr, 10);
	const int result = ((notation < 2) || (notation > 36)) ? 0 : notation;
	if (!result)
	{
		const char* sourceDest = (whatOfTwo) ? "destination" : "source";
		std::cout << "Invalid " << sourceDest << " notation! Number between 2 and 36 expected" << std::endl;
	}
	return result;
}

std::string getNewImage(const std::string& givenString, const int sourceNotation, const int destiNotation)
{
	errorType error = NoError;
	
	int amount = StringToInt(givenString, sourceNotation, error);
	if (error == IllegalSymbol)
	{
		std::cout << "Illegal symbols in number image!" << std::endl;
	}
	if (error == OutOfRange)
	{
		std::cout << "Given number " << givenString.c_str() << " is out of integer range!" << std::endl;
	}

	return (error == NoError) ? IntToString(amount, destiNotation, error) : "";
}

int main(int argc, char* argv[])
{
	std::cout << "Transform given integer value form one number system to other\n" << std::endl;
	std::cout << "Radices of value from 2 to 36. Digits from 10 to 35 are letters form A to Z\n" << std::endl;
	
	if (NoEnoughArgs(argc)) return 0; // недостаточно аргументов
	const int sourceNotation = whatNotation(argv[1], false);
	const int destiNotation = whatNotation(argv[2], true);
	if (!(sourceNotation && destiNotation)) return 1; // неправильные основания систем счисления

	const std::string givenString = argv[3];
	
	std::string newImage = getNewImage(givenString, sourceNotation, destiNotation);
	if (newImage == "") return 1; // невозможно корректно обработать данную строку
	
	std::cout << givenString.c_str() << " in radix " << sourceNotation << " will in radix "
		<< destiNotation << " be " << newImage.c_str() << std::endl;
			
	return 0;
}

