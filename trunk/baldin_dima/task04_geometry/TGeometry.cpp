#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;


template <typename T>
class IShape;
template <typename T>
class TSegment;
enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
template <typename T>
class TPoint: public IShape<T>
{
	T x,y;
public:
	
	TPoint()
	{
		x = y = 0;
	}
	TPoint (const TPoint &a)
	{
		x = a.GetX();
		y = a.GetY();
	}
	TPoint (T a, T b)
	{
		x = a;
		y = b;
	}
	bool HasPoint(const TPoint <T> &p) const
	{
		return ((x == p.GetX()) && (y == p.GetY()));
		
	
	}
	bool Intersects(const TSegment <T> &s) const
	{
		return (Area(s.GetBeg(), s.GetEnd(), *this));
	}
    
	T GetX() const 
	{
		return x;
	}
	T GetY() const 
	{
		return y;
	}
	void ChangeCoord(T a, T b)
	{
		x = a; y = b;
	}
	TPoint<T> operator- (TPoint<T> &p)
	{
		return TPoint<T> (x - p.GetX(), y - p.GetY());
	}
	
	int Classify( TPoint<T> &p0, TPoint<T> &p1) const
	{
		
		
		
		TPoint<T> p2 = *this;
		TPoint<T> a = p1 - p0;
		TPoint<T> b = p2 - p0;
		double sa = a.GetX() * b.GetY() - b.GetX() * a.GetY();
		if (sa > 0.0)
			return LEFT;
		if (sa < 0.0)
			return RIGHT;
		if ((a.GetX() * b.GetX() < 0.0 ) || (a.GetY() * b.GetY() < 0.0))
			return BEHIND;
		if ((a.GetX()*a.GetX() + a.GetY()*a.GetY()) <
			(b.GetX()*b.GetX() + b.GetY()*b.GetY()))
			return BEYOND;
		if ((p0.GetX() == p2.GetX()) && (p0.GetY() == p2.GetY()))
			return ORIGIN;
		if ((p1.GetX() == p2.GetX()) && (p1.GetY() == p2.GetY()))
			return DESTINATION;
		return BETWEEN;
	}

};
template <typename T>
class TSegment: public IShape<T>
{
private:
	TPoint<T> beginning;
	TPoint<T> ending;
public:
	TSegment()
	{
	}
	
	TSegment(const TPoint<T> &a,const TPoint<T> &b)
	{
		beginning = a;
		ending = b;
	}
	
	bool HasPoint(const TPoint <T> &p) const
	{
		
		return (!Area(beginning, ending, p));
			
		
	}
	bool Intersect_1 (const TSegment<T> &y) const
	{
		T ax = GetBeg().GetX();
		T ay = GetBeg().GetY();
		T bx = GetEnd().GetX();
		T by = GetEnd().GetY();
		T cx = y.GetBeg().GetX();
		T cy = y.GetBeg().GetY();
		T dx = y.GetEnd().GetX();
		T dy = y.GetEnd().GetY();
		if (ax > bx) swap(ax, bx);
		if (cx > dx) swap(cx, dx);
		if (ay > by) swap(ay, by);
		if (cy > dy) swap(cy, dy);
		return ((max(ax, cx) <= min (bx, dx)) && (max(ay, cy) <= min (by, dy)));
}
	bool Intersects(const TSegment <T> &s) const
	{
		return Intersect_1(s) && 
		Area(GetBeg(), GetEnd(), s.GetBeg()) * Area(GetBeg(), GetEnd(), s.GetEnd()) <= 0
		&&
		Area(s.GetBeg(), s.GetEnd(), GetBeg()) * Area(s.GetBeg(), s.GetEnd(), GetEnd()) <= 0;
	}
	const TPoint<T>& GetBeg() const
	{
		return beginning;
	}
	const TPoint<T>& GetEnd() const
	{
		return ending;
	}

};
template <typename T>
class TCircle: public IShape<T>
{
private:
	TPoint<T> center;
	T radius;
public:
	TCircle()
	{
	}
	TCircle(TCircle<T> &a)
	{
		center = a.center;
		radius = a.radius;
	}
	TCircle(TPoint<T> &a, T r)
	{
		center = a;
		radius = r;
	}
	bool HasPoint(const TPoint <T> &p) const
	{
		return ((center.GetX()-p.GetX())*(center.GetX()-p.GetX()) + (center.GetY()-p.GetY())*(center.GetY()-p.GetY())) - radius * radius <= 0;
	}
	 bool Intersects(const TSegment <T> &s) const
	 {
		 if ((this ->HasPoint(s.GetBeg())) && (this ->HasPoint(s.GetEnd()))) return false;
		 if ((this ->HasPoint(s.GetBeg())) ^ (this ->HasPoint(s.GetEnd()))) return false;
		 T A = s.GetEnd().GetY() - s.GetBeg().GetY();
		 T B = s.GetBeg().GetX() - s.GetEnd().GetX();
		 T C = s.GetBeg().GetY()*s.GetEnd().GetX() - s.GetBeg().GetX()*s.GetEnd().GetY();
		 T x1 = s.GetBeg().GetX() - center.GetX();
		 T y1 = s.GetBeg().GetY() - center.GetY();
		 T x2 = s.GetEnd().GetX() - center.GetX();
		 T y2 = s.GetEnd().GetY() - center.GetY();
		 if ((x1*A + y1*B) * (x2*A + y2*B)>0)
			 return false;
		 else 
		 {
			 double d = (A * center.GetX() + B * center.GetY() + C)/(sqrt((double)A*A + B*B));
			 if (d <= radius)
				 return true;
			 else return false;
				 
		 }
	 }
};
template <typename T>
class TPolygon: public IShape<T>
{
private:
	vector< TPoint<T> > pol;
public:
	enum {OUTSIDE, INSIDE, BOUNDARY};
	enum { TOUCHING, CROSSING, INESSENTIAL };
	TPolygon()
	{
	}
	TPolygon(const vector< TPoint<T> > &p)
	{
		pol = p;
		pol.push_back(p[0]);
	}
	
	size_t PolygonSize () const
	{
		return pol.size();
	}
	bool HasPoint(const TPoint <T> &p)  const
	{
		int parity = 0;
		
		TPoint<T> x,y;
		for (size_t i = 1; i < this ->PolygonSize(); ++i)
		{
			x = pol[i-1]; y = pol[i];
			switch (SegmentType(p,x,y))
			{
			case TOUCHING:
				return BOUNDARY;
			case CROSSING:
				parity = 1 - parity;
			}
		}
		return (parity ? INSIDE : OUTSIDE);
	}
	int SegmentType (const TPoint<T> &a,TPoint<T> &x, TPoint<T> &y) const
	{
		switch (a.Classify(x,y))
		{
		case LEFT:
			return ((x.GetY() < a.GetY()) && (a.GetY() <= y.GetY()))
				? CROSSING : INESSENTIAL;
		case RIGHT:
			return ((y.GetY() < a.GetY()) && (a.GetY() <= x.GetY()))
				? CROSSING : INESSENTIAL;
		case BETWEEN:
		case ORIGIN:
		case DESTINATION:
			return TOUCHING;
		default:
			return INESSENTIAL;
		}
	}
	bool Intersects(const TSegment <T> &s) const
	{
		TSegment<T> a;
		for (size_t i = 1; i < this ->PolygonSize(); ++i)
		{
			a = TSegment<T>(pol[i - 1], pol[i]);
			if (a.Intersects(s)) return true;
			
		}
		return false;
	}

};
template <typename T>
class IShape
{
public:
	//template <typename U>
	virtual bool HasPoint(const TPoint <T> &p)  const = 0;
	virtual bool Intersects(const TSegment <T> &s) const = 0;
};
template <typename T>
T Area (const TPoint<T> &a, const TPoint<T> &b, const TPoint<T> &c)
{
	return (b.GetX() - a.GetX()) * (c.GetY() - a.GetY())
		- (b.GetY() - a.GetY()) * (c.GetX() - a.GetX());
}





int main()
{
	
	vector<TPoint<int> > p;
	TPoint<int> a(-2,3);
	p.push_back(a);
	TPoint<int> b(-4,1);
	p.push_back(b);
	TPoint<int> c(0,-2);
	p.push_back(c);
	TPoint<int> d(4,1);
	p.push_back(d);
	TPoint<int> e(2,3);
	p.push_back(e);
	cout << "Create Polygon with vertices((-2,3),(-4,1),(0,-2),(4,1),(2,3))" << endl;
	TPolygon<int> pol(p);
	TPoint<int> f(-2,3);
	TPoint<int> g(0,0);
	cout << "Check one of the vertices (-2,3)" << endl;
	cout << pol.HasPoint(f)<< endl;
	f.ChangeCoord(0,0);
	cout << "Check point inside (0,0)" << endl;
	cout << pol.HasPoint(f) << endl;
	f.ChangeCoord(4,0);
	cout << "Check point outside (4,0)" << endl;
	cout << pol.HasPoint(f) << endl;
	TSegment<int> fg(f,g);
	cout << "Check segment intersecting ((0,0),(4,0))" << endl;
	cout << pol.Intersects(fg) << endl;
	g.ChangeCoord(0,-3);
	fg = TSegment<int>(f, g);
	cout << "Check segment not intersecting ((0,-3),(4,0))" << endl;
	cout << pol.Intersects(fg) << endl;
	cout << "Create circle center (0,0), radius = 3" << endl;
	f.ChangeCoord(0,0);
	TCircle<int> w (f,3);
	cout << "Check point inside (0,0)" << endl;
	cout << w.HasPoint(f) << endl;
	cout<< "Check point outside (4,0)" << endl;
	f.ChangeCoord(4,0);
	cout << w.HasPoint(f) << endl;
	TSegment<int> ab(a,b);
	cout << "Check segment not intersecting ((-2,3),(-4,1))" << endl;
	cout << w .Intersects(ab) << endl;
	
	cout << "Check segment intersecting ((0,-2),(4,1))" << endl;
	cout << w.Intersects(ab) << endl;
	

	system("pause");
	return 0;

}