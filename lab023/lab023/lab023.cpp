// lab023.cpp: определяет точку входа для консольного приложения.
// Словарь для перевода слов и фраз с русского языка на английский

#include "stdafx.h"


typedef std::multimap<std::string, std::string> dict;
enum state { WaitingForPhrase = 1, WaitingForTranslation, WaitingForAddTranslation };

// дописывает пары в файл словаря

// true, если файл словаря найден и открыт
bool VocaFileOpened(const std::string& vocaFileName, std::ifstream& vocaFile)
{
	vocaFile.open(vocaFileName, std::ios::out);
	return vocaFile.is_open();
}

// сохраняет словарь в файл
void StoreVocabular(const dict& vocabular, std::ostream& vocaFile)
{
	for (auto it = vocabular.begin(); it != vocabular.end(); ++it)
	{
		vocaFile << (*it).first << "\n" << (*it).second << "\n";
	}
}

// выгружает словарь из файла в память в виде multimap
bool LoadVocabular(std::istream& vocaFile, dict& vocabular)
{
	bool result = true;
	std::string eng, rus;
	while (getline(vocaFile, eng))
	{
		if (getline(vocaFile, rus))
		{
			vocabular.insert(std::pair<std::string, std::string>(eng, rus));
		}
		else
		{
			result = false;
		}
	}
	return result;
}

// проверяет, есть ли в словаре данное слово
bool PhraseExists(dict& vocabular, const std::string& phrase)
{
	return (vocabular.upper_bound(phrase) != vocabular.lower_bound(phrase));
}

// проверяет, существует ли уже данный перевод в словаре
bool TheTranslationExists(dict& vocabular, const std::string& phrase, const std::string& translation)
{
	bool result = false;
	for (auto it = vocabular.lower_bound(phrase); it != vocabular.upper_bound(phrase); ++it)
	{
		if (it->second == translation)
		{
			result = true;
			break;
		}
	}
	return result;
}

// добавляет перевод слова
void AddTranslation(dict& vocabular, const std::string& phrase, const std::string& translation)
{
	if (!TheTranslationExists(vocabular, phrase, translation))
	{
		vocabular.insert(std::pair<std::string, std::string>(phrase, translation));
	}
}

// выводит переводы данного слова
void PrintTranslations(dict& vocabular, const std::string& phrase)
{
	std::cout << std::endl;
	for (dict::iterator it = vocabular.lower_bound(phrase); it != vocabular.upper_bound(phrase); ++it)
	{
		std::cout << (*it).second << "\n";
	}
	std::cout << std::endl;
}


void SavePrevPhrase(std::string& prevPhrase, const std::string& inputPhrase)
{
	if ((inputPhrase != "") && (inputPhrase != "+"))
	{
		prevPhrase = inputPhrase;
	}
}

state OnPhraseRequest(const std::string& inputPhrase, dict& vocabular) // реакция на вводную фразу
{
	state waitFor;
	if (PhraseExists(vocabular, inputPhrase))
	{
		std::cout << "Translation(s) for \"" << inputPhrase << "\": ";
		PrintTranslations(vocabular, inputPhrase);
		std::cout << "If you want to add one more translation enter \"+\"" << std::endl;
		waitFor = WaitingForAddTranslation;
	}
	else
	{
		std::cout << "Where is no \"" << inputPhrase << "\" in dictionary yet." << std::endl;
		std::cout << "Write the translation or press only enter to skip" << std::endl;
		waitFor = WaitingForTranslation;
	}
	return waitFor;
}

state OnTranslationPrompt(const std::string& prevPhrase, const std::string& inputPhrase, dict& vocabular, bool& vocaChanged)
{	// реакция на запрос перевода
	state waitFor;
	if (inputPhrase != "")
	{
		AddTranslation(vocabular, prevPhrase, inputPhrase);
		std::cout << "Translation \"" << inputPhrase << "\" for \"" << prevPhrase << "\"is accepted" << std::endl;
		vocaChanged = true;
	}
	std::cout << "Enter phrase to translate" << std::endl;
	waitFor = WaitingForPhrase;
	return waitFor;
}

state OnAddTranslationPrompt(const std::string& inputPhrase)
{	// реакция на запрос добавочного перевода
	state waitFor;
	if (inputPhrase == "+")
	{
		std::cout << "Write the translation or press only enter to skip" << std::endl;
		waitFor = WaitingForTranslation;
	}
	else
	{
		std::cout << "Enter phrase to translate" << std::endl;
		waitFor = WaitingForPhrase;
	}
	return waitFor;
}

// обрабатывает введенную фразу
bool ProcessInputPhrase(const std::string& inputPhrase, std::string& prevPhrase, dict& vocabular, state& waitFor)
{
	bool vocaChanged = false;
	
	switch (waitFor)
	{
		case WaitingForPhrase:
		{
			waitFor = OnPhraseRequest(inputPhrase, vocabular);
			break;
		}
		case WaitingForTranslation:
		{
			waitFor = OnTranslationPrompt(prevPhrase, inputPhrase, vocabular, vocaChanged);
			break;
		}
		case WaitingForAddTranslation:
		{
			waitFor = OnAddTranslationPrompt(inputPhrase);
			break;
		}
		default:
			break;
	}
	SavePrevPhrase(prevPhrase, inputPhrase);
	return vocaChanged;
}





bool Session(dict& vocabular) // true -- словарь был дополнен
{
	std::string inputPhrase;
	std::string prevPhrase;
	bool vocaChanged = false;

	state waitFor = WaitingForPhrase;
	
	while (true)
	{
		std::cout << "> ";
		getline(std::cin, inputPhrase);
		if (inputPhrase == "...") break;
		if (ProcessInputPhrase(inputPhrase, prevPhrase, vocabular, waitFor))
		{
			vocaChanged = true;
		}
	} 
		
	return vocaChanged;
}

void SaveDictionary(dict& vocabular, const std::string& vocaFileName)
{
	std::cout << "The dictionary was changed. Save changes? (y/Y)" << std::endl;
	std::cout << "> ";
	char save = ' ';
	std::cin >> save;
	if ((save == 'y') || (save == 'Y'))
	{
		std::ofstream newVocaFile;
		newVocaFile.open(vocaFileName, std::ios::trunc);
		StoreVocabular(vocabular, newVocaFile);
		std::cout << "Dictionary has saved in file " << vocaFileName << std::endl;
	}
}

void GetDictionaryFromFile(const std::string& vocaFileName, dict& vocabular)
{
	std::ifstream vocaFile;
	
	if (VocaFileOpened(vocaFileName, vocaFile))
	{
		if (!LoadVocabular(vocaFile, vocabular))
		{
			std::cout << "Warning! Wrong dictionary file" << std::endl;
		}
	}
	else
	{
		std::cout << "Dictionary is not yet exists! We are to fill a new dictionary!" << std::endl;
	}
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	
	std::cout << "Translates words and sentences from english into russian\n" 
			  <<  "Input phrase to translate or ... to exit" << std::endl;
	
	std::string vocaFileName = (argc > 1) ? argv[1] : "Vocabulary1.vcb";
	dict currVocabular = {};

	GetDictionaryFromFile(vocaFileName, currVocabular);
		
	if (Session(currVocabular)) // сессия работы со словарем
	{
		SaveDictionary(currVocabular, vocaFileName);
	}
	std::cout << "Good bye!" << std::endl;
	
	return 0;
}

