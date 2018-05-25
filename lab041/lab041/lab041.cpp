// lab041.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "IShape.h"
#include "ISolidShape.h"


static const std::vector<std::string> shapeNames =
{ std::string("LineSegment"), std::string("Circle"), std::string("Triangle"), std::string("Rectangle") };



IShape* GetShape(std::string const& shapeDescription, std::vector<std::string> const& shapeNames)
{
	std::stringstream inputLine(shapeDescription);
	std::string sName;
	inputLine >> sName;

	auto it = std::find(shapeNames.begin(), shapeNames.end(), sName);
	if (it == shapeNames.end())
	{
		return nullptr;
	}

	if (*it == "LineSegment")
	{
		result.operaType = Exit;
	}
	if (*it == "Circle")
	{
		result.operaType = Info;
	}
	if (*it == "Triangle")
	{
		result.operaType = EngOn;
	}
	if (*it == "Rectangle")
	{
		result.operaType = EngOff;
	}
	if ((*it == "SetGear") || (*it == "SetSpeed"))
	{
		inputLine >> partOfPhrase;
		int numData = IntFromString(partOfPhrase);
		result.operaType = (*it == "SetGear") ? SetGear : SetSpeed;
		result.numerical = numData;
	}
	return result;
}





int main(int argc, char* argv[])
{
	CCar testCar;
	CarOperation driveElem;
	while (DriveCar(driveElem, testCar))
	{
		PrintCarState(testCar);
		std::cout << "> ";
		std::string inputPhrase;
		getline(std::cin, inputPhrase);
		driveElem = ReadOperation(inputPhrase, CommandPrefixes);
	}
	std::cout << "Thank you!" << std::endl;

	return 0;
}
