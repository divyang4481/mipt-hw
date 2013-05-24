#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>
#include <string>
#include <stdlib.h>
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
	vector <unsigned char> Digits;
	static const int BASE = 256;
	static const int BASE_DIGITS = 3;
	friend ostream& operator<< (ostream& out, const TBigUInt &a);
	friend istream& operator>> (istream& in, TBigUInt &a);
	friend TBigUInt KaratsubaMultiply(const TBigUInt& a, const TBigUInt& b);
	TBigUInt (const TBigUInt &other, size_t from, size_t to)
	{
		if (from>=other.Digits.size())
			Digits.push_back(0);
		else
			if (to<=other.Digits.size())
				for (size_t i=from; i<to; ++i)
					Digits.push_back(other.Digits[i]);
			else 
				for (size_t i=from; i<other.Digits.size(); ++i)
					Digits.push_back(other.Digits[i]);
	}
public:
	TBigUInt()
	{
		Digits.push_back(0);
	}
	TBigUInt(const TBigUInt& a)
	{
		*this = a;
	}
	TBigUInt(unsigned long long n)
	{
		while (n)
		{
			Digits.push_back(n%BASE);
			n/=BASE;
		}
	}
	explicit TBigUInt(const char* str)
	{
		string st;
		char c=str[0];
		for (int i=1; c!='\0'; ++i)
		{
			st.push_back(c);
			c=str[i];
		}
		TBigUInt temp(st);
		*this=temp;		
	}
	explicit TBigUInt(const std::string& str)
	{
		Digits.reserve(str.size());
		size_t decbase = 10;
		for (size_t i=0; i<str.size(); ++i)
			*this = ((*this)*decbase + ((int)str[i]-(int)'0'));
	}

	TBigUInt& operator= (const TBigUInt &a)
	{
		Digits = a.Digits;
		return *this;
	}
	TBigUInt operator+ (const TBigUInt &other) const
	{
		TBigUInt result;
		result.Digits.pop_back();
		int carry=false;
		const TBigUInt &a = (Digits.size()>other.Digits.size()) ? *this : other;
		const TBigUInt &b = (Digits.size()>other.Digits.size()) ? other : *this;
		for (size_t i=0; i<a.Digits.size(); ++i)
		{
			int tp;
			if (i<b.Digits.size()) tp = (int)a.Digits[i] + (int)b.Digits[i];
			else tp = (int) a.Digits[i];
			if (carry) 
			{
				++tp;
				carry=false;
			}
			if (tp>=BASE)
			{
				carry=true;
				result.Digits.push_back(tp-BASE);
			}
			else result.Digits.push_back(tp);
		}
		if (carry) result.Digits.push_back(1);
		return result;
	}
	void operator+= (const TBigUInt &other)
	{
		*this = *this + other;
	}
	void operator-= (const TBigUInt &other)
	{
		*this = *this - other;
	}
	void operator*= (const TBigUInt &other)
	{
		*this = *this * other;
	}
	TBigUInt operator- (const TBigUInt &other) const
	{
		if (Digits.size()>=other.Digits.size())
		{
			TBigUInt result;
			result.Digits.pop_back();
			int carry=false;
			for (size_t i=0; i<Digits.size(); ++i)
			{
				int tp;
				if (i<other.Digits.size()) tp = (int)Digits[i] - (int)other.Digits[i];
				else tp = (int) Digits[i];
				if (carry) 
				{
					--tp;
					carry=false;
				}
				if (tp<0)
				{
					carry=true;
					result.Digits.push_back(tp+BASE);
				}
				else result.Digits.push_back(tp);
			}
			for (size_t i=result.Digits.size()-1; !(result.Digits[i]) && i>0; --i) result.Digits.pop_back();
			return result;
		}
		TBigUInt result;
		return result;
	}
	TBigUInt operator* (const TBigUInt &other) const
	{
		TBigUInt result;
		for (size_t i = 1; i <= Digits.size()+other.Digits.size(); i++) result.Digits.push_back(0);
		for (size_t i = 0; i < Digits.size(); i++) 
		{
			size_t carry = 0;
			size_t j;
			for (j = 0; j < other.Digits.size(); j++) 
			{
				size_t temp = Digits[i] * other.Digits[j] + result.Digits[i+j] + carry;
				carry = temp/BASE;
				result.Digits[i+j] = temp - carry*BASE;
			}
			result.Digits[i+j] = carry;
		}
		for (int i=result.Digits.size()-1; !(result.Digits[i]) && i>0; --i)
			result.Digits.pop_back();
		return result;
	}
	void operator/= (const TBigUInt &a) 
	{
		TBigUInt res, t;
		if (a.Digits.size()>Digits.size() || 
			(a.Digits.size()==Digits.size() && a.Digits[Digits.size()-1]>Digits[Digits.size()-1]))
			{
				*this = res;
				return;
			}
		if (*this == a)
		{
			*this = 1;
			return;
		}
		for (size_t i=0; i<Digits.size(); ++i)
		{
			t = (t*BASE + Digits[Digits.size()-i-1]);
			res *= BASE;
			if (t<a)
				continue;
			while (t>=a)
			{
				t -= a;
				++res;
			}
		}
		*this = res;
	}
	TBigUInt operator/ (const TBigUInt &a) const
	{
		TBigUInt t(*this);
		t/=a;
		return t;
	}
	TBigUInt operator% (const TBigUInt &a) const
	{
		return (*this)-((*this)/a)*a;
	}
	void operator%= (const TBigUInt &a)
	{
		(*this)-=((*this)/a)*a;
	}
	unsigned char operator% (unsigned char c)
	{
		TBigUInt tp(c);
		TBigUInt tp1;
		tp1 = *this / tp;
		tp = *this - (tp1*tp);
		return tp.Digits[0];
	}
	TBigUInt& operator++ ()
	{
		TBigUInt i(1);
		*this=*this+i;
		return *this;
	}
	TBigUInt operator++ (int)
	{
		TBigUInt i(*this);
		++*this;
		return i;
	}
	TBigUInt& operator-- ()
	{
		TBigUInt i(1);
		*this=*this-i;
		return *this;
	}
	TBigUInt operator-- (int)
	{
		TBigUInt i(*this);
		--*this;
		return i;
	}
	TBigUInt& operator+= (TBigUInt &other)
	{
		*this = *this + other;
		return *this; 
	}
	bool operator == (TBigUInt a)
	{
		if (Digits.size()!=a.Digits.size())
			return false;
		else
			for (int i=Digits.size()-1; i>=0; --i)
				if (Digits[i]!=a.Digits[i])
					return false;
		return true;
	}
	bool operator !=(TBigUInt a)
	{
		return !(*this==a);
	}
	bool operator>= (TBigUInt a)
	{
		return ((*this>a) || (*this==a));
	}
	bool operator<= (TBigUInt a)
	{
		return ((*this<a) || (*this==a));
	}
	bool operator>(TBigUInt a)
	{
		if (Digits.size()> a.Digits.size())
			return true;
		else if (Digits.size()<a.Digits.size())
			return false;
		else
		{
			for (int i=Digits.size()-1; i>=0; --i)
				if (Digits[i]>a.Digits[i])
					return true;
				else if (Digits[i]<a.Digits[i])
					return false;
		}
		return false;
	}
	bool operator<(TBigUInt a)
	{
		return a>*this;
	}
};


TBigUInt KaratsubaMultiply(const TBigUInt& a, const TBigUInt& b)
{
	size_t maxDigits = max(a.Digits.size(), b.Digits.size());
	if (maxDigits <= 50) 
		return a*b;
	size_t n = maxDigits / 2;
	TBigUInt a1(a, 0, n);
	TBigUInt a2(a, n, maxDigits); 
	TBigUInt b1(b, 0, n);
	TBigUInt b2(b, n, maxDigits);
	TBigUInt z2 = KaratsubaMultiply(a2, b2);
	TBigUInt z0 = KaratsubaMultiply(a1, b1);
	TBigUInt z1 = KaratsubaMultiply(a1 + a2, b1 + b2) - z2 - z0;
	z2.Digits.insert(z2.Digits.begin(), 2 * n, 0);
	z1.Digits.insert(z1.Digits.begin(), n, 0);
	return z2 + z1 + z0;
}
ostream& operator<< (ostream& out, const TBigUInt &a)
{
	int dec=10;
	vector<unsigned char> d;
	TBigUInt b(dec);
	TBigUInt tmp(a);
	if (tmp.Digits[0] == 0 && tmp.Digits.size() == 1)
		d.push_back(0);
	while (tmp>1)
	{
		unsigned char c=(tmp % b).Digits[0];
		d.push_back(c);
		tmp/=b;
	}
	if (tmp == 1)
		d.push_back(1);
	vector<unsigned char>::const_reverse_iterator pos=d.rbegin(), end=d.rend();
	for(; pos!=end; ++pos)
		out<<(int)(*pos);
	return out;
}

istream& operator>> (istream& in, TBigUInt& a)
{
	string str;
	getline (in, str);
	TBigUInt tp (str);
	a = tp;
	return in;
}

int main()
{
	TBigUInt a("1313");
	cout << "a(\"1313\"): " << a << endl;
	TBigUInt b(123456789);
	cout << "b(123456789): " << b << endl;
	cout << "a+b: " << a+b<< endl;
	TBigUInt c(a);
	c += 100;
	cout << "c(a) c += 100: " << c << endl;
	string str = "1230";
	TBigUInt d(str);
	cout << "d(string \"1230\") c-d: " << c-d << endl;
	cout << "c*d: " << c*d<<endl;
	cout << "b/a: " << b/a << endl;
	cout<<"KaratsubaMultiply(c, d): "<<KaratsubaMultiply(c, d)<<endl<<endl<<endl;


	srand((unsigned int)time(NULL));
	string s1, s2;
	TBigUInt res1, res2;
	size_t n = 10;
	TTimePrinter timer;
	for (int k=0; k < 6; k++)
	{
		timer.Reset();
		for (size_t i=0; i<n; ++i)
		{
			s1.push_back(rand() % 10 + (int)'0');
			s2.push_back(rand() % 10 + (int)'0');
		}
		TBigUInt x(s1), y(s2);
		double time = timer.GetTime();
		cout << "Generation time: " << time<<endl;
		timer.Reset();
		res1 = KaratsubaMultiply(x, y);
		time = timer.GetTime();
		cout << "N = " << n << endl;
		cout << "Karatsuba method: " << time <<endl;
		timer.Reset();
		res2 = x * y;
		time = timer.GetTime();
		cout << "Usual method: "<< time <<endl<<endl;
		n*=10;
	}	
	return 0;
}
