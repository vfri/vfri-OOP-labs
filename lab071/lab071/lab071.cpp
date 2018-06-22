// lab071.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Findmax.h"

struct Sportsman
{
public:
	explicit Sportsman(const char* name, double weight, int age)
		:m_name(name), m_weight(weight), m_age(age)
	{}
private:
	const char* m_name;
	double m_weight;
	int m_age;
};


int main()
{
	std::vector<int> intVec = { 12, 2, 31, 5, 21, 7, 82, 13, 24 };
	std::vector<double> doubleVec = { 1e-2, .23, 1.204, 0.23, -4.32, 1.8e-1 };
	std::vector <std::string> strVec = { std::string("cat"), std::string("dog"), std::string("catalog"),
		std::string("door"), std::string("ifelse"), std::string("ace"), std::string("arcus") };

	std::vector<const char*> cstrVec = { "red", "orange", "yellow", "green", "white", "black", "cian" };
	std::vector<int> intEmptyVec = {};

	FindAndPrintMax(intVec);
	FindAndPrintMax(doubleVec);
	FindAndPrintMax(strVec);
	FindAndPrintMax(cstrVec);
	FindAndPrintMax(intEmptyVec);

	std::vector<Sportsman> staff;
	staff.push_back(Sportsman("Nicolas", 68.5, 32));
	staff.push_back(Sportsman("Boris", 77.2, 35));
	staff.push_back(Sportsman("Alex", 70.5, 36));
	staff.push_back(Sportsman("Miguel", 55.6, 27));
	staff.push_back(Sportsman("Ivan", 75.1, 36));
	
	return 0;
}
