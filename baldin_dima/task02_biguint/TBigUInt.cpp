
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
const unsigned int radix = 256;
typedef unsigned long long  ulong;
typedef unsigned char uchar;
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
class TBigUInt
{
public: vector <uchar> buf;
public:
    TBigUInt()
    {
        buf.push_back(0);
    }
    TBigUInt(const TBigUInt& a)
    {
        buf = a.buf;
    }
    TBigUInt(ulong a)
    {
        for(;a != 0;a/=radix)
            buf.push_back((a%radix));
    }
    TBigUInt(unsigned int a)
    {
        TBigUInt b((ulong )a);
        *this = b;
    }
    explicit TBigUInt(const char* str)
    {
        string s;
        s = str;
        TBigUInt b(s);
        *this = b;
    }
    explicit TBigUInt(const string& str)
    {
        if (str.size() < 0)
        {
            ulong a = 0;
            for (unsigned int i = 0; i < str.size();
            a =a*10 + (str[i] - '0'), ++i);
            TBigUInt aa(a);
            *this = aa;
        }
        else
        {
            vector<unsigned int> help;

			for (unsigned int i = str.size() - 1; i > 0; --i)
            {
                help.push_back(str[i] - '0');
            }
			help.push_back(str[0] - '0');

			vector<unsigned int> m; bool f = true;
			for (;  f  ; )
			{
			//f = false;
				unsigned  int n = 0;
			for (unsigned int i = help.size() - 1; i > 0; --i)
            {
                n = n*10 + help[i];
                if (n >= radix)
                {
                    m.push_back(n / radix);
                    n = n % radix ;
                }
				else if (n == 0) m.push_back(n);
            }
            n = n*10 +help[0];
            if (n >= radix)
            {
				m.push_back(n / radix);
                n = (n % radix) ;
            }
			else if (n == 0) m.push_back(n);
			buf.push_back(n);
			help.clear();
			if (!m.empty())
			{
				for (unsigned int i = m.size()-1; i>0;--i)
								help.push_back(m[i]);
				help.push_back(m[0]);
				m.clear();
			}
			else f = false;
			}
        }
    }
	TBigUInt (const TBigUInt a, unsigned int x, unsigned int y)
	{
	    if (x >= a.buf.size()) buf.push_back(0);
	    else
        {
            if (y > a.buf.size()) y = a.buf.size();
            for (unsigned int i = x; i < y; ++i)
                buf.push_back(a.buf[i]);
        }
	}
	bool operator>(TBigUInt& a)
	{
		for (;a.buf[a.buf.size()-1]==0 && (a.buf.size()>1); a.buf.pop_back());
		for(;(buf[buf.size()-1] == 0) && (buf.size()>1);buf.pop_back());
		if (buf.size() > a.buf.size()) return true;
		else if (buf.size() < a.buf.size()) return false;
		else
		{
			for (int i = buf.size() - 1; i >= 0; --i)
				if (buf[i] > a.buf[i])
					return true;
				else if (buf[i] < a.buf[i])
					return false;
			return false;
		}

	}
	bool operator>=(TBigUInt& a)
	{
		return ((*this > a)||( *this == a));
	}
	bool operator<(TBigUInt& a)
	{
		return a>*this;
	}
	TBigUInt& operator = (const TBigUInt& a)
	{
		buf = a.buf;
		return *this;
	}
	TBigUInt operator +( TBigUInt& a)
	{
	    TBigUInt result;
        result.buf.pop_back();
        int per=0;
        const TBigUInt &x = (buf.size()>a.buf.size()) ? *this : a;
        const TBigUInt &y = (buf.size()>a.buf.size()) ?  a : *this;
        for (size_t i=0; i<x.buf.size(); ++i)
		{
			int h;
            if (i<y.buf.size()) h = (int)x.buf[i] + (int)y.buf[i];
            else h = (int) x.buf[i];
            if (per != 0) 
            {
				++h;
                per = 0;
			}
			if (h>=radix)
			{
				per=1;
				result.buf.push_back(h-radix);
			}
			else result.buf.push_back(h);
		}
		if (per != 0) result.buf.push_back(1);
        return result;



	}
	
	bool operator==(TBigUInt& a)
	{
		for (;a.buf[a.buf.size()-1]==0 && (a.buf.size()>1); a.buf.pop_back());
		for(;(buf[buf.size()-1] == 0) && (buf.size()>1);buf.pop_back());
		if (buf.size() != a.buf.size()) return false;
		else for (size_t i = 0; i < buf.size(); ++i)
			if (buf[i] != a.buf[i]) return false;
		return true;
		
	}
	TBigUInt operator -(const TBigUInt& b)
	{
		if (buf.size()>=b.buf.size())
		{
			TBigUInt result;
			result.buf.pop_back();
			int per = 0;
			for (size_t i=0; i<buf.size(); ++i)
			{
				int help;
				if (i<b.buf.size()) help = (int)buf[i] - (int)b.buf[i];
				else help = (int) buf[i];
				if (per != 0) 
				{
					--help;
					per = 0;
				}
				if (help<0)
				{
					per=1;
					result.buf.push_back(help + radix);
				}
				else result.buf.push_back(help);
			}
			for (size_t i=result.buf.size()-1; !(result.buf[i]) && i>0; --i) result.buf.pop_back();
			return result;
		}
		TBigUInt result;
		return result;
	    
	}
	TBigUInt operator*(const TBigUInt& a)const
	{
		TBigUInt result;
		for (size_t i = 1; i <= buf.size()+a.buf.size(); i++) result.buf.push_back(0);
		for (size_t i = 0; i < buf.size(); i++) 
		{
			size_t per = 0;
			size_t j;   
			for (j = 0; j < a.buf.size(); j++) 
			{
				size_t help = buf[i] * a.buf[j] + result.buf[i+j] + per;
				per = help/radix;
				result.buf[i+j] = help - per*radix;
			}
			result.buf[i+j] = per;
		}
		for (int i=result.buf.size()-1; !(result.buf[i]) && i>0; --i)
			result.buf.pop_back();
		return result;
	}
	TBigUInt operator/(TBigUInt& a)
	{
		TBigUInt result, help;
		TBigUInt _radix(radix);
		if (a.buf.size()>buf.size() || (a.buf.size()==buf.size() && a.buf[buf.size()-1]>buf[buf.size()-1]))
		{
			return result;
			
		}
		if (*this == a)
		{
			++result;
			return result;
		}
		for (size_t i=0; i<buf.size(); ++i)
		{
			TBigUInt _buf((ulong)buf[buf.size()-i-1]);
			help = (help*_radix + _buf);
			result *= _radix;
			if (help < a)
				continue;
			while (help >= a)
			{
				help -= a;
				++result;
			}
		}
		return result;
	}
	void operator++()
	{
	    TBigUInt one;
	    one.buf[0] = 1;
	    *this = *this + one;
	}
	void operator++(int)
	{
	    ++*this;
	}
	void operator--()
	{
	    TBigUInt one;
	    one.buf[0] = 1;
	    *this = *this - one;
	}
	void operator--(int)
	{
	    --*this;
	}
	void operator += (TBigUInt a)
	{
	    *this = (*this + a);
    }
    void operator -=(TBigUInt a)
	{
	    *this = (*this - a);
	}
	void operator *=(TBigUInt a)
	{
        *this = (*this * a);
	}
	void operator /=(TBigUInt a)
	{
	    *this = (*this/a);
	}
    unsigned char operator%(unsigned char a)
    {
		TBigUInt help1, help2; help1.buf.clear(); help2.buf.clear();
        help1.buf.push_back(a);
        help2 = *this/help1;
        help1 = help2*help1;
        help1 = *this - help1;
        return help1.buf[0];
    }
    void power_radix(unsigned int p)
    {
        buf.insert(buf.begin(), p, 0);
    }
	friend TBigUInt KarMul(const TBigUInt& a, const TBigUInt& b);

};
TBigUInt KarMul(const TBigUInt& a, const TBigUInt& b)
{
    size_t maxDigits = max(a.buf.size(), b.buf.size());
	if (maxDigits <= 64) 
		return a*b;
	size_t n = maxDigits / 2;
	TBigUInt a1(a, 0, n);
	TBigUInt a2(a, n, maxDigits); 
	TBigUInt b1(b, 0, n);
	TBigUInt b2(b, n, maxDigits);
	TBigUInt z2 = KarMul(a2, b2);
	TBigUInt z0 = KarMul(a1, b1);
	TBigUInt z1 = KarMul(a1 + a2, b1 + b2) - z2 - z0;
	z2.buf.insert(z2.buf.begin(), 2 * n, 0);
	z1.buf.insert(z1.buf.begin(), n, 0);
	return z2 + z1 + z0;
}
ostream& operator << (ostream& out, const TBigUInt& b)
{
    unsigned int d = 10;
    vector<uchar> toprint;
    TBigUInt a(d);
    TBigUInt help;
    help = b;
    TBigUInt help1;
    uchar c;
    for (;help > help1;)
    {
        c = help%d;
        toprint.push_back(c);
        help/=a;
    }
	for (int i = toprint.size() - 1; i >= 0; --i)
		out << (int)toprint[i];
    return out;
}
istream& operator>> (istream& in, TBigUInt& a)
{
    string str;
    getline(in, str );
    TBigUInt help(str);
    a = help;
    return in;
}
void print (TBigUInt a)
{
	for (unsigned int i = 0; i < a.buf.size(); ++i)
		cout << (int)a.buf[i] << ' ';
	cout << endl;
}
int main()
{
    TBigUInt a("1234");
	TBigUInt b("56789");
	cout << b - a << endl;
	cout << b + a << endl;
	cout << a * b << endl;
	cout << b / a << endl;

	srand((unsigned int)time(NULL));
    string s1, s2;
    TBigUInt res1, res2;
    size_t n = 10;
    TTimePrinter timer;bool f = true;
    for (int k=0; k < 7; k++)
    {
		cout <<"n = 10^" << k+1 << endl;
		timer.Reset();
		s1.clear(); s2.clear();
		s1.push_back(rand() % 9 + (int)'1');
		s2.push_back(rand() % 9 + (int)'1');
		for (size_t i=0; i<n-1; ++i)
        {
             s1.push_back(rand() % 10 + (int)'0');
             s2.push_back(rand() % 10 + (int)'0');
        }
		
		//cout << "s1 = " << s1 << endl;
		//cout << "s2 = " << s2 << endl;
        TBigUInt x(s1), y(s2);
        double time = timer.GetTime();
        cout << "Generation time: " << time<<endl;
        timer.Reset();
        res1 = KarMul(x, y);
        time = timer.GetTime();
        cout << "N = " << n << endl;
        cout << "Karatsuba: " << time <<endl;
        timer.Reset();
        res2 = x * y;
        time = timer.GetTime();
        cout << "Usual "<< time <<endl;
		if (!(res1 == res2)) {cout << "false" << endl; f= false;}
		else cout << "true" << endl;
        n*=10;
    }   
//	print(c);
	return 0;
}
