#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <cmath>

using namespace std;

typedef long long i64;
i64 GetClock() { return clock() * 1000 / CLOCKS_PER_SEC;}
class TTimePrinter {
      i64 Start;
  public:
      TTimePrinter()
          : Start(GetClock()) {
      }
      void Print() const {
          cout << "\tTime: " << this->GetTime() << " sec" << endl; //milliseconds?
      }
      double GetTime() const {
          return (GetClock() - Start) * 0.001;
      }
      void Reset() {
          Start = GetClock();
      }
  };

const int BASE = 10000;

class TBigUInt
{
private:
	vector<int> number;
public:
	TBigUInt() : number(0) {};
	TBigUInt(unsigned long long other)
	{
		do 
		{
			number.push_back(other % BASE);
			other = other / BASE;
		} while(other != 0);
	}
	explicit TBigUInt(const string& str)
	{
		vector<int> string;
		for(unsigned int i = 0; i < str.size(); ++i)
			string.push_back(str[i] -'0');
		number.reserve(str.size());
		unsigned int resid;
		while (string.size() >= 1 && string[0] != 0)
		{
			int tmp = 0;
			vector<int> part;
			for(int i = string.size() - 1; i >= 0; --i)
			{
				if(i == string.size() - 1)
				{
					int k = 0;
					while(BASE > tmp)
					{
						tmp *= 10;
						tmp += string[k];
						++k;
						--i;
						if(k == string.size())
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
			number.push_back(resid);
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
		if (bound1 >= num.number.size())
			number.push_back(0);
		else
			if (bound2 <= num.number.size())
				for (int i = bound1; i < bound2; ++i)
					number.push_back(num.number[i]);
			else 
				for (int i = bound1; i < num.number.size(); ++i)
					number.push_back(num.number[i]);
	}
	TBigUInt(const TBigUInt& other) { number = other.number;}

	TBigUInt operator+ (const TBigUInt& other) const
	{
		TBigUInt result;
		int rest = 0;
		vector<int>::const_iterator beg1 = (*this).number.begin(), beg2 = other.number.begin();
		vector<int>::const_iterator end1 = (*this).number.end(), end2 = other.number.end();
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
			result.number.push_back(sum % BASE);
			rest = sum/BASE;
		};
		if (rest > 0) result.number.push_back(rest);
		return result;
	}
	TBigUInt operator- (const TBigUInt& other) const
	{
		TBigUInt result;
		if ((*this).number == other.number) 
			return 0;
		int rest = 0;
		vector<int>::const_iterator beg1 = (*this).number.begin(), beg2 = other.number.begin();;
		vector<int>::const_iterator end1 = (*this).number.end(), end2 = other.number.end();
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
				result.number.push_back(sum);
		}
		if (rest > 0) result.number.push_back(rest);
		while(result.number.back() == 0)
			result.number.pop_back();
		return result;
	}
	TBigUInt operator* (const TBigUInt& other) const
	{
		TBigUInt res;
		int rest(0), s(0);
		vector<int>::const_iterator beg1 = (*this).number.begin(), beg2 = other.number.begin();
		vector<int>::const_iterator beg1_1 = (*this).number.begin(), beg2_2 = other.number.begin();
		vector<int>::const_iterator end1 = (*this).number.end(), end2 = other.number.end();
		if ((*this).number.size() < other.number.size())
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
			res.number.push_back(sum%BASE);
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
			res.number.push_back(sum % BASE);
			rest = sum/BASE;
			++beg1;
		}
		if (rest != 0) 
			res.number.push_back(rest);
		while (!res.number.back() && res.number.size() != 1)
			res.number.pop_back();
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
		for (int i = (int)(*this).number.size() - 1; i >= 0; --i)
		{
			cur *= BASE;
			cur.number[0] = (*this).number[i];
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
			res.number.push_back(tmp);
			cur -= other * tmp;
		}
		TBigUInt src;
		while(!res.number.empty())
		{
			src.number.push_back(res.number.back());
			res.number.pop_back();
		}
		while (!src.number.back() && src.number.size() != 1)
			src.number.pop_back();
		return src;
	}
	bool operator<= (const TBigUInt& other) const
	{
		if (number.size() < other.number.size())
			return true;
		else
			if(number.size() > other.number.size())
				return false;
			else
				for(int i = (int)number.size() - 1; i > 0; --i)
					if (number[i] < other.number[i])
						return true;
					else
						if (number[i] > other.number[i])
							return false;
		return true;
	}
	bool operator== (const TBigUInt& other) const
	{
		if (number.size() == other.number.size())
		{
			for (int i = (int)number.size() - 1; i > 0; --i)
			{
				if (number[i] != other.number[i])
					return 1;
			}
			return 0;
		}
		return 1;
	}
	bool operator> (const TBigUInt& other) const { return !(*this <= other);;}
	bool operator< (const TBigUInt& other) const { return !(other <= *this);}
	bool operator>= (const TBigUInt& other) const { return !(other <= *this);}
	bool operator!= (const TBigUInt& other) const { return !(*this == other);}
	TBigUInt& operator++ () { *this += 1; return *this;}
	TBigUInt operator++ (int) { TBigUInt tmp(*this); *this += 1; return tmp;}
	TBigUInt& operator-- () { *this -= 1; return *this;}
	TBigUInt operator-- (int) { TBigUInt tmp(*this); *this -= 1; return tmp;}
	TBigUInt& operator+= (const TBigUInt& other) { *this = *this + other; return *this;}
	TBigUInt& operator-= (const TBigUInt& other) { *this = *this - other; return *this;}
	TBigUInt& operator*= (const TBigUInt& other) { *this = (*this) * other; return *this;}
	TBigUInt& operator/= (const TBigUInt& other) { *this = (*this) / other; return *this;}
	friend ostream& operator<<(ostream& s, const TBigUInt& x);
	friend TBigUInt KaratsubaMultiply(const TBigUInt& A, const TBigUInt& B);
};
TBigUInt KaratsubaMultiply(const TBigUInt& A, const TBigUInt& B)
{
	int stop = 100;
	if ((A.number.size() <  stop) && (B.number.size() <  stop))
		return (A * B);
	int digit = max(A.number.size(), B.number.size());
	int part = digit / 2;
	TBigUInt A0(A, 0, part), A1(A, part, digit); 
	TBigUInt B0(B, 0, part), B1(B, part, digit); 
	TBigUInt sumA(A0 + A1), sumB(B0 + B1);
	TBigUInt sum_of_parts = KaratsubaMultiply(sumA, sumB);
	TBigUInt first_part = KaratsubaMultiply(A0, B0);
	TBigUInt second_part = KaratsubaMultiply(A1, B1);
	TBigUInt sum_of_middle_terms = sum_of_parts - first_part - second_part;
	second_part.number.insert(second_part.number.begin(), 2 * part, 0);
	sum_of_middle_terms.number.insert(sum_of_middle_terms.number.begin(), part, 0);
	return (first_part + second_part + sum_of_middle_terms);
}


ostream& operator<< (ostream& stream, const TBigUInt& num)
{
	for(vector<int>::const_reverse_iterator it = num.number.rbegin(); it != num.number.rend(); ++it)
	{
		char buf[10];
		if (it == num.number.rbegin()) 
			stream << *it;
		else
		{
			sprintf(buf,"%04d", *it);
			stream << buf;
		}
	}
	return stream;
}
istream& operator>> (istream& stream, TBigUInt& num)
{
	string str;
	getline(stream, str);
	TBigUInt tmp (str);
	num = tmp;
	return stream;
}
void simple_tests()
{
	TBigUInt a;
	cout << a;
	TBigUInt b(123456789);
	TBigUInt c(b);
	cout << "\n" << c << "\n"<< b << "\n";
	TBigUInt n1(4000000000);
	TBigUInt n2(200000);
	TBigUInt n3;
	cout << "\n n1 = " << n1 << "\n n2 = "<< n2 << "\n";
	n3 = n1 + n2;
	cout << "n1 + n2 = " <<n3<< "\n";
	n3 = n1 - n2;
	cout << "n1 - n2 = " <<n3<< "\n";
	n3 = n1 * n2;
	cout << "n1 * n2 = " <<n3<< "\n";
	cout << "KaratsubaMultiply(n1, n2) = " << KaratsubaMultiply(n1, n2) << "\n";
	if (n2 < n3)
		n3 = n1 / n2;
	cout << "n1 / n2 = " <<n3<< "\n";
	TBigUInt n5("70003000");
	char* p = "4567";
	TBigUInt n6(p);
	cout << "\n n5(string) "<< n5;
	cout << "\n n6(char*) "<< n6;
	cout << "\n give! ";
	cin >> n6;
	cout << " "<< n6;
}
void test_time()
{
	srand(time(NULL));
	int MAX;
	int step = 4;
	for (int j = 0; j < step; ++j)
	{
		MAX = (int)pow(10.0, j);
		ofstream on;
		int n;
		on.open("in.txt");
		char* c = 0;
		n = 1 + rand() %10;
		on << n;
		for (int i = 1; i < MAX; ++i)
		{
			n = 0 + rand() %10;
			on << n;
		}
		on.close();
		ifstream in;
		in.open("in.txt");
		TBigUInt number;
		in >> number;
		in.close();
		cout << "__________________________";
		cout << "\n" << MAX << " elem: ";
		cout << "\n simple \n";
		TTimePrinter tp;
		number * number;
		tp.Print();
		cout << "\n KaratsubaMultiply \n";
		tp.Reset();
		KaratsubaMultiply(number, number);
		tp.Print();
	}
}
int main()
{
	//simple_tests();
	test_time();
	system("pause");
	return 0;
}