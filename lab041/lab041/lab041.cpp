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


IShape* SegmentInit(std::stringstream& segmentParams)
{
	double startPX = 0.0;
	double startPY = 0.0;
	double endPX = 0.0;
	double endPY = 0.0;
	std::string outlineC("ff0000");

	segmentParams >> startPX >> startPY >> endPX >> endPY >> outlineC;
	CLineSegment* lsPtr = new CLineSegment(startPX, startPY, endPX, endPY, outlineC);
	return static_cast<IShape*>(lsPtr);
}

IShape* CircleInit(std::stringstream& circleParams)
{
	double centerX = 0.0;
	double centerY = 0.0;
	double radius = 0.0;
	std::string outlineC("ff0000");
	std::string fillC("00ff00");

	circleParams >> centerX >> centerY >> radius >> outlineC >> fillC;
	CCircle* circPtr = new CCircle(centerX, centerY, radius, outlineC, fillC);
	return static_cast<IShape*>(circPtr);
}

IShape* TriangleInit(std::stringstream& triangleParams)
{
	double vert1X = 0.0;
	double vert1Y = 0.0;
	double vert2X = 0.0;
	double vert2Y = 0.0;
	double vert3X = 0.0;
	double vert3Y = 0.0;
	std::string outlineC("ff0000");
	std::string fillC("00ff00");

	triangleParams >> vert1X >> vert1Y >> vert2X >> vert2Y >> vert3X >> vert3Y >> outlineC >> fillC;
	CTriangle* trngPtr = new CTriangle(vert1X, vert1Y, vert2X, vert2Y, vert3X, vert3Y, outlineC, fillC);
	return static_cast<IShape*>(trngPtr);
}

IShape* RectangleInit(std::stringstream& rectangleParams)
{
	double leftTopX = 0.0;
	double leftTopY = 0.0;
	double width = 0.0;
	double height = 0.0;
	std::string outlineC("ff0000");
	std::string fillC("00ff00");

	rectangleParams >> leftTopX >> leftTopY >> width >> height >> outlineC >> fillC;
	CRectangle* rctgPtr = new CRectangle(leftTopX, leftTopY, width, height, outlineC, fillC);
	return static_cast<IShape*>(rctgPtr);
}


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
		return SegmentInit(inputLine);
	}
	if (*it == "Circle")
	{
		return CircleInit(inputLine);
	}
	if (*it == "Triangle")
	{
		return TriangleInit(inputLine);
	}
	if (*it == "Rectangle")
	{
		return RectangleInit(inputLine);
	}
	return nullptr;
}

void FillShapeCollection(std::istream& istrm, std::vector<IShape*>& anyShapes)
{
	std::string shapeDescription;
	size_t counter = 0;

	while (getline(istrm, shapeDescription))
	{
		IShape* currParamSet = GetShape(shapeDescription, shapeNames);
		if (currParamSet != nullptr)
		{
			anyShapes.push_back(currParamSet);
			++counter; 
		}
	}
	std::cout << counter << " figures overall given" << std::endl;
}

void ShowShapeOfMaxArea(const std::vector<IShape*>& anyShapes)
{
	IShape* maxAreaPtr = nullptr;
	if (!anyShapes.empty())
	{
		double maxAreaVal = 0.0;
		for (auto it = anyShapes.begin(); it != anyShapes.end(); ++it)
		{
			int newArea = (*it)->GetArea();
			if (newArea >= maxAreaVal)
			{
				maxAreaVal = newArea;
				maxAreaPtr = *it;
			}
		}
		std::cout << maxAreaPtr->ToString() << std::endl;
	}
}

void ShowShapeOfMinPerimeter(const std::vector<IShape*>& anyShapes)
{
	IShape* minPeriPtr = nullptr;
	if (!anyShapes.empty())
	{
		double minPeriVal = (*anyShapes.begin())->GetPerimeter();
		for (auto it = anyShapes.begin(); it != anyShapes.end(); ++it)
		{
			int newPeri = (*it)->GetPerimeter();
			if (newPeri <= minPeriVal)
			{
				minPeriVal = newPeri;
				minPeriPtr = *it;
			}
		}
		std::cout << minPeriPtr->ToString() << std::endl;
	}
}

int main(int argc, char* argv[])
{
	std::vector<IShape*> anyShapes;
	FillShapeCollection(std::cin, anyShapes);

	if (anyShapes.size() != 0)
	{
		std::cout << "Figure of maximal area:" << std::endl;
		ShowShapeOfMaxArea(anyShapes);
		std::cout << "Figure of minimal perimeter:" << std::endl;
		ShowShapeOfMinPerimeter(anyShapes);
	}
	else
	{
		std::cout << "There are no shapes at all!" << std::endl;
	}

	return 0;
}
