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
	template <typename U>
	friend TMatrix<U> ShtrassenMultiply(const TMatrix<U> &A, const TMatrix<U> &B);
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
    {}
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
					matrix[i][j] = other.matrix[i][j];
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
			    matrix[i][j] += m.matrix[i][j];
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
			    matrix[i][j] -= m.matrix[i][j];
    }
    TMatrix operator* (T a) const 
    {
    	TMatrix temp=*this;
    	for(size_t i=0; i<row; i++)
    		for(size_t j=0; j<col; j++)
	    		temp.At(i,j) = matrix[i][j]*a;
    	return temp;
    }
    TMatrix operator* (const TMatrix &m) const 
    {
	    //TMatrix res(row, m.colCount());
		vector<vector<T> > mat(row);
		size_t colm = m.colCount();
        for (size_t i=0; i<row; i++)
            for (size_t j=0; j<colm; j++)
			{
				T val = 0;
                for (size_t k=0; k<col; k++)
                    val += matrix[i][k]*m.matrix[k][j];
				mat[i].push_back(val);
				//res.matrix[i][j] = val;
			}
		TMatrix res;
		res.row = row;
		res.col = colm;
		res.matrix.swap(mat);
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

template <typename U>
TMatrix<U> ShtrassenMultiply(const TMatrix<U> &A, const TMatrix<U> &B)
{
	if (A.rowCount()<=128) return A*B;

	size_t col = A.colCount();
	TMatrix <U> temp;
	size_t n = (size_t)ceil(col/2.);
	vector<vector<U> > A11(n), A12(n), A21(n), A22(n), B11(n), B12(n), B21(n), B22(n);
	vector<vector<U> > S1(n), S2(n), S3(n), S4(n), S5(n), S6(n), S7(n), S8(n);
	vector<vector<U> > P1(n), P2(n), P3(n), P4(n), P5(n), P6(n), P7(n);
	vector<vector<U> > T1(n), T2(n);
	vector<vector<U> > C11(n), C12(n), C21(n), C22(n);
	TMatrix <U> mA11, mA12, mA21, mA22, mB11, mB12, mB21, mB22;
	//TMatrix <U> mC11, mC12, mC21, mC22;
	TMatrix <U> mP1, mP2, mP3, mP4, mP5, mP6, mP7;
	TMatrix <U> mS1, mS2, mS3, mS4, mS5, mS6, mS7, mS8;
	//TMatrix <U> mT1, mT2;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			A11[i].push_back( A.matrix[i][j] );
			if (j+n < col) A12[i].push_back( A.matrix[i][j+n] );
			else A12[i].push_back( 0 );
			if (i+n < col) A21[i].push_back( A.matrix[i+n][j] );
			else A21[i].push_back( 0 );
			if (j+n < col && i+n < col) A22[i].push_back( A.matrix[i+n][j+n] );
			else A22[i].push_back( 0 );

			B11[i].push_back( B.matrix[i][j] );
			if (j+n < col) B12[i].push_back( B.matrix[i][j+n] );
			else B12[i].push_back( 0 );
			if (i+n < col) B21[i].push_back( B.matrix[i+n][j] );
			else B21[i].push_back( 0 );
			if (j+n < col && i+n < col) B22[i].push_back( B.matrix[i+n][j+n] );
			else B22[i].push_back( 0 );

			S1[i].push_back( A21[i][j] + A22[i][j] );
			S2[i].push_back( S1[i][j] - A11[i][j] );
			S3[i].push_back( A11[i][j] - A21[i][j] );
			S4[i].push_back( A12[i][j] - S2[i][j]);
			S5[i].push_back( B12[i][j] - B11[i][j] );
			S6[i].push_back( B22[i][j] - S5[i][j]);
			S7[i].push_back( B22[i][j] - B12[i][j] );
			S8[i].push_back( S6[i][j] - B21[i][j] );
		}
	}

//  {S}_{1} := ( {A}_{2,1} +  {A}_{2,2}) +
//  {S}_{2} := ( {S}_{1} -  {A}_{1,1}) 
//  {S}_{3} := ( {A}_{1,1} -  {A}_{2,1}) +
//  {S}_{4} := ( {A}_{1,2} -  {S}_{2}) 
//  {S}_{5} := ( {B}_{1,2} -  {B}_{1,1}) +
//  {S}_{6} := ( {B}_{2,2} -  {S}_{5}) 
//  {S}_{7} := ( {B}_{2,2} -  {B}_{1,2}) +
//  {S}_{8} := ( {S}_{6} -  {B}_{2,1}) 

	mA11.matrix.swap(A11);	mA11.col = n;	mA11.row = n;
	mA12.matrix.swap(A12);	mA12.col = n;	mA12.row = n;
	mA21.matrix.swap(A21);	mA21.col = n;	mA21.row = n;
	mA22.matrix.swap(A22);	mA22.col = n;	mA22.row = n;
	mB11.matrix.swap(B11);	mB11.col = n;	mB11.row = n;
	mB12.matrix.swap(B12);	mB12.col = n;	mB12.row = n;
	mB21.matrix.swap(B21);	mB21.col = n;	mB21.row = n;
	mB22.matrix.swap(B22);	mB22.col = n;	mB22.row = n;
	
	mS1.matrix.swap(S1);	mS1.col = n;	mS1.row = n;
	mS2.matrix.swap(S2);	mS2.col = n;	mS2.row = n;
	mS3.matrix.swap(S3);	mS3.col = n;	mS3.row = n;
	mS4.matrix.swap(S4);	mS4.col = n;	mS4.row = n;
	mS5.matrix.swap(S5);	mS5.col = n;	mS5.row = n;
	mS6.matrix.swap(S6);	mS6.col = n;	mS6.row = n;
	mS7.matrix.swap(S7);	mS7.col = n;	mS7.row = n;
	mS8.matrix.swap(S8);	mS8.col = n;	mS8.row = n;

    mP1 = ShtrassenMultiply(mS2, mS6);
    mP2 = ShtrassenMultiply(mA11, mB11);
    mP3 = ShtrassenMultiply(mA12, mB21);
    mP4 = ShtrassenMultiply(mS3, mS7);
    mP5 = ShtrassenMultiply(mS1, mS5);
    mP6 = ShtrassenMultiply(mS4, mB22);
    mP7 = ShtrassenMultiply(mA22, mS8);
//  {P}_{1} :=  {S}_{2} * {S}_{6} 
//  {P}_{2} :=  {A}_{1,1} * {B}_{1,1} 
//  {P}_{3} :=  {A}_{1,2} * {B}_{2,1} 
//  {P}_{4} :=  {S}_{3} * {S}_{7} 
//  {P}_{5} :=  {S}_{1} * {S}_{5} 
//  {P}_{6} :=  {S}_{4} * {B}_{2,2} 
//	{P}_{7} :=  {A}_{2,2} * {S}_{8} 

	vector<vector<U> > matrix(col);
	for (size_t i = 0; i < col ; i++)
		matrix[i].resize(col);
    //for (size_t i = 0; i < n ; i++)
    //{
    //    for (size_t j = 0; j < n ; j++)
    //    {
    //        matrix[i][j] = mC11.matrix[i][j];
    //        if (j+n < col) matrix[i][j+n] = mC12.matrix[i][j];
    //        if (i+n < col) matrix[i+n][j] = mC21.matrix[i][j];
    //        if (j+n < col && i+n < col) matrix[i+n][j+n] = mC22.matrix[i][j];
    //    }
    //}
	for (size_t i=0; i<n; i++)
		for (size_t j=0; j<n; j++)
		{
			T1[i].push_back( mP1.matrix[i][j] + mP2.matrix[i][j] );
			T2[i].push_back( T1[i][j] + mP4.matrix[i][j] );
			C11[i].push_back( mP2.matrix[i][j] + mP3.matrix[i][j] );
			C12[i].push_back( T1[i][j] + mP5.matrix[i][j] + mP6.matrix[i][j] );
			C21[i].push_back( T2[i][j] - mP7.matrix[i][j] );
			C22[i].push_back( T2[i][j] + mP5.matrix[i][j] );
            
			matrix[i][j] = C11[i][j];
            if (j+n < col) matrix[i][j+n] = C12[i][j];
            if (i+n < col) matrix[i+n][j] = C21[i][j];
            if (j+n < col && i+n < col) matrix[i+n][j+n] = C22[i][j];
		}
	//mT1 = mP1 + mP2;
	//mT2 = mT1 + mP4;

	//mC11 = mP2 + mP3;
	//mC12 = mT1 + mP5 + mP6;
	//mC21 = mT2 - mP7;
	//mC22 = mT2 + mP5;

//	{T}_{1} := {P}_{1} + {P}_{2}
//	{T}_{2} := {T}_{1} + {P}_{4}
//
//
//	{C}_{1,1} := {P}_{2} + {P}_{3}
//	{C}_{1,2} := {T}_{1} + {P}_{5} + {P}_{6}
//	{C}_{2,1} := {T}_{2} - {P}_{7}
//	{C}_{2,2} := {T}_{2} + {P}_{5}

	temp.matrix.swap( matrix );
	temp.col = col;
	temp.row = col;
    return temp;
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
		if (res1 == res2)
			cout << "Matrixs are equal" <<endl;
		else 
		{
			cout << "Not equal" << endl;
			return 0;
		}
	}	
	return 0;
}