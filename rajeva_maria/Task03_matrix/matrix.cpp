#include <iostream>
#include<vector>
#include<stdlib.h>
using namespace std;

template <typename T>
class TMatrix
{public:
	vector <vector<T> > matrix;
	TMatrix()
	{};
/*	const size_t Row() const
	{
		return matrix.size();
	};
	const size_t Col() const
	{
		return matrix[1].size();
	};*/
	TMatrix(const TMatrix& matr)
	{	
		Resize(matr.Row()+1, matr.Col()+1);
		for (size_t i=1;i<matr.Row()+1;i++)
			for (int j=1;j<matr.Col()+1;j++)
				matrix[i][j]=matr.At(i,j);
		
	};
	void Resize(size_t r, size_t c)
	{
		matrix.resize(r);
		for (size_t i=1;i<r;++i)
		{
			matrix[i].resize(c);
		}
	};
	const T& At (size_t row, size_t col) const
	{
		return (matrix[row][col]);
	};
	T& At(size_t row, size_t col)
	{
		return (matrix[row][col]);
	};
	size_t Row() const
	{
		return(matrix.size()-1);
	};
	size_t Col() const
	{
		return(matrix[1].size()-1);
	}
	TMatrix(size_t rowCount,size_t colCount)
	{				
		//cout<<rowCount<<' '<<colCount<<endl;
		matrix.resize(rowCount+1);
		for (int i=1;i<rowCount+1;i++)
				matrix[i].resize(colCount+1);
		//cout<<Col()<<' '<<Row()<<endl<<endl;
	}
	TMatrix<T>operator = (const TMatrix<T>&matr)
	{
		Resize(matr.Row()+1, matr.Col()+1);
		for (int i=1;i<matr.Row()+1;i++)
			for (int j=1;j<matr.Col();j++)
				matrix[i][j]=matr.At(i,j);
				return *this;
	}
	TMatrix<T> operator + (const TMatrix<T>&matr)
	{
		TMatrix<T> m(*this);
		for (size_t i=1;i<matr.Row()+1;i++)
			for(size_t j=1;j<matr.Col()+1;j++)
				m.At(i,j)=m.At(i,j)+matr.At(i,j);
		return m;
	}
	TMatrix<T> operator - (const TMatrix<T>&matr)
	{
		TMatrix<T> m(*this);
		for ( size_t i=1;i<matr.Row()+1;i++)
			for(size_t j=1;j<matr.Col()+1;j++)
				m.At(i,j)=m.At(i,j)-matr.At(i,j);
		return m;
	}
	TMatrix<T>operator * (const int &n)
	{
		TMatrix<T> m (*this);
		for (int i=1;i<m.Row()+1;i++)
			for(int j=1;j<m.Col()+1;j++)
			m.At(i,j)=n*(m.At(i,j));
			return (m);
	}
	TMatrix<T> operator * (const TMatrix<T>&matr)
	{
		TMatrix<T>m(Row()+1,matr.Col()+1);
		for (int i=1;i<Row()+1;i++)
			for(int j=1;j<matr.Col()+1;j++)
				for (int p=1;p<Col()+1;p++)
				{	
					
					m.At(i,j)=m.At(i,j)+At(i,p)*matr.At(p,j);
				}
		return m;
	}
	TMatrix<T>& operator *=(const T N)
	{
		//TMatrix<T> t(*this);
		*this=*this*N;
		
		return *this;
	}
	TMatrix<T>&operator*=(const TMatrix<T>matr)
	{
		*this=*this*matr;
		return *this;
	}
	TMatrix<T>&operator+=(const TMatrix<T>&matr)
	{
		*this=*this+matr;
		return *this;
	}
	TMatrix<T>&operator-=(const TMatrix<T>&matr)
	{
		*this=*this-matr;
		return *this;
	}
	TMatrix<T> Transpose()
	{	
		TMatrix<T>matr(*this);
		
		TMatrix<T>newmatr(matr.Col(),matr.Row());
		for (size_t i=1;i<matr.Row()+1;i++)
			for (size_t j=1;j<matr.Col()+1;j++)
			{
				newmatr.At(i,j)=At(j,i);
			}
			*this=newmatr;
			return *this;
	}
};
template<typename T>
	ostream& operator << (ostream& out,const TMatrix<T>&m)
	{
		//out<<m.Row()<<' '<<m.Col();
		for (size_t i=1;i<m.Row()+1;++i)
			for (size_t j=1;j<m.Col()+1;++j)
			{
				out<<m.At(i,j)<<' ';
			}
			out<<endl;
		return out;
	} 
template<typename T>
istream& operator >> (ostream&out, const TMatrix<T>&m)
{
	for (size_t i=1;i<m.Row()+1;++i)
		for(size_t j=1;j<m.Col()+1;++j)
		{
			cin>>m.At(i,j);
		}
		return in;
		
}



int main()
{
TMatrix<int> M1(3,3);
for (int i=1;i<4;i++)
for (int j=1;j<4;j++)
	M1.At(i,j)=i;

TMatrix<int>M2(M1);
//cout<<M2;
//M2=M1;
TMatrix<int>M3(3,3);

M3=M1+M2;
cout<<M3;
//cout<<M3.Col()<<' '<<M3.Row()<<endl;
M1*=M2;
M3*=4;
//M3-=M3;
//for (int i=1;i<4;i++)
//for (int j=1;j<4;j++)
//	cout<<M3.At(i,j)<<' ';
//cout<<M3.Col()<<' '<<M3.Row()<<endl;
M3.Transpose();
//cout<<M3.Col()<<' '<<M3.Row()<<endl;
//for (int i=1;i<4;i++)
//for (int j=1;j<4;j++)
	//cout<<M3.At(i,j)<<' ';
//cout<<M3<<' ';
system("pause");
return 0;
}