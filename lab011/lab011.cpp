// lab011.cpp: определяет точку входа для консольного приложения.
// Отмечает номера строк в данном файле, включающих заданную подстроку

#include "stdafx.h"

using namespace std;

bool PrintLineNumbersWithText(istream& inFile, string& exampleString) // выводит номера строк, в которых встретился образец
{
	string currString; // очередная строка данного файла

	size_t stringNumber = 1;
	string::size_type positionToFind;
	bool found = false;

	while (getline(inFile, currString)) // пока не достигнут конец файла, читаем очередную его строку в currString
	{
		positionToFind = currString.find(exampleString); // выводим на экран
		if (positionToFind != string::npos)
		{
			cout << stringNumber << endl;
			found = true;
		}
		stringNumber++;
	}

	return found; // true, если текст встретился
}


int main(int argc, char* argv[])
{
	cout << "Program is to find inclusions of the given string in given file" << endl;

	if (argc < 3)
	{
		cout << "The program must have two arguments: 1) file name; 2) string to find" << endl;
		return 0; // недостаточно аргументов
	}

	string fileName = argv[1];
	ifstream sourceFile(fileName); // попытка открыть файл
	if (!sourceFile)
	{
		cout << "File is not found!" << endl;
		return 1;
	}

	string exampleString = argv[2]; // строка, которую ищем

	if (PrintLineNumbersWithText(sourceFile, exampleString))
	{
		cout << "These are numbers of strings in file " << fileName << ", there the string \"" << exampleString << "\" is appear." << endl;
	}
	else
	{
		cout << "There are no appearences of string " << exampleString << " in file " << fileName << endl;
		return 1;
	}

	
	return 0;
}

