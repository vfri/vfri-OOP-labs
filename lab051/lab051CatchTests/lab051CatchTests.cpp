// lab051CatchTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../lab051/CRational.h"


TEST_CASE("Default constructor gives ratio 0/1")
{
	CRational zeroToOne;
	int num = zeroToOne.GetNumerator();
	int den = zeroToOne.GetDenominator();
	CHECK(num == 0);
	CHECK(den == 1);
}

TEST_CASE("Constructor with one argument m gives ratio m/1")
{
	CRational integerRatio(3);
	int num = integerRatio.GetNumerator();
	int den = integerRatio.GetDenominator();
	CHECK(num == 3);
	CHECK(den == 1);

	CRational anotherIntRatio = CRational(-5);
	num = anotherIntRatio.GetNumerator();
	den = anotherIntRatio.GetDenominator();
	CHECK(num == -5);
	CHECK(den == 1);

	CRational oneMoreZeroToOne(0);
	CHECK(oneMoreZeroToOne.GetNumerator() == 0);
	CHECK(oneMoreZeroToOne.GetDenominator() == 1);
}

TEST_CASE("Constructor with two relative prime arguments m and n gives ratio m/n when n is nonzero")
{
	CRational irreducible(10, 21);
	int num = irreducible.GetNumerator();
	int den = irreducible.GetDenominator();
	CHECK(num == 10);
	CHECK(den == 21);

	CRational irredNegativeDenom(9, -35);
	num = irredNegativeDenom.GetNumerator();
	den = irredNegativeDenom.GetDenominator();
	CHECK(num == -9);
	CHECK(den == 35);

	CRational irredNegativeDenom2(-7, -35); // здесь не взаимно простые 
	num = irredNegativeDenom2.GetNumerator();
	den = irredNegativeDenom2.GetDenominator();
	CHECK(num == 1);
	CHECK(den == 5);

	CRational zeroDenom(5, 0);
	num = zeroDenom.GetNumerator();
	den = zeroDenom.GetDenominator();
	CHECK(num == 0);
	CHECK(den == 1);
	CHECK(zeroDenom.GetErrorMessage() == std::string("Zero denominator. Ratio is set to 0/1"));
}

TEST_CASE("Normalize to irreducible fraction")
{
	CRational redbFrac(136, 248);
	CRational irrFrac = redbFrac.Normalize();
	int num = irrFrac.GetNumerator();
	int den = irrFrac.GetDenominator();
	CHECK(num == 17);
	CHECK(den == 31);

	CRational redbFrac2(-2000, 3525);
	CRational irrFrac2 = redbFrac2.Normalize();
	num = irrFrac2.GetNumerator();
	den = irrFrac2.GetDenominator();
	CHECK(num == -80);
	CHECK(den == 141);

	CRational redbFrac3(0, 3525);
	CRational irrFrac3 = redbFrac3.Normalize();
	num = irrFrac3.GetNumerator();
	den = irrFrac3.GetDenominator();
	CHECK(num == 0);
	CHECK(den == 1);

	CRational redbFrac4(-100, -76);
	CRational irrFrac4 = redbFrac4.Normalize();
	num = irrFrac4.GetNumerator();
	den = irrFrac4.GetDenominator();
	CHECK(num == 25);
	CHECK(den == 19);
}

TEST_CASE("Unary plus gives ratio itself, unary minus changes numerator signum")
{
	CRational initial(90, -145);
	CHECK(initial.GetNumerator() == -18);
	CHECK(initial.GetDenominator() == 29);

	CRational plusInitial = +initial;
	CHECK(plusInitial.GetNumerator() == -18);
	CHECK(plusInitial.GetDenominator() == 29);

	CRational minusInitial = -initial;
	CHECK(minusInitial.GetNumerator() == 18);
	CHECK(minusInitial.GetDenominator() == 29);

	CRational zero(0, 6);
	CHECK((-zero).GetNumerator() == 0);
	CHECK((-zero).GetDenominator() == 1);
}

TEST_CASE("Adding ratio leads to normalize result")
{
	CRational left(1, 3);
	CRational right(1, 6);
	left += right;
	CHECK(left.GetNumerator() == 1);
	CHECK(left.GetDenominator() == 2);

	CRational left2(3, 2);
	CRational right2(-1, 6);
	left2 += right2;
	CHECK(left2.GetNumerator() == 4);
	CHECK(left2.GetDenominator() == 3);

	CRational left3(4, 7);
	CRational right3(-5, 0);
	left3 += right3;
	CHECK(left3.GetNumerator() == 4);
	CHECK(left3.GetDenominator() == 7);
	CHECK(right3.GetErrorMessage() == std::string("Zero denominator. Ratio is set to 0/1"));
}

TEST_CASE("Adding integer by same operator must be successfull")
{
	CRational left(3, 5);
	int right = -2;
	left += right; 
	CHECK(left.GetNumerator() == -7);
	CHECK(left.GetDenominator() == 5);
}

TEST_CASE("Subtracting ratio leads to normalize result")
{
	CRational left(3, 4);
	CRational right(5, 12);
	left -= right;
	CHECK(left.GetNumerator() == 1);
	CHECK(left.GetDenominator() == 3);

	CRational left2(2, 15);
	CRational right2(-4, 15);
	left2 -= right2;
	CHECK(left2.GetNumerator() == 2);
	CHECK(left2.GetDenominator() == 5);

	CRational left3(-4, 7);
	CRational right3(-4, 7);
	left3 -= right3;
	CHECK(left3.GetNumerator() == 0);
	CHECK(left3.GetDenominator() == 1);
	CHECK(right3.GetErrorMessage() == "");
}

TEST_CASE("Subtracting integer by same operator must be successfull")
{
	CRational left(14, 5);
	int right = -4;
	left -= right;
	CHECK(left.GetNumerator() == 34);
	CHECK(left.GetDenominator() == 5);
}

TEST_CASE("Addition must work with rational or integer arguments")
{
	CRational smd1(2, 3);
	CRational smd2(3, 28);
	CRational res = smd1 + smd2;
	CHECK(res.GetNumerator() == 65);
	CHECK(res.GetDenominator() == 84);

	CRational smd11(2, 3);
	int smd21 = 8;
	res = smd11 + smd21;
	CHECK(res.GetNumerator() == 26);
	CHECK(res.GetDenominator() == 3);

	int smd12 = 5;
	CRational smd22(-3, 7);
	res = smd12 + smd22;
	CHECK(res.GetNumerator() == 32);
	CHECK(res.GetDenominator() == 7);

}

TEST_CASE("Multiplication on ratio leads to normalize result")
{
	CRational left(8, 125);
	CRational right(10, 44);
	left *= right;
	CHECK(left.GetNumerator() == 4);
	CHECK(left.GetDenominator() == 275);

	CRational left2(2, -15);
	CRational right2(-15, 2);
	left2 *= right2;
	CHECK(left2.GetNumerator() == 1);
	CHECK(left2.GetDenominator() == 1);

	CRational left3(5, -7);
	CRational right3(0, 7);
	left3 *= right3;
	CHECK(left3.GetNumerator() == 0);
	CHECK(left3.GetDenominator() == 1);
}

TEST_CASE("Multiplying on integer by same operator must be successfull")
{
	CRational left(14, 15);
	int right = -25;
	left *= right;
	CHECK(left.GetNumerator() == -70);
	CHECK(left.GetDenominator() == 3);
}

TEST_CASE("Multiplication must work correctly with rational or integer arguments on both left and right sides")
{
	CRational mr1(12, 35);
	CRational mr2(49, 54);
	CRational res = mr1 * mr2;
	CHECK(res.GetNumerator() == 14);
	CHECK(res.GetDenominator() == 45);

	CRational mr11(3, 16);
	int mr21 = 12;
	res = mr11 * mr21;
	CHECK(res.GetNumerator() == 9);
	CHECK(res.GetDenominator() == 4);

	int mr12 = 15;
	CRational mr22(-3, 20);
	res = mr12 * mr22;
	CHECK(res.GetNumerator() == -9);
	CHECK(res.GetDenominator() == 4);
}

