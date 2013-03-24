// TMatrix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <ostream>
#include <istream>

using namespace std;

template <typename T>
class TMatrix
{
	
	friend TMatrix operator+ (int a, const TMatrix<T>&matr);
	//friend ostream& operator<<(ostream& out, const TMatrix<T> &matr);
	//friend istream& operator>>(istream& in, TMatrix<T>& matr);
public:
	vector<vector<T>> m;
public:
	TMatrix()
	{}
	TMatrix(const TMatrix<T>& matr)
	{
		size_t rowCount = matr.m.size(), colCount = matr.m[0].size();
		m.resize(rowCount);
		for (size_t i = 0; i < rowCount; ++i)
			m[i].resize(colCount, 0);
		for (size_t i = 0; i < rowCount; ++i)
	    {
		   for (size_t j = 0; j < colCount; ++j)
			  m[i][j] = matr.m[i][j];
		}
       
	}
	TMatrix(size_t rowCount, size_t colCount)
	{
		
	    m.resize(rowCount);
		for (size_t i = 0; i < rowCount; ++i)
			m[i].resize(colCount, 0);
	}
	TMatrix operator= (const TMatrix<T> matr)
	{
		size_t rowCount = matr.m.size(), colCount = matr.m[0].size();
		m.resize(rowCount);
		for (size_t i = 0; i < rowCount; ++i)
			m[i].resize(colCount, 0);

		for (size_t i = 0; i < rowCount; ++i)
	    {
		   for (size_t j = 0; j < colCount; ++j)
			  m[i][j] = matr.m[i][j];
		}
		return *this;
	}
	TMatrix operator+ (const TMatrix<T>& matr)
	{
		TMatrix<T> help(*this);
		for (size_t i = 0; i < help.m.size(); ++i)
	    {
		   for (size_t j = 0; j < help.m[i].size(); ++j)
			  help.m[i][j] = help.m[i][j] + matr.m[i][j];
		}
        return help;
	}
	TMatrix& operator+= (const TMatrix<T>& matr)
	{
		
		for (size_t i = 0; i < m.size(); ++i)
	    {
		   for (size_t j = 0; j < m[i].size(); ++j)
			  m[i][j] = m[i][j] + matr.m[i][j];
		}
        return *this;
	}
	TMatrix operator- (const TMatrix<T>& matr)
	{
		TMatrix<T> help(*this);
		for (size_t i = 0; i < help.m.size(); ++i)
	    {
		   for (size_t j = 0; j < help.m[i].size(); ++j)
			  help.m[i][j] = help.m[i][j] - matr.m[i][j];
		}
        return help;
	}
	TMatrix& operator-= (const TMatrix<T>& matr)
	{
		
		for (size_t i = 0; i < m.size(); ++i)
	    {
		   for (size_t j = 0; j < m[i].size(); ++j)
			  m[i][j] = m[i][j] - matr.m[i][j];
		}
        return *this;
	}
	TMatrix operator* (const TMatrix<T>& matr)
	{
	    
		size_t rowCount = m.size(), colCount = matr.m[0].size(),
		mulCount = m[0].size();
		TMatrix<T> help(rowCount, colCount);
		for (size_t i = 0; i < rowCount; ++i)
			for (size_t j = 0; j < colCount; ++j)
				for (size_t k = 0; k < mulCount; ++k)
				{
					help.m[i][j] += m[i][k]*matr.m[k][j];
				}
		return help;
    }
	TMatrix operator*= (const TMatrix<T>& matr)
	{
	    
		size_t rowCount = m.size(), colCount = matr.m[0].size(),
		mulCount = m[0].size();
		TMatrix<T> help(rowCount, colCount);
		for (size_t i = 0; i < rowCount; ++i)
			for (size_t j = 0; j < colCount; ++j)
				for (size_t k = 0; k < mulCount; ++k)
				{
					help.m[i][j] += m[i][k]*matr.m[k][j];
				}
		*this = help;
		return *this;
    }
	TMatrix operator*= (int a)
	{
		
		int rowCount = m.size(), colCount = m[0].size();
		for (size_t i = 0; i <rowCount; ++i)
			for (size_t j = 0; j < colCount; ++j)
				m[i][j] *= a;
		return *this;

	}
	TMatrix operator* (int a)
	{
		
		int rowCount = m.size(), colCount = m[0].size();
		TMatrix<T> help(*this);
		for (size_t i = 0; i <rowCount; ++i)
			for (size_t j = 0; j < colCount; ++j)
				help.m[i][j] *= a;
		return help;

	}

	
	
	void Resize(size_t rowCount, size_t colCount)
	{
		m.resize(rowCount);
		for (size_t i = 0; i < rowCount; ++i)
			m[i].resize(colCount, 0);
	}
	const T& At(size_t row, size_t col) const
	{
		return m[row][col];
	}
	T& At(size_t row, size_t col)
	{
		return m[row][col];
	}
	void Transpose()
	{
		
		TMatrix help(m[0].size(), m.size());
		
		for (size_t i = 0; i < m.size(); ++i)
			for (size_t j = 0; j < m[0].size(); ++j)
				help.m[j][i] = m[i][j];
		Resize(m[0].size(), m.size());
		*this = help;
	}
	
    void Separate (TMatrix<T>& matr,TMatrix<T>& a,TMatrix<T>& b,TMatrix<T>& c,TMatrix<T>& d)
	{
		size_t size = matr.m.size();
		for (size_t i = 0; i < size/2; ++i)
			for (size_t j = 0; j < size/2; ++j)
			{
				a.m[i][j] = matr.m[i][j];
				b.m[i][j] = matr.m[i][size/2 + j];
				c.m[i][j] = matr.m[size/2 + i][j];
				d.m[i][j] = matr.m[size/2 + i][size/2 +j];
			}
	}
	TMatrix Merge (TMatrix &R, TMatrix &S, TMatrix &L, TMatrix &U)
	{
		size_t size = R.m.size();
		TMatrix help(2*size, 2*size);
		for (size_t i = 0; i < size; ++i)
			for (size_t j = 0; j < size; ++j)
			{
				help.m[i][j] = R.m[i][j];
				help.m[size + i][j] = S.m[i][j];
				help.m[i][j+size] = L.m[i][j];
				help.m[size + i][j + size] = U.m[i][j];
			}
		return help;
	}
	TMatrix MulShtrass(TMatrix& a, TMatrix& b)
	{
		size_t size = a.m.size();
		TMatrix help = _MulShtrass(a,b);
		help.Resize(size,size);
		return help;
	}
	TMatrix _MulShtrass (TMatrix& a, TMatrix& b)
	{
		//to return
		if (a.m.size() == 1)
		{
			TMatrix<T> help(1,1);
			help.m[0][0] = a.m[0][0]*b.m[0][0];
			return help;
		}
		else
		{
			size_t size = a.m.size();
			if (size%2 != 0)
			{
				a.Resize(size+1,size+1);
				b.Resize(size+1, size+1);
				
				a.m[size][size] = 1;
				b.m[size][size] = 1;
				size += size%2;
			}
			TMatrix A(size/2, size/2);
			TMatrix B(size/2, size/2);
			TMatrix C(size/2, size/2);
			TMatrix D(size/2, size/2);
			Separate(a,A,B,C,D);
			TMatrix E(size/2, size/2);
			TMatrix F(size/2, size/2);
			TMatrix G(size/2, size/2);
			TMatrix H(size/2, size/2);
			Separate(b,E,F,G,H);
			TMatrix P1,P2,P3,P4,P5,P6,P7;
			P1 = _MulShtrass(A, G - H);
			P2 = _MulShtrass(A + B, H);
			P3 = _MulShtrass(C + D, E);
			P4 = _MulShtrass(D, F - E);
			P5 = _MulShtrass(A + D, E + H);
			P6 = _MulShtrass(B - D, F + H);
			P7 = _MulShtrass(A - C, E + G);
			//TMatrix R(size/2, size/2);
			//TMatrix S(size/2, size/2);
			//TMatrix L(size/2, size/2);
			//TMatrix U(size/2, size/2);
			TMatrix R,S,L,U;
			R = P5 + P4 - P2 + P6;
			S = P1 + P2;
			L = P3 + P4;
			U = P5 + P1 - P3 - P7;
			//TMatrix wr = Merge(R,S,L,U);
			cout << Merge(R,S,L,U);
			return Merge(R,S,L,U);

		}
	}
};

template <typename T>
ostream& operator<<(ostream& out, const TMatrix<T>& matr)
{
	size_t rowCount = matr.m.size(), colCount = matr.m[0].size(); 
	out << matr.m.size() << ' ' << matr.m[0].size() << endl;
	for (size_t i = 0; i < rowCount; ++i)
	{
		for (size_t j = 0; j < colCount; ++j)
			out << matr.m[i][j] << ' ';
	    out << endl;
	}
	
	return out;
}
template <typename T>
istream& operator>>(istream& in, TMatrix<T>& matr) 
{
	size_t rowCount, colCount;
	cin >> rowCount >> colCount;
	matr.Resize(rowCount, colCount);
	for (size_t i = 0; i < rowCount; ++i)
		for (size_t j = 0; j < colCount; ++j)
			cin >> matr.m[i][j];
	return in;
}
template <typename T>
TMatrix<T> operator* (int a, const TMatrix<T>&matr)
{
	int rowCount = matr.m.size(), colCount = matr.m[0].size();
	TMatrix<T> help(matr);
	for (size_t i = 0; i <rowCount; ++i)
		for (size_t j = 0; j < colCount; ++j)
			help.m[i][j] *= a;
	return help;
}

int main()
{
	/*TMatrix<int> Matrix1(5, 5);
	TMatrix<int> Matrix2(5, 5);
	for (int i = 0; i < 5; ++i)
	  Matrix2.m[i][i]= 2;	
	Matrix1.m[0][0] = 3;
	Matrix1 += Matrix2;
	Print_Matrix(Matrix1);
	Matrix1.Resize(5,6);
	Print_Matrix(Matrix1);
	Matrix1.At(0,0) = 12;
	Matrix1.Transpose();
	Print_Matrix(Matrix1);
	cin >> Matrix1;
	cout << Matrix1 << endl;*/
	TMatrix<int> M1(3,3);
	TMatrix<int> M2(3,3);
	M1.At(0,0) = 1;
	M2.At(0,0) = 1;
	M1.At(1,1) = 1;
	M2.At(1,1) = 1;
	M1.At(2,2) = 1;
	//TMatrix<int> M3(3,3);
	M1 = M1.MulShtrass(M1, M2);
	cout << M1;//._MulShtrass(M1,M2);
	//M1 = M3._MulShtrass(M1,M2);
	//cout << M1;
	return 0;
}

