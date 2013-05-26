#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <time.h>

using namespace std;
typedef long long i64;
i64 GetClock() { return clock() * 1000 / CLOCKS_PER_SEC;}
class TTimePrinter {
      i64 Start;
  public:
      TTimePrinter()
          : Start(GetClock()) {
      }
      void Print() const {
          cout << "\tTime: " << this->GetTime() << " sec" << endl; //milliseconds?
      }
      double GetTime() const {
          return (GetClock() - Start) * 0.001;
      }
      void Reset() {
          Start = GetClock();
      }
  };
template <class T>
class TMatrix
{
private:
	int row;
	int col;
	bool transp;
	vector<T> matrix;
public:
	TMatrix()
	{
		row = 1;
		col = 1;
		transp = false;
		matrix = vector<T> (1, 0);
	}
	TMatrix (const TMatrix& m) { *this = m;}
	TMatrix (int new_row, int new_col)
	{
		row = new_row;
		col = new_col;
		transp = false;
		matrix = vector<T> (row*col, 0);
	}
	TMatrix& operator= (const TMatrix &m)
	{
		if(&m != this)
		{
			row = m.row;
			col = m.col;
			transp = m.transp;
			matrix = vector<T> (row*col, 0);
			for(size_t i = 0; i < matrix.size(); i++)
				(*this).matrix[i] = m.matrix[i];	
		}
		return *this;
	}
	TMatrix operator+ (const TMatrix &m) const 
	{
		TMatrix tmp = *this;
		tmp += m;
		return tmp;
	}
	TMatrix operator- (const TMatrix &m) const 
	{
		TMatrix tmp = *this;
		tmp -= m;
		return tmp;
	}
	TMatrix operator* (T a) const 
	{
		TMatrix tmp = *this;
		for(size_t i = 0; i < matrix.size(); i++)
			tmp.matrix[i] = (*this).matrix[i] * a;
		return tmp;
	}
	TMatrix operator* (const TMatrix &m) const 
	{
		TMatrix mult(count_row(), m.count_col());
		for (int i = 0; i < count_row(); ++i)
			for (int j = 0; j < m.count_col(); ++j)
				for(int k = 0; k < count_col(); ++k)
					mult(i, j) = mult(i, j) + (*this)(i, k) * m(k, j);
			return mult;
	}
	void operator+= (const TMatrix &m)
	{
		for(size_t i = 0; i < matrix.size(); i++)
			(*this).matrix[i] = (*this).matrix[i] + m.matrix[i];
	}
	void operator-= (const TMatrix &m)
	{
		for(size_t i = 0; i < matrix.size(); i++)
			(*this).matrix[i] = (*this).matrix[i] - m.matrix[i];
	}
	void operator *= (T a) { *this = *this * a;}
	void operator *= (const TMatrix &m) { *this = *this * m;}
	TMatrix& resize(int new_row, int new_col)
	{
		if ((new_row == row) && (new_col == col)) return *this;
		TMatrix tmp(new_row, new_col);
		for (int i = 0; i < new_row; ++i)
			for (int j = 0; j < new_col; ++j)
				if ((i < row) && (j < col))
					tmp(i, j) = (*this)(i, j);
				else 
					tmp(i, j) = 0;
		matrix = tmp.matrix;
		row = new_row;
		col = new_col;
		(*this) = tmp;
		return (*this); 
	}
	T& At(int i, int j) 
	{
		if (transp)
			return matrix[(j-1) * col + (i-1)];
		return matrix[(i-1) * col + (j-1)];
	}
	T At(int i, int j) const
	{
		if (transp)
			return matrix[(j-1) * col + (i-1)];
		return matrix[(i-1) * col + (j-1)];
	}
	T& operator() (int i, int j) 
	{
		if (transp)
			return matrix[(j) * col + (i)];
		return matrix[(i) * col + (j)];
	}
	T operator() (int i, int j) const
	{
		if (transp)
			return matrix[(j) * col + (i)];
		return matrix[(i) * col + (j)];
	}
	TMatrix& transpose()
	{
		transp =! transp;
		return *this;
	}
	int count_row() const
	{
		if (transp)
			return col;
		return row;
	}
	int count_col() const
	{
		if (transp)
			return row;
		return col;
	}
	bool is_transp() const { return transp;}
};	

template <class T>
TMatrix<T> ShtrassenMultiply(const TMatrix<T>& A, const TMatrix<T>& B)
{
	if (A.count_row() <= 16) { return A * B;}
	int row = A.count_row();
	int part = row/2;
    TMatrix<T> A11(part, part), A12(part, part), A21(part, part), A22(part, part); 
	TMatrix<T> B11(part, part), B12(part, part), B21(part, part), B22(part, part);
    for (int i = 0; i < part; ++i) 
        for (int j = 0; j < part; ++j) 
		{
			if ((i < row) && (j < row)) 
				A11(i, j) = A(i, j);
			if ((i < row) && (j + part < row))  
				A12(i, j) = A(i, j + part);
			if ((i + part < row) && (j < row)) 
				A21(i, j) = A(i + part, j);
			if ((i + part < row) && (j + part < row)) 
				A22(i, j) = A(i + part, j + part);
			if ((i < row) && (j < row)) 
				B11(i, j) = B(i, j);
			if ((i < row) && ((j + part < row))) 
				B12(i, j) = B(i, j + part);
			if ((i + part < row) && (j < row)) 
				B21(i, j) = B(i + part, j);
			if ((i + part < row) && (j + part < row)) 
				B22(i, j) = B(i + part, j + part);
        }
    TMatrix<T> P1(part, part), P2(part, part), P3(part, part), P4(part, part), P5(part, part), P6(part, part), P7(part, part);
    P1 = ShtrassenMultiply ((A11 + A22), (B11 + B22));
    P2 = ShtrassenMultiply ((A21 + A22), (B11));
    P3 = ShtrassenMultiply (A11, (B12 - B22));
    P4 = ShtrassenMultiply (A22, (B21 - B11));
    P5 = ShtrassenMultiply ((A11 + A12), (B22));
    P6 = ShtrassenMultiply ((A21 - A11), (B11 + B12));
    P7 = ShtrassenMultiply ((A12 - A22), (B21 + B22));
    TMatrix<T> mult(row, row);
	for (int i = 0; i < row; ++i) 
		for (int j = 0; j < row; ++j) 
			if ((i < part) && (j < part)) 
				mult(i, j) = P1(i,j) + P4(i, j) + P7(i, j) - P5(i, j) ;
			else 
				if (i < part) 
					mult(i, j) = P3(i, j - part) + P5(i, j - part);
				else 
					if (j < part) 
						mult(i, j) = P2(i - part, j) + P4(i - part, j);
					else 
						mult(i, j) = P1(i-part, j-part) - P2(i-part, j-part) + P3(i-part, j-part) + P6(i-part, j-part);
    return mult;
}
template <class T>
std::ostream& operator << (std::ostream& stream, const TMatrix<T>& m) 
{
	stream << std::endl;
	for(int i = 0; i < m.count_row(); i++)
	{
		for(int j = 0; j < m.count_col(); j++)
			stream << m(i, j)<<' ';
		stream << std::endl;
	}
	return stream;
}
template <class T>
std::istream& operator >> (std::istream& stream, TMatrix<T>& m)
{
       int row, col;
        cin >> row >> col;
        m.resize(row, col);
        for (size_t i = 0; i < m.count_row(); ++i)
                for (size_t j = 0; j < m.count_col(); ++j)
                        cin >> m(i,j);
        return stream;
}
void simple_tests()
{
	TMatrix<int> mat;
	cout << " TMatrix<int> mat \n" << mat << "\n";
	TMatrix<int> mat2(3,3);
	cout << " TMatrix<int> mat2(3,3) \n" << mat2 << "\n";
	mat2.At(1,2) = 1;
	TMatrix<int> mat3(mat2);
	cout << "mat2.At(1,2) = 1; \nTMatrix<int> mat3(mat2);\n" << mat3;
	mat = mat3;
	cout << "mat = mat3\n" << mat << "\n";
	mat.At(3,2) = 2;
	mat.At(2,2) = 3;
	//arifm
	mat2 += mat;
	mat2 = mat2 + mat;
	mat2 = mat - mat2;
	mat2 -= mat3;
	cout << mat2;
	mat2 *= -1;
	mat2 = mat2 * 2;
	cout << mat3 << mat2 << mat;
	mat3 = mat2 * mat;
	cout << mat3;
	mat3.resize(2, 2);
	mat2.resize(3, 3);
	mat.resize(4, 4);
	cout << mat3 << mat2 << mat;
	mat3.transpose();
	mat2.transpose();
	mat.transpose();
	cout << mat3 << mat2 << mat;
}
void check_Shtrassen()
{
	//CREATE BIG MATRIX (RANDOM ELEM)
	srand((unsigned int)time(NULL));
	ofstream first;
	first.open("first_matrix.txt");
	ofstream second;
	second.open("second_matrix.txt");
	ofstream res;
	res.open("ShtrassenMultiply.txt");
	int row = 32; //<----------------------- set row 2^
	TMatrix<int> Shtrassen1(row, row);
	TMatrix<int> Shtrassen2(row, row);
	TMatrix<int> simple_result;
	TMatrix<int> Sht_result;
	//first << row <<"\n";
	//second << row <<"\n";
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			Shtrassen1(i, j) = -10 + rand() %20;
			//first << Shtrassen1(i, j) << " ";
			Shtrassen2(i, j) = -10 + rand() %20;
			//second << Shtrassen2(i, j) << " ";
		}
		//first << endl;
		//second << endl;
	}
	TTimePrinter tp;
	simple_result = Shtrassen1 * Shtrassen2;
	tp.Print();
	tp.Reset();
	Sht_result = ShtrassenMultiply(Shtrassen1, Shtrassen2);
	tp.Print();
	res << Sht_result;
	first.close();
	second.close();
	res.close();
}
int main()
{
	simple_tests();
	check_Shtrassen();
	system ("pause");
	return 0;
}