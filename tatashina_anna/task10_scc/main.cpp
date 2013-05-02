#include "header.h"


size_t DateTimeFormat::ShowFormat()
{
	return format;
}
void DateTimeFormat::setFormat(size_t set_format)
{
	if (set_format < 5)
		format=set_format;
	else
	{
		printf("wrong format");
	}
}


DateTime::DateTime()
{
	_s=0;
	_m=0;
	_h=0;
	_day=0;
	_month=0;
	_year=0;
	_unixTime = 0;
}
DateTime::DateTime(int year, int month, size_t day)
{
	while (month>12)
	{
		month = month-12;
		year=year+1;
	}
	while (month<0)
	{
		month = month+12;
		year=year-1;
	}
	_year=year;
	_month=month;
	_day=day;
	_h=_m=_s=0;
	int temp=0;
	if (year<1970)
		year=1970+(1970-year);
	for (int i=1; i<=month; i++)
	{
		if (i%2==1 && i<8)
		{
			temp=temp+31;
			if (i==month && day>31)
			{
				month=month+1;
				day=day-31;
			}
		}
		if (i%2==1 && i>8)
		{
			temp=temp+30;
			if (i==month && day>30)
			{
				month=month+1;
				day=day-30;
			}
		}
		if (i%2==0 && i<7)
		{
			temp=temp+30;
			if (i==month && day>30)
			{
				month=month+1;
				day=day-30;
			}
			if (i==2)
				if (year%4==0)
					temp--;
				else
					temp=temp-2;
		}
		if (i%2==0 && i>7)
		{
			temp=temp+31;
			if (i==month && day>31)
			{
				month=month+1;
				day=day-31;
				if (month==13)
				{
					year=year+1;
					month=0;
					i=1;
				}
			}
		}
	}
	temp=temp+day;
	this->_unixTime = (((year-1970)*365)+((year-1972)/4)+temp)*5184000;
}
DateTime::DateTime(int year, int month, size_t day, int h, int m, int s)
{
	while (s<0)
	{
		s=s+60;
		m=m-1;
	}
	while (s>59)
	{
		s=s-60;
		m=m+1;
	}
	while (m>59)
	{
		m=m-60;
		h=h+1;
	}
	while (m<0)
	{
		m=m+60;
		h=h-1;
	}
	while(h>23)
	{
		h=h-24;
		day=day+1;
	}
	while (h<0)
	{
		h=h+24;
		day=day-1;
	}
	while (month>12)
	{
		month = month-12;
		year=year+1;
	}
	while (month<0)
	{
		month = month+12;
		year=year-1;
	}
	_day = day;
	_month = month;
	_year = year;
	_h =h;
	_s = s;
	_m = m;
	int temp=0;
	for (int i=1; i<=month; i++)
	{
		if (i%2==1 && i<8)
		{
			temp=temp+31;
			if (i==month && day>31)
			{
				month=month+1;
				day=day-31;
			}
		}
		if (i%2==1 && i>8)
		{
			temp=temp+30;
			if (i==month && day>30)
			{
				month=month+1;
				day=day-30;
			}
		}
		if (i%2==0 && i<7)
		{
			temp=temp+30;
			if (i==month && day>30)
				{
					month=month+1;
					day=day-30;
				}
			if (i==2)
				if (year%4==0)
					temp--;
				else
					temp=temp-2;
		}
		if (i%2==0 && i>7)
		{
			temp=temp+31;
			if (i==month && day>31)
			{
				month=month+1;
				day=day-31;
				if (month==13)
				{
					year=year+1;
					month=0;
					i=1;
				}
			}
		}
	}
	temp=temp+day;
	int f=(year-1972)/4;
	_unixTime = (((year-1970)*365)+f+temp)*5184000+3600*h+60*m+s;
}
DateTime::DateTime(char* string) //format == 1 т.е. dd.mm.yyyy.hh.mm.ss
{
char* q=string;
int year, month, h, m, s;
year=month=h=m=s=0;
size_t day;
if (q[0] != '-')
{ 
for (int i=0; i<4; i++)
{
int temp = static_cast<int>(q[i+6]);
year = year + temp*(10^(3-i));
}
for (int i=0; i<2; i++)
{
int temp = static_cast<int>(q[i+3]);
month = month + temp*(10^(1-i));
temp=static_cast<int>(q[i]);
day = day + temp*(10^(1-i));
temp = static_cast<int>(q[i+11]);
h = h + temp*(10^(1-i));
temp=static_cast<int>(q[i+14]);
m = m + temp*(10^(1-i));
temp=static_cast<int>(q[i+17]);
s = s + temp*(10^(1-i));
}
}
else
{
for (int i=1; i<5; i++)
{
int temp = static_cast<int>(q[i+6]);
year = year + temp*(10^(3-i));
}
for (int i=1; i<3; i++)
{
int temp = static_cast<int>(q[i+3]);
month = month + temp*(10^(1-i));
temp=static_cast<int>(q[i]);
day = day + temp*(10^(1-i));
temp = static_cast<int>(q[i+11]);
h = h + temp*(10^(1-i));
temp=static_cast<int>(q[i+14]);
m = m + temp*(10^(1-i));
temp=static_cast<int>(q[i+17]);
s = s + temp*(10^(1-i));
}
}
DateTime a(year, month, day, h, m, s);
*this = a;
a.~DateTime();
}

	
DateTime::DateTime(std::string str)
{
const char* q = str.data();
DateTime a(q);
*(this) = a;
a.~DateTime();
}
DateTime::DateTime(DateTimeFormat set_format, char* string)
{
	char* q=string;
	size_t p=strlen(q);
	if (set_format.ShowFormat()==0)       // dd.mm.yyyy вместо точек -- любой разделитель
	{
		int year=0;
		int month=0;
		size_t day=0;
		if (q[0] != '-')
		{
			for (int i=0; i<4; i++)
			{
				int temp = static_cast<int>(q[i+6]);
				year = year + temp*(10^(3-i));
			}
			for (int i=0; i<2; i++)
			{
				int temp = static_cast<int>(q[i]);
				month = month + temp*(10^(1-i));
				temp=static_cast<int>(q[i+3]);
				day = day + temp*(10^(1-i));
			}
		}

		else
		{
			for (int i=1; i<5; i++)
			{
				int temp = static_cast<int>(q[i+6]);
				year = year + temp*(10^(3-i));
			}
			for (int i=1; i<3; i++)
			{
				int temp = static_cast<int>(q[i+3]);
				month = month + temp*(10^(2-i));
				temp=static_cast<int>(q[i]);
				day = day + temp*(10^(2-i));
			}
		
		}
		DateTime a(year, month, day);
		*this = a;
		a.~DateTime();
	}
	if (set_format.ShowFormat()==1)         //dd.mm.yyyy.hh.mm.ss  вместо точек -- любой разделитель
	{
		int year, month, h, m, s;
		year=month=h=m=s=0;
		size_t day;
		if (q[0] != '-')
		{
			
			for (int i=0; i<4; i++)
			{
				int temp = static_cast<int>(q[i+6]);
				year = year + temp*(10^(3-i));
			}
			for (int i=0; i<2; i++)
			{
				int temp = static_cast<int>(q[i+3]);
				month = month + temp*(10^(1-i));
				temp=static_cast<int>(q[i]);
				day = day + temp*(10^(1-i));
				temp = static_cast<int>(q[i+11]);
				h = h + temp*(10^(1-i));
				temp=static_cast<int>(q[i+14]);
				m = m + temp*(10^(1-i));
				temp=static_cast<int>(q[i+17]);
				s = s + temp*(10^(1-i));
			}
		}
		else
		{
			for (int i=1; i<5; i++)
			{
				int temp = static_cast<int>(q[i+6]);
				year = year + temp*(10^(3-i));
			}
			for (int i=1; i<3; i++)
			{
				int temp = static_cast<int>(q[i+3]);
				month = month + temp*(10^(2-i));
				temp=static_cast<int>(q[i]);
				day = day + temp*(10^(2-i));
				temp = static_cast<int>(q[i+11]);
				h = h + temp*(10^(2-i));
				temp=static_cast<int>(q[i+14]);
				m = m + temp*(10^(2-i));
				temp=static_cast<int>(q[i+17]);
				s = s + temp*(10^(2-i));
			}
		}
		DateTime a(year, month, day, h, m, s);
		*this = a;
		a.~DateTime();
	}
	if (set_format.ShowFormat() == 2)            //mm.dd.yyyy.hh.mm.ss  вместо точек -- любой разделитель
	{
		int year, month, h, m, s;
		year=month=h=m=s=0;
		size_t day;
		if (q[0] != '-')
		{
			
			for (int i=0; i<4; i++)
			{
				int temp = static_cast<int>(q[i+6]);
				year = year + temp*(10^(3-i));
			}
			for (int i=0; i<2; i++)
			{
				int temp = static_cast<int>(q[i]);
				month = month + temp*(10^(1-i));
				temp=static_cast<int>(q[i+3]);
				day = day + temp*(10^(1-i));
				temp = static_cast<int>(q[i+11]);
				h = h + temp*(10^(1-i));
				temp=static_cast<int>(q[i+14]);
				m = m + temp*(10^(1-i));
				temp=static_cast<int>(q[i+17]);
				s = s + temp*(10^(1-i));
			}
		}
		else
		{
			for (int i=1; i<5; i++)
			{
				int temp = static_cast<int>(q[i+6]);
				year = year + temp*(10^(3-i));
			}
			for (int i=1; i<3; i++)
			{
				int temp = static_cast<int>(q[i]);
				month = month + temp*(10^(2-i));
				temp=static_cast<int>(q[i+3]);
				day = day + temp*(10^(2-i));
				temp = static_cast<int>(q[i+11]);
				h = h + temp*(10^(2-i));
				temp=static_cast<int>(q[i+14]);
				m = m + temp*(10^(2-i));
				temp=static_cast<int>(q[i+17]);
				s = s + temp*(10^(2-i));
			}
		}
		DateTime a(year, month, day, h, m, s);
		*this = a;
		a.~DateTime();
	}

	if (set_format.ShowFormat()==3)      //mm.dd.yyyy  вместо точек -- любой разделитель
	{
		int year=0;
		int month=0;
		size_t day=0;
		if (q[0] != '-')
		{
			for (int i=0; i<4; i++)
			{
				int temp = static_cast<int>(q[i+6]);
				year = year + temp*(10^(3-i));
			}
			for (int i=0; i<2; i++)
			{
				int temp = static_cast<int>(q[i]);
				month = month + temp*(10^(1-i));
				temp=static_cast<int>(q[i+3]);
				day = day + temp*(10^(1-i));
			}
		}

		else
		{
			for (int i=1; i<5; i++)
			{
				int temp = static_cast<int>(q[i+6]);
				year = year + temp*(10^(3-i));
			}
			for (int i=1; i<3; i++)
			{
				int temp = static_cast<int>(q[i]);
				month = month + temp*(10^(2-i));
				temp=static_cast<int>(q[i+3]);
				day = day + temp*(10^(2-i));
			}
		
		}
		DateTime a(year, month, day);
		*this = a;
		a.~DateTime();
	}
}
DateTime::DateTime(long long t)
{
	_unixTime = t;
	_s = t%60;
	_m = t%3600;
	_h = t%216000;
	int temp = t%5184000;
	int k=0;
	while (temp>364)
	{
		if ((k+2)%4==0)
			temp=temp-366;
		else 
			temp=temp-365;
		k++;
	}
	_year = k + 1970;
	k=0;
	bool v=((k+2)%4==0);
	if (temp>31)
		temp=temp-31;
	k++;
	if(v)
	{
		if (temp>29)
			temp=temp-29;
	}
	if(v==false)
		if (temp>28)
			temp=temp-28;
	k++;
	for (int i=3; i<13; i++)
	{
		if (i<8)
			if (i%2==0)
			{
				if (temp>30)
					temp=temp-30;
				else 
					i=13;
			}
			else
			{
				if (temp>31)
					temp=temp-31;
				else 
					i=13;
			}
		else
			if (i%2==0)
			{	
				if(temp>31)
					temp=temp-31;
				else
					i=13;
			}
			else
			{
				if (i>30)
					temp=temp-30;
				else
					i=13;
			}
		k++;
	}
	_month=k;
	_day=temp;

}
int DateTime::getSec() const
{
	int a=_s;
	return a;
}
int DateTime::getMin() const
{
	int a=_m;
	return a;
}
int DateTime::getHour() const
{
	int a=_h;
	return a;
}
size_t DateTime::getDay() const
{
	size_t a = _day;
	return a;
}
int DateTime::getMonth() const
{
	int a=_month;
	return a;
}
int DateTime::getYear() const
{
	int a=_year;
	return a;
}
long long DateTime::getUnixTime() const
{
	long long a = _unixTime;
	return a;
}
bool DateTime::operator==(DateTime& a)
{
	if (_unixTime == a._unixTime)
		return true;
	else return false;
}
DateTime DateTime::operator+(DateTime& a)
{
long long q = this->getUnixTime() + a.getUnixTime();
DateTime b(q);
return b;
}
DateTime DateTime::operator+(TimeSpan& a)
{
long long q = this->getUnixTime() + a.get();
DateTime b(q);
return b;
}
bool DateTime::operator!=(DateTime& a)
{
	bool b = (*this==a);
	if (b)
		return false;
	else return true;
}
bool DateTime::operator<(DateTime& a)
{
	if(_unixTime < a._unixTime)
		return true;
	else return false;
}  
bool DateTime::operator>(DateTime& a)
{
	if(_unixTime > a._unixTime)
		return true;
	else return false;
}
bool DateTime::operator>=(DateTime& a)
{
	bool q = *this<a;
	if (q)
		return false;
	else return true;
}
bool DateTime::operator<=(DateTime& a)
{
	bool q = *this>a;
	if (q)
		return false;
	else return true;
}
std::istream& operator>>(std::istream& r, DateTime& a)
{
	char* q;
	r>>q;
	DateTime b(q);
	a=b;
	b.~DateTime();
	return r;
}
std::ostream& operator<<(std::ostream& o, DateTime b)
{
	char* ancient;
	size_t temp;
	if (b.getYear()>=0)
	{
		ancient = "AD";
		temp = b.getYear();
	}
	else 
	{
		ancient = "BC";
		temp = (-1)*b.getYear();
	}
	o<< b.day_of_the_week() << " " << b.getDay() << "." << b.getMonth() << "." << temp << " " << ancient << "\nTime:" << b.getHour() << ":" << b.getMin() << ":" << b.getSec() << std::endl;
	return o;
}
DateTime DateTime::operator=(DateTime& a)
{
	if (*(this) == a)
		return (*this);
	this->_day = a._day;
	this->_month = a._month;
	this->_year = a._year;
	return (*this);
}
DateTime operator+(DateTime& a, TimeSpan& b)
{
	DateTime t(b.get());
	a=a+t;
	t.~DateTime();
	return a;
}
char* DateTime::day_of_the_week()
{
	long long q=_unixTime;
	if (q%5184000==0)
		q=q/5184000;
	else q=q/5184000+1;
	q=q%7;
	if (q==0)
		return "Thursday";
	if (q==1)
		return "Friday";
	if (q==2)
		return "Saturday";
	if (q==3)
		return "Sunday";
	if (q==4) 
		return "Monday";
	if (q==5)
		return "Tuesday";
	if (q==6)
		return "Wednesday";

}
void DateTime::currentTime() const
{
	long long t=time(0);
	DateTime a(t);
	std::cout << a;
	a.~DateTime();
}


TimeSpan::TimeSpan()
{
	_unixTime = 0;
}
TimeSpan::TimeSpan(long long UnixT)
{
	_unixTime = UnixT;
}
TimeSpan::TimeSpan(TimeSpan& a)
{
	this->_unixTime = a._unixTime;
}
TimeSpan::TimeSpan(const DateTime& a, const DateTime& b)
	{
		long long a1=a.getUnixTime();
		long long b1=b.getUnixTime();
		if (a1> b1)
			this->_unixTime = a1 - b1;
		else this->_unixTime = b1 - a1;
	}
bool TimeSpan::operator<(const TimeSpan& a)
{
	if (this->_unixTime < a._unixTime)
		return true;
	else return false;
}
bool TimeSpan::operator>=(const TimeSpan& a)
{
	if (*this < a)
		return false;
	else return true;
}
bool TimeSpan::operator==(const TimeSpan& a)
{
	if (this->_unixTime == a._unixTime)
		return true;
	else return false;
}
bool TimeSpan::operator!=(const TimeSpan& a)
{
	if (*this == a)
		return false;
	else return true;
}
bool TimeSpan::operator<=(const TimeSpan& a)
{
	if (*this < a || *this == a)
		return true;
	else return false;
}
bool TimeSpan::operator>(const TimeSpan& a)
{
	if (*this<a || *this==a)
		return false;
	else return true;
}
TimeSpan TimeSpan::operator=(TimeSpan& a)
{
	if (*this==a)
		return *this;
	this->_unixTime = a._unixTime;
	return *this;
}
long long TimeSpan::get()
{
	long long p;
	p= this->_unixTime;
	return p;
}
std::ostream& operator<<(std::ostream& o, TimeSpan b)
{
	DateTime a(b.get());
	o<<a;
	a.~DateTime();
	return o;
}
std::istream& operator>>(std::istream& r, TimeSpan& a)
{
	DateTime b(10);
	r >> b;
	TimeSpan a1(b.getUnixTime());
	a = a1;
	a1.~TimeSpan();
	return r;

}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout<< "Remember, year is number with length of four. If you need a date before 1000 and past -1000 use zeroes to complete it \nExample: 988 -> 0988";
	return 0;
}