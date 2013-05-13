#include <time.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class TTimeSpan
{
        time_t timer;
        bool LeapYear(int year)
        {
                if (year % 400 == 0)
                        return true;
                if (year % 4 == 0 && year % 100 != 0)
                        return true;
                return false;
        }
public:
        TTimeSpan():timer(0) {}
        TTimeSpan(int year, int yday, int h, int m, int s)
        {
                
                int day = 0;
                int i = 0;
                if (yday <= 31)
                         day = yday;
                else
                {
                        int M[12];
                        M[0] = 31;
                        if (LeapYear(year))
                                M[1] = 29;
                        else
                                M[1] = 28;
                        M[2] = 31;
                        M[3] = 30;
                        M[4] = 31;
                        M[5] = 30;
                        M[6] = 31;
                        M[7] = 31;
                        M[8] = 30;
                        M[9] = 31;
                        M[10] = 30;
                        M[11] = 31;
                        while (yday > day)
                        {
                                day += M[i];
                                ++i;
                        }
                        --i;
                        day -= M[i];
                        day = yday - day;
                }
                tm tmp;
                tmp.tm_year = year + 70;
                tmp.tm_mon = i;
                tmp.tm_mday = day + 1;
                tmp.tm_hour = h + 3;
                tmp.tm_min = 0;
                tmp.tm_sec = 0;
                timer = mktime(&tmp);
        }
        TTimeSpan (int h, int m, int s)
        {
                tm tmp;
                tmp.tm_year = 70;
                tmp.tm_mon = 0;
                tmp.tm_mday = 1;
                tmp.tm_hour = h + 3;
                tmp.tm_min = m;
                tmp.tm_sec = s;
                timer = mktime(&tmp);
        }
        TTimeSpan (time_t t)
        {
                timer = t;
        }
        time_t GetUnixTimestamp() const
        {
                return timer;
        }
        TTimeSpan operator - (const TTimeSpan &oth)
        {
                time_t timer1 = GetUnixTimestamp(), timer2 = oth.GetUnixTimestamp(), timer;
                if (timer2 > timer1)
                        timer = timer2 - timer1;
                else timer = timer1 - timer2;
                TTimeSpan tmp(timer);
                return tmp;
        }
        TTimeSpan operator + (const TTimeSpan &oth)
        {
                time_t timer1 = GetUnixTimestamp(), timer2 = oth.GetUnixTimestamp(), timer;
                timer = timer1 + timer2;
                TTimeSpan tmp(timer);
                return tmp;
        }
        TTimeSpan operator = (TTimeSpan oth)
        {
                timer = oth.GetUnixTimestamp();
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
       TDateTime (int Year, int Mon, int Day, int H, int M, int S)
        {
                year = Year;
                month = Mon;
                day = Day;
                h = H;
                m = M;
                s = S;
        }
        TDateTime (int Year, int Month, int Day)
        {
                year = Year;
                month = Month;
                day = Day;
                h = 0;
                m = 0;
                s = 0;
        }
        TDateTime (string str)
        {
                sscanf(str.c_str(), "%d %d %d %d:%d:%d", &year, &month, &day, &h, &m, &s);
        }
        int Year () const
        {
                return year;
        }
        int Month () const
        {
                return month;
        }        
        int Day () const
        {
                return day;
        }
        int Hour () const
        {
                return h;
        }
        int Minute () const
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
                tm tmp;
                tmp.tm_year = year - 1900;
                tmp.tm_mon = month - 1;
                tmp.tm_mday = day;
                tmp.tm_hour = h;
                tmp.tm_min = m;
                tmp.tm_sec = s;
                time_t timer = mktime(&tmp);
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
        TDateTime operator + (const TTimeSpan &delta) //- возвращает дату-время, смещенную на delta
        {
                time_t t = GetUnixTimestamp();
                t += delta.GetUnixTimestamp();
                TDateTime tmp(t);
                return tmp;
        }

        TDateTime operator - (const TTimeSpan &delta) //- возвращает дату-время, смещенную на -delta
        {
                time_t t = GetUnixTimestamp();
                t -= delta.GetUnixTimestamp();
                TDateTime tmp(t);
                return tmp;
        }
        TTimeSpan operator - (const TDateTime &oth) const //- возвращает временной промежуток между двумя датами
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
        strftime(str, 80, "%T %d %b %Y\n", tmp);
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

ostream& operator << (ostream& out, const TTimeSpan tts)
{
        tm * tmp;
        time_t t = tts.GetUnixTimestamp();
        tmp = gmtime(&t);
        out << "Years: "<< tmp -> tm_year - 70 << " YearDays: " << tmp -> tm_yday << " Hours: " << tmp -> tm_hour << " Minutes: " << tmp -> tm_min << " Seconds: " << tmp -> tm_sec << endl;
        return out;
}
istream& operator >> (istream& in, TTimeSpan& tts)
{
        cout << "Format: YYYY DDD HH:MM:SS" << endl;
        int year, yday, hour, min, sec;
        in >> year >> yday >> hour >> min >> sec;
        TTimeSpan tmp(year, yday, hour, min, sec);
        tts = tmp;
        return in;
}

int main ()
{
        TDateTime T1;
        cout << "T1: " << T1;
        TDateTime T2(2001, 2, 3, 4, 5, 6);
        cout << "T2: " << T2;
        cout << T2;
        TTimeSpan S1;
        cout << "S1: " << S1 << "S1 = T2 - T1" << endl;
        S1 = T2 - T1;
        cout << "S1: " << S1;
        cout << "Test cin S2: ";
        TTimeSpan S2;
        cin >> S2;
        cout << "T1 + S2 = " << T1 + S2;
        return 0;
}

