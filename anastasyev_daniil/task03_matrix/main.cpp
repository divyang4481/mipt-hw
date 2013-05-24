#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
using namespace std;

typedef long long i64;
i64 GetClock() {
	return clock() * 1000 / CLOCKS_PER_SEC;
}
class TTimePrinter {
	i64 Start;
public:
	TTimePrinter()
		: Start(GetClock()) {
	}
  
	void Print() const {
		cout << "\tTime: " << this->GetTime() << " sec" << endl;
	}
  
	double GetTime() const {
		return (GetClock() - Start) * 0.001;
	}

	void Reset() {
		Start = GetClock();
	}
};

template <typename T>
struct TFoo 
{
    T Value;
    TFoo() : Value(T(0)) { ++Created; }
	TFoo(T v): Value(v) { ++Created; }
    TFoo(const TFoo &other) : Value(other.Value) { ++Created; }
    ~TFoo() { ++Deleted; }
    bool operator< (const TFoo& other) const
    {
        return Value < other.Value;
    }
    TFoo& operator= (const TFoo& other)
    {
        Value = other.Value;
		return *this;
    }
    TFoo& operator= (T r) 
    {
        Value = r;
		return *this;
    }
	void operator += (const TFoo &other)
	{
		Value += other.Value;
	}
	void operator -= (const TFoo &other)
	{
		Value -= other.Value;
	}
	void operator *= (const TFoo &other)
	{
		Value *= other.Value;
	}
	TFoo operator+ (const TFoo &other) const
	{
		TFoo temp(*this);
		temp+=other;
		return temp;
	}
	TFoo operator- (const TFoo &other) const
	{
		TFoo temp(*this);
		temp-=other;
		return temp;
	}
	TFoo operator*(const TFoo &other) const
	{
		TFoo temp(*this);
		temp *= other;
		return temp;
	}
	TFoo operator* (T v) const
	{
		TFoo temp(*this);
		temp.Value*=v;
		return temp;
	}
	bool operator== (const TFoo &a) const
	{
		return (Value == a.Value);
	}
	static int Created;
    static int Deleted;
    static void PrintStats() 
	{
        cout << "TFoo::Created = " << Created << endl << "TFoo::Deleted = " << Deleted << endl;
    }
};


template<> int TFoo<int>::Created = 0;
template<> int TFoo<int>::Deleted = 0;

template <typename T>
class TMatrix
{
    size_t row;
    size_t col;
    vector <vector<T> > matrix;
public:
    TMatrix()
    {
        row = 0;
        col = 0;
    }
    TMatrix(const TMatrix &other)
    {
		*this = other;
    }
    TMatrix(size_t rowCount, size_t colCount)
    {
		if (rowCount > 0 && colCount > 0)
		{
			row = rowCount;
			col = colCount;
			matrix.resize(row);
			for (size_t j=0; j<rowCount; ++j)
				matrix[j].resize(col);
		}
    }
    ~TMatrix()
    {

	}
    TMatrix& operator= (const TMatrix <T>& other)
    {
    	if (&other!=this)
    	{
			row = other.rowCount(); col = other.colCount();
			matrix.resize(row);
			for (size_t i = 0; i < row; ++i)
				matrix[i].resize(col);
			for (size_t i = 0; i < row; ++i)
			{
				for (size_t j = 0; j < col; ++j)
					matrix[i][j] = other.At(i,j);
			}
	    }
	    return *this;
    }
    size_t colCount() const
    {
        return col;
    }
    size_t rowCount() const
    {
        return row;
    }
    TMatrix operator+ (const TMatrix &m) const 
    {
    	TMatrix temp(*this);
		temp += m;
    	return temp;
    }
    void operator+= (const TMatrix &m)
    {
	    for (size_t i=0; i<row; i++)
		    for (size_t j=0; j<col; j++)
			    matrix[i][j] += m.At(i,j);
    }
    TMatrix operator- (const TMatrix &m) const 
    {
	    TMatrix temp(*this);
		temp -= m;
    	return temp;
    }
    void operator-= (const TMatrix &m)
    {
	    for (size_t i=0; i<row; i++)
		    for (size_t j=0; j<col; j++)
			    matrix[i][j] -= m.At(i,j);
    }
    TMatrix operator* (T a) const 
    {
    	TMatrix temp=*this;
    	for(size_t i=0; i<row; i++)
    		for(size_t j=0; j<col; j++)
	    		temp.At(i,j)=matrix[i][j]*a;
    	return temp;
    }
    TMatrix operator* (const TMatrix &m) const 
    {
	    TMatrix res(row, m.colCount());
        for(size_t i=0; i<row; i++)
            for(size_t j=0; j<m.colCount(); j++)
                for(size_t k=0; k<col; k++)
                    res.At(i,j) += matrix[i][k]*m.At(k,j);
        return res;
    }
    void operator*= (const TMatrix &m)
    {
        *this=*this*m;
    }
    void operator*= (const T a)
    {
        *this=*this*a;
    }
	bool  operator== ( TMatrix &m)
	{
		if (row != m.rowCount() || col != m.colCount())
			return false;
		for (size_t i = 0; i < row; ++i)
			for (size_t j = 0; j < col; ++j)
				if (At(i, j) != m.At(i, j))
					return false;
		return true;
	}
    void Resize(size_t rowCount, size_t colCount)
    {
        row = rowCount;
        col = colCount;
        matrix.resize(row);
        for(size_t i=0; i<row; i++) 
            matrix[i].resize(col);
    }
    const T& At(size_t r, size_t c) const
    {
		return matrix[r][c];
    }
    T& At(size_t r, size_t c)
    {
		return matrix[r][c];
    }
    void Transpose()
    {
        for (size_t i=0; i<row; ++i)
            for (size_t j=i+1; j<col; ++j)
                swap(matrix[i][j], matrix[j][i]);
    }
};

template <typename T>
TMatrix<T> ShtrassenMultiply(const TMatrix<T> &A, const TMatrix<T> &B)
{
    if (A.rowCount()<=128) return A*B;
	size_t col = A.colCount();	
	TMatrix <T> result(col, col);
	size_t n = (size_t)ceil(col/2.);
	TMatrix <T> m1(n, n);
	TMatrix <T> m2(n, n);
	TMatrix <T> m3(n, n);
	//S1
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (n+i >= col) m1.At(i,j) = 0;
			else if (n+j >= col) m1.At(i, j) = A.At(n+i, j);
			else m1.At(i,j) = A.At(n+i, j) + A.At(n+i, n+j);
	//S5
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (n+j >= col) m2.At(i,j) -= B.At(i, j);
			else m2.At(i,j) = B.At(i, j+n) - B.At(i, j);
	//P5
	m3 = ShtrassenMultiply(m1, m2);
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
		{
			if (j+n < col)
			{
				result.At(i, j+n) = m3.At(i, j);
				if (i+n < col) result.At(i+n, j+n) = m3.At(i, j);
			}
		}
	//S2
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			m1.At(i,j) -= A.At(i, j);
	//S6
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (n+i >= col || n+j >= col) m2.At(i,j) -= m2.At(i, j);
			else m2.At(i,j) = B.At(i+n, j+n) - m2.At(i, j);
	//P1
	m3 = ShtrassenMultiply(m1, m2);
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
		{
			if (n+i < col)
			{
				result.At(i+n, j) = m3.At(i, j);
				if (n+j < col)
				{
					result.At(i, j+n) += m3.At(i, j);
					result.At(i+n, j+n) += m3.At(i, j);
				}
			}
		}

	//S4
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (j+n >= col) m1.At(i,j) -= m1.At(i, j);
			else m1.At(i,j) = A.At(i, j+n) - m1.At(i, j);
	//S8
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (i+n >= col) m2.At(i,j) -= 0;
			else m2.At(i,j) -= B.At(i+n, j);
	//B22
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (i+n >= col || j+n >= col) m3.At(i,j) = 0;
			else m3.At(i,j) = B.At(i+n, j+n);
	//P6
	m3 = ShtrassenMultiply(m1, m3);
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (j+n < col)
				result.At(i, j+n) += m3.At(i, j);

	//A22
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (i+n >= col || j+n >= col) m3.At(i,j) = 0;
			else m3.At(i,j) = A.At(i+n, j+n);
	//P7
	m3 = ShtrassenMultiply(m2, m3);
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (i+n < col)
				result.At(i+n, j) -= m3.At(i, j);

	//A11
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			m1.At(i,j) = A.At(i, j);
	//B11
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			m2.At(i,j) = B.At(i, j);
	//P2
	m3 = ShtrassenMultiply(m1, m2);
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
		{
			result.At (i, j) = m3.At(i, j);
			if (n+i < col)
			{
				result.At(i+n, j) += m3.At(i, j);
				if (n+j < col)
				{
					result.At(i, j+n) += m3.At(i, j);
					result.At(i+n, j+n) += m3.At(i, j);
				}
			}
		}

	//A12
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (j+n >= col) m1.At(i,j) = 0;
			else m1.At(i,j) = A.At(i, j+n);
	//B21
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (i+n >= col) m2.At(i,j) = 0;
			else m2.At(i,j) = B.At(i+n, j);
	//P3
	m3 = ShtrassenMultiply(m1, m2);
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			result.At(i, j) += m3.At(i, j);

	//S3
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (i+n >= col) m1.At(i,j) = A.At(i, j);
			else m1.At(i,j) = A.At(i, j) - A.At(i+n, j);
	//S7
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
			if (j+n >= col) m2.At(i,j) = 0;
			else if (i+n >= col) m2.At(i,j) -= B.At(i, j+n);
			else m2.At(i,j) = B.At(i+n, j+n) - B.At(i, j+n);
	//P4
	m3 = ShtrassenMultiply(m1, m2);
	for (size_t i=0; i<n; ++i)
		for (size_t j=0; j<n; ++j)
		{
			if (i+n < col)
			{
				result.At (i+n, j) += m3.At(i, j);
				if (j+n < col)
					result.At (i+n, j+n) += m3.At(i, j);
			}
		}
	return result;

    //int N = A.rowCount();
    //int Ns = ceil(N/2.);
    //TMatrix <T> temp(N,N);
    //if (N<=128) temp = A*B;
    //else
    //{
    //    TMatrix <T> A11(Ns,Ns);
    //    TMatrix <T> A12(Ns,Ns);
    //    TMatrix <T> A21(Ns,Ns);
    //    TMatrix <T> A22(Ns,Ns);
    //    TMatrix <T> B11(Ns,Ns);
    //    TMatrix <T> B12(Ns,Ns);
    //    TMatrix <T> B21(Ns,Ns);
    //    TMatrix <T> B22(Ns,Ns);
    //    TMatrix <T> C11(Ns,Ns);
    //    TMatrix <T> C12(Ns,Ns);
    //    TMatrix <T> C21(Ns,Ns);
    //    TMatrix <T> C22(Ns,Ns);
    //    TMatrix <T> P1(Ns,Ns);
    //    TMatrix <T> P2(Ns,Ns);
    //    TMatrix <T> P3(Ns,Ns);
    //    TMatrix <T> P4(Ns,Ns);
    //    TMatrix <T> P5(Ns,Ns);
    //    TMatrix <T> P6(Ns,Ns);
    //    TMatrix <T> P7(Ns,Ns);

    //    for (int i = 0; i < Ns; i++)
    //    {
    //        for (int j = 0; j < Ns; j++)
    //        {
    //            A11.At(i,j) = A.At(i,j);
    //            if (j+Ns<A.colCount()) A12.At(i,j) = A.At(i,j+Ns);
    //            else A12.At(i,j) = 0;
    //            if (i+Ns<A.colCount()) A21.At(i,j) = A.At(i+Ns,j);
    //            else A21.At(i,j) = 0;
    //            if (j+Ns<A.colCount() && i+Ns<A.colCount()) A22.At(i,j) = A.At(i+Ns,j+Ns);
    //            else A22.At(i,j) = 0;

    //            B11.At(i,j) = B.At(i,j);
    //            if (j+Ns<B.colCount()) B12.At(i,j) = B.At(i,j+Ns);
    //            else B12.At(i,j) = 0;
    //            if (i+Ns<B.colCount()) B21.At(i,j) = B.At(i+Ns,j);
    //            else B21.At(i,j) = 0;
    //            if (j+Ns<B.colCount() && i+Ns<B.colCount()) B22.At(i,j) = B.At(i+Ns,j+Ns);
    //            else B22.At(i,j) = 0;                
    //        }
    //    }
    //    P1 = ShtrassenMultiply(A11+A22, B11+B22);
    //    P2 = ShtrassenMultiply(A21+A22, B11);
    //    P3 = ShtrassenMultiply(A11, B12-B22);
    //    P4 = ShtrassenMultiply(A22, B21-B11);
    //    P5 = ShtrassenMultiply(A11+A12, B22);
    //    P6 = ShtrassenMultiply(A21-A11, B11+B12);
    //    P7 = ShtrassenMultiply(A12-A22, B21+B22);
    //    C11 = P1+P4-P5+P7;
    //    C12 = P3+P5;
    //    C21 = P2+P4;
    //    C22 = P1-P2+P3+P6;

    //    for (size_t i = 0; i < Ns ; i++)
    //    {
    //        for (size_t j = 0; j < Ns ; j++)
    //        {
    //            temp.At(i,j) = C11.At(i,j);
    //            if (j+Ns<temp.colCount()) temp.At(i, j+Ns) = C12.At(i,j);
    //            if (i+Ns<temp.colCount())temp.At(i+Ns, j) = C21.At(i,j);
    //            if (j+Ns<temp.colCount() && i+Ns<temp.colCount()) temp.At(i+Ns, j+Ns) = C22.At(i,j);
    //        }
    //    }
    //}
    //return temp;
}

template <typename T>
ostream& operator<< (ostream &out, const TFoo<T> &t) 
{
	out << t.Value;
    return out;
};

template <typename T>
ostream& operator<< (ostream &out, const TMatrix<T> &m) 
{
    for (size_t i=0; i<m.rowCount(); i++)
    {
    	for (size_t j=0; j<m.colCount(); j++) out<<m.At(i,j)<<' ';
    	out<<endl;
    }
    return out;
};

template<typename T>
istream& operator>> (istream& in, TMatrix<T> &m)
{
	int row, col;
	in>>row>>col;
	TMatrix<T> result (row, col);
	for (int i=0; i<row; ++i)
	{
		for(int j=0; j<col; ++j)
		{
			T a;
			cin >> tp;
			result.At(i,j)=a;
		}
	}
	m=result;
	return in;
}

int main()
{
	{	
	cout<<"A:"<<endl;
    TMatrix<TFoo<int> > a(5, 5);
    for (size_t i=0, k=0; i<a.rowCount(); ++i)
        for (size_t j=0; j<a.colCount(); ++j, ++k) 
			a.At(i,j) = k;
    cout<<a<<endl;
	cout << "\t\tB = A * 2:"<<endl;
    TMatrix<TFoo<int> > b(a);
    b=a*2;
    cout<<b<<endl;
    a=a+b;
    cout<<"\t\tA = A + B :"<<endl<<a<<endl;
    TMatrix<TFoo<int> > c=a*b;
    cout<<"\t\tC = A * B :"<<endl<<c<<endl;
    a = ShtrassenMultiply(a,b);
    cout<<"\t\tShtrassenMultiply A = A * B :"<<endl<<a<<endl;
    b+=a;
    cout<<"\t\tB+=A :"<<endl<<b<<endl;
    a-=b;
    cout<<"\t\tA-=B :"<<endl<<a<<endl;
	a*= -1;
    cout<<"\t\tA*(-1) :"<<endl<<a<<endl;
	}
	TFoo<int>::PrintStats();




	srand((unsigned int)time(NULL));
	int n=16;
	TMatrix<int> a(n,n);
	TMatrix<int> b(n,n);
	a*=b;
	TTimePrinter timer;
	for (int i=0; i<n; ++i)
	{
		for (int j=0; j<n; ++j)
		{
			a.At(i,j)=rand() % 100;
			b.At(i,j)=rand() % 100;
		}
	}
	TMatrix <int> m1(n,n);
	TMatrix <int> m2(n,n);
	for (int k=0; k < 6; k++)
	{
		n*=2;
		cout << "N = " << n << endl;
		a.Resize (n, n);
		b.Resize (n, n);
		for (int i = 0; i < n/2; i++)
		{
			for (int j = 0; j < n/2; j++)
			{
				a.At(i, j+n/2) = rand() % 100;
				a.At(i+n/2, j) = rand() % 100; 
				b.At(i, j+n/2) = rand() % 100;
				b.At(i+n/2, j) = rand() % 100;
			}
		}

		timer.Reset();
		TMatrix <int> res1 = ShtrassenMultiply(a,b);
		double time = timer.GetTime();
		cout << "Strassen method: " << time <<endl;
		timer.Reset();
		TMatrix <int> res2 = a*b;
		time = timer.GetTime();
		cout << "Usual method: "<< time <<endl;
	}	
	return 0;
}