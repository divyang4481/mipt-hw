#include <algorithm>
#include <iostream>
using namespace std;

template<typename T>
class IShape;

template<typename T>
class TSegment;

template<typename T>
class TPoint:public IShape<T>
{
        T x, y;
public:
        TPoint()
        {
                x = 0;
                y = 0;
        }
        TPoint (T a, T b)
        {
                x = a;
                y = b;
        }
        T X() const
        {
                return x;
        }
        T Y() const
        {
                return y;
        }
        TPoint& operator = (const TPoint<T>& oth)
        {
                this -> x = oth.X();
                this -> y = oth.Y();
                return *this;
        }
        bool HasPoint(const TPoint<T>& p) const
        {
                return (x == p.X() && y == p.Y());
        }
        bool Intersects(const TSegment <T>& s) const
        {
                TPoint a(x, y);
                return s.HasPoint(a);
        }
};

template<typename T>
class TSegment:public IShape<T>
{
        TPoint<T> p1, p2;
public:
        TSegment(TPoint<T> a, TPoint<T> b)
        {
                p1 = a;
                p2 = b;
        }
        TSegment(T x1, T y1, T x2, T y2)
        {
                TPoint<T> a(x1, y1);
                TPoint<T> b(x2, y2);
                p1 = a;
                p2 = b;
        }
        const TPoint<T>& P1() const
        {
                return p1;
        }
        const TPoint<T>& P2() const
        {
                return p2;
        }
        bool HasPoint(const TPoint<T>& p) const
        {
                T x1 = p.X() - p1.X();
                T y1 = p.Y() - p1.Y();
                T x2 = p2.X() - p1.X();
                T y2 = p2.Y() - p1.Y();
                return !Direction(x1, y1, x2, y2) && (p.X() >= p1.X() && p.Y() >= p1.Y() && p.X() <= p2.X() && p.Y() <= p2.Y() || p.X() >= p1.X() && p.Y() >= p1.Y() && p.X() <= p2.X() && p.Y() <= p2.Y());
        }
        bool Intersects(const TSegment <T>& s) const
        {
                T x1 = min(p1.X(), p2.X());
                T x2 = max(p1.X(), p2.X());
                T x3 = min(s.p1.X(), s.p2.X());
                T x4 = max(s.p1.X(), s.p2.X());
                T y1 = min(p1.Y(), p2.Y());
                T y2 = max(p1.Y(), p2.Y());
                T y3 = min(s.p1.Y(), s.p2.Y());
                T y4 = max(s.p1.Y(), s.p2.Y());
                T d1 = Direction(s.p1.X() - p1.X(), s.p1.Y() - p1.Y(), p2.X() - p1.X(), p2.X() - p1.X());
                T d2 = Direction(s.p2.X() - p1.X(), s.p2.Y() - p1.Y(), p2.X() - p1.X(), p2.X() - p1.X());
                T d3 = Direction(p1.X() - s.p1.X(), p1.Y() - s.p1.Y(), s.p2.X() - s.p1.X(), s.p2.X() - s.p1.X());
                T d4 = Direction(p2.X() - s.p1.X(), p2.Y() - s.p1.Y(), s.p2.X() - s.p1.X(), s.p2.X() - s.p1.X());
                if (x2 >= x3 && x4 >= x1 && y2 >= y3 && y4 >= y1 && d1 * d2 <= 0 && d3 * d4 <=0)
                        return true;
                return false;
        }
};

template<typename T>
class TCircle:public IShape<T>
{
        T r;
        TPoint<T> ctr;
public:
        TCircle()
        {
                r = 0;
                ctr = 0;
        }
        TCircle(T R, TPoint<T> C)
        {
                r = R;
                ctr = C;
        }
        bool HasPoint(const TPoint<T>& p) const
        {
                if (r * r >= ((p.X() - ctr.X()) * (p.X() - ctr.X()) + (p.Y() - ctr.Y()) * (p.Y() - ctr.Y())))
                        return true;
                return false;
        }
        bool Intersects(const TSegment <T>& s) const
        {
                T a = s.P2().Y() - s.P1().Y();
                T b = s.P2().X() - s.P1().X();
                T c = s.P1().X() * s.P2().Y() - s.P1().Y() * s.P2().X();
                T m = a * a + b * b;
                T n = a * c + a * ctr.Y() * b - ctr.X() * b * b;
                T k = b * b * (ctr.X() * ctr.X() + ctr.Y() * ctr.Y()- r * r) + c * c + 2 * c * ctr.Y() * b;
                T D = n * n - m * k;
                if (D > 0)
                {
                        double x1 = (sqrt((double)D) - (double)n) / (double)m;
                        double x2 = (- sqrt((double)D) - (double)n) / (double)m;
                        double y1 = (- c - a * x1) / b;
                        double y2 = (- c - a * x2) / b;
                        TPoint<double> pp1(x1, y1);
                        TPoint<double> pp2(x2, y2);
                        TSegment<double> ss(pp1, pp2);
                        return (ss.HasPoint(pp1) && ss.HasPoint(pp2));
                }
                else if (!D)
                {
                        double x1 = (double)n / (double)m;
                        if (b) 
                        {
                                double y1 = (- c - a * x1) / b;
                                TPoint<T> p(x1, y1);
                                return s.HasPoint(p);
                        }
                        double y1 = ctr.Y() + sqrt(r * r - (x1 - ctr.X()) * (x1 - ctr.X()));
                        double y2 = ctr.Y() - sqrt(r * r - (x1 - ctr.X()) * (x1 - ctr.X()));
                        return (min(s.P1().Y(), s.P2().Y()) <= y2 || max(s.P1().Y(), s.P2().Y()) >= y1);
                }
                return false;
        }
};

template<typename T>
class IShape
{
public:
        virtual bool HasPoint(const TPoint<T>& p) const = 0; // Проверяет, что точка лежит внутри фигуры или на границе
        virtual bool Intersects(const TSegment <T>& s) const = 0; // Проверяет, что отрезок пересекает границу фигуры или касается ее
};

template <typename T>
 T Direction(T x1, T y1, T x2, T y2)
{
        return (x1*y2 - x2*y1);
};
int main()
{
        cout << "Creating Point1(-1, 1)" << endl;
        TPoint<int> P1(-1, 1);
        cout << "Creating Point2(1, 1)" << endl;
        TPoint<int> P2(1, 1);
        cout << "Creating Point3(0, 0)" << endl;
        TPoint<int> P3(0, 0);
        cout << "Creating Point4(2, 0)" << endl;
        TPoint<int> P4(2, 0);
        cout << "Creating Point5(3, 0)" << endl;
        TPoint<int> P5(3, 0);
        cout << "Point1.HasPoint(Point1): " << P1.HasPoint(P1) << endl;
        cout << "Point1.HasPoint(Point2): " << P1.HasPoint(P2) << endl;
        cout << "Creating Segment1(Point1, Point2)" << endl;
        TSegment<int> S1(P1, P2);
        cout << "Creating Segment2(0, -1, 0, 3)" << endl;
        TSegment<int> S2(0, -1, 0, 3);
        cout << "Creating Segment3(-1, 1, 0, 1)" << endl;
        TSegment<int> S3(-1, 1, 0, 1);
        cout << "Creating Segment4(-1, 4, 0, 4)" << endl;
        TSegment<int> S4(-1, 4, 0, 4);
        cout << "Creating Segment5(2, -2, 2, 2)" << endl;
        TSegment<int> S5(2, -2, 2, 2);
        cout << "Creating Segment6(-2, 2, 2, 2)" << endl;
        TSegment<int> S6(-2, 2, 2, 2);
        cout << "Segment1.HasPoint(Point1): " << S1.HasPoint(P1) << endl;
        cout << "Segment1.HasPoint(Point3): " << S1.HasPoint(P3) << endl;
        cout << "Segment2.HasPoint(Point3): " << S2.HasPoint(P3) << endl;
        cout << "Segment2.Intersects(Segment1): " << S2.Intersects(S1) << endl;
        cout << "Segment1.Intersects(Segment1): " << S1.Intersects(S1) << endl;
        cout << "Segment2.Intersects(Segment3): " << S2.Intersects(S3) << endl;
        cout << "Segment2.Intersects(Segment4): " << S2.Intersects(S4) << endl;
        cout << "Segment1.Intersects(Segment4): " << S1.Intersects(S4) << endl;
        cout << "Creating Circle(2, Point3)" << endl;
        TCircle<int> C(2, P3);
        cout << "Circle.HasPoint(Point1): " << C.HasPoint(P1) << endl;
        cout << "Circle.HasPoint(Point4): " << C.HasPoint(P4) << endl;
        cout << "Circle.HasPoint(Point5): " << C.HasPoint(P5) << endl;
        cout << "Circle.Intersects(Segment1): " << C.Intersects(S1) << endl;
        cout << "Circle.Intersects(Segment2): " << C.Intersects(S2) << endl;
        cout << "Circle.Intersects(Segment5): " << C.Intersects(S5) << endl;
        cout << "Circle.Intersects(Segment6): " << C.Intersects(S6) << endl;
        cout << "Circle.Intersects(Segment4): " << C.Intersects(S4) << endl;
        system("pause");
        return 0;
}