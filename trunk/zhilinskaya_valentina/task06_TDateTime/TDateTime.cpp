#include <iostream>
#include <time.h>
#include <ctime>
#include <string>

using namespace std;

time_t usual_form(int year, int month, int day, int h=0, int m=0, int s=0)
{
	time_t time = 0;
	int months[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
	for (int i = 1970; i < year; ++i)
		if ((((i % 4) == 0) && ((i % 100) != 0)) || ((i % 400) == 0)) //leap-year
			time += 60*60*24*366;
		else
			time += 60*60*24*365;
	if ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0)) {months[1] = 29;}
	for (int i = 0; i < (month -1); ++i)
		time += months[i]*3600*24;
	time += (day-1)*24*3600 + h*3600 + m*60 + s;
	return time;
}

class TTimeSpan
{
private:
	time_t _time;
public:
	TTimeSpan () {_time = 0;}
	TTimeSpan (const TTimeSpan &new_time) { _time=new_time._time;}
    TTimeSpan (time_t t) {_time=t;}
	TTimeSpan (int year, int month, int day, int h, int m, int s) { _time = usual_form(year + 1970, month + 1, day + 1, h, m, s);}
	int Day(){return _time/(24*60*60);}
    int Hour(){return _time/(60*60);}
    int Minute(){return _time/(60);}
    int Second(){return _time;}
	time_t GetUnixTimestamp() const {return (*this)._time;}
	friend istream& operator >> (istream& stream, TTimeSpan& time);
	friend ostream& operator << (ostream& stream, const TTimeSpan& time);
};
class TDateTime
{
private:
	time_t _time;
public:
	TDateTime () { _time = time(NULL) + 4*3600;}
	TDateTime (const TDateTime &new_time) { _time=new_time._time;}
	TDateTime (time_t t) { _time = t;}
	TDateTime (int year, int month, int day, int h, int m, int s) { _time = usual_form(year, month, day, h, m, s);}
	TDateTime (int year, int month, int day) {_time = usual_form(year, month, day);}
	TDateTime (string str) 
	{
		int len = str.length(), mas[7] = {0}, cur(0);
		for (int i = 0; i < len; ++i)
			if (((str[i]-'0') <= 9) || ((str[i]-'0') >= 0))
				mas[cur] = mas[cur]*10 + (str[i] - '0');
			else 
				cur++;
	}
	int Year () const { return gmtime(&_time)->tm_year + 1900;}
	int Month () const { return gmtime(&_time)->tm_mon + 1;}
	int Day () const { return gmtime(&_time)->tm_mday;}
	int Hour () const { return gmtime(&_time)->tm_hour;}
	int Minute () const { return gmtime(&_time)->tm_min;}
	int Second () const { return gmtime(&_time)->tm_sec;}
	int DayOfWeek () const { return !(gmtime(&_time)->tm_wday) ? 7 : gmtime(&_time)->tm_wday;}
	time_t GetUnixTimestamp() const { return usual_form(Year(), Month(), Day(), Hour(), Minute(), Second());}
	static TDateTime Now () { return TDateTime();}

	friend istream& operator >> (istream& stream, TDateTime& time);
	friend ostream& operator << (ostream& stream, const TDateTime& time);

	TDateTime operator+ (const TTimeSpan& delta) {
        return TDateTime(_time + delta.GetUnixTimestamp());
    }
    TDateTime operator- (const TTimeSpan& delta) { 
		return TDateTime(_time - delta.GetUnixTimestamp());
    }
    TTimeSpan operator- (const TDateTime& t) { 
		return TTimeSpan(this->_time - t._time);
    }
};

istream& operator >> (istream& stream, TDateTime& time) {
    int year, month, day, h, m, s;
    stream >> year >> month >> day >> h >> m >> s;
    time._time = usual_form(year, month, day, h, m, s);
    return stream;
}
ostream& operator << (ostream& stream, const TDateTime& time) {
	string mas[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
	stream << time.Year() << "y " << time.Month() << "m " << time.Day() << "d " << time.Hour() << "h " << time.Minute() << "m " << time.Second() << "s " << mas[time.DayOfWeek()-1];
	return stream;
}
istream& operator >> (istream& stream, TTimeSpan& time) {
    int year, month, day, h, m, s;
    stream >> year >> month >> day >> h >> m >> s;
    time._time = usual_form(year + 1970, month + 1, day + 1, h, m, s);
    return stream;
}
ostream& operator << (ostream& stream, const TTimeSpan& time) {
	stream << time._time;
    return stream;
}

int main()
{
	TDateTime time1;
	TDateTime time2(time1);
	TDateTime time3(0);
	TDateTime time4(1970,1,2);
	TDateTime time5(2013, 5, 8, 23, 55, 0);
	cout << time1 - time5 << '\n';
	cout << time1 << '\n'<< time2 << '\n'<< time3<< '\n'<< time4 <<'\n'<< time5 << '\n';
	TTimeSpan delta(3600000);
	cout << "delta 3600000 = "<<delta.Day()<<"days or "<< delta.Hour()<< "hours\n";
	cout << time1 + delta << '\n'<< time1 - delta << '\n'<< time2 - time1 <<'\n';
	cout << "Input time pls (year month day hour minute second) \n";
	cin >> time1;
	string mas[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
	cout << mas[time1.DayOfWeek()-1]<<'\n';
	cout << time1.GetUnixTimestamp()<<'\n';
	cout << "Input span pls (year month day hour minute second) \n";
	cin >> delta;
	cout <<"Your time + span = "<< time1 + delta <<'\n';
	cout << " delta.GetUnixTimestampe() "<< delta.GetUnixTimestamp();
	cout << "\n now "<<time1.Now() <<'\n';
	system ("pause");
	return 0;
}