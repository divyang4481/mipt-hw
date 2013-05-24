#include <iostream>
#include <time.h>
using namespace std;

struct TTime
{
	int sec;
	int min;
	int hour;
	int day;
	int wday;
	int month;
	int year;
	TTime(): sec(0), min(0), hour(0), day(0), wday(0), month(0), year(0) {}
	void operator =(struct tm *time)
	{
		sec = time->tm_sec;
		min = time->tm_min;
		hour = time->tm_hour;
		day = time->tm_mday;
		wday = time->tm_wday;
		month = time->tm_mon;
		year = time->tm_year;
	}
};

class TTimeSpan
{
	time_t timer;
public:
	TTimeSpan(): timer(0)
	{}
	TTimeSpan (time_t t): timer(t)
	{}
	TTimeSpan (int year, int day, int h, int m, int s)
	{
		timer = s;
		timer += m * 60;
		timer += h * 60 * 60;
		timer += day * 24 * 60 * 60;
		timer += year * 365 * 24 * 60 * 60;
	}
	TTimeSpan (int h, int m, int s)
	{
		timer = s;
		timer += m * 60;
		timer += h * 60 * 60;
	}
	int Year () const
	{
		time_t tmp = timer;
		return (tmp / (24*3600*365));
	}
	int Day () const
	{
		time_t tmp = timer;
		return (tmp / (24*60*60)) % 365;
	}
	int Hour () const
	{
		time_t tmp = timer;
		return (tmp / (60*60)) % 24;
	}
	int Minute () const
	{
		time_t tmp = timer;
		return (tmp / 60) % 60;
	}
	int Second () const
	{
		time_t tmp = timer;
		return tmp % 60;
	}
	time_t GetUnixTimestamp() const
	{
		return timer;
	}
	TTimeSpan& operator= (TTimeSpan& other)
	{
		timer = other.GetUnixTimestamp();
		return *this;		
	}
	TTimeSpan operator+ (const TTimeSpan &delta)
	{
		return TTimeSpan(GetUnixTimestamp() + delta.GetUnixTimestamp());
	}
	TTimeSpan operator- (const TTimeSpan &delta)
	{
		return TTimeSpan(GetUnixTimestamp() - delta.GetUnixTimestamp());
	}
	bool operator< (const TTimeSpan &other)
	{
		return GetUnixTimestamp() < other.GetUnixTimestamp();
	}
};

ostream& operator<< (ostream& out, const TTimeSpan& date)
{
	out << date.Hour() << ":" << date.Minute() << ":" <<
		date.Second() << " " << date.Day() << "." << date.Year();
	return out;
}
istream& operator>> (istream& in, TTimeSpan& date)
{
	int year, day, hour, min, sec;
	cout << "Year: ";
	in >> year;
	cout << "Day: ";
	in >> day;
	cout << "Hour: ";
	in >> hour;
	cout << "Minute: ";
	in >> min;
	cout << "Second: ";
	in >> sec;
	TTimeSpan temp (year, day, hour, min, sec);
	date = temp;
	return in;
}

class TDateTime
{
	TTime mtime;
public:
	TDateTime ()
	{
		time_t tmr;
		struct tm * timeinfo;
		time(&tmr);
		timeinfo = localtime(&tmr);
		mtime = timeinfo;
	}
	TDateTime (time_t t)
	{
		struct tm * timeinfo;
		timeinfo = localtime(&t);
		mtime = timeinfo;
	}
	TDateTime (int year, int month, int day, int h, int m, int s)
	{
		mtime.day = day;
		mtime.hour = h;
		mtime.min = m;
		mtime.month = month-1;
		mtime.sec = s;
		mtime.year = year-1900;
		time_t t = GetUnixTimestamp();
		struct tm * timeinfo = localtime(&t);
		mtime.wday = timeinfo->tm_wday;
	}
	TDateTime (int year, int month, int day)
	{
		mtime.day = day;
		mtime.month = month-1;
		mtime.year = year-1900;
		time_t t = GetUnixTimestamp();
		struct tm * timeinfo = localtime(&t);
		mtime.wday = timeinfo->tm_wday;
	}
	TDateTime (string s)
	{
		mtime.hour = ((int)s[0] - '0')* 10 + (int)s[1] - '0';
		mtime.min = ((int)s[3] - '0')* 10 + (int)s[4] - '0';
		mtime.sec = ((int)s[6] - '0')* 10 + (int)s[7] - '0';
		mtime.day = ((int)s[9] - '0')* 10 + (int)s[10] - '0';
		mtime.month = ((int)s[12] - '0')* 10 + (int)s[13] - '0' - 1;
		mtime.year = ((int)s[15] - '0')* 1000 + ((int)s[16] - '0') * 100 + ((int)s[17] -'0')* 10 + (int)s[18] - '0' - 1900;
	}
	int Year () const
	{
		return mtime.year + 1900;
	}
	int Month () const
	{
		return mtime.month + 1;
	}
	int Day () const
	{
		return mtime.day;
	}
	int Hour () const
	{
		return mtime.hour;
	}
	int Minute () const
	{
		return mtime.min;
	}
	int Second () const
	{
		return mtime.sec;
	}
	int DayOfWeek () const
	{
		return mtime.wday+1;
	}
	time_t GetUnixTimestamp() const
	{
		time_t t;
		time(&t);
		struct tm * timeptr;
		timeptr = localtime(&t);
		timeptr->tm_hour = mtime.hour;
		timeptr->tm_mday = mtime.day;
		timeptr->tm_min = mtime.min;
		timeptr->tm_mon = mtime.month;
		timeptr->tm_sec = mtime.sec;
		timeptr->tm_wday = mtime.wday;
		timeptr->tm_year = mtime.year;
		return mktime(timeptr);
	}
	static TDateTime Now ()
	{
		TDateTime a;
		return a;		
	}
	bool operator< (const TDateTime &other)
	{
		return GetUnixTimestamp() < other.GetUnixTimestamp();
	}
	TDateTime& operator= (const TDateTime &other)
	{
		mtime.day = other.Day();
		mtime.hour = other.Hour();
		mtime.min = other.Minute();
		mtime.month = other.Month() - 1;
		mtime.sec = other.Second();
		mtime.wday = other.DayOfWeek() - 1;
		mtime.year = other.Year() - 1900;
		return *this;
	}
	TDateTime operator+ (const TTimeSpan &delta)
	{
		return TDateTime(GetUnixTimestamp() + delta.GetUnixTimestamp());
	}
	TDateTime operator- (const TTimeSpan &delta)
	{
		return TDateTime(GetUnixTimestamp() - delta.GetUnixTimestamp());
	}
	TTimeSpan operator- (const TDateTime &other)
	{
		return TTimeSpan(GetUnixTimestamp() - other.GetUnixTimestamp());
	}
};

ostream& operator<< (ostream& out, const TDateTime& date)
{
	out << date.Hour() << ":" << date.Minute() << ":" <<
		date.Second() << " " << date.Day() << "." <<
		date.Month() << "." << date.Year();
	return out;
}
istream& operator>> (istream& in, TDateTime& date)
{
	int year, month, day, hour, min, sec;
	cout << "Year: ";
	in >> year;
	cout << "Month: ";
	in >> month;
	cout << "Day: ";
	in >> day;
	cout << "Hour: ";
	in >> hour;
	cout << "Minute: ";
	in >> min;
	cout << "Second: ";
	in >> sec;
	TDateTime temp (year, month, day, hour, min, sec);
	date = temp;
	return in;
}

int main()
{
	TDateTime time1;
	cout<<"CurTime:  "<<time1<<endl;
	TDateTime time2(2000, 12, 01);
	cout<<"time2(2000, 12, 01):  "<<time2<<endl;
	TDateTime time3("12:40:15 01.12.1990");
	cout<<"12:40:15 01.12.1990:  "<<time3<<endl;
	time_t t1 = time1.GetUnixTimestamp();
	TDateTime time4(t1);
	cout<<time4<<endl;
	TDateTime time5(2000, 12, 1, 15, 15, 16);
	cout<< "time5(2000, 12, 1, 15, 15, 16):  "<< time5<<endl;
	time2 = time4;
	cout<< "time2 = time4 => time2:  "<<time2<<endl;
	cout<<time1 <<" < "<< time3<<":  " <<(time1 < time3)<<endl;
	TTimeSpan sptime1(12, 2, 5);
	cout<<time1<<" + 12:2:5 :  "<<time1 + sptime1<<endl;
	TTimeSpan sptime2(0, 23, 11, 3, 4);
	cout<<"sptime2(0, 23, 11, 3, 4): "<<sptime2<<endl;
	cout<<time3<<" + 23 11:03:04:  "<<time3 + sptime2<<endl;
	cout<<time5<< " - "<< time3 << ":  "<< (time5-time3)<<endl;
	cout<<sptime2<<" - "<<sptime1<<" :  "<<(sptime2-sptime1)<<endl;
	cout<<sptime1<<" < "<<sptime2<<" :  "<<(sptime1<sptime2)<<endl;
        TDateTime dt = TDateTime::Now();
        cout << dt << endl;

        TTimeSpan span(1, 31, 0, 0, 0);
        TDateTime dt2 = dt + span;
        cout << dt2 << endl;

        cout << (dt + span) << endl;

        dt = dt + span;
        cout << dt << endl;

        dt = dt - span;
        cout << dt << endl;
	return 0;
}