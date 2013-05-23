#include <iostream>;
#include <vector>;
#include <string>;
#include <cmath>
using namespace std;

template <typename T>
class TMatrix
{
    int row;
    int col;
    vector <vector<T> > matrix;
    //friend istream& operator>> (istream& in, TMatrix<T> &m);
public:
    TMatrix()
    {
        row = 0;
        col = 0;
        matrix = 0;
    }
    TMatrix(const TMatrix <T> &other)
    {
    	row = other.rowCount();
    	col = other.colCount();
        matrix.resize(row);
    	for (int i=0; i<row; i++)
	   	{
	    	matrix[i].resize(col);
      		for (int j=0; j<col; j++) matrix[i][j] = other.At(i,j);	
	    }
    }
    TMatrix(size_t rowCount, size_t colCount)
    {
        if (rowCount>0 && colCount>0)
        {
	        row = rowCount;
        	col = colCount;
            matrix.resize(row);
        	for (int i=0; i<row; i++)
        	{
        		matrix[i].resize(col);
		        for(int j=0; j<col; j++)
			        matrix[i][j]=0;
	        } 
        }
    }
    ~TMatrix()
    {}
    TMatrix& operator= (const TMatrix <T>& other)
    {
    	if (&other!=this)
    	{
    		for(int i=0; i<row; i++)
    			matrix[i].clear();
            matrix.clear();
    		row = other.rowCount();
    		col = other.colCount();
            matrix.resize(row);
    		for (int i=0; i<row; i++)
	    	{
		    	matrix[i].resize(col);
	       		for (int j=0; j<col; j++) matrix[i][j] = other.At(i,j);	
		    }
	    }
	    return *this;
    }
    int colCount() const
    {
        return col;
    }
    int rowCount() const
    {
        return row;
    }
    TMatrix operator+ (const TMatrix &m) const 
    {
    	TMatrix temp(*this);
	    for (int i=0; i<row; i++)
		    for (int j=0; j<col; j++)
			    temp.At(i,j) = matrix[i][j] + m.At(i,j);
    	return temp;
    }
    void operator+= (const TMatrix &m)
    {
        *this=*this+m;
    }
    TMatrix operator- (const TMatrix &m) const 
    {
	    TMatrix temp = *this;
		for(int i=0; i<row; i++)
			for(int j=0; j<col; j++)
				temp.At(i,j) = matrix[i][j] - m.At(i,j);
    	return temp;
    }
    void operator-= (const TMatrix &m)
    {
        *this=*this-m;
    }
    TMatrix operator* (T a) const 
    {
    	TMatrix temp=*this;
    	for(int i=0; i<row; i++)
    		for(int j=0; j<col; j++)
	    			temp.At(i,j)=matrix[i][j]*a;
    	return temp;
    }
    TMatrix operator* (const TMatrix &m) const 
    {
	    TMatrix res(row, m.colCount());
        for(int i=0; i<row; i++)
            for(int j=0; j<m.colCount(); j++)
                for(int k=0; k<col; k++)
                    res.At(i,j)=res.At(i,j)+matrix[i][k]*m.At(k,j);
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
        TMatrix temp(col, row);
        for (int i=0; i<row; ++i)
            for (int j=0; j<col; ++j)
                temp.At(i,j)=matrix[j][i];
        *this=temp;
    }
};

template <typename T>
TMatrix<T> ShtrassenMultiply(const TMatrix<T> &A, const TMatrix<T> &B)
{
    int N = A.rowCount();
    int Ns = ceil(N/2.);
    TMatrix <T> temp(N,N);
    if (N<=2) temp = A*B;
    else
    {
        TMatrix <T> A11(Ns,Ns);
        TMatrix <T> A12(Ns,Ns);
        TMatrix <T> A21(Ns,Ns);
        TMatrix <T> A22(Ns,Ns);
        TMatrix <T> B11(Ns,Ns);
        TMatrix <T> B12(Ns,Ns);
        TMatrix <T> B21(Ns,Ns);
        TMatrix <T> B22(Ns,Ns);
        TMatrix <T> C11(Ns,Ns);
        TMatrix <T> C12(Ns,Ns);
        TMatrix <T> C21(Ns,Ns);
        TMatrix <T> C22(Ns,Ns);
        TMatrix <T> P1(Ns,Ns);
        TMatrix <T> P2(Ns,Ns);
        TMatrix <T> P3(Ns,Ns);
        TMatrix <T> P4(Ns,Ns);
        TMatrix <T> P5(Ns,Ns);
        TMatrix <T> P6(Ns,Ns);
        TMatrix <T> P7(Ns,Ns);

        for (int i = 0; i < Ns; i++)
        {
            for (int j = 0; j < Ns; j++)
            {
                A11.At(i,j) = A.At(i,j);
                if (j+Ns<A.colCount()) A12.At(i,j) = A.At(i,j+Ns);
                else A12.At(i,j) = 0;
                if (i+Ns<A.colCount()) A21.At(i,j) = A.At(i+Ns,j);
                else A21.At(i,j) = 0;
                if (j+Ns<A.colCount() && i+Ns<A.colCount()) A22.At(i,j) = A.At(i+Ns,j+Ns);
                else A22.At(i,j) = 0;

                B11.At(i,j) = B.At(i,j);
                if (j+Ns<B.colCount()) B12.At(i,j) = B.At(i,j+Ns);
                else B12.At(i,j) = 0;
                if (i+Ns<B.colCount()) B21.At(i,j) = B.At(i+Ns,j);
                else B21.At(i,j) = 0;
                if (j+Ns<B.colCount() && i+Ns<B.colCount()) B22.At(i,j) = B.At(i+Ns,j+Ns);
                else B22.At(i,j) = 0;                
            }
        }
        P1 = ShtrassenMultiply(A11+A22, B11+B22);
        P2 = ShtrassenMultiply(A21+A22, B11);
        P3 = ShtrassenMultiply(A11, B12-B22);
        P4 = ShtrassenMultiply(A22, B21-B11);
        P5 = ShtrassenMultiply(A11+A12, B22);
        P6 = ShtrassenMultiply(A21-A11, B11+B12);
        P7 = ShtrassenMultiply(A12-A22, B21+B22);
        C11 = P1+P4-P5+P7;
        C12 = P3+P5;
        C21 = P2+P4;
        C22 = P1-P2+P3+P6;

        for (size_t i = 0; i < Ns ; i++)
        {
            for (size_t j = 0; j < Ns ; j++)
            {
                temp.At(i,j) = C11.At(i,j);
                if (j+Ns<temp.colCount()) temp.At(i, j+Ns) = C12.At(i,j);
                if (i+Ns<temp.colCount())temp.At(i+Ns, j) = C21.At(i,j);
                if (j+Ns<temp.colCount() && i+Ns<temp.colCount()) temp.At(i+Ns, j+Ns) = C22.At(i,j);
            }
        }
    }
    return temp;
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


int main()
{
    TMatrix<int> a(5,5); 
    for (int i=0, k=0; i<a.rowCount(); ++i)
        for (int j=0; j<a.colCount(); ++j, ++k) a.At(i,j) = k;
    cout<<a<<endl;
    TMatrix<int> b(a);
    b=a*2;
    cout<<b<<endl;
    a=a+b;
    cout<<a<<endl;
    TMatrix<int> c=a*b;
    cout<<c<<endl;
    a = ShtrassenMultiply(a,b);
    cout<<a<<endl;
    b+=a;
    cout<<b<<endl;
    a-=b;
    cout<<a<<endl;
    a*=-1;
    cout<<a<<endl;
    return 0;
}