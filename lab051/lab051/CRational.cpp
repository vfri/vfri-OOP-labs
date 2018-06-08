#include "stdafx.h"
#include "CRational.h"


CRational::CRational()
	:m_numerator(0)
	,m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

int GCommDiv(int u, int v)
{
	while (v != 0) {
		int r = u % v;
		u = v;
		v = r;
	}
	return u;
}

CRational::CRational(int numerator, int denominator)
{
	if (denominator > 0)
	{
		m_numerator = numerator;
		m_denominator = denominator;
	}
	else if (denominator < 0)
	{
		m_numerator = -numerator;
		m_denominator = -denominator;
	}
	else if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
		m_errorMess = "Zero denominator. Ratio is set to 0/1";
	}
	int factor = std::gcd(std::abs(m_numerator), std::abs(m_denominator));
	m_numerator /= factor;
	m_denominator /= factor;
}


int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

CRational& CRational::Normalize()
{
	if (m_numerator == 0)
	{
		m_denominator = 1;
	}
	else
	{
		int gcdNumDenom = std::gcd(std::abs(m_numerator), std::abs(m_denominator));
		m_numerator /= gcdNumDenom;
		m_denominator /= gcdNumDenom;
	}
	return *this;
}



CRational& CRational::operator+=(CRational summand)
{
	m_numerator = m_numerator * summand.m_denominator + m_denominator * summand.m_numerator;
	m_denominator = m_denominator * summand.m_denominator;
	return Normalize();
}

CRational& CRational::operator-=(CRational subtrahend)
{
	m_numerator = m_numerator * subtrahend.m_denominator - m_denominator * subtrahend.m_numerator;
	m_denominator = m_denominator * subtrahend.m_denominator;
	return Normalize();
}

CRational& CRational::operator*=(CRational multiplier)
{
	m_numerator *= multiplier.m_numerator;
	m_denominator *= multiplier.m_denominator;
	return Normalize();
}

CRational& CRational::operator/=(CRational divisor)
{
	if (divisor.m_numerator == 0)
	{
		throw std::invalid_argument("Zero division attempt!");
	}
	else
	{
		m_numerator = m_numerator * divisor.m_denominator;
		m_denominator = m_denominator * divisor.m_numerator;
	}
	return Normalize();
}


std::string CRational::GetErrorMessage() const
{
	return m_errorMess;
}

CRational operator+(const CRational& ratio)
{
	return ratio;
}

CRational operator-(const CRational& ratio)
{
	return CRational(-ratio.GetNumerator(), ratio.GetDenominator());
}

CRational operator+(CRational summand1, CRational summand2)
{
	return summand1 += summand2;
}

CRational operator-(CRational minuend, CRational subtrahend)
{
	return minuend -= subtrahend;
}

CRational operator*(CRational multiplier1, CRational multiplier2)
{
	return multiplier1 *= multiplier2;
}

CRational operator/(CRational dividend, CRational divisor)
{
	return dividend /= divisor;
}

bool operator==(CRational left, CRational right)
{
	return ((left.GetNumerator() == right.GetNumerator()) && (left.GetDenominator() == right.GetDenominator()));
}

bool operator!=(CRational left, CRational right)
{
	return !(left == right);
}

bool operator>(CRational left, CRational right)
{
	return (left.GetNumerator() * right.GetDenominator() > left.GetDenominator() * right.GetDenominator());
}

bool operator<(CRational left, CRational right)
{
	return (right > left);
}

bool operator>=(CRational left, CRational right)
{
	return !(right > left);
}

bool operator<=(CRational left, CRational right)
{
	return !(left > right);
}
