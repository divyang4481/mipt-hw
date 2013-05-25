#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
using namespace std;
class TTimeSpan
{

	time_t interval;
public:
	TTimeSpan():interval(0) {}
	TTimeSpan(time_t t):interval(t) {}
	TTimeSpan(const TTimeSpan &a):interval(a.interval){}
	TTimeSpan(int days, int hh, int mm, int ss)
	{
		
		interval = days*86400 + hh * 3600 + mm * 60 + ss;
	}
	/*TTimeSpan(int year, int yday, int hh, int mm, int ss)
	{
		int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0) ) ++days_in_months[1];
		int month = 0, day;
		if (yday < days_in_months[0]) day = yday;
		else
		{
			
			for (;yday >= days_in_months[month]; yday -= days_in_months[month], ++month);
			day = yday; 
		}

		tm temp;
		temp.tm_year = year + 70;
		temp.tm_mon = month;
		temp.tm_mday = day + 1;
		temp.tm_hour = hh + DIFFERENCE_FROM_GMT;
		temp.tm_min = mm;
		temp.tm_sec = ss;
		interval = mktime(&temp);
	}*/
	time_t GetUnixTimestamp() const
	{
		return interval;
	}
	TTimeSpan operator - (const TTimeSpan &a)
	{
		time_t int1 = GetUnixTimestamp();
		time_t int2 = a.GetUnixTimestamp();
		if (int2 > int1) swap(int1, int2);
		time_t _int = int1 - int2;
		TTimeSpan temp(_int);
		return temp;
	}
	TTimeSpan operator + (const TTimeSpan &a)
	{
		time_t int1 = GetUnixTimestamp();
		time_t int2 = a.GetUnixTimestamp();
		time_t _int = int1 + int2;
		TTimeSpan temp(_int);
		return temp;
	}
	TTimeSpan operator = (const TTimeSpan &a)
	{
		this->interval = a.GetUnixTimestamp();
		return *this;

	}

};
class TDateTime
{
public:
	int year, month, day, hour, minute, second;


public:
	TDateTime()
	{
		time_t current;
		time(&current);
		tm* temp;
		temp = localtime(&current);
		year = temp ->tm_year + 1900;
		month = temp ->tm_mon + 1;
		day = temp->tm_mday;
		hour = temp->tm_hour;
		minute = temp->tm_min;
		second = temp->tm_sec;
	}
	TDateTime(time_t time)
	{
		tm* temp;
		temp = localtime(&time);
		year = temp ->tm_year + 1900;
		month = temp ->tm_mon + 1;
		day = temp->tm_mday;
		hour = temp->tm_hour;
		minute = temp->tm_min;
		second = temp->tm_sec;
	}
	TDateTime(int _year, int _month, int _day, int _hour, int _minute, int _second)
	{
		year = _year;
		month = _month;
		day = _day;
		hour = _hour;
		minute = _minute;
		second = _second;
	}
	TDateTime(int _year, int _month, int _day)
	{
		year = _year;
		month = _month;
		day = _day;
		hour = minute = second = 0;
	}
	TDateTime(const string &str)
	{
		sscanf(str.c_str(), "%d:%d:%d %d. %d. %d",  &hour, &minute, &second, &day, &month, &year);
	}
	int Year() const
	{
		return year;
	}
	int Month() const
	{
		return month;
	}
	int Day() const
	{
		return day;
	}
	int Hour() const
	{
		return hour;
	}
	int Minute() const
	{
		return minute;
	}
	int Second() const
	{
		return second;
	}
	int DayOfWeek() const
	{
		time_t t = GetUnixTimestamp();
		tm* temp = localtime(&t);
		return temp->tm_wday;
	}
	time_t GetUnixTimestamp() const
	{
		tm temp;
		temp.tm_year = year - 1900;
		temp.tm_mon = month - 1;
		temp.tm_mday = day;
		temp.tm_hour = hour;
		temp.tm_min = minute;
		temp.tm_sec = second;
		time_t t = mktime(&temp);
		return t;
	}
	static TDateTime Now()
	{
		TDateTime temp;
		return temp;
	}
	bool operator < (const TDateTime &a)
	{
		return (GetUnixTimestamp() < a.GetUnixTimestamp());
	}
	TDateTime& operator=(const TDateTime& a)
	{
		year = a.year;
		month = a.month;
		day = a.day;
		hour = a.hour;
		minute = a.minute;
		second = a.second;
		return *this;
	}
	TDateTime operator-(const TTimeSpan& delta)
	{
		time_t t = GetUnixTimestamp();
		t -= delta.GetUnixTimestamp();
		TDateTime temp(t);
		return temp;
	}
	TDateTime operator+(const TTimeSpan& delta)
	{
		time_t t = GetUnixTimestamp();
		t += delta.GetUnixTimestamp();
		TDateTime temp(t);
		return temp;
	}
	TTimeSpan operator-(const TDateTime& a)
	{
		time_t int1 = GetUnixTimestamp(), int2 = a.GetUnixTimestamp();
		if (int2 > int1) swap(int1, int2);
		time_t _int = int1 - int2;
		TTimeSpan temp(_int);
		return temp;
	}
};
ostream& operator << (ostream& out, const TDateTime& a)
{
	tm* temp;
	time_t  t = a.GetUnixTimestamp();
	temp = localtime(&t);
	char buffer [80];
	strftime(buffer, 80, "%H:%M:%S %d.%m.%Y", temp);
	out << buffer;
	return out;
}
ostream& operator << (ostream& out, const TTimeSpan& a)
{
	tm* temp;
	time_t t = a.GetUnixTimestamp();
	temp = gmtime(&t);
	out << temp->tm_hour << ':' << temp->tm_min << ':' << temp->tm_sec << ' ' 
		<< temp->tm_mday - 1 << '.' << temp->tm_mon << '.' << temp->tm_year - 70;
	return out;
}
/*istream& operator >> (istream& in, TDateTime& a)
{
	cout << "HH:MM:SS DD.MM.YYYY" << endl;
	int year, month, day, hour, minute, second;
	scanf("%d:%d:%d %d.%d.%d", &year, &month, &day, &hour, &minute, &second);
	TDateTime temp(year, month, day, hour, minute, second);
	a = temp;
	return in;
}
istream& operator >> (istream& in, TTimeSpan& a)
{
	cout << "HH:MM:SS DD.MM.YYYY" << endl;
	int year, month, day, hour, minute, second;
	scanf("%d:%d:%d %d.%d.%d", &year, &month, &day, &hour, &minute, &second);
	TTimeSpan temp(year, month, day, hour, minute, second);
	a = temp;
	return in;
}*/

int main()
{
	/*TDateTime Date1("12:00:00 11.11.2011");
	TDateTime Date2("12:00:00 14.11.2011");
	cout << "Date1: "<< 
		Date1 << endl 
		<< "Date2: " << Date2 << endl;
	TTimeSpan a = Date1 - Date2;
	cout << "Date1 - Date2: " << a << endl;*/
	
	
	
	

	    TDateTime d1 = TDateTime::Now();
        cout << d1 << endl;

        TTimeSpan sp( 366, 1, 1, 1);
        TDateTime d2 = d1 + sp;
        TDateTime d3 = d2 - sp;
        cout << d2 << endl
            << d3 << endl;

        d1 = d1 + sp;
        cout << d1 << endl;
        d1 = d1 - sp;
        cout << d1 << endl;



	
	
	return 0;
}
