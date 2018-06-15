// lab061.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Equation4.h"

static double epsilonApprox = 1e-5;

bool ApproximatelyEqual(double foo, double bar)
{
	return std::abs(foo - bar) < epsilonApprox;
}

EquationRoot2 SolveQuadric(double p, double q) // x^2 + px + q = 0
{
	EquationRoot2 result;
	result.numRoots2 = 3;
	const double epsilonD = 0.0000000001;
	double Discr = std::pow(p, 2) - 4 * q;
	if (Discr < -epsilonD)
	{
		result.numRoots2 = 0;
	}
	else if (Discr > epsilonD)
	{
		result.numRoots2 = 2;
		result.roots2[0] = (-p - std::pow(Discr, 0.5)) / 2;
		result.roots2[1] = (-p + std::pow(Discr, 0.5)) / 2;
	}
	else
	{
		result.numRoots2 = 1;
		result.roots2[0] = -p / 2;
	}
	return result;
}

double CubicPolyValue(double x, double p, double q, double r) // x^3 + px^2 + qx + r
{
	return std::pow(x, 3) + p * std::pow(x, 2) + q * x + r;
}


bool ShrinkBordersToCubucRoot(double p, double q, double r, double& leftBorder, double& rightBorder, double& middle)
{	
	double leftBorderValue = CubicPolyValue(leftBorder, p, q, r);
	double rightBorderValue = CubicPolyValue(rightBorder, p, q, r);
	double middleValue = CubicPolyValue(middle, p, q, r);
	double side = leftBorderValue * middleValue;
	if (side == 0) // сравниваем знаки многочлена в середине отрезка и на концах 
	{
		return false;
	}
	else if (side > 0)
	{
		leftBorder = middle;
	}
	else 
	{
		rightBorder = middle;
	}
	middle = (leftBorder + rightBorder) / 2;
	return true;
}

double MakeBorder(double p, double q, double r)
{
	double preBorder = std::max(std::abs(p), std::abs(q));
	preBorder = std::max(preBorder, std::abs(r));
	return 2 * std::max(preBorder, 1.0);
}

double FindSomeRootOfCubic(double p, double q, double r) // для нахождения корня кубической резольвенты
{
	const double epsilon = std::numeric_limits<double>::epsilon();
	const double multiplier = 10;

	double preBorder = MakeBorder(p, q, r);
	double leftBorder = -preBorder;		// левая граница для корня
	double rightBorder = preBorder;		// правая граница для корня
	double middle = (leftBorder + rightBorder) / 2;
	double difference = rightBorder - leftBorder;
	
	size_t counter = 0;
	while ((difference > multiplier * epsilon) && (counter < 100))
	{
		if (!ShrinkBordersToCubucRoot(p, q, r, leftBorder, rightBorder, middle)) break;
		difference = rightBorder - leftBorder;
	}
	
	return middle;
}

void MakeReducedEq4(double a, double b, double c, double d, double e, double& p, double& q, double& r)
{
	double b1 = b / a;
	double c1 = c / a;
	double d1 = d / a;
	double e1 = e / a;
	p = c1 - 3 * std::pow(b1, 2) / 8;
	q = std::pow(b1, 3) / 8 - b1 * c1 / 2 + d1;
	r = -3 * std::pow(b1, 4) / 256 + std::pow(b1, 2)* c1 / 16 - d1 * b1 / 4 + e1;
}

double GetResolventaRoot(double p, double q, double r)
{
	double resP = -p / 2;
	double resQ = -r;
	double resR = r * p / 2 - std::pow(q, 2.0) / 8;
	double root = FindSomeRootOfCubic(resP, resQ, resR);
	
	return root;
}

EquationRoot4 SolveBiquadricWithOneRoot(EquationRoot2 const& preRoots) // x^4 + px^2 + q -- полный квадрат
{
	EquationRoot4 res;
	res.numRoots = 0;

	double onlyRoot = preRoots.roots2[0];
	if (onlyRoot < 0)
	{
		throw std::domain_error("Equation has no roots! (from Biquadratic1)");
	}
	else if (onlyRoot == 0.0)
	{
		res.numRoots = 1;
		res.roots[0] = 0.0;
	}
	else
	{
		res.numRoots = 2;
		res.roots[0] = -std::pow(onlyRoot, 0.5);
		res.roots[1] = std::pow(onlyRoot, 0.5);
	}

	return res;
}


EquationRoot4 SolveBiquadricWithTwoRoots(EquationRoot2 const& preRoots) // x^4 + px^2 + q = (x^2 - y1)(x^2 - y2)
{
	EquationRoot4 res;
	res.numRoots = 0;

	double left = preRoots.roots2[0];
	double right = preRoots.roots2[1];
	if (right < 0)
	{
		throw std::domain_error("Equation has no roots! (from Biquadratic 2)");
	}
	else if (right == 0.0)
	{
		res.numRoots = 1;
		res.roots[0] = 0.0;
	}
	else
	{
		res.roots[0] = -std::pow(right, 0.5);
		res.roots[1] = std::pow(right, 0.5);
		if (left < 0)
		{
			res.numRoots = 2;
		}
		if (left == 0.0)
		{
			res.numRoots = 3;
			res.roots[2] = 0.0;
		}
		if (left > 0)
		{
			res.numRoots = 4;
			res.roots[2] = -std::pow(left, 0.5);
			res.roots[3] = std::pow(left, 0.5);
		}
	}
	
	return res;
}


EquationRoot4 SolveBiquadric(double p, double q) // x^4 + px^2 + q = 0
{
	EquationRoot4 result;
	result.numRoots = 0;
	
	EquationRoot2 biquadric = SolveQuadric(p, q);
	
	if (biquadric.numRoots2 == 1)
	{
		result = SolveBiquadricWithOneRoot(biquadric);
	}
	if (biquadric.numRoots2 == 2)
	{
		result = SolveBiquadricWithTwoRoots(biquadric);
	}
	
	return result;
}

EquationRoot4 SpecialCaseOfPossiblyOneRoot(double p, double q, double resRoot)
{
	EquationRoot4 res;
	res.numRoots = 0;

	const double epsilonSpec = 0.000000001;
	const double probRootCondVal = std::abs(4 * std::pow(2 * resRoot - p, 2)*resRoot - q * q);
	if (probRootCondVal > epsilonSpec)
	{
		throw std::domain_error("Equation has no roots! (from special case)");
	}
	else
	{
		res.numRoots = 1;
		res.roots[0] = q / (4 * resRoot - 2 * p);
	}
	
	return res;
}

EquationRoot4 SolveDecouplingOnTwoQuadratic(double p, double q, double resRoot)
{
	EquationRoot4 res;
	res.numRoots = 0;

	double co1x = -std::pow(2 * resRoot - p, 0.5);
	double co2x = -co1x;
	double co1free = q / (2 * co2x) + resRoot;
	double co2free = q / (2 * co1x) + resRoot;
	EquationRoot2 quadric1 = SolveQuadric(co1x, co1free);
	EquationRoot2 quadric2 = SolveQuadric(co2x, co2free);
	res.numRoots = quadric1.numRoots2 + quadric2.numRoots2;
	
	for (size_t i = 0; i < quadric1.numRoots2; ++i)
	{
		res.roots[i] = quadric1.roots2[i];
	}
	for (size_t j = 0; j < quadric2.numRoots2; ++j)
	{
		res.roots[j + quadric1.numRoots2] = quadric2.roots2[j];
	}
	if (res.numRoots == 0)
	{
		throw std::domain_error("Equation has no roots! (from coupling case)");
	}

	return res;
}

void SortRoots4(EquationRoot4& roots4)
{
	std::vector<double> vecRoots;
	if (roots4.numRoots != 0)
	{
		for (size_t i = 0; i < roots4.numRoots; ++i) vecRoots.push_back(roots4.roots[i]);
		std::sort(vecRoots.begin(), vecRoots.end());
		for (size_t i = 0; i < roots4.numRoots; ++i) roots4.roots[i] = vecRoots[i];
	}
}

void DelRepeated(EquationRoot4& roots4) 
{
	SortRoots4(roots4);
	size_t numDistRoots = 0;
	double prev = 0.0;
	if (roots4.numRoots > 1)
	{
		numDistRoots = 1;
		for (size_t i = 1; i < roots4.numRoots; ++i)
		{
			if (ApproximatelyEqual(roots4.roots[i - 1], roots4.roots[i])) continue;
			else
			{
				double temp = roots4.roots[i];
				roots4.roots[numDistRoots] = temp;
				numDistRoots++;
			}
		}
		roots4.numRoots = numDistRoots;
	}
}


EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	EquationRoot4 result;
		
	if (a == 0)
	{
		throw std::invalid_argument("Leading coefficient must not be equal to zero!");
	}
	else
	{
		double p, q, r;
		MakeReducedEq4(a, b, c, d, e, p, q, r);
		double resRoot = GetResolventaRoot(p, q, r);
		
		double factor = p - 2 * resRoot;
		
		if (ApproximatelyEqual(factor, 0.0))
		{
			result = SolveBiquadric(2 * resRoot, r);
		}
		else if (factor > 0)
		{
			result = SpecialCaseOfPossiblyOneRoot(p, q, resRoot);
		}
		else
		{
			result = SolveDecouplingOnTwoQuadratic(p, q, resRoot);
		}
		for (size_t n = 0; n < result.numRoots; ++n)
		{
			result.roots[n] -= b / (4 * a);
		}
		DelRepeated(result);
	}
	return result;
}


void PrintRoots(EquationRoot4 const& rootSet)
{
	std::cout << rootSet.numRoots << " distinct roots: " << std::endl;
	for (size_t i = 0; i < rootSet.numRoots; ++i)
	{
		std::cout << std::fixed << std::setprecision(16) << rootSet.roots[i] << std::endl;
	}
}

void Solve4WithExpns(double a, double b, double c, double d, double e)
{
	EquationRoot4 result4;
	try
	{
		result4 = Solve4(a, b, c, d, e);
		PrintRoots(result4);
	}
	catch (std::invalid_argument const& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	catch (std::domain_error const& e)
	{
		std::cout << "Achtung! " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown error!" << std::endl;
	}
}


void SolveMultipleEqns4()
{
	double coeffs[5];
	double nextCoeff;
	int cntr = 0;

	std::cout << "Enter coeffs a, b, c, d, e in equation ax^4 + bx^3 + cx^2 + dx + e = 0" << std::endl;
	while (std::cin >> nextCoeff)
	{
		coeffs[cntr++] = nextCoeff;
		if (cntr == 5)
		{
			std::cout << "Equation: " << coeffs[0] << "x^4 + " << coeffs[1] << "x^3 + "
				<< coeffs[2] << "x^2 + " << coeffs[3] << "x + " << coeffs[4] << " = 0" << std::endl;
			Solve4WithExpns(coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4]);
			cntr = 0;

			std::cout << "\nEnter coeffs a, b, c, d, e in equation ax^4 + bx^3 + cx^2 + dx + e = 0" << std::endl;
		}
	}
}





