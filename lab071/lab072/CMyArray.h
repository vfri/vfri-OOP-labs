#pragma once
#include "stdafx.h"

template <typename T> 
class CMyArray
{
public:
	
	CMyArray();
	CMyArray(size_t num);

	~CMyArray();

	CMyArray(CMyArray const& arr);

	CMyArray& operator=(CMyArray const& arr);

	// CMyArray(CMyArray&& arr);

	//CMyArray& operator=(CMyArray&& arr);
	
	size_t GetSize() const;

	void Push_back(T const& elem);

	//T& operator[](size_t index);
	
	//T const& operator[](size_t index) const;

	//void Resize(size_t newSize);
	   
private:  
	T* m_pElems;  
	size_t m_size;
};


CMyArray<T>::CMyArray()
	:m_size(0)
	, m_pElems(nullptr)
{
}

CMyArray<T>::CMyArray<T>(size_t num)
try
	:m_size(num)
	, m_pElems(nullptr)
{
	m_pElems = new T[num];
}
catch (std::bad_alloc const&)
{
	delete[] m_pElems;
	throw;
}

CMyArray<T>::CMyArray<T>(CMyArray<T> const& arr)
	: m_size(arr.m_size)
{
	try
	{
		m_pElems = new T[m_size];
		for (size_t i = 0; i < m_size; ++i) m_pElems[i] = arr.m_pElems[i];
	}
	catch (std::bad_alloc const&)
	{
		delete[] m_pElems;
		throw;
	}
}


CMyArray<T>::~CMyArray()
{
	delete[] m_pElems;
}

CMyArray<T>& CMyArray<T>::operator=(CMyArray<T> const& arr)
{
	if (this != &arr)
	{
		delete[] m_pElems;
		m_size = arr.m_size;
		try
		{
			m_pElems = new T[m_size];
			for (size_t i = 0; i < m_size; ++i) m_pElems[i] = arr.m_pElems[i];
		}
		catch (std::bad_alloc const&)
		{
			delete[] m_pElems;
			throw;
		}

	}
	return *this;
}

size_t CMyArray<T>::GetSize() const
{
	return m_size;
}

void CMyArray<T>::Push_back(T const& arr)
{
	
}
