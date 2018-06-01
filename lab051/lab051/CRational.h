#pragma once

class CRational
{
	public:
		CRational();
		CRational(int value);
		CRational(int numeretor, int denominator);
		~CRational();

		int GetNumerator() const;
		int GetDenominator() const;
		CRational& Normalize();

		CRational& operator+();
		CRational& operator-();
		CRational& operator+=(CRational summand);
		CRational& operator-=(CRational subtrahend);
		CRational& operator*=(CRational multiplier);

		std::string GetErrorMessage() const;

		//double ToDouble() const;

	private:
		int m_numerator;
		int m_denominator;
		std::string m_errorMess;
};

CRational operator+(CRational summand1, CRational summand2);
CRational operator-(CRational minuend, CRational subtrahend);
CRational operator*(CRational multiplier1, CRational multiplier2);
bool operator==(CRational left, CRational right);
bool operator!=(CRational left, CRational right);
bool operator>(CRational left, CRational right);
bool operator<(CRational left, CRational right);
bool operator>=(CRational left, CRational right);
bool operator<=(CRational left, CRational right);

