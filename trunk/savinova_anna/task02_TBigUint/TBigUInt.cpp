#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <cmath>
#include <stdlib.h>

using namespace std;

const int BASE = 10000;

class TBigUInt
{
private:
	vector<int> v;
public:
	TBigUInt() : v(0) {};
	TBigUInt(unsigned long long other)
	{
		do 
		{
			v.push_back(other % BASE);
			other = other / BASE;
		} while(other != 0);
	}
	explicit TBigUInt(const string& str)
	{
		vector<int> string;
		for(unsigned int i = 0; i < str.size(); ++i)
			string.push_back(str[i] -'0');
		v.reserve(str.size());
		unsigned int resid;
		while (string.size() >= 1 && string[0] != 0)
		{
			int tmp = 0;
			vector<int> part;
			for(int i = string.size() - 1; i >= 0; --i)
			{
				if(i == (int)string.size() - 1)
				{
					int k = 0;
					while(BASE > tmp)
					{
						tmp *= 10;
						tmp += string[k];
						++k;
						--i;
						if(k == (int)string.size())
							break;
					}
					++i;
				}
				else
				{
					tmp *= 10;
					tmp += string[string.size() - i - 1];
				}
				if (tmp < BASE)
				{
					resid = tmp;
					part.push_back(0);
					continue;
				}
				unsigned int k = 0;
				while(tmp >= BASE)
				{
					tmp = tmp - BASE;
					++k;
				}
				resid = tmp;
				part.push_back(k);
			}
			v.push_back(resid);
			string = part;
		}
	}
	explicit TBigUInt(const char* str)
	{
		string tmp;
		char c = str[0];
		for (int i = 1; c != '\0'; ++i){
			tmp.push_back(c);
			c = str[i];
		}
		TBigUInt src(tmp);
		*this = src;
	}
	TBigUInt (const TBigUInt num, unsigned int bound1, unsigned int bound2) //for KaratsubaMultiply
	{
		if (bound1 >= num.vsize())
			v.push_back(0);
		else
			if (bound2 <= num.vsize())
				for (unsigned int i = bound1; i < bound2; ++i)
					v.push_back(num.v[i]);
			else 
				for (unsigned int i = bound1; i < num.vsize(); ++i)
					v.push_back(num.v[i]);
	}
	TBigUInt(const TBigUInt& other)
    { 
        v = other.v;
    }
    size_t vsize() const
    {
        return v.size();
    }
	TBigUInt operator+ (const TBigUInt& other) const
	{
		TBigUInt result;
		int rest = 0;
		vector<int>::const_iterator beg1 = (*this).v.begin(), beg2 = other.v.begin();
		vector<int>::const_iterator end1 = (*this).v.end(), end2 = other.v.end();
		while ((beg1 != end1) || (beg2 != end2))
		{
			int sum;
			if ((beg1 != end1) && (beg2 != end2))
			{
				sum = (*beg1) + (*beg2) + rest;
				++beg1;
				++beg2;
			}
			else
				if (beg1 != end1)
				{
					sum = *beg1 + rest;
					++beg1;
				}
				else 
				{
					sum = *beg2 + rest;
					++beg2;
				};
			result.v.push_back(sum % BASE);
			rest = sum/BASE;
		};
		if (rest > 0) result.v.push_back(rest);
		return result;
	}
	TBigUInt operator- (const TBigUInt& other) const
	{
		TBigUInt result;
		if ((*this).v == other.v) 
			return 0;
		int rest = 0;
		vector<int>::const_iterator beg1 = (*this).v.begin(), beg2 = other.v.begin();;
		vector<int>::const_iterator end1 = (*this).v.end(), end2 = other.v.end();
		while ((beg1 != end1) || (beg2 != end2))
		{
			int sum;
			if ((beg1 != end1) && (beg2 != end2))
			{
				if (((*beg1) + rest) < (*beg2))
				{
					sum = (*beg1) - (*beg2) + BASE + rest;
					rest = -1;
				}
				else 
				{
					sum = (*beg1) - (*beg2) + rest;
					rest = 0;
				};
				++beg1;
				++beg2;
			}
			else
				if (beg1 != end1)
				{
					sum = *beg1 + rest;
					rest = 0;
					++beg1;
				}
				result.v.push_back(sum);
		}
		if (rest > 0) result.v.push_back(rest);
		while(result.v.back() == 0)
			result.v.pop_back();
		return result;
	}
	TBigUInt operator* (const TBigUInt& other) const
	{
		TBigUInt res;
		int rest(0), s(0);
		vector<int>::const_iterator beg1 = (*this).v.begin(), beg2 = other.v.begin();
		vector<int>::const_iterator beg1_1 = (*this).v.begin(), beg2_2 = other.v.begin();
		vector<int>::const_iterator end1 = (*this).v.end(), end2 = other.v.end();
		if ((*this).vsize() < other.vsize())
		{
			swap(beg1,beg2);
			swap(beg1_1,beg2_2);
			swap(end1,end2);
		}
		while ((beg1 != end1) || (beg2 != end2))
		{
			int sum = 0;     
			vector<int>::const_iterator beg22 = beg2;
			if (beg2 == end2) 
			{
				++s;
				--beg22;
			};
			vector<int>::const_iterator beg12 = beg1_1 + s;
			for (; beg22 != (beg2_2); --beg22, ++beg12)
			{
				sum = sum + (*beg12) * (*beg22);
			};
			sum = sum + (*beg2_2) * (*beg12);
			sum += rest;
			res.v.push_back(sum%BASE);
			rest = sum/BASE;
			++beg1;
			if (beg2 != end2) 
				++beg2;
		}
		beg1 = beg1_1 + s + 1;
		while (beg1 != (end1))
		{
			int sum = 0;
			vector<int>::const_iterator beg12 = beg1;
			for(beg2 = end2 - 1; beg12 != end1; ++beg12, --beg2)
			{
				sum = sum + (*beg12) * (*beg2);
			};
			sum += rest;
			res.v.push_back(sum % BASE);
			rest = sum/BASE;
			++beg1;
		}
		if (rest != 0) 
			res.v.push_back(rest);
		while (!res.v.back() && res.vsize() != 1)
			res.v.pop_back();
		return res;
	}
	TBigUInt operator* (const long long a) const
	{
		TBigUInt tmp(a);
		return *this * tmp;
	}
	TBigUInt operator/ (const TBigUInt& other) const
	{
		TBigUInt res, cur = 0;
		for (int i = (int)(*this).vsize() - 1; i >= 0; --i)
		{
			cur *= BASE;
			cur.v[0] = (*this).v[i];
			int tmp(0), left(0), right(BASE);
			while (left <= right)
			{
				int m = (left + right) >> 1;
				TBigUInt cur2 = other * m;
				if (cur2 <= cur)
				{
					tmp = m;
					left = m + 1;
				}
				else
					right = m - 1;
			}
			res.v.push_back(tmp);
			cur -= other * tmp;
		}
		TBigUInt src;
		while(!res.v.empty())
		{
			src.v.push_back(res.v.back());
			res.v.pop_back();
		}
		while (!src.v.back() && src.vsize() != 1)
			src.v.pop_back();
		return src;
	}
	bool operator < (const TBigUInt& b) const
    {
        if (vsize() < b.vsize())
            return true;
        if (vsize() > b.vsize())
            return false;
        size_t i = vsize() - 1;
        for (;v[i] == b.v[i] && i < vsize(); ++i);
        if (v[i] < b.v[i])
            return true;
        return false;            
    }
	bool operator == (const TBigUInt& b) const
    {
        return (!(*this < b) && !(b < *this));
    }
    bool operator != (const TBigUInt& b) const
    {
        return (!(*this == b));
    }
    bool operator > (const TBigUInt& b) const
    {
        return (!(*this < b) && b != *this);
    }
    bool operator <= (const TBigUInt& b) const
    {
        return (b > *this);
    }
    bool operator >= (const TBigUInt& b) const
    {
        return (*this < b);
    }
	TBigUInt& operator++ () 
    { *this += 1; 
        return *this;
    }
	TBigUInt operator++ (int) 
    { 
        TBigUInt tmp(*this); 
        *this += 1; 
        return tmp;
    }
	TBigUInt& operator-- () 
    { 
        *this -= 1; 
        return *this;
    }
	TBigUInt operator-- (int) 
    { 
        TBigUInt tmp(*this); 
        *this -= 1; 
        return tmp;
    }
	TBigUInt& operator+= (const TBigUInt& other) 
    { 
        *this = *this + other; 
        return *this;
    }
	TBigUInt& operator-= (const TBigUInt& other) 
    { 
        *this = *this - other; 
        return *this;
    }
	TBigUInt& operator*= (const TBigUInt& other) 
    { 
        *this = (*this) * other; 
        return *this;
    }
	TBigUInt& operator/= (const TBigUInt& other) 
    { 
        *this = (*this) / other; 
        return *this;
    }
	friend ostream& operator<<(ostream& s, const TBigUInt& x);
	friend TBigUInt KaratsubaMultiply(const TBigUInt& A, const TBigUInt& B);
};
TBigUInt KaratsubaMultiply(const TBigUInt& a, const TBigUInt& b)
{
	size_t maxDigits = max(a.vsize(), b.vsize());
	if (maxDigits <= 50) 
		return a * b;
	size_t n = maxDigits / 2;
	TBigUInt a1(a, 0, n);
	TBigUInt a2(a, n, maxDigits); 
	TBigUInt b1(b, 0, n);
	TBigUInt b2(b, n, maxDigits);
	TBigUInt z2 = KaratsubaMultiply(a2, b2);
	TBigUInt z0 = KaratsubaMultiply(a1, b1);
	TBigUInt z1 = KaratsubaMultiply(a1 + a2, b1 + b2) - z2 - z0;
	z2.v.insert(z2.v.begin(), 2 * n, 0);
	z1.v.insert(z1.v.begin(), n, 0);
	return z2 + z1 + z0;
}


ostream& operator<< (ostream& out, const TBigUInt& num)
{
	for(vector<int>::const_reverse_iterator it = num.v.rbegin(); it != num.v.rend(); ++it)
	{
		char buf[10];
		if (it == num.v.rbegin()) 
			out << *it;
		else
		{
			sprintf(buf,"%04d", *it);
			out << buf;
		}
	}
	return out;
}
istream& operator>> (istream& stream, TBigUInt& num)
{
	string str;
	getline(stream, str);
	TBigUInt tmp (str);
	num = tmp;
	return stream;
}

int main()
{
	/*TBigUInt t1(12345);
    cout << "t1(12345) " << t1 << endl;
    TBigUInt t2("87654321");
    cout << "t2(\"87654321\") " << t2 << endl;
    cout << "t2 + t1 " << t2 + t1 << endl;
    TBigUInt t3 = t1 * t2;
    cout << "t3 = t1 * t2 " << t3 << endl;
    t3 /= t2;
    cout << "t3 /= t1 " << t3 << endl;
    cout << "KaratsubaMultiply(t1, t2)" << KaratsubaMultiply(t1, t2) << endl;*/
    srand(time(NULL));
    int n = 0;
    cin >> n;
    string s1, s2;
    for (int i = 0; i < n; ++i)
    {
        s1.push_back(rand() % 10 + (int)'0');
        s2.push_back(rand() % 10 + (int)'0');
    }
    TBigUInt A(s1), B(s2), res1, res2;
    //cout << s1 << endl << s2 << endl;
    time_t timer1, timer2;
    cout << "Start Mult" << endl;
    time(&timer1);
    res2 = A * B;
    time(&timer2);
    //cout << res2 << endl;
    cout << "Finish Mult" << endl;
    cout << "Mult time: " << (timer2 - timer1) << endl;
    cout << "Start Karatsuba" << endl;
    time(&timer1);
    res1 = KaratsubaMultiply(A, B);
    time(&timer2);
    //cout << res1 << endl;
    cout << "Finish Karatsuba, check: " << (res1 == res2) << endl;
    cout << "Karatsuba time: " << (timer2 - timer1) << endl << endl;
    return 0;
}
