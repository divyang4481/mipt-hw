#include <vector>
#include <math.h>
#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
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
  
      double Print() const {
          return this->GetTime() ;
      }
  
      double GetTime() const {
          return (GetClock() - Start) * 0.001;
      }

      void Reset() {
          Start = GetClock();
      }
  };
template <typename T>
class TMatrix
{
public:
        vector<vector<T> > m;
    void Separate (const TMatrix &matr,TMatrix &a,TMatrix &b,TMatrix &c,TMatrix &d, size_t size)
        {
                
                for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                        {
                                a.m[i][j] = matr.m[i][j];
                                b.m[i][j] = matr.m[i][size + j];
                                c.m[i][j] = matr.m[size + i][j];
                                d.m[i][j] = matr.m[size + i][size +j];
                        }
        }
        TMatrix Merge (const TMatrix &R,const TMatrix &S, const TMatrix &L, const TMatrix &U)
        {
                size_t size = R.rows();
                size_t bigsize = 2 * size;
                TMatrix help(bigsize, bigsize);
                for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                        {
                                help.m[i][j] = R.m[i][j];
                                help.m[i][j + size] = S.m[i][j];
                                help.m[i + size][j] = L.m[i][j];
                                help.m[i + size][j + size] = U.m[i][j];
                        }
                
                return help;
        }
        TMatrix _MulShtrass (const TMatrix& a, const TMatrix& b)
        {
                //to return
                if (a.m.size() <= 128)
                {
                        TMatrix<T> help;
                        help = a*b;
                        return help;
                }
                else
                {
                       
					    size_t size = a.cols();
						size_t s = size / 2;
						TMatrix A(s, s);
                        TMatrix B(s, s);
                        TMatrix C(s, s);
                        TMatrix D(s, s);
                        Separate(a,A,B,C,D, a.rows()/2);
                        TMatrix E(s, s);
                        TMatrix F(s, s);
                        TMatrix G(s, s);
                        TMatrix H(s, s);
						Separate(b,E,G,F,H, b.rows()/2);
                        TMatrix P1,P2,P3,P4,P5,P6,P7;
                        P1 = _MulShtrass(A, G - H);
                        P2 = _MulShtrass(A + B, H);
                        P3 = _MulShtrass(C + D, E);
                        P4 = _MulShtrass(D, F - E);
                        P5 = _MulShtrass(A + D, E + H);
                        P6 = _MulShtrass(B - D, F + H);
                        P7 = _MulShtrass(A - C, E + G);
                       /* A.Resize(size, size);
						B.Resize(size, size);
						C.Resize(size, size);
						D.Resize(size, size);
						E.Resize(size, size);
						F.Resize(size, size);
						G.Resize(size, size);
						H.Resize(size, size);*/
						
                        TMatrix R,S,L,U;
                        R = P5 + P4 - P2 + P6;
                        S = P1 + P2;
                        L = P3 + P4;
                        U = P5 + P1 - P3 - P7;
                        //Merge(R,S,L,U,flag);

                        return Merge(R,S,L,U);
                }
        }
public:
        TMatrix()
        {}
        TMatrix(const TMatrix<T>& matr)
        {
                *this = matr;
       
        }
        TMatrix(size_t rowCount, size_t colCount)
        {
                
            m.resize(rowCount);
                for (size_t i = 0; i < rowCount; ++i)
                        m[i].resize(colCount);
        }
        void Transpose()
        {
        size_t rowCount = rows(), colCount = cols();            
                TMatrix help(colCount, rowCount);
                
                for (size_t i = 0; i < rowCount; ++i)
                        for (size_t j = 0; j < colCount; ++j)
                                help.m[j][i] = m[i][j];
                Resize(colCount, rowCount);
                *this = help;
        }

        TMatrix& operator= (const TMatrix &matr)
        {
                size_t rowCount = matr.rows(), colCount = matr.cols();
                m.resize(rowCount);
                for (size_t i = 0; i < rowCount; ++i)
                        m[i].resize(colCount);

                for (size_t i = 0; i < rowCount; ++i)
            {
                   for (size_t j = 0; j < colCount; ++j)
                          m[i][j] = matr.m[i][j];
                }
                return *this;
        }
        TMatrix operator+ (const TMatrix<T> &matr)
        {
               TMatrix<T> help(*this);
               help+=matr;
			   return help;
        }
        TMatrix& operator+= (const TMatrix<T> &matr)
        {
			for (size_t i = 0; i < matr.rows(); ++i)
            {
				for (size_t j = 0; j < matr.cols(); ++j)
                     m[i][j] += matr.m[i][j];
            }
			return *this;
        }
        TMatrix operator- (const TMatrix<T> &matr)
        {
              TMatrix<T> help(*this);
              help-=matr;
			  return help;
        }
        TMatrix& operator-= (const TMatrix<T> &matr)
        {
            for (size_t i = 0; i < matr.rows(); ++i)
            {
				for (size_t j = 0; j < matr.cols(); ++j)
                     m[i][j] -= matr.m[i][j];
            }
			return *this;  
		}        
        TMatrix operator* (const TMatrix<T>& matr) const
        {
            
                TMatrix<T> help(*this);
				size_t rowCount = rows(), colCount = cols();
                TMatrix<T> h(rowCount, colCount);
				size_t mulCount = m[0].size();
                //TTimePrinter t; 
				for (size_t i = 0; i < rowCount; ++i)
				 {   
					// t.Reset();
					 for (size_t j = 0; j < colCount; ++j)
                                
						{
							  
							  for (size_t k = 0; k < mulCount; ++k)
                                {
                                        h.m[i][j] += m[i][k] * matr.m[k][j];
                                }
							  
						}
					// cout << t.Print() << ' '<< i << endl ;
				 }
				
                return h;
    }
        TMatrix& operator*= (const TMatrix<T>& matr)
        {
                *this = *this * matr;
			   
				return *this;
        }
        TMatrix& operator*= (int a)
        {
                
			
			    size_t rowCount = rows(), colCount = cols();
                for (size_t i = 0; i <rowCount; ++i)
                        for (size_t j = 0; j < colCount; ++j)
                                m[i][j] *= a;
				return *this;

        }
        TMatrix operator* (int a) const
        {
                
                TMatrix<T> help(*this);
				help *= a;
                return help;

        }

        bool operator == (const TMatrix<T> &a) const
		{
			
			for (size_t i = 0; i < a.rows(); ++i)
				for (size_t j = 0; j < a.cols(); ++j)
					if (m[i][j] != a.m[i][j]) { return false;}
			return true;
		}
        
        void Resize(size_t rowCount, size_t colCount)
        {
                m.resize(rowCount);
                for (size_t i = 0; i < rowCount; ++i)
                        m[i].resize(colCount);
        }
        const T& At(size_t row, size_t col) const
        {
                return m[row][col];
        }
        T& At(size_t row, size_t col)
        {
                return m[row][col];
        }
        
        TMatrix MulShtrass(TMatrix& a, TMatrix& b)
        {
                size_t size = a.rows();
                size_t i = 1;
				for (;size > i; i*=2);
				a.Resize(i,i);
				b.Resize(i,i);
				TMatrix help = _MulShtrass(a,b);
                help.Resize(size,size);
                a.Resize(size,size);
                b.Resize(size,size);
                return help;
        }
        
        size_t rows() const 
        {
                return m.size();
        }
        size_t cols() const
        {
                return m[0].size();
        }
};

template <typename T>
ostream& operator<<(ostream& out, const TMatrix<T>& matr)
{
        size_t rowCount = matr.rows(), colCount = matr.cols(); 
        out << rowCount << ' ' << colCount << endl;
        for (size_t i = 0; i < rowCount; ++i)
        {
                for (size_t j = 0; j < colCount; ++j)
                        out << matr.At(i,j) << ' ';
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
                        cin >> matr.At(i,j);
        return in;
}
template <typename T>
TMatrix<T> operator* (int a, const TMatrix<T>& matr)
{
        return matr*a;
}

TMatrix<int> GenerateMatrix(size_t n)
{
       
        TMatrix<int> help(n, n);
        for (size_t i = 0; i < help.rows(); ++i)
                for (size_t j = 0; j < help.cols(); ++j)
                        help.At(i,j) = rand() % 1000;
        return help;

}
template <typename T>
void InOutTest(TMatrix<T> &matr1,TMatrix<T> &matr2)
{
        cout << "enter two matrix - matr1 and matr2" << endl;
        cin >> matr1 >> matr2;
        cout << "matr1" << endl << matr1 << endl << "matr2" << endl << matr2 << endl;
}


void DoSwap()
{
        TMatrix<int> matr1 = GenerateMatrix(10);
		TMatrix<int> matr2 = GenerateMatrix(10);
		cout << "swap_test is " << endl;
        TMatrix<int> help, matr11, matr21;
        matr11 = matr1; matr21 = matr2;
		help = matr1;
        matr1 = matr2;
        matr2 = help;
        if ((matr1 == matr21)&&(matr2 == matr11)) cout << "success" << endl;
		else cout << "unsuccess" << endl;

}

void DoPlus()
{
        TMatrix<int> matr1 = GenerateMatrix(10);
		TMatrix<int> matr2 = GenerateMatrix(10);
		cout << "{We use + and +=}  plus_test is " << endl;
		TMatrix<int> help = matr1 + matr2;
        TMatrix<int> help1 = matr1;
        help1 += matr2;
		if (help == help1) cout << "success" << endl;
		else cout << "unsuccess" << endl;
        
}

void DoMinus()
{
        TMatrix<int> matr1 = GenerateMatrix(10);
		TMatrix<int> matr2 = GenerateMatrix(10);
		cout << "{We use - and -=}  minus_test is " << endl;
		TMatrix<int> help = matr1 - matr2;
        TMatrix<int> help1 = matr1;
        help1 -= matr2;
		if (help == help1) cout << "success" << endl;
		else cout << "unsuccess" << endl;
}
void DoMul()
{
        TMatrix<int> matr1 = GenerateMatrix(10);
		TMatrix<int> matr2 = GenerateMatrix(10);
		cout << "{We use * and *=}  mul_test is " << endl;
		TMatrix<int> help = matr1 * matr2;
        TMatrix<int> help1 = matr1;
        help1 *= matr2;
		if (help == help1) cout << "success" << endl;
		else cout << "unsuccess" << endl;
}
void DoTranspose()
{
        TMatrix<int> matr1 = GenerateMatrix(3);
		/*matr1.At(0,0) = 1;
		matr1.At(0,1) = 2;
		matr1.At(0,2) = 3;
		matr1.At(1,0) = 4;
		matr1.At(1,1) = 5;
		matr1.At(1,2) = 6;
		matr1.At(2,0) = 7;
		matr1.At(2,1) = 8;
		matr1.At(2,2) = 9;*/
		cout << "transpose_test is " << endl;
		TMatrix<int> help(matr1);
		help.Transpose();
		bool f = true;
		for (size_t i = 0; i < help.rows(); ++i)
			for (size_t j = 0; j < help.cols(); ++j)
				if (matr1.At(i,j) != help.At(j,i)) f = false;
		if (f == true) cout << "success" << endl;
		else cout << "unsuccess" << endl;
}
struct myint
{
        size_t x;
        static int Created;
        static int Deleted;
        myint()
        {
                ++Created;
                x = 0;
        }
        myint(const myint &a)
        {
                ++Created;
                x = a.x;
        }
        ~myint()
        {
                ++Deleted;
        
        }
		myint operator+(myint a)
		{
			myint b;
			b.x = a.x + x ;
			return b;
		}
		myint& operator+=(myint a)
		{
			x += a.x;
			return *this;
		}
};
int myint::Created = 0;
int myint::Deleted = 0;

void CheckMemory()
{
	{
		TMatrix<myint> matr1(10,10);
		for (int i = 0; i < 10; ++i)
			for (int j = 0;  j < 10; ++j)
				matr1.At(i,j).x = rand() % 1000;
        TMatrix<myint> matr2(matr1);
        TMatrix<myint> matr3 = matr1 +matr2;
		cout << "memory_test is " << endl;
	}	
		if (myint::Created == myint::Deleted) cout << "success" << endl;
		else cout << "unsuccess" << endl;
}
//template <typename T>

template <typename T>
void _MulTime(TMatrix<T> &matr1, TMatrix<T> &matr2)
{
        TMatrix<T> help1(matr1.rows(), matr1.cols());
        TTimePrinter t;
        help1 = matr1* matr2;
		cout << "time of matr1* matr2 = " << t.Print() << " sec" << endl;
        TMatrix<T> help2(matr1.rows(), matr1.cols());
		t.Reset();
        help2 = help2.MulShtrass(matr1, matr2);
		cout << "time of MulShtrass(matr1, matr2) = " << t.Print() << " sec" << endl;
        //Check
        for (size_t i = 0; i < help1.rows(); ++i)
                for (size_t j = 0; j < help1.cols(); ++j)
                        if (help1.At(i,j) != help2.At(i,j))
                                {
                                        cout << "false" << endl;
                                        exit(1);
                                };
        cout << "true" << endl;
}
void MulTime()
{
		
		for (int i = 0, j = 32; i < 8; ++i, j*=2)
		{
			//int j = 1024;
			TMatrix<int> matr1 = GenerateMatrix(j);
			TMatrix<int> matr2 = GenerateMatrix(j);
			cout << "N = " << j << endl;
			_MulTime(matr1,matr2);
		}
}
int main()
{
        srand((unsigned int)time(NULL));

		
		

		
		//tests
        //InOutTest(matr1, matr2);
        DoSwap();
        DoPlus();
        DoMinus();
        DoMul();
		DoTranspose();
        CheckMemory();
        //MulTime();

		system("pause");
        return 0;
}
