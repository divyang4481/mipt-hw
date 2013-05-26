#include <iostream>
#include<vector>
#include <string>
#include <time.h>
#include <math.h>
using namespace std;

long long exp10 (int e){
	long long r=1;
	for (int i=0; i<e; ++i)
		r*=10;
	return r;
}

class TBigUInt{
//public: //should be public for comparision of Karatsuba and usual methods of multiplying
	vector<unsigned char> dig;
	static const int base = 256;
public:
	TBigUInt(){	
	}
	TBigUInt(const TBigUInt& src){
		dig=src.dig;
	}
	explicit TBigUInt(unsigned long long src){
		while(src>0){
			dig.push_back(src%base);
			src/=256;
		}
	}
	explicit TBigUInt(const char* str){
		string alt;
		char c=str[0];
		for(int i=1; c!='\0'; ++i){
			alt.push_back(c);
			c=str[i];
		}
		TBigUInt temp(alt);
		*this=temp;
	}
	explicit TBigUInt(const std::string& str){
		//If you can cast it into a longlong
		if(str.size()<=18){
			long long int num=0;
			int exp;
			for(unsigned int i=0, exp=str.size()-1; i<str.size(); ++i, --exp){
				num+=(int)(str[i]-'0')*static_cast<long long>(exp10(exp));
			}
			TBigUInt temp(num);
			*this=temp;
		}
		//If you can't
		else{	
			vector<int> vec_temp;
			int temp_base=10;
			vector<unsigned char>::iterator pos;
			unsigned char remainder;
			dig.reserve(str.size());
			for(unsigned int i=0; i<str.size(); ++i)
				vec_temp.push_back((int)str[i]-(int)'0');
			while (vec_temp.size()>=1 && vec_temp[0]!=0){
				int temp=0;
				vector<int> quotient;
				for(int i=vec_temp.size()-1; i>=0;--i){
					if(i==vec_temp.size()-1){
						int k=0;
						while(base>temp){
							temp*=temp_base;
							temp+=vec_temp[k];
							++k;
							--i;
							if(k==vec_temp.size())
								break;
						}
						++i;
					}
					else{
						temp*=temp_base;
						temp+=vec_temp[vec_temp.size()-1-i];
					}
					if (temp<base){
						remainder=temp;
						quotient.push_back(0);
						continue;
					}
					unsigned char k=0;
					while(temp>=base){
						temp=temp-base;
						++k;
					}
					remainder=temp;
					quotient.push_back(k);
				}
				dig.push_back(remainder);
				vec_temp=quotient;
			}
		}
	}
	TBigUInt (const TBigUInt a, unsigned int from, unsigned int to){
		if (from>=a.dig.size()){
			dig.push_back(0);
		}
		else{
			if (to<=a.dig.size()){
				for (unsigned int i=from; i<to; ++i)
					dig.push_back(a.dig[i]);
			} else {
				for (unsigned int i=from; i<a.dig.size(); ++i)
					dig.push_back(a.dig[i]);
			}
		}
	}

	TBigUInt operator=(TBigUInt a){
		dig=a.dig;
		return *this;
	}
	TBigUInt operator+(TBigUInt a){
		TBigUInt result;
		int carry=0;
		unsigned int pos;
		bool abig;
		abig=(dig.size()<a.dig.size());
		pos=(abig)? dig.size() : a.dig.size();
		for(unsigned int i=0; i<pos;++i){
			int cur=dig[i]+a.dig[i]+carry;
			if(cur<base){
				result.dig.push_back(cur);
				carry=0;
			}
			else{
				result.dig.push_back(cur-base);
				carry=1;
			}
		}
		if(dig.size()==a.dig.size() && carry>0){
			result.dig.push_back(carry);
			return result;
		}
		if(!abig){
			for(unsigned int i=pos; i<dig.size(); ++i){
				int tp=dig[i]+carry;
				if(tp<base){
					result.dig.push_back(tp);
					carry=0;
				}
				else{
					result.dig.push_back(0);
					carry=1;
				}
			}
		}
		else{
			for(unsigned int i=pos; i<a.dig.size(); ++i){
				int tp=a.dig[i]+carry;
				if(tp<base){
					result.dig.push_back(tp);
					carry=0;
				}
				else{
					result.dig.push_back(0);
					carry=1;
				}
			}
		}
		if(carry)
			result.dig.push_back(carry);
		return result;
	}

	TBigUInt operator-(TBigUInt a){
		TBigUInt result;
		if(dig.size()<a.dig.size()||(dig.size()==a.dig.size() && dig[dig.size()-1]<a.dig[a.dig.size()-1]))
			return result;
		//because unsinged type
		int carry=0;
		int cur;
		if(dig.size()==a.dig.size()){
			//finding the digit
			for(unsigned int i=0; i<a.dig.size()-1;++i){
				cur=dig[i]-a.dig[i]-carry;
				if(cur>=0){
					result.dig.push_back(cur);
					carry=0;
				}
				else{
					result.dig.push_back(cur+base);
					carry=1;
				}
			}
			//applying it
			cur=dig[dig.size()-1]-a.dig[dig.size()-1]-carry;
			if(cur>=0)
				result.dig.push_back(cur);
			else{
				result.dig.clear();
				result.dig.push_back(0);
				return result;
			}
		}
		else{
			//a can't have more digits than ours, that would lead to negatives
			for(unsigned int i=0; i<a.dig.size();++i){
				int cur=dig[i]-a.dig[i]-carry;
				if(cur>=0){
					result.dig.push_back(cur);
					carry=0;
				}
				else{
					result.dig.push_back(cur+base);
					carry=1;
				}
			}
			for(unsigned int i=a.dig.size(); i<dig.size();++i){
				int tp=dig[i]-carry;
				if(tp>=0){
					result.dig.push_back(tp);
					carry=0;
				}
				else{
					result.dig.push_back(tp+base);
					carry=1;
				}
			}
		}
		if(result.dig[result.dig.size()-1]==0 && result.dig.size()>1)
			result.dig.resize(dig.size()-1);
		return result;
	}
	TBigUInt operator*(const TBigUInt a) const{
		TBigUInt result;
		result.dig.push_back(0);
		for(unsigned int i=0; i<a.dig.size(); ++i){
			TBigUInt tp;
			int carry=0;
			int temp;
			for(unsigned int j=0; j<dig.size(); ++j){
				temp=dig[j]*a.dig[i]+carry;
				if(temp >= base){
					tp.dig.push_back(temp%base);
					carry=temp/base;
				} 
				else{
					tp.dig.push_back(temp);
					carry=0;
				}
			}
			if (carry >0)
				tp.dig.push_back(carry);
			tp.dig.resize(tp.dig.size()+i);
			for(unsigned int k=0; k<tp.dig.size()-i; ++k){
				tp.dig[tp.dig.size()-k-1]=tp.dig[tp.dig.size()-i-k-1];
			}
			for(unsigned int k=0; k<i;++k)
				tp.dig[k]=0;
			result+=tp;
		}
		return result;
	}
	bool operator== (TBigUInt a){
		if (dig.size()!=a.dig.size())
			return false;
		else
			for(int i=dig.size()-1; i>=0; --i)
				if(dig[i]!=a.dig[i])
					return false;
		return true;
	}
	TBigUInt operator*(const long long a) const{
		TBigUInt tp(a);
		return *this*tp;
	}

	bool operator !=(TBigUInt a){
		return !(*this==a);
	}
	bool operator>= (TBigUInt a){
		return ((*this>a) || (*this==a));
	}
	bool operator<= (TBigUInt a){
		return ((*this<a) || (*this==a));
	}
	bool operator>(TBigUInt a){
		if (dig.size()> a.dig.size())
			return true;
		else if (dig.size()<a.dig.size())
			return false;
		else{
			for(int i=dig.size()-1; i>=0; --i)
				if(dig[i]>a.dig[i])
					return true;
				else if (dig[i]<a.dig[i])
					return false;
		}
		return false;
	}
	bool operator<(TBigUInt a){
		return a>*this;
	}
	bool operator>(unsigned char a){
	TBigUInt tp;
	tp.dig.push_back(a);
	return *this>tp;
	}
	bool operator<(unsigned char a){
		return !(*this>a);
	}
	TBigUInt operator/(TBigUInt a){
		TBigUInt result;
		TBigUInt temp;
		if(a.dig.size()>dig.size() || (a.dig.size()==dig.size() && a.dig[dig.size()-1]>dig[dig.size()-1]))
			return result;
		vector<unsigned char>:: iterator pos=result.dig.begin();
		vector<unsigned char>:: iterator pos1=temp.dig.begin();
		for(int i=dig.size()-1; i>=0;--i){
			if(i==dig.size()-1){
				while(a>temp){
				pos1=temp.dig.insert(pos1,dig[i]);
				--i;
				}
			++i;
			}
			else{
				pos1=temp.dig.insert(pos1,dig[i]);
			}
			if(temp<a){
				pos=result.dig.insert(pos, 0);
				continue;
			}
			if(temp.dig[temp.dig.size()-1]==0)
				temp.dig.resize(temp.dig.size()-1);
			unsigned char k=0;
			while(temp>=a){
				temp=temp-a;
				++k;
			}
			pos=result.dig.insert(pos, k);
		}
		return result;
	}

	unsigned char operator%(unsigned char a){
		TBigUInt tp;
		TBigUInt tp1;
		tp.dig.push_back(a);
		tp1=*this/tp;
		tp=*this-(tp1*tp);
		return tp.dig[0];
	}
	//prefix
	TBigUInt operator++(){
		if(dig.empty()){
			dig.push_back(1);
			return *this;
		}
		for(int i=0; ; ++i){
			if(dig[i]<(base-1)){
				dig[i]+=1;
				break;
			}
			else{
				dig[i]=0;
				if(dig.size()==(i+1)){
					dig.push_back(1);
					break;
				}
			}
		}
		return *this;
	}
	//postfix
	TBigUInt operator++(int){
		TBigUInt temp;
		temp=*this;
		++*this;
		return temp;
	}
	//prefix
	TBigUInt operator--(){
		if(dig.size()==1 && dig[0]==0)
			return *this;
			if(dig[0]>0){
				dig[0]-=1;
				return *this;
			}
			else{
				dig[0]=(base-2);
				for(unsigned int i=1; i<dig.size();++i){
					if(dig[i]>0){
						dig[i]-=1;
						break;
					}
					dig[i]=base-2;
				}
			}
		return *this;
	}
	//postfix
	TBigUInt operator--(int){
		TBigUInt temp=*this;
		--*this;
		return temp;
	}

	void operator+=(TBigUInt a){
		*this=(*this+a);
	}

	void operator-=(TBigUInt a){
		*this=(*this-a);
	}

	void operator*=(TBigUInt a){
		*this=(*this*a);
	}

	void operator/=(TBigUInt a){
		*this=(*this/a);
	}

	TBigUInt operator<<(int exp){
		vector<unsigned char>::iterator pos=dig.begin();
		dig.insert(pos, exp, 0);
		return *this;
	}
	 unsigned int vsize() const {
		return dig.size();
	}
};

TBigUInt KaratsubaMultiply(const TBigUInt& a, const TBigUInt& b){//- умножение длинных чисел, реализованное с помощью алгоритма Карацубы
		unsigned int maxsize = max(a.vsize(), b.vsize());
		if (maxsize <= 50) 
			return a*b;
		int median = maxsize / 2;
		TBigUInt aPart1(a, 0, median);
		TBigUInt aPart2(a, median, maxsize); 
		TBigUInt bPart1(b, 0, median);
		TBigUInt bPart2(b, median, maxsize);
		TBigUInt z2 = KaratsubaMultiply(aPart2, bPart2);
		TBigUInt z0 = KaratsubaMultiply(aPart1, bPart1);
		TBigUInt z1 = KaratsubaMultiply(aPart1 + aPart2, bPart1 + bPart2) - z2 - z0;
		z2<<(2 * median);
		z1<<(median);
		return z2 + z1 + z0;
	}

ostream& operator<<(ostream& out, const TBigUInt& num){
	int outbase=10;
	vector<unsigned char> print;
	TBigUInt a(outbase);
	TBigUInt tp;
	tp=num;
	while(tp>0){
		unsigned char c=tp%outbase;
		print.push_back(c);
		tp/=a;
	}
	vector<unsigned char>::const_reverse_iterator pos=print.rbegin(),
											end=print.rend();
	for(;pos!=end; ++pos)
		out<<(int)(*pos);
	return out;
}

istream& operator>> (istream& in, TBigUInt& num){
	string str;
	getline(in,str);
	TBigUInt tp (str);
	num=tp;
	return in;
}

void CommonTests(){
	string str;
	for (int i=1; i<30; i++)
		str.push_back((char)((i*53*179)%10+(int)'0'));
	TBigUInt a(str);
	cout << a << " This is number A" << endl;
	str.clear();
	for (int i=1; i<25; i++)
		str.push_back((char)((i*37*13)%10+(int)'0'));
	TBigUInt b(str);
	cout << b << " This is number B" << endl;
	TBigUInt cc;
	++a;
	cout << a << " supposed to be A+1" << endl;
	a--;
	cout << a << " back to A original" << endl;
	cc=a+b;
	cout << cc << " A+B" << endl;
	cc=a-b;
	cout << cc << " A-B" << endl;
	cc=a*b;
	cout << cc << " A*B" << endl;
	cc=a/b;
	cout << cc << " A/B" << endl;
	str.clear();
	for (int i=1; i<20; i++)
		str.push_back((char)((i*241*123)%10+(int)'0'));
	TBigUInt a2(str);
	TBigUInt b2(str);
	cout << a2 << " New A" << endl;
	cout << a2*b2 << " A squared, common mult" << endl;
	cout << KaratsubaMultiply(a2,b2) << " A squared, courtesy of Karatsuba" << endl;
	system("pause");
	return;
}

void KaratsubaTests(){
	string str;
	int num=200;
	for(int i=1; i<num; i++)
			str.push_back((char)(((i*231)%13)+(int)'0'));
	clock_t t;
	TBigUInt a(str);
	TBigUInt b(str);
	TBigUInt y;
		b=a;
		t=clock();
		y=a*b;
		t=clock()-t;
		cout << "Common method time spent: " <<(float)t/CLOCKS_PER_SEC<<endl;
		t=clock();
		y=KaratsubaMultiply(a,b);
		t=clock()-t;
		cout << "Karatsuba method time spent: " <<(float)t/CLOCKS_PER_SEC<<endl;
		str.clear();
		cout << ((KaratsubaMultiply(a,b)==(a*b))? "correct" : "something wrong") << endl;
		system("pause");

}

int main(){	
	//CommonTests();
	KaratsubaTests();
	return 0;
}