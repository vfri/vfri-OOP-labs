#pragma once

template <typemane T> 
class CMyArray
{
public:
	
	CMyArray();
	~CMyArray();

	CMyArray(CMyArray const& arr);

	CMyArray& operator=(CMyArray const& arr);

	CMyArray(CMyArray&& arr);

	CMyArray& operator=(CMyArray&& arr)
	
	size_t GetSize() const;

	void Push(T const& elem);

	T& operator[](size_t index);
	
	T const& operator[](size_t index) const;

	void Resize(size_t newSize);
	   
private:  
	T* m_pElems;  
	size_t m_size;
};

