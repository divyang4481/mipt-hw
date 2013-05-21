#include <time.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class TTimeSpan
{
        time_t timer;
        /*bool LeapYear(int year)
        {
                if (year % 400 == 0)
                        return true;
                if (year % 4 == 0 && year % 100 != 0)
                        return true;
                return false;
        }*/
public:
        TTimeSpan():timer(0) {}
        TTimeSpan(size_t year, size_t yday, size_t h, size_t m, size_t s)
        {
                timer = s;
                timer += m * 60;
                timer += h * 60 * 60;
                timer += yday * 24 * 60 * 60;
                timer += year * 365 * 24 * 60 * 60;
        }
        TTimeSpan (size_t h, size_t m, size_t s)
        {
                timer = s;
                timer += m * 60;
                timer += h * 60 * 60;
        }
        TTimeSpan (time_t t)
        {
                timer = t;
        }
        time_t GetTime() const
        {
                return timer;
        }
        TTimeSpan& operator - (const TTimeSpan &oth)
        {
                time_t timer1 = GetTime(), timer2 = oth.GetTime(), timer3;
                if (timer2 > timer1)
                        timer3 = timer2 - timer1;
                else timer3 = timer1 - timer2;
                TTimeSpan* tmp = new TTimeSpan(timer3);
                return *tmp;
        }
        TTimeSpan& operator + (const TTimeSpan &oth)
        {
                time_t timer1 = GetTime(), timer2 = oth.GetTime(), timer3;
                timer3 = timer1 + timer2;
                TTimeSpan* tmp = new TTimeSpan(timer3);
                return *tmp;
        }
        TTimeSpan operator = (const TTimeSpan& oth)
        {
                timer = oth.GetTime();
                return *this;
        }
};

class TDateTime
{
        int year, month, day, h, m, s;
public:
        TDateTime()
        {
                time_t timer;
                time(&timer);
                tm* tmp;
                tmp = localtime(&timer);
                year = tmp->tm_year + 1900;
                month = tmp->tm_mon + 1;
                day = tmp->tm_mday;
                h = tmp->tm_hour;
                m = tmp->tm_min;
                s = tmp->tm_sec;
                
        }
        TDateTime (time_t t)
        {
                tm* tmp;
                tmp = localtime(&t);
                year = tmp->tm_year + 1900;
                month = tmp->tm_mon + 1;
                day = tmp->tm_mday;
                h = tmp->tm_hour;
                m = tmp->tm_min;
                s = tmp->tm_sec;
        }
       TDateTime (int Year, int Mon, int Day, int H, int M, int S): year(Year), month(Mon), day(Day), h(H), m(M), s(S) {};
        TDateTime (int Year, int Mon, int Day): year(Year), month(Mon), day(Day), h(0), m(0), s(0) {};
        TDateTime (string str)
        {
                sscanf(str.c_str(), "%d %d %d %d:%d:%d", &year, &month, &day, &h, &m, &s);
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
                return h;
        }
        int Minute() const
        {
                return m;
        }
        int Second () const
        {
                return s;
        }
        int DayOfWeek () const
        {
                time_t t = GetUnixTimestamp();
                tm* tmp = localtime(&t);
                return tmp -> tm_wday;
        }
        time_t GetUnixTimestamp() const //возвращает unix timestamp
        {
                time_t tmr;
                time(&tmr);
                tm* tmp;
                tmp = localtime(&tmr);
                tmp->tm_year = year - 1900;
                tmp->tm_mon = month - 1;
                tmp->tm_mday = day;
                tmp->tm_hour = h;
                tmp->tm_min = m;
                tmp->tm_sec = s;
                time_t timer = mktime(tmp);
                return timer;
        }
        static TDateTime Now () //статический метод, возвращающий текущую дату-время
        {
                TDateTime tmp;
                return tmp;
        }
        bool operator < (TDateTime b)
        {
                return GetUnixTimestamp() < b.GetUnixTimestamp();
        }
        TDateTime& operator = (TDateTime& oth)
        {
                year = oth.Year();
                month = oth.Month();
                day = oth.Day();
                h = oth.Hour();
                m = oth.Minute();
                s = oth.Second();
                return *this;
        }
        TDateTime& operator + (const TTimeSpan &delta) // возвращает дату-время, смещенную на delta
        {
                time_t t = GetUnixTimestamp();
                t += delta.GetTime();
                TDateTime* tmp = new TDateTime(t);
                return *tmp;
        }
        TDateTime& operator += (const TTimeSpan &delta) // возвращает дату-время, смещенную на delta
        {
                time_t t = GetUnixTimestamp();
                t += delta.GetTime();
                TDateTime tmp(t);
                *this = tmp;
                return *this;
        }

        TDateTime& operator - (const TTimeSpan &delta) // возвращает дату-время, смещенную на -delta
        {
                time_t t = GetUnixTimestamp();
                t -= delta.GetTime();
                TDateTime* tmp = new TDateTime(t);
                return *tmp;
        }
        TTimeSpan operator - (const TDateTime &oth) const // возвращает временной промежуток между двумя датами
        {
                time_t timer1 = GetUnixTimestamp(), timer2 = oth.GetUnixTimestamp(), timer;
                if (timer2 > timer1)
                        timer = timer2 - timer1;
                else timer = timer1 - timer2;
                TTimeSpan tmp(timer);
                return tmp;
        }
};
ostream& operator << (ostream& out, const TDateTime tdt)
{
        tm * tmp;
        time_t t = tdt.GetUnixTimestamp();
        tmp = localtime(&t);
        char str[80];
        strftime(str, 80, "%T %d %b %Y", tmp);
        out << str;
        return out;
}
istream& operator >> (istream& in, TDateTime& tdt)
{
        cout << "Format: YYYY MM DD HH:MM:SS" << endl;
        int year, mon, day, hour, min, sec;
        char c;
        in >> year >> mon >> day >> hour >> c >> min >> c >> sec;
        TDateTime tmp(year, mon, day, hour, min, sec);
        tdt = tmp;
        return in;
}

int main ()
{
        TDateTime T1;
        cout << "T1: " << T1 << endl;
        TDateTime T2(2001, 2, 3, 4, 5, 6);
        cout << "T2: " << T2 << endl;
        TTimeSpan S1(0,0,1,0,0);
        cout << "S1(0,0,1,0,0)" << endl << "T1 = T1 + S1" << endl;
        T1 = T1 + S1;
        cout << "T1: " << T1 << endl;
        S1 = T2 - T1;
        cout << "S1 = T2 - T1" << endl << "T1 + S1: " << T1 + S1 << endl;
        TTimeSpan S2;
        cout << "T1 + S2 = " << T1 + S2 << endl;
        TTimeSpan S3(1,0,0,0,0);
        TTimeSpan S4(2,0,0,0,0);
        TDateTime T3, T4;
        T3 += S3;
        T3 += S3;
        T4 += S4;
        cout << T3 << endl << T4 << endl;


        /*TDateTime dt1 = TDateTime::Now();
        cout << dt1 << endl;

        TTimeSpan sp(1, 1, 1, 1, 1);

        TDateTime dt2 = dt1 + sp;
        dt1 = dt1 + sp;
        TDateTime dt3 = dt2 - sp;
        dt1 = dt1 - sp;

        cout << dt1 << endl;
        cout << dt2 << endl;
        cout << dt3 << endl;

        */
        return 0;
}

