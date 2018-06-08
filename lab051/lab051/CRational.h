#pragma once

class CRational
{
	public:
		CRational();
		CRational(int value);
		CRational(int numeretor, int denominator);
		
		int GetNumerator() const;
		int GetDenominator() const;
		
		
		CRational& operator+=(CRational summand);
		CRational& operator-=(CRational subtrahend);
		CRational& operator*=(CRational multiplier);
		CRational& operator/=(CRational divisor);

		double ToDouble() const;

	private:
		int m_numerator;
		int m_denominator;
		CRational& Normalize();
};

CRational operator+(const CRational& ratio);
CRational operator-(const CRational& ratio);
CRational operator+(CRational summand1, CRational summand2);
CRational operator-(CRational minuend, CRational subtrahend);
CRational operator*(CRational multiplier1, CRational multiplier2);
CRational operator/(CRational dividend, CRational divisor);

bool operator==(CRational left, CRational right);
bool operator!=(CRational left, CRational right);
bool operator>(CRational left, CRational right);
bool operator<(CRational left, CRational right);
bool operator>=(CRational left, CRational right);
bool operator<=(CRational left, CRational right);



