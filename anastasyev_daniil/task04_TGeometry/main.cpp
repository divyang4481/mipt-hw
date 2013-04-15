#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class IShape;

template<typename T>
class TSegment;

template<typename T>
class TPolygon;

template <typename T>
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
	T getX() const
	{
		return x;
	}
	T getY() const
	{
		return y;
	}
	TPoint& operator = (const TPoint <T>& p)
	{
		this -> x = p.getX();
		this -> y = p.getY();
		return *this;
	}
	bool HasPoint(const TPoint<T> &p) const
    {
		return (x == p.getX() && y == p.getY());
	}
	bool Intersects(const TSegment <T> &s) const
	{
		TPoint a(x, y);
		return s.HasPoint(a);
	}
};

template<typename T>
class TSegment: public IShape<T>
{
        TPoint<T> pbeg, pend;
public:
	TSegment()
	{}
	TSegment(TPoint<T> a, TPoint<T> b)
	{
		pbeg = a;
		pend = b;
	}
	TSegment(T x1, T y1, T x2, T y2)
	{
		TPoint<T> a(x1, y1);
		TPoint<T> b(x2, y2);
		pbeg = a;
		pend = b;
	}
	const TPoint<T> &Beg() const
	{
		return pbeg;
	}
	const TPoint<T> &End() const
	{
		return pend;
	}
	bool HasPoint(const TPoint<T> &p) const
	{
		return !PointOnLine(pbeg, pend, p) && (p.getX() >= pbeg.getX() 
			&& p.getY() >= pbeg.getY() && p.getX() <= pend.getX() 
			&& p.getY() <= pend.getY() || p.getX() >= pbeg.getX() 
			&& p.getY() >= pbeg.getY() && p.getX() <= pend.getX() && p.getY() <= pend.getY());
	}
	bool Intersects(const TSegment <T> &s) const
	{
		T v1 = (s.End().getX() - s.Beg().getX()) * (pbeg.getY() - s.Beg().getY()) - (s.End().getY() - s.End().getY()) * (s.Beg().getX() - pbeg.getX());
		T v2 = (s.End().getX() - s.Beg().getX()) * (pend.getY() - s.Beg().getY()) - (s.End().getY() - s.End().getY()) * (s.Beg().getX() - pend.getX());
		T v3 = (pend.getX() - pbeg.getX()) * (s.Beg().getY() - pbeg.getY()) - (pend.getY() - pbeg.getY()) * (s.Beg().getX() - pbeg.getX());
		T v4 = (pend.getX() - pbeg.getX()) * (s.End().getY() - pbeg.getY()) - (pend.getY() - pbeg.getY()) * (s.End().getX() - pbeg.getX());
		return (v1 * v2 <= 0) && (v3 * v4 <= 0);
	}
};

template <typename T>
class TPolygon: public IShape<T>
{
private:
	vector< TPoint<T> > poly;
public:
	TPolygon()
	{}
	TPolygon(const vector< TPoint<T> > &p)
	{
		poly = p;
		poly.push_back(p[0]);
	}
	size_t PolygonSize () const
	{
		return poly.size();
	}
	bool HasPoint(const TPoint <T> &p)  const
	{
		T max = poly[0].getX();
		int k = 0;

		for (int i=1; i<PolygonSize(); ++i)
			if (poly[i].getX() > max)
				max = poly[i].getX();
		TPoint <T> m(max+1, p.getY());
		TSegment <T> line(p, m);
		for (int i=0; i<PolygonSize()-1; ++i)
		{
			TSegment <T> edge(poly[i], poly[i+1]);
			if (line.Intersects(edge)) ++k;
		}
		return ((k % 2) ? false : true);
	}
	bool Intersects(const TSegment <T> &s) const
	{
		for (int i = 1; i < PolygonSize(); ++i)
		{
			TSegment <T> a(poly[i - 1], poly[i]);
			if (a.Intersects(s)) return true;
		}
		return false;
	}
};

template<typename T>
class TCircle:public IShape<T>
{
	T r;
	TPoint<T> cntr;
public:
	TCircle()
	{
		r = 0;
		cntr = 0;
	}
	TCircle(T R, TPoint<T> C)
	{
		r = R;
		cntr = C;
	}
	bool HasPoint(const TPoint<T> &p) const
	{
		return ((r * r >= ((p.getX() - cntr.getX()) * (p.getX() - cntr.getX()) 
			+ (p.getY() - cntr.getY()) * (p.getY() - cntr.getY()))) ? true : false);
	}
	bool Intersects(const TSegment <T> &s) const
	{
		 if ((HasPoint(s.Beg())) && (HasPoint(s.End()))) return false;
		 T A = s.End().getY() - s.Beg().getY();
		 T B = s.Beg().getX() - s.End().getX();
		 T C = s.Beg().getY() * s.End().getX() - s.Beg().getX() * s.End().getY();
		 T x1 = s.Beg().getX() - cntr.getX();
		 T y1 = s.Beg().getY() - cntr.getY();
		 T x2 = s.End().getX() - cntr.getX();
		 T y2 = s.End().getY() - cntr.getY();
		 if ((x1*A + y1*B) * (x2*A + y2*B)>0)
			 return false;
		 else 
		 {
			 double d = (A * cntr.getX() + B * cntr.getY() + C)/(sqrt((double)A*A + B*B));
			 if (d <= r)
				 return true;
			 else return false;
		 }
	}
};

template<typename T>
class IShape
{
public:
	virtual bool HasPoint(const TPoint<T>& p) const = 0;
	virtual bool Intersects(const TSegment <T>& s) const = 0;
};

template <typename T>
T PointOnLine(const TPoint <T> &a, const TPoint <T> &b, const TPoint <T> &c)
{
	return ((c.getX() - b.getX()) * (a.getY() - b.getY()) - (c.getY() - b.getY()) * (a.getX() - b.getX()));
};
int main()
{
        cout << "Point1(-1, 1)" << endl;
        TPoint <int> p1(-1, 1);
        cout << "Point2(1, 1)" << endl;
        TPoint <int> p2(1, 1);
        cout << "Point3(3, 0)" << endl;
        TPoint <int> p3(0, 2);
        cout << "Point4(0, 0)" << endl;
        TPoint <int> p4(0, 0);
        cout << "Point1.HasPoint(Point1): " << p1.HasPoint(p1) << endl;
        cout << "Point1.HasPoint(Point2): " << p1.HasPoint(p2) << endl;
        cout << "Segment1(Point1, Point2)" << endl;
        TSegment <int> s1(p1, p2);
        cout << "Segment2(0, -1, 0, 3)" << endl;
        TSegment <int> s2(0, -1, 0, 3);
        cout << "Segment3(-1, -2, 0, 1)" << endl;
        TSegment <int> s3(-1, -2, 0, 1);
        cout << "Segment4(-1, 4, 0, 4)" << endl;
        TSegment <int> s4(-1, 3, 2, 4);
        cout << "Segment1.HasPoint(Point1): " << s1.HasPoint(p1) << endl;
        cout << "Segment1.HasPoint(Point3): " << s1.HasPoint(p3) << endl;
        cout << "Segment2.HasPoint(Point3): " << s2.HasPoint(p3) << endl;
        cout << "Segment2.Intersects(Segment1): " << s2.Intersects(s1) << endl;
        cout << "Segment1.Intersects(Segment1): " << s1.Intersects(s1) << endl;
        cout << "Segment2.Intersects(Segment3): " << s2.Intersects(s3) << endl;
        cout << "Segment2.Intersects(Segment4): " << s2.Intersects(s4) << endl;
        cout << "Segment1.Intersects(Segment4): " << s1.Intersects(s4) << endl;
		vector <TPoint <int>> a;
		a.push_back(p1); a.push_back(p2); a.push_back(p3); a.push_back(p4); a.push_back(p1);
		TPolygon <int> Poly1(a);
		cout << "Polygon1(Point1, Point2, Point3, Point4, Point1)" << endl;
		TPoint <int> p(1, 0);
		cout << "Polygon1.HasPoint( (1,0) ): " << Poly1.HasPoint(p) << endl;
		cout << "Polygon1.Intersects( Segment2 ): " << Poly1.Intersects(s2) << endl;
        cout << "Circle(2, Point3)" << endl;
        TCircle<int> C(2, p3);
        cout << "Circle.HasPoint(Point1): " << C.HasPoint(p1) << endl;
        cout << "Circle.HasPoint(Point4): " << C.HasPoint(p4) << endl;
        cout << "Circle.Intersects(Segment1): " << C.Intersects(s1) << endl;
        cout << "Circle.Intersects(Segment2): " << C.Intersects(s2) << endl;
        cout << "Circle.Intersects(Segment3): " << C.Intersects(s3) << endl;
        return 0;
}