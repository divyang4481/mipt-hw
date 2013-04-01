#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


template <typename T>
class IShape;
template <typename T>
class TSegment;
template <typename T>
class TPoint: public IShape<T>
{
	T x,y;
public:
	
	TPoint()
	{
		x = y = 0;
	}
	TPoint (TPoint &a) 
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
		if ((x == p.GetX()) && (y == p.GetY()))
		return true;
		else return false;
	
	}
	bool Intersects(const TSegment <T> &s) const
	{
		 
		
		if (Area(s.GetBeg(), s.GetEnd(), *this))
			return true;
		else return false;
		
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
	
	TSegment(TPoint<T> &a, TPoint<T> &b)
	{
		beginning = a;
		ending = b;
	}
	
	bool HasPoint(const TPoint <T> &p) const
	{
		
		if (Area(beginning, ending, p))
			return false;
		else return true;
		
	}
	bool Intersects(const TSegment <T> &s) const
	{
		return Intersect_1(*this, s) && 
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
		 if ((x1*A + y1*B) * (x2*A + y2*B)<0)
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
	return (b.GetX() - a.GetX()) * (c.GetX() - a.GetY())
		- (b.GetY() - a.GetY()) * (c.GetX() - a.GetX());
}
template <typename T>
bool Intersect_1 (const TSegment<T> &x, const TSegment<T> &y)
{
	T ax = x.GetBeg().GetX();
	T ay = x.GetBeg().GetY();
	T bx = x.GetEnd().GetX();
	T by = x.GetEnd().GetY();
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




int main()
{
	
	TPoint<int> *a = new TPoint<int> (0,0);
	IShape<int> *c = new TCircle<int> (*a, 2);
	TPoint<int> *b = new TPoint<int> (-2,2);
	TPoint<int> *d = new TPoint<int> (3,3);
	TSegment<int> *e = new TSegment<int>(*b, *d);
	//cout << c -> HasPoint(*b) << endl;
	//cout << d ->Intersects(*d1) << endl;
	//cout << c ->HasPoint(*b) << endl;
	//cout << d -> HasPoint(*a) << endl;
	cout << c ->Intersects(*e) << endl;
	system("pause");

}