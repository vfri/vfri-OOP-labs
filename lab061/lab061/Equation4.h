#pragma once

#include "stdafx.h"

struct EquationRoot2
{
	size_t numRoots2;
	double roots2[2];
};


struct EquationRoot4
{
	size_t numRoots;
	double roots[4];
};

bool ApproximatelyEqual(double foo, double bar);
EquationRoot2 SolveQuadric(double p, double q);
double CubicPolyValue(double x, double p, double q, double r);
bool ShrinkBordersToCubucRoot(double p, double q, double r, double& leftBorder, double& rightBorder, double& middle);
double MakeBorder(double p, double q, double r);
double FindSomeRootOfCubic(double p, double q, double r);
void MakeReducedEq4(double a, double b, double c, double d, double e, double& p, double& q, double& r);
double GetResolventaRoot(double p, double q, double r);
EquationRoot4 SolveBiquadricWithOneRoot(EquationRoot2 const& preRoots);
EquationRoot4 SolveBiquadricWithTwoRoots(EquationRoot2 const& preRoots);
EquationRoot4 SolveBiquadric(double p, double q);
EquationRoot4 SpecialCaseOfPossiblyOneRoot(double p, double q, double resRoot);
EquationRoot4 SolveDecouplingOnTwoQuadratic(double p, double q, double resRoot);
void SortRoots4(EquationRoot4& roots4);
void DelRepeated(EquationRoot4& roots4);
EquationRoot4 Solve4(double a, double b, double c, double d, double e);
void Solve4WithExpns(double a, double b, double c, double d, double e);
void PrintRoots(EquationRoot4 const& rootSet);
void SolveMultipleEqns4();
