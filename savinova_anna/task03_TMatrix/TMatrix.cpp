#include <time.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class TMatrix
{
        vector<vector<T> > Buf;
        void StrasSum(size_t rs, size_t cs, const TMatrix<T>& src, size_t r, size_t c, size_t n)
        {
                for (size_t i = 0; i < n; ++i)
                        for (size_t j = 0; j < n; ++j)
                                At(r + i, c + j) = At(r + i, c + j) + src.At(rs + i, cs + j);
        }
        void StrasSub(size_t rs, size_t cs, const TMatrix<T>& src, size_t r, size_t c, size_t n)
        {
                for (size_t i = 0; i < n; ++i)
                        for (size_t j = 0; j < n; ++j)
                                At(r + i, c + j) = At(r + i, c + j) - src.At(rs + i, cs + j);                        
        }
public:
        const size_t Row() const
        {
                return Buf.size();
        }
        const size_t Col() const
        {
                if (Row())
                        return Buf[0].size();
                else return 0;
        }
        TMatrix()
        {
        }
        TMatrix(const TMatrix & m)
        {
                Resize(m.Row(), m.Col());
                for (size_t i = 0; i < m.Row(); ++i)
                        for (size_t j = 0; j < m.Col(); ++ j)
                                Buf[i][j] = m.At(i,j);
        }
        TMatrix(size_t rowCount, size_t colCount)
        {
                Buf.resize(rowCount);
                for (size_t i = 0; i < rowCount; ++i)
                        Buf[i].resize(colCount);
        }
        TMatrix<T> operator = (const TMatrix<T>& m)
        {
                Resize(m.Row(), m.Col());
                for (size_t i = 0; i < m.Row(); ++i)
                        for (size_t j = 0; j < m.Col(); ++ j)
                                Buf[i][j] = m.At(i,j);
                return *this;
        }
        TMatrix<T> operator + (const TMatrix<T>& m)
        {
                TMatrix<T> res(*this);                
                for (size_t i = 0; i < res.Row(); ++i)
                        for (size_t j = 0; j < res.Col(); ++j)
                                res.At(i, j) += m.At(i, j);
                return res;
        }
        TMatrix<T> operator - (const TMatrix<T>& m)
        {
                TMatrix<T> res(*this);                
                for (size_t i = 0; i < res.Row(); ++i)
                        for (size_t j = 0; j < res.Col(); ++j)
                                res.At(i, j) -= m.At(i, j);
                return res;
        }
        TMatrix<T> operator * (const T val)
        {
                TMatrix<T> res(*this);                
                for (size_t i = 0; i < res.Row(); ++i)
                        for (size_t j = 0; j < res.Col(); ++j)
                                res.At(i, j) *= val;
                return res;
        }
        TMatrix<T> operator * (const TMatrix<T>& m)
        {
                TMatrix<T> res(Row(), m.Col());
                for (size_t i = 0; i < res.Row(); ++i)
                        for (size_t j = 0; j < res.Col(); ++j)
                        {
                                res.At(i, j) = 0;
                                for (size_t k = 0; k < Col(); ++k)
                                        res.At(i, j) += At(i, k) * m.At(k, j);
                        }
                return res;
        }
        TMatrix<T>& operator += (const TMatrix<T>& m)
        {
                *this = *this + m;
                return *this;
        }
        TMatrix<T>& operator -= (const TMatrix<T>& m)
        {
                *this = *this - m;
                return *this;
        }
        TMatrix<T>& operator *= (const T val)
        {
                *this = *this * val;
                return *this;
        }
        TMatrix<T>& operator *= (const TMatrix<T>& m)
        {
                *this = *this * m;
                return *this;
        }
        void Resize(size_t rowCount, size_t colCount)
        {
                Buf.resize(rowCount);
                for (size_t i = 0; i < rowCount; ++i)
                        Buf[i].resize(colCount);
        }
        const T& At(size_t row, size_t col) const
        {
                return Buf[row][col];
        }
        T& At(size_t row, size_t col)
        {
                return Buf[row][col];
        }
        void Transpose()
        {
                TMatrix<T> res(Col(), Row());
                for (size_t i = 0; i < Row(); ++i)
                        for (size_t j = 0; j < Col(); ++j)
                                res.At(j, i) = At(i, j);
                *this = res;
        }
        void Clean()
        {
                for (size_t i = 0; i < Row(); ++i)
                        for (size_t j = 0; j < Col(); ++j)
                                Buf[i][j] = 0;
        }
        TMatrix<T> ShtrassenMultiply(const TMatrix<T>& m)
        {
                if (m.Row() < 32)
                        return (*this) * m;
                TMatrix<T> res(m.Row(), m.Col());
                size_t sz = m.Row() / 2;
                TMatrix<T> tmp1(sz, sz);
                TMatrix<T> tmp2(sz, sz);
                res.Clean();
                //P1
                tmp1.Clean();
                tmp2.Clean();
                tmp1.StrasSum(0, 0, *this, 0, 0, sz);
                tmp1.StrasSum(sz, sz, *this, 0, 0, sz);
                tmp2.StrasSum(0, 0, m, 0, 0, sz);
                tmp2.StrasSum(sz, sz, m, 0, 0, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), 0, 0, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), sz, sz, sz);
                //P2
                tmp1.Clean();
                tmp2.Clean();
                tmp1.StrasSum(sz, 0, *this, 0, 0, sz);
                tmp1.StrasSum(sz, sz, *this, 0, 0, sz);
                tmp2.StrasSum(0, 0, m, 0, 0, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), sz, 0, sz);
                res.StrasSub(0, 0, tmp1.ShtrassenMultiply(tmp2), sz, sz, sz);
                //P3
                tmp1.Clean();
                tmp2.Clean();
                tmp1.StrasSum(0, 0, *this, 0, 0, sz);
                tmp2.StrasSum(0, sz, m, 0, 0, sz);
                tmp2.StrasSub(sz, sz, m, 0, 0, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), 0, sz, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), sz, sz, sz);
                //P4
                tmp1.Clean();
                tmp2.Clean();
                tmp1.StrasSum(sz, sz, *this, 0, 0, sz);
                tmp2.StrasSum(sz, 0, m, 0, 0, sz);
                tmp2.StrasSub(0, 0, m, 0, 0, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), 0, 0, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), sz, 0, sz);
                //P5
                tmp1.Clean();
                tmp2.Clean();
                tmp1.StrasSum(0, 0, *this, 0, 0, sz);
                tmp1.StrasSum(0, sz, *this, 0, 0, sz);
                tmp2.StrasSum(sz, sz, m, 0, 0, sz);
                res.StrasSub(0, 0, tmp1.ShtrassenMultiply(tmp2), 0, 0, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), 0, sz, sz);
                //P6
                tmp1.Clean();
                tmp2.Clean();
                tmp1.StrasSum(sz, 0, *this, 0, 0, sz);
                tmp1.StrasSub(0, 0, *this, 0, 0, sz);
                tmp2.StrasSum(0, 0, m, 0, 0, sz);
                tmp2.StrasSum(0, sz, m, 0, 0, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), sz, sz, sz);
                //P7
                tmp1.Clean();
                tmp2.Clean();
                tmp1.StrasSum(0, sz, *this, 0, 0, sz);
                tmp1.StrasSub(sz, sz, *this, 0, 0, sz);
                tmp2.StrasSum(sz, 0, m, 0, 0, sz);
                tmp2.StrasSum(sz, sz, m, 0, 0, sz);
                res.StrasSum(0, 0, tmp1.ShtrassenMultiply(tmp2), 0, 0, sz);
                return res;
                
        }
};

template <typename T>
ostream& operator << (ostream& out, const TMatrix<T>& m)
{
        out << "Row: " << m.Row() << " Col: " << m.Col() << endl;
        for (size_t i = 0; i < m.Row(); ++i)
        {
                for (size_t j = 0; j < m.Col(); ++j)
                        out << m.At(i,j) << ' ';
                out << endl;
        }
        return out;
}

template <typename T>
istream& operator >> (istream& in, TMatrix<T>& m) 
{
        size_t rowCount, colCount;
        cin >> rowCount >> colCount;
        m.Resize(rowCount, colCount);
        for (size_t i = 0; i < rowCount; ++i)
                for (size_t j = 0; j < colCount; ++j)
                        cin >> m.At(i,j);
        return in;
}

template <typename T>
bool Check(TMatrix<T>& a, TMatrix<T>& b)
{
        bool tmp = true;
        for (size_t i = 0; i < a.Row(); ++i)
                for (size_t j = 0; j < a.Col(); ++j)
                {
                        if (a.At(i,j) != b.At(i,j))
                                tmp = false;
                }
        return tmp;
}
int main()
{
        /*cout << "Creating Matrix M1" << endl;
        TMatrix<int> M1;
        cout << "M1:" << endl << M1;
        cout << "Creating Matrix M2(5, 5)" << endl;
        TMatrix<int> M2(5, 5);
        cout << "M2:" << endl << M2;
        cout << "Filling M2..." << endl;
        int k = 0;
        for (size_t i = 0; i < M2.Row(); ++i)
                for (size_t j = 0; j < M2.Col(); ++j, ++k)
                        M2.At(i,j) = k;
        cout << "M2:" << endl << M2;
        cout << "Creating Matrix M3(M2)" << endl;
        TMatrix<int> M3(M2);
        cout << "M3:" << endl << M3;
        cout << "M2.At(3, 2) = 4" << endl;
        M2.At(3, 2) = 4;
        cout << "M2:" << endl << M2;
        cout << "M3 = M2" << endl;
        M3 = M2;
        cout << "M3:" << endl << M3;
        cout << "M3 = M2 + M3" << endl;
        M3 = M2 + M3;        
        cout << "M3:" << endl << M3;
        cout << "Creating Matrix M4(5, 5)" << endl << "Filling M4..." << endl;
        TMatrix<int> M4(5, 5);
        for (size_t i = 0; i < M4.Row(); ++ i)
                for (size_t j = 0; j < M4.Col(); ++j)
                        M4.At(i, j) = 1;
        cout << "M4:" << endl << M4;
        cout << "M2 = M3 - M4" << endl;
        M2 = M3 - M4;
        cout << "M2:" << endl << M2;
        cout << "M4.At(1, 3) = 2" << endl;
        M4.At(1, 3) = 2;
        cout << "M4:" << endl << M4;
        cout << "M3 = M4 * 3" << endl;
        M3 = M4 * 3;
        cout << "M3:" << endl << M3;
        cout << "M3 = M2 * M4" << endl;
        M3 = M2 * M4;
        cout << "M3:" << endl << M3;
        cout << "M2 += M4" << endl;
        M2 += M4;
        cout << "M2:" << endl << M2;
        cout << "M3 -= M4" << endl;
        M3 -= M4;
        cout << "M3:" << endl << M3;
        cout << "M2 *= -1" << endl;
        M2 *= -1;
        cout << "M2:" << endl << M2;        
        cout << "Resize M1(1, 5)" << endl;
        M1.Resize(1, 5);
        cout << "Filling M1..." << endl;
        for (size_t i = 0; i < M1.Col(); ++i)
                M1.At(0, i) = i;
        cout << "M1:" << endl << M1;
        cout << "M1 *= M2" << endl;
        M1 *= M2;
        cout << "M1:" << endl << M1;
        cout << "Creating M5(3, 5)" << endl;
        TMatrix<int> M5(3, 5);
        cout << "Filling M5..." << endl;
        k = 1;
        for (size_t i = 0; i < M5.Row(); ++i)
                for (size_t j = 0; j < M5.Col(); ++j, ++k)
                        M5.At(i, j) = k;
        cout << "M5:" << endl << M5;
        cout << "M5.Transpose()" << endl;
        M5.Transpose();
        cout << "M5:" << endl << M5;
        cout << "Test >> M5:" << endl;
        cin >> M5;
        cout << "M5:" << endl << M5;
        TMatrix<int> M6;
        cin >> M6;
        cout << "M6:" << endl << M6;
        cout << "M5 * M6" << endl << M5.ShtrassenMultiply(M6);*/
        size_t N = 0;
        cin >> N;
        srand(time(NULL));
        TMatrix<long long> A(N, N);
        for (size_t i = 0; i < A.Row(); ++i)
                for (size_t j = 0; j < A.Col(); ++j)
                        A.At(i, j) = rand() % 10 - rand() % 10;
        TMatrix<long long> B(N, N);
        for (size_t i = 0; i < B.Row(); ++i)
                for (size_t j = 0; j < B.Col(); ++j)
                        B.At(i, j) = rand() % 10 - rand() % 10;
        TMatrix<long long> res1(N, N);
        TMatrix<long long> res2(N, N);
        time_t timer1, timer2;
        cout << "Start Mult" << endl;
        time(&timer1);
        res2 = A * B;
        time(&timer2);
        cout << "Finish Mult" << endl;
        cout << "Mult time: " << (timer2 - timer1) << endl;
        cout << "Start Shtrassen" << endl;
        time(&timer1);
        res1 = A.ShtrassenMultiply(B);
        time(&timer2);
        bool tmp = Check(res1, res2);
        cout << "Finish Shtrassen, check: " << tmp << endl;
        cout << "Shtrassen time: " << (timer2 - timer1) << endl << endl;
        return 0;
}
