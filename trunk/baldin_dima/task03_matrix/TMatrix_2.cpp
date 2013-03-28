#include <vector>
#include <math.h>
#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <time.h>

using namespace std;

template <typename T>
class TMatrix
{
        
        
        
private:
        vector<vector<T>> m;
                
    void Separate (TMatrix &matr,TMatrix &a,TMatrix &b,TMatrix &c,TMatrix &d)
        {
                size_t size = matr.rows()/2;
                for (size_t i = 0; i < size; ++i)
                        for (size_t j = 0; j < size; ++j)
                        {
                                a.m[i][j] = matr.m[i][j];
                                b.m[i][j] = matr.m[i][size + j];
                                c.m[i][j] = matr.m[size + i][j];
                                d.m[i][j] = matr.m[size + i][size +j];
                        }
        }
        TMatrix Merge (TMatrix &R, TMatrix &S, TMatrix &L, TMatrix &U, bool flag)
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
                //if (flag)
                        //help.Resize( bigsize - 1, bigsize - 1);
                
                //cout << R.rows() << endl;
                return help;
        }
        TMatrix _MulShtrass (TMatrix& a, TMatrix& b)
        {
                //to return
                if (a.m.size() <= 32)
                {
                        TMatrix<T> help;
                        help = a*b;
                        return help;
                }
                else
                {
                        size_t size = a.rows();
                        bool flag = false;
                        if (size%2 != 0)
                        {
                                a.Resize(size+1,size+1);
                                b.Resize(size+1, size+1);
                                flag = true;
                                a.m[size][size] = 1;
                                b.m[size][size] = 1;
                                size += size%2;
                        }
                        size_t s = size / 2;
						TMatrix A(s, s);
                        TMatrix B(s, s);
                        TMatrix C(s, s);
                        TMatrix D(s, s);
                        Separate(a,A,B,C,D);
                        TMatrix E(s, s);
                        TMatrix F(s, s);
                        TMatrix G(s, s);
                        TMatrix H(s, s);
                        Separate(b,E,G,F,H);
                        TMatrix P1,P2,P3,P4,P5,P6,P7;
                        P1 = MulShtrass(A, G - H);
                        P2 = MulShtrass(A + B, H);
                        P3 = MulShtrass(C + D, E);
                        P4 = MulShtrass(D, F - E);
                        P5 = MulShtrass(A + D, E + H);
                        P6 = MulShtrass(B - D, F + H);
                        P7 = MulShtrass(A - C, E + G);
                        /*if (flag)
                        {
                                size_t s = size - 1;
                                P1.Resize(s,s);
                                P2.Resize(s,s);
                                P3.Resize(s,s);
                                P4.Resize(s,s);
                                P5.Resize(s,s);
                                P6.Resize(s,s);
                                P7.Resize(s,s);
                        }*/
                        TMatrix R,S,L,U;
                        R = P5 + P4 - P2 + P6;
                        S = P1 + P2;
                        L = P3 + P4;
                        U = P5 + P1 - P3 - P7;
                        //Merge(R,S,L,U,flag);

                        return Merge(R,S,L,U,flag);
                }
        }
public:
        TMatrix()
        {}
        TMatrix(const TMatrix<T>& matr)
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
                for (size_t i = 0; i < help.rows(); ++i)
            {
                   for (size_t j = 0; j < help.cols(); ++j)
                          help.m[i][j] = help.m[i][j] + matr.m[i][j];
                }
        return help;
        }
        TMatrix& operator+= (const TMatrix<T> &matr)
        {
                
                *this = *this + matr;
                return *this;
        }
        TMatrix operator- (const TMatrix<T> &matr)
        {
                size_t rowCount = rows(), colCount = cols();
                TMatrix<T> help(*this);
                for (size_t i = 0; i < rowCount; ++i)
            {
                   for (size_t j = 0; j < colCount; ++j)
                          help.m[i][j] = help.m[i][j] - matr.m[i][j];
                }
        return help;
        }
        TMatrix& operator-= (const TMatrix<T> &matr)
        {
                
                *this = *this - matr;
        return *this;
        }
        TMatrix operator* (const TMatrix<T>& matr)
        {
            
                size_t rowCount = rows(), colCount = cols(),
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
        TMatrix& operator*= (const TMatrix<T>& matr)
        {
                *this = *this * matr;
                return *this;
    }
        TMatrix& operator*= (int a)
        {
                *this = *this * a;
                return *this;

        }
        TMatrix operator* (int a) const
        {
                
                size_t rowCount = rows(), colCount = cols();
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

template <typename T>
void InOutTest(TMatrix<T> &matr1,TMatrix<T> &matr2)
{
        cout << "enter two matrix - matr1 and matr2" << endl;
        cin >> matr1 >> matr2;
        cout << "matr1" << endl << matr1 << endl << "matr2" << endl << matr2 << endl;
}

template <typename T>
void DoSwap(TMatrix<T> &matr1,TMatrix<T> &matr2)
{
        cout << "enter two matrix - matr1 and matr2" << endl;
        cin >> matr1 >> matr2;
        cout << "swap" << endl;
        TMatrix<T> help;
        help = matr1;
        matr1 = matr2;
        matr2 = help;
        cout << "matr1" << endl << matr1 << endl << "matr2" << endl << matr2 << endl;

}
template <typename T>
void DoPlus(TMatrix<T> &matr1, TMatrix<T> &matr2)
{
        cout << "enter two matrix - matr1 and matr2" << endl;
        cin >> matr1 >> matr2;
        cout << "plus +" << endl;
        TMatrix<T> help = matr1 + matr2;
        cout << "result of +" << endl;
        cout << help << endl;
        cout << "plus +=" << endl;
        help = matr1;
        help += matr2;
        cout << help << endl;
}
template <typename T>
void DoMinus(TMatrix<T> &matr1, TMatrix<T> &matr2)
{
        cout << "enter two matrix - matr1 and matr2" << endl;
        cin >> matr1 >> matr2;
        cout << "minus -" << endl;
        TMatrix<T> help = matr1 - matr2;
        cout << "result of -" << endl;
        cout << help << endl;
        cout << "minus -=" << endl;
        help = matr1;
        help -= matr2;
        cout << help << endl;
}
template <typename T>
void DoTranspose(TMatrix<T> &matr1)
{
        cout << "enter matrix" << endl;
        cin >> matr1;
        cout << "transposed matrix" << endl;
        matr1.Transpose();
        cout << matr1;
}
template <typename T>
void DoMul(TMatrix<T> &matr1, TMatrix<T> &matr2)
{
        
        //freopen("input.txt", "r", stdin);
        cout << "enter 2 matrix - matr1 and matr2, correct to mul" << endl;
        cin >> matr1 >> matr2;
        cout << " 3 * matr1" << endl << 3*matr1 << endl;
        cout << " matr2 * 5 " << endl << matr2*5 << endl;
        cout << " matr1 * matr2 " << endl << matr1*matr2 << endl;
        cout << " matr1 * matr2 Shtrass " << endl << matr1.MulShtrass(matr1,matr2);
        matr1 *= matr2;
        cout << " matr1*=matr2 " << endl << matr1 << endl;
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
};
int myint::Created = 0;
int myint::Deleted = 0;

void CheckMemory()
{
        TMatrix<myint> matr1(2,2);
        TMatrix<myint> matr2(matr1);
        TMatrix<myint> matr3(10, 10);
        matr2 = matr1;
    matr1 = matr2;
}
//template <typename T>
TMatrix<int> GenerateMatrix(size_t n)
{
        srand(time(NULL));
        TMatrix<int> help(n, n);
        for (size_t i = 0; i < help.rows(); ++i)
                for (size_t j = 0; j < help.cols(); ++j)
                        help.At(i,j) = rand()%1000000000;
        return help;

}
template <typename T>
void MulTime(TMatrix<T> &matr1, TMatrix<T> &matr2)
{
        TMatrix<T> help1(matr1.rows(), matr1.cols());
        size_t t = clock();
        help1 = matr1* matr2;
        size_t t1 = clock();
        cout << "time of matr1* matr2 = " << (((t1-t)*1000)/CLOCKS_PER_SEC) << " ms" << endl;
        TMatrix<T> help2(matr1.rows(), matr1.cols());
        t = clock();
        help2 = help2.MulShtrass(matr1, matr2);
        t1 = clock();
        cout << "time of MulShtrass(matr1, matr2) = " << (((t1-t)*1000)/CLOCKS_PER_SEC) << " ms" << endl;
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
int main()
{
        TMatrix<int> matr1;
        TMatrix<int> matr2;
        //tests
        //InOutTest(matr1, matr2);
        //DoSwap(matr1, matr2);
        //DoPlus(matr1, matr2);
        //DoMinus(matr1, matr2);
        //DoTranspose(matr1);
        //DoMul(matr1,matr2); 
        //CheckMemory();
        //cout << myint::Created <<endl << myint::Deleted << endl;
        //size_t n = 101;
        //TMatrix<int> help = GenerateMatrix(n);
        //MulTime(help, help);

		system("pause");
        return 0;
}