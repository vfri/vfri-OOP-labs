// lab061.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

struct EquationRoot2
{
	int numRoots2;
	double roots2[2];
};


struct EquationRoot4
{
	int numRoots;
	double roots[4];
};


EquationRoot2 SolveQuadric(double p, double q) // x^2 + px + q = 0
{
	EquationRoot2 result;
	result.numRoots2 = 3;
	double Discr = std::pow(p, 2) - 4 * q;
	if (Discr < 0)
	{
		result.numRoots2 = 0;
	}
	if (Discr == 0)
	{
		result.numRoots2 = 1;
		result.roots2[0] = -p / 2;
	}
	if (Discr > 0)
	{
		result.numRoots2 = 2;
		result.roots2[0] = (-p - std::pow(Discr, 0.5)) / 2;
		result.roots2[1] = (-p + std::pow(Discr, 0.5)) / 2;
	}
	return result;
}

double CubicPolyValue(double x, double p, double q, double r) // x^3 + px^2 + qx + r
{
	return std::pow(x, 3) + p * std::pow(x, 2) + q * x + r;
}


double FindSomeRootOfCubic(double p, double q, double r)
{
	const double epsilon = std::numeric_limits<double>::epsilon();
	const double multiplier = 10;

	double preBorder = std::max(std::abs(p), std::abs(q));
	preBorder = std::max(preBorder, std::abs(r));

	double leftBorder = -preBorder;
	double rightBorder = preBorder;
	double difference = rightBorder - leftBorder;
	double middle = (leftBorder + rightBorder) / 2;
	while (difference > multiplier * epsilon)
	{
		double leftBorderValue = CubicPolyValue(leftBorder, p, q, r);
		double rightBorderValue = CubicPolyValue(rightBorder, p, q, r);
		double middleValue = CubicPolyValue(middle, p, q, r);
		if (middleValue == 0)
		{
			break;
		}
		else if (leftBorderValue * middleValue > 0)
		{
			leftBorder = middle;
		}
		else
		{
			rightBorder = middle;
		}
		difference = rightBorder - leftBorder;
		middle = (leftBorder + rightBorder) / 2;
	}

	return middle;
}

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	EquationRoot4 result;
	result.numRoots = 5;
	
	if (a == 0)
	{
		return result;
	}
	else
	{
		double b1 = b / a;
		double c1 = c / a;
		double d1 = d / a;
		double e1 = e / a;
		double p = c1 - 3 * std::pow(b1, 2) / 8;
		double q = std::pow(b1, 3) / 8 - b1 * c1 / 2 + d1;
		double r = -3 * std::pow(b1, 4) / 256 + std::pow(b1, 2)* c1 / 16 - d1 * b1 / 4 + e1;
		double resP = -p / 2;
		double resQ = -r;
		double resR = r * p / 2 - std::pow(q, 2) / 8;
		double resRoot = FindSomeRootOfCubic(resP, resQ, resR);
		
		if (p - 2 * resRoot == 0)
		{
			EquationRoot2 biquadric = SolveQuadric(2 * resRoot, r);
			result.numRoots = 0;
			if (biquadric.numRoots2 == 1)
			{
				double onlyRoot = biquadric.roots2[0];
				if (onlyRoot == 0.0)
				{
					result.numRoots = 1;
					result.roots[0] = 0.0;
				}
				if (onlyRoot > 0)
				{
					result.numRoots = 2;
					result.roots[0] = -std::pow(onlyRoot, 0.5);
					result.roots[1] = std::pow(onlyRoot, 0.5);
				}
			}
			if (biquadric.numRoots2 == 2)
			{
				double left = biquadric.roots2[0];
				double right = biquadric.roots2[1];
				if (right == 0.0)
				{
					result.numRoots = 1;
					result.roots[0] = 0.0;
				}
				if (right > 0)
				{
					result.roots[0] = -std::pow(right, 0.5);
					result.roots[1] = std::pow(right, 0.5);
					if (left < 0)
					{
						result.numRoots = 2;
					}
					if (left == 0.0)
					{
						result.numRoots = 3;
						result.roots[2] = 0.0;
					}
					if (left > 0)
					{
						result.numRoots = 4;
						result.roots[2] = -std::pow(left, 0.5);
						result.roots[3] = std::pow(left, 0.5);
					}
				}
			}
		}
		if (p - 2 * resRoot > 0)
		{
			if (4 * std::pow(2 * resRoot - p, 2)*resRoot == q * q)
			{
				result.numRoots = 1;
				result.roots[0] = q / (4 * resRoot - 2 * p);
			}
		}
		if (p - 2 * resRoot < 0)
		{
			double co1x = - std::pow(2 * resRoot - p, 0.5);
			double co2x = -co1x;
			double co1free = q / (2 * co2x) + resRoot;
			double co2free = q / (2 * co1x) + resRoot;
			EquationRoot2 quadric1 = SolveQuadric(co1x, co1free);
			EquationRoot2 quadric2 = SolveQuadric(co2x, co2free);
			result.numRoots = quadric1.numRoots2 + quadric2.numRoots2;
			for (size_t i = 0; i < quadric1.numRoots2; ++i)
			{
				result.roots[i] = quadric1.roots2[i];
			}
			for (size_t j = 0; j < quadric2.numRoots2; ++j)
			{
				result.roots[j + quadric1.numRoots2] = quadric2.roots2[j];
			}
		}
		for (size_t n = 0; n < result.numRoots; ++n)
		{
			result.roots[n] -= b1 / 4;
		}
	}
	return result;
}

void PrintRoots(EquationRoot4 const& rootSet)
{
	for (size_t i = 0; i < rootSet.numRoots; ++i)
	{
		std::cout << std::fixed << std::setprecision(16) << rootSet.roots[i] << std::endl;
	}
	std::cout << std::endl;
}



int main(int argc, char* argv[])
{
	double a = 1.0;
	double b = 0.0;
	double c = 0.0;
	double d = 0.0;
	double e = 0.0;
	std::cout << "Enter coeffs a, b, c, d, e in equation ax^4 + bx^3 + cx^2 + dx + e = 0" << std::endl;
	std::cin >> a >> b >> c >> d >> e;
	EquationRoot4 test4;
	test4 = Solve4(a, b, c, d, e);
	std::cout << "solve done!" << std::endl;
	PrintRoots(test4);
	return 0;
}

