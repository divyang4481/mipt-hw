#include <iostream>
#include<vector>
#include <string>
#include <time.h>
#include <math.h>
using namespace std;


class TBigUInt{
//public: should be public for comparision of Karatsuba and usual methods of multiplying
	vector<unsigned char> vec;
	static const int base = 256;
	static const int BASE_DIGITSbase_digits = 3;
public:
	TBigUInt(){	//����������� �� ���������, ������� ����� "0"
	}
	TBigUInt(const TBigUInt& a){// - ����������� �����������
		vec=a.vec;
	}
	explicit TBigUInt(unsigned long long a){// - ����������� �������� ����� �� unsigned int
		while(a>0){
			vec.push_back(a%base);
			a/=256;
		}
	}
	explicit TBigUInt(const char* str){// - ����������� �������� ����� �� ��-������
		string a;
		char c=str[0];
		for(int i=1; c!='\0'; ++i){
			a.push_back(c);
			c=str[i];
		}
		TBigUInt temp(a);
		*this=temp;
	}

	explicit TBigUInt(const std::string& str){// - ����������� �������� ����� �� std::string
		//If number in string can be contained in long long - I use another contructor
		if(str.size()<=18){
			long long int num=0;
			int pow_n;
			for(unsigned int i=0; i<str.size(); ++i){
				pow_n=str.size()-1-i;
				num+=((int)str[i]-(int)'0')* static_cast<long long >(pow(10.0,pow_n));
			}
			TBigUInt a(num);
			*this=a;
		}
		//In other case, just divide until we will have TBigUInt
		else{	
			vector<int> vec_temp;
			int new_base=10;
			vector<unsigned char>::iterator pos;
			unsigned char remainder;
			vec.reserve(str.size());
			for(unsigned int i=0; i<str.size(); ++i)
				vec_temp.push_back((int)str[i]-(int)'0');
			while (vec_temp.size()>=1 && vec_temp[0]!=0){
				int temp=0;
				vector<int> quotient;
				for(int i=vec_temp.size()-1; i>=0;--i){
					if(i==vec_temp.size()-1){
						int k=0;
						while(base>temp){
							temp*=new_base;
							temp+=vec_temp[k];
							++k;
							--i;
							if(k==vec_temp.size())
								break;
						}
						++i;
					}
					else{
						temp*=new_base;
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
				vec.push_back(remainder);
				vec_temp=quotient;
			}
		}
	}

	TBigUInt operator=(TBigUInt a){
		vec=a.vec;
		return *this;
	}

	TBigUInt operator+(TBigUInt a){
		TBigUInt result;
		int carry=0;
		unsigned int minsize;
		bool flag;
		flag=(vec.size()<a.vec.size())? true:false;
		minsize=(flag)? vec.size():a.vec.size();
		for(unsigned int i=0; i<minsize;++i){
			int tp=vec[i]+a.vec[i]+carry;
			if(tp<base){
				result.vec.push_back(tp);
				carry=0;
			}
			else{
				result.vec.push_back(tp-base);
				carry=1;
			}
		}
		if(vec.size()==a.vec.size() && carry>0){
			result.vec.push_back(carry);
			return result;
		}
		if(!flag){
			for(unsigned int i=minsize; i<vec.size(); ++i){
				int tp=vec[i]+carry;
				if(tp<base){
					result.vec.push_back(tp);
					carry=0;
				}
				else{
					result.vec.push_back(0);
					carry=1;
				}
			}
		}
		else{
			for(unsigned int i=minsize; i<a.vec.size(); ++i){
				int tp=a.vec[i]+carry;
				if(tp<base){
					result.vec.push_back(tp);
					carry=0;
				}
				else{
					result.vec.push_back(0);
					carry=1;
				}
			}
		}
		if(carry)
			result.vec.push_back(carry);
		return result;
	}

	TBigUInt operator-(TBigUInt a){
		TBigUInt result;
		//check, whether the result can be negative
		if(vec.size()<a.vec.size()||(vec.size()==a.vec.size() && vec[vec.size()-1]<a.vec[a.vec.size()-1]))
			return result;
		int carry=0;
		int tp;
		//if sizes are equal
		if(vec.size()==a.vec.size()){
			for(unsigned int i=0; i<a.vec.size()-1;++i){
				tp=vec[i]-a.vec[i]-carry;
				if(tp>=0){
					result.vec.push_back(tp);
					carry=0;
				}
				else{
					result.vec.push_back(tp+base);
					carry=1;
				}
			}
			//check whether it can be a negative result
			tp=vec[vec.size()-1]-a.vec[vec.size()-1]-carry;
			if(tp>=0)
				result.vec.push_back(tp);
			else{
				result.vec.clear();
				result.vec.push_back(0);
				return result;
			}
		}
		//if size are not equal
		else{
			for(unsigned int i=0; i<a.vec.size();++i){
				int tp=vec[i]-a.vec[i]-carry;
				if(tp>=0){
					result.vec.push_back(tp);
					carry=0;
				}
				else{
					result.vec.push_back(tp+base);
					carry=1;
				}
			}
			//add other elements
			for(unsigned int i=a.vec.size(); i<vec.size();++i){
				int tp=vec[i]-carry;
				if(tp>=0){
					result.vec.push_back(tp);
					carry=0;
				}
				else{
					result.vec.push_back(tp+base);
					carry=1;
				}
			}
		}
		//resize vector if it is needed
		if(result.vec[result.vec.size()-1]==0 && result.vec.size()>1)
			result.vec.resize(vec.size()-1);
		return result;
	}

	
	TBigUInt operator*(const TBigUInt a) const{ //������ ���� ���������� � �������������� ��������� ��������� ��������� ��������
		TBigUInt result;
		result.vec.push_back(0);
		for(unsigned int i=0; i<a.vec.size(); ++i){
			TBigUInt tp;
			int carry=0;
			int temp;
			for(unsigned int j=0; j<vec.size(); ++j){
				temp=vec[j]*a.vec[i]+carry;
				if(temp >= base){
					tp.vec.push_back(temp%base);
					carry=temp/base;
				} 
				else {
					tp.vec.push_back(temp);
					carry=0;
				}
			}
			if (carry >0)
				tp.vec.push_back(carry);
			tp.vec.resize(tp.vec.size()+i);
			for(unsigned int k=0; k<tp.vec.size()-i; ++k){
				tp.vec[tp.vec.size()-k-1]=tp.vec[tp.vec.size()-i-k-1];
			}
			for(unsigned int k=0; k<i;++k)
				tp.vec[k]=0;
			result+=tp; //should be multiplied 
		}
		return result;
	}
	bool operator == (TBigUInt a){
		if (vec.size()!=a.vec.size())
			return false;
		else
			for(int i=vec.size()-1; i>=0; --i)
				if(vec[i]!=a.vec[i])
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
		if (vec.size()> a.vec.size())
			return true;
		else if (vec.size()<a.vec.size())
			return false;
		else{
			for(int i=vec.size()-1; i>=0; --i)
				if(vec[i]>a.vec[i])
					return true;
				else if (vec[i]<a.vec[i])
					return false;
		}
		return false;
	}
	bool operator<(TBigUInt a){
		return a>*this;
	}
	bool operator>(unsigned char a){
	TBigUInt tp;
	tp.vec.push_back(a);
	return *this>tp;
	}
	bool operator<(unsigned char a){
		return !(*this>a);
	}
	TBigUInt operator/(TBigUInt a){
		TBigUInt result;
		TBigUInt temp;
		if(a.vec.size()>vec.size() || (a.vec.size()==vec.size() && a.vec[vec.size()-1]>vec[vec.size()-1]))
			return result;
		vector<unsigned char>:: iterator pos=result.vec.begin();
		vector<unsigned char>:: iterator pos1=temp.vec.begin();
		for(int i=vec.size()-1; i>=0;--i){
			if(i==vec.size()-1){
				while(a>temp){
				pos1=temp.vec.insert(pos1,vec[i]);
				--i;
				}
			++i;
			}
			else{
				pos1=temp.vec.insert(pos1,vec[i]);
			}
			if(temp<a){
				pos=result.vec.insert(pos, 0);
				continue;
			}
			if(temp.vec[temp.vec.size()-1]==0)
				temp.vec.resize(temp.vec.size()-1);
			unsigned char k=0;
			while(temp>=a){
				temp=temp-a;
				++k;
			}
			pos=result.vec.insert(pos, k);
		}
		return result;
	}

	unsigned char operator%(unsigned char a){
		TBigUInt tp;
		TBigUInt tp1;
		tp.vec.push_back(a);
		tp1=*this/tp;
		tp=*this-(tp1*tp);
		return tp.vec[0];
	}
	//prefix
	void operator++(){
		if(vec.empty()){
			vec.push_back(1);
			return;
		}
		for(int i=0; ; ++i){
			if(vec[i]<(base-1)){
				vec[i]+=1;
				break;
			}
			else{
				vec[i]=0;
				if(vec.size()==(i+1)){
					vec.push_back(1);
					break;
				}
			}
		}
	}
	//postfix
	void operator++(int){
		++*this;
	}
	//prefix
	void operator--(){
		if(vec.size()==1 && vec[0]==0)
			return;
			if(vec[0]>0){
				vec[0]-=1;
				return;
			}
			else{
				vec[0]=(base-2);
				for(unsigned int i=1; i<vec.size();++i){
					if(vec[i]>0){
						vec[i]-=1;
						break;
					}
					vec[i]=base-2;
				}
			}
	}
	//postfix
	void operator--(int){
		--*this;
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


	TBigUInt KaratsubaMultiply(const TBigUInt& a, const TBigUInt& b){//- ��������� ������� �����, ������������� � ������� ��������� ��������
		//if (a.vec.size()<30 ||a.vec.size()!=b.vec.size())
		//	return a*b;
		int p=a.vec.size()/2;
		TBigUInt a1,a2,b1,b2;
		for (unsigned int i=p; i<a.vec.size(); ++i)
			a1.vec.push_back(a.vec[i]);
		for (unsigned int i=p; i<b.vec.size(); ++i)
			b1.vec.push_back(b.vec[i]);
		for(unsigned int i=0; i<p; i++){
			a2.vec.push_back(a.vec[i]);
			b2.vec.push_back(b.vec[i]);
		}
		TBigUInt result,tp,tp1,tp2;
		TBigUInt power (base);
		tp1=a1*b1;
		tp2=b2*a2;
		result=tp2;
		tp=(a1+a2)*(b1+b2)-tp2-tp1;
		for(int i=1; i<p; ++i)
			power=power*base;
		tp=tp*power;
		result+=tp;
		tp1=tp1*power;
		tp1=tp1*power;
		result+=tp1;
		return result;
	}
};


ostream& operator<<(ostream& out, const TBigUInt& num){
	int dec=10;
	vector<unsigned char> printvec;
	TBigUInt a(dec);
	TBigUInt tp;
	tp=num;
	while(tp>0){
		unsigned char c=tp%dec;
		printvec.push_back(c);
		tp/=a;
	}
	vector<unsigned char>::const_reverse_iterator pos=printvec.rbegin(),
											end=printvec.rend();
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


int main(){	
	TBigUInt a(1243524141);
	TBigUInt b(82893);
	TBigUInt c;
	++a;
	cout<<a<<endl;
	a++;
	cout<<a<<endl;
	--a;
	cout<<a<<endl;
	a--;
	cout<<a<<endl;
	c=a+b;
	cout<<c<<endl;
	c=a-b;
	cout<<c<<endl;
	c=a*b;
	cout<<c<<endl;
	c=a/b;
	cout<<c<<endl;
	cout<<b<<endl;
	string str;
	for (int i=1; i<35; i++)
		str.push_back((char)((i*241*123)%10+(int)'0'));
	TBigUInt aa(str);
	cout<<aa<<endl;
	str.clear();
	for (int i=1; i<20; i++)
		str.push_back((char)((i*21*23)%10+(int)'0'));
	TBigUInt bb(str);
	cout<<bb<<endl;
	TBigUInt cc;
	++aa;
	cout<<aa<<endl;
	aa++;
	cout<<aa<<endl;
	--aa;
	cout<<aa<<endl;
	aa--;
	cout<<aa<<endl;
	cc=aa+bb;
	cout<<cc<<endl;
	cc=aa-bb;
	cout<<cc<<endl;
	cc=aa*bb;
	cout<<cc<<endl;
	cc=aa/bb;
	cout<<cc<<endl;
	str.clear();
	for (int i=1; i<120; i++)
		str.push_back((char)((i*241*123)%10+(int)'0'));
	TBigUInt aaa(str);
	TBigUInt bbb(str);
	cout<<aaa<<endl;
	cout<<aaa*bbb<<endl;
	cout<<aaa.KaratsubaMultiply(aaa,bbb)<<endl;
	// comparision of Karatsuba and usual methods of multiplying
	//string str;
	//int num=10;
	//for(int i=1; i<num; i++)
	//		str.push_back((char)(((i*15)%7)+(int)'0'));
	//clock_t t;
	//TBigUInt a(str);
	//TBigUInt b(str);
	////long long power=static_cast<long long >(pow(256.0, 10));
	//for (int i=1; i<7; i++){
	//	for(int k=num; k<num*10; ++k)
	//		a.vec.push_back((char)(i*k*14*267*13)%256);
	//	num*=10;
	//	b=a;
	//	if (i<2)
	//		cout<<a;
	//	t=clock();
	//	a*b;
	//	t=clock()-t;
	//	cout << "Usual method for num="<<num<<" time: "<<(float)t/CLOCKS_PER_SEC<<endl;
	//	t=clock();
	//	a.KaratsubaMultiply(a,b);
	//	t=clock()-t;
	//	cout << "Karatsuba method for num="<<num<<" time: "<<(float)t/CLOCKS_PER_SEC<<endl;
	//	str.clear();
	//}
	return 0;
}