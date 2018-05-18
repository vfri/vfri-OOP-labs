// main.cpp: ���������� ����� ����� ��� ����������� ����������.
// ������� ��� �������� ���� � ���� � �������� ����� �� ����������

#include "stdafx.h"
#include "../lab023/Dictionary.h"

int main(int argc, char* argv[])
{
	// setlocale(LC_ALL, "Rus");

	std::cout << "Translates words and sentences from english into russian\n"
		<< "Input phrase to translate or ... to exit" << std::endl;

	std::string vocaFileName = (argc > 1) ? argv[1] : "Vocabulary1.vcb";
	dict currVocabularDir = {}; // c������ ���� -> ���
	dict currVocabularRev = {}; // ������� ��� -> ����

	GetDictionaryFromFile(vocaFileName, currVocabularDir);
	BuildRevDictionary(currVocabularRev, currVocabularDir);

	if (Session(currVocabularDir, currVocabularRev)) // ������ ������ �� ��������
	{
		SaveDictionary(currVocabularDir, vocaFileName);
	}

	std::cout << "Good bye!" << std::endl;

	return 0;
}