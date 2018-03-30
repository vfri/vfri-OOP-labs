// lab013.cpp: определяет точку входа для консольного приложения.
// Читает матрицу 3 на 3 из файла и находит обратную

#include "stdafx.h"

#define MSIZE 5

using namespace std;



struct Matrix // квадратная матрица размером не более MSIZE
{
	float elem[MSIZE][MSIZE];
	unsigned int matSize;
};

Matrix SetMatrix(istream& matrixFile, const unsigned int& mSize)
{
	Matrix resMatrix;
	
	if (mSize > MSIZE)
	{
		cout << "Matrix size is setted to max size " << MSIZE << endl;
		resMatrix.matSize = MSIZE;
	}
	else
	{
		resMatrix.matSize = mSize;
	}
	
	string line;
	
	for (unsigned int i = 0; i < resMatrix.matSize; i++)
	{
		getline(matrixFile, line);
		istringstream dataPieces(line);
		for (unsigned int j = 0; j < resMatrix.matSize; j++)
		{
			dataPieces >> resMatrix.elem[i][j];
		}
	}
	return resMatrix;
}

Matrix Minor(const Matrix& matr, const unsigned int row, const unsigned int col)
{
	Matrix minor;

	if ((row >= matr.matSize) || (col >= matr.matSize))
	{
		cout << "Unable to set minor!" << endl;
	}

	
	minor.matSize = matr.matSize - 1;
	unsigned int i = 0;
	
	while (i < minor.matSize)
	{
		unsigned int j = 0;
		while (j < minor.matSize)
		{
			minor.elem[i][j] = matr.elem[i + (int)(i >= row)][j + (int)(j >= col)];
			j++;			
		}
		i++;
	}

	return minor;
}

void PrintMatrix(const Matrix& matr)
{
	for (unsigned int i = 0; i < matr.matSize; i++)
	{
		for (unsigned int j = 0; j < matr.matSize; j++)
		{
			cout << setprecision(3) << setw(12) << matr.elem[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

 

float matDeterm(const Matrix& matr)
{
	float result;
	if (matr.matSize == 1)
	{
		result = matr.elem[0][0];
	}
	else
	{
		result = 0.0;
		for (unsigned int i = 0; i < matr.matSize; i++)
		{
			Matrix minor = Minor(matr, 0, i);
			PrintMatrix(minor);
			result = result + matr.elem[0][i] * (1 - 2 * ((int)i % 2)) * matDeterm(minor);
			
		}
	}

	return result;
}

Matrix InverseForNonsingular(const Matrix& theMatrix)
{
	Matrix invMat;

	invMat.matSize = theMatrix.matSize;

	float det = matDeterm(theMatrix);

	for (unsigned int i = 0; i < invMat.matSize; i++)
	{
		for (unsigned int j = 0; j < invMat.matSize; j++)
		{
			int signum = 1 - 2 * ((int)(i + j) % 2);
			invMat.elem[i][j] = matDeterm(Minor(theMatrix, j, i)) * signum / det;
		}
	}
	return invMat;
}



int main(int argc, char* argv[])
{
	cout << "Calculates inverse matrix for given 3x3 matrix" << endl;

	Matrix dataMat;

	if (argc < 2)
	{
		cout << "The program must have argument: name of file where given matrix is" << endl;
		return 0; // недостаточно аргументов
	}

	string fileName = argv[1];
	ifstream matrixFile(fileName); // попытка открыть файл
	if (!matrixFile)
	{
		cout << "File is not found!" << endl;
		return 1;
	}
	
	const unsigned int dataMatSize = 3;
	dataMat = SetMatrix(matrixFile, dataMatSize);

	matrixFile.close(); // закрываем файл, где содержится данная матрица

	PrintMatrix(dataMat);
	float det = matDeterm(dataMat);

	if (abs(det) < 1.e-8)
	{
		cout << "Given matrix is singular, so there is no inverse for it!" << endl;
	}
	else
	{
		cout << "Inverse for given matrix is matrix" << endl;
		PrintMatrix(InverseForNonsingular(dataMat));
	}

	cout << matDeterm(dataMat) << endl;
			
	

	return 0;
}

