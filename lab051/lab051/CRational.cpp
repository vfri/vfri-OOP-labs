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
	int factor = GCommDiv(std::abs(m_numerator), std::abs(m_denominator));
	m_numerator /= factor;
	m_denominator /= factor;
}

CRational::~CRational()
{
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
		int gcdNumDenom = GCommDiv(std::abs(m_numerator), std::abs(m_denominator));
		m_numerator /= gcdNumDenom;
		m_denominator /= gcdNumDenom;
	}
	return *this;
}

CRational& CRational::operator+()
{
	return *this;
}

CRational& CRational::operator-()
{
	m_numerator = -m_numerator;
	return *this;
}

CRational& CRational::operator+=(CRational summand)
{
	m_numerator = m_numerator * summand.m_denominator + m_denominator * summand.m_numerator;
	m_denominator = m_denominator * summand.m_denominator;
	return (*this).Normalize();
}

CRational& CRational::operator-=(CRational subtrahend)
{
	m_numerator = m_numerator * subtrahend.m_denominator - m_denominator * subtrahend.m_numerator;
	m_denominator = m_denominator * subtrahend.m_denominator;
	return (*this).Normalize();
}


std::string CRational::GetErrorMessage() const
{
	return m_errorMess;
}

CRational operator+(CRational summand1, CRational summand2)
{
	CRational result = summand1;
	return result += summand2;
}