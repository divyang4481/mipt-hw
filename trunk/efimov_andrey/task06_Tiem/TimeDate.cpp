#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
using namespace std;
const int GMTmod = 4;

class TTimeSpan{
	time_t interval;
public:
	TTimeSpan(): interval(0) {}
	TTimeSpan(time_t t): interval(t) {}
	TTimeSpan(const TTimeSpan &a): interval(a.interval) {}
	TTimeSpan(int year, int month, int day, int hh, int mm, int ss){
		tm temp;
		temp.tm_year = year + 70;
		temp.tm_mon = month;
		temp.tm_mday = day + 1;
		temp.tm_hour = hh + GMTmod;
		temp.tm_min = mm;
		temp.tm_sec = ss;
		interval = mktime(&temp);
	}
	TTimeSpan(int year, int day, int hh, int mm, int ss){
		int mlengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0) ) ++mlengths[1];
		int month = 0, dayt;
		if (day < mlengths[0]) dayt = day;
		else{
			for (;day >= mlengths[month]; day -= mlengths[month], ++month);
			dayt = day; 
		}
		tm temp;
		temp.tm_year = year + 70;
		temp.tm_mon = month;
		temp.tm_mday = day + 1;
		temp.tm_hour = hh + GMTmod;
		temp.tm_min = mm;
		temp.tm_sec = ss;
		interval = mktime(&temp);
	}
	time_t GetUnixTimestamp() const{
		return interval;
	}
	TTimeSpan operator- (const TTimeSpan &that){
		time_t ts1 = GetUnixTimestamp();
		time_t ts2 = that.GetUnixTimestamp();
		if (ts2 > ts1) swap(ts1, ts2);
		time_t tsr = ts1 - ts2;
		TTimeSpan temp(tsr);
		return temp;
	}
	TTimeSpan operator+ (const TTimeSpan &that){
		time_t ts1 = GetUnixTimestamp();
		time_t ts2 = that.GetUnixTimestamp();
		time_t tsr = ts1 + ts2;
		TTimeSpan temp(tsr);
		return temp;
	}
	TTimeSpan operator= (const TTimeSpan &that){
		this->interval = that.interval;
		return *this;
	}
};
class TDateTime{
public:
	int year, month, day, hour, minute, second;
public:
	TDateTime(){
		time_t current;
		time(&current);
		tm* temp;
		temp = localtime(&current);
		year = temp-> tm_year + 1900;
		month = temp-> tm_mon + 1;
		day = temp-> tm_mday;
		hour = temp-> tm_hour;
		minute = temp-> tm_min;
		second = temp-> tm_sec;
	}
	TDateTime(time_t time){
		tm* temp;
		temp = localtime(&time);
		year = temp-> tm_year + 1900;
		month = temp-> tm_mon + 1;
		day = temp-> tm_mday;
		hour = temp-> tm_hour;
		minute = temp-> tm_min;
		second = temp-> tm_sec;
	}
	TDateTime(int _year, int _month, int _day, int _hour, int _minute, int _second){
		year = _year;
		month = _month;
		day = _day;
		hour = _hour;
		minute = _minute;
		second = _second;
	}
	TDateTime(int _year, int _month, int _day){
		year = _year;
		month = _month;
		day = _day;
		hour = minute = second = 0;
	}
	TDateTime(const string &str){
		sscanf(str.c_str(), "%d:%d:%d %d.%d.%d",  &hour, &minute, &second, &day, &month, &year);
	}
	int Year() const{
		return year;
	}
	int Month() const{
		return month;
	}
	int Day() const{
		return day;
	}
	int Hour() const{
		return hour;
	}
	int Minute() const{
		return minute;
	}
	int Second() const{
		return second;
	}
	int DayOfWeek() const{
		time_t t = GetUnixTimestamp();
		tm* temp = localtime(&t);
		return temp->tm_wday;
	}
	time_t GetUnixTimestamp() const{
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
	static TDateTime Now(){
		TDateTime temp;
		return temp;
	}
	bool operator < (const TDateTime &other){
		return (GetUnixTimestamp()< other.GetUnixTimestamp());
	}
	TDateTime& operator=(const TDateTime& other){
		year = other.year;
		month = other.month;
		day = other.day;
		hour = other.hour;
		minute = other.minute;
		second = other.second;
		return *this;
	}
	TDateTime operator-(const TTimeSpan& delta){
		time_t t = GetUnixTimestamp();
		t -= delta.GetUnixTimestamp();
		TDateTime temp(t);
		return temp;
	}
	TDateTime operator+(const TTimeSpan& delta){
		time_t t = GetUnixTimestamp();
		t += delta.GetUnixTimestamp();
		TDateTime temp(t);
		return temp;
	}
	TTimeSpan operator-(const TDateTime& other){
		time_t dt1 = GetUnixTimestamp();
		time_t dt2 = other.GetUnixTimestamp();
		if (dt2>dt1) swap(dt1, dt2);
		time_t dtr = dt1 - dt2;
		TTimeSpan temp(dtr);
		return temp;
	}
};
ostream& operator<< (ostream& out, const TDateTime& src){
	tm* temp;
	time_t  t = src.GetUnixTimestamp();
	temp = localtime(&t);
	char text[80];
	strftime(text, 80, "%H:%M:%S %d.%m.%Y", temp);
	out << text;
	return out;
}
ostream& operator<< (ostream& out, const TTimeSpan& src){
	tm* temp;
	time_t t = src.GetUnixTimestamp();
	temp = gmtime(&t);
	out << temp->tm_hour << ':' << temp->tm_min << ':' << temp->tm_sec << ' ';
	out << temp->tm_mday - 1 << '.' << temp->tm_mon << '.' << temp->tm_year - 70;
	return out;
}
istream& operator>> (istream& in, TDateTime& a){
	cout << "Format: HH:MM:SS DD.MM.YYYY" << endl;
	int year, month, day, hour, minute, second;
	scanf("%d:%d:%d %d.%d.%d", &year, &month, &day, &hour, &minute, &second);
	TDateTime temp(year, month, day, hour, minute, second);
	a = temp;
	return in;
}
istream& operator>> (istream& in, TTimeSpan& a){
	cout << "Format: HH:MM:SS DD.MM.YYYY" << endl;
	int year, month, day, hour, minute, second;
	scanf("%d:%d:%d %d.%d.%d", &year, &month, &day, &hour, &minute, &second);
	TTimeSpan temp(year, month, day, hour, minute, second);
	a = temp;
	return in;
}

void I_DEMAND_A_TEST(){
	TDateTime D1("23:59:54 21.12.2012");
	TDateTime D2("06:18:44 03.03.2013");
	cout << "Time 1: " << D1 << endl;
	cout << "Time 2: " << D2 << endl;
	TTimeSpan S1=D2-D1;
	cout << "Span 1-2: " << S1 << endl;
	D1=TDateTime("23:22:11 31.12.2023");
	cout << "New Time 1:" << D1 << endl;
	S1=TTimeSpan(0,0,1,0,0);
	cout << "Added 1hr: " << D1+S1 << endl;
	D2=TDateTime();
	cout << "Nao: " << D2 << endl;
	S1=TTimeSpan(0,44,0,0,0);
	cout << "44 days to the past: " << D2-S1 << endl;
	cout << "and to the future: " << D2+S1 << endl;
	system("pause");
}

int main(){
	I_DEMAND_A_TEST();
	return 0;
}
