#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

template<typename T>
class TPoint;

template<typename T>
class TSegment;

template <typename T>
class IShape
{
public:
        virtual bool HasPoint(const TPoint<T> &point) const=0{};
        virtual bool Intersects(const TSegment<T> &segment) const=0{};
};


	
template <typename T>
class TPoint:public IShape<T>
{
	T x, y;
public:
	TPoint()
	{
		x=0;
		y=0;
	}
	TPoint(T a, T b)
	{
		x=a;
		y=b;
	}
	 T X() const
	{
		return x;
	}
	 T Y() const
	{
		return y;
	}
	TPoint& operator = (const TPoint<T> &p)
	{

		this->x=p.X();
		this->y=p.Y();
		return *this;
	}
	
	bool HasPoint( const TPoint<T> &point) const
	{
		return ((point.X()==x)&&(point.Y()==y));
	}
	bool Intersects(const TSegment<T> &segment) const
	{
		//TPoint<T> pt1;
		//	pt1=segment.Point1();
		//TPoint<T> pt2=segment.Point2();
	//double l1=sqrt((float)((pt1.X()-pt2.X())*(pt1.X()-pt2.X())));//+(y1-y2)*(y1-y2));
		//double l2;
		//double l3;
		TSegment<T> s2 (segment.Point1(),*this);
		TSegment<T> s3 (segment.Point2(),*this);
		double a,b,c;
		a=segment.Dlina(); 
		b=s2.Dlina();
		c=s3.Dlina();
		//cout<<a<<b<<c<<endl;
		return (a==b+c);
	}
};
template <typename T>
class TSegment: public IShape <T>
{
	TPoint<T> p1, p2;
public:
	TSegment()
	{
		p1(0,0);
		p2(0,0);
	}
	TSegment(TPoint<T> a,TPoint<T> b)
	{
		p1=a;
		p2=b;
	}
	TPoint<int> Point1() const
	{
		return p1;
	}
	TPoint<int> Point2() const
	{
		return p2;
	}
	double Dlina() const
	{
		TPoint<T> pt1;
		pt1=Point1();
		TPoint<T> pt2=Point2();
		double l1=sqrt((float)((pt1.X()-pt2.X())*(pt1.X()-pt2.X())+(pt1.Y()-pt2.Y())*(pt1.Y()-pt2.Y())));
		return l1;//+(y1-y2)*(y1-y2));
	}

	bool HasPoint(const TPoint<T> &point) const
	{
		return (point.Intersects(*this));
	}
	bool Intersects(const TSegment<T> &segment) const
	{
		TPoint<T> p1=Point1();
		TPoint<T> p2=Point2();
		TPoint<T> p3=segment.Point1();
		TPoint<T> p4=segment.Point2();
		return(BoundingBox(p1.X(),p2.X(),p3.X(),p4.X())&&BoundingBox(p1.Y(),p2.Y(),p3.Y(),p4.Y())&&((Area(p1,p2,p3)*Area(p1,p2,p4))<=0)&&((Area(p3,p4,p1)*Area(p3,p4,p2))<=0));
	}
};
template <typename T>
class TCircle:public IShape<T>
{
	TPoint<T> centr;
	T r;
	
public:
	TCircle()
	{
		r=0;
		TPoint<T> nul;
		centr=nul;
	}
	TCircle(T a, TPoint<T> p)
	{
		r=a;
		centr=p;
	}
	T Radius()
	{
		return r;
	}
	TPoint<T> Centre() const
	{
		return centr;
	}
        /*TPoint<T>& Centre()
	{
		return centr;
	}*/
	bool HasPoint(const TPoint<T> &point) const
	{
		TSegment<T> s(point,centr);
		return (s.Dlina()<=r);
	}
	bool Intersects(const TSegment<T> &segment) const
	{
		TPoint<T> p1=segment.Point1();
		TPoint<T> p2=segment.Point2();
		TPoint<T> p3=Centre();
		T x01=p1.X()-p3.X();
		T y01=p1.Y()-p3.Y();
		T x02=p2.X()-p3.X();
		T y02=p2.Y()-p3.Y();
		T dx=x02-x01;
		T dy=y02-y01;
		T a=dx*dx+dy*dy;
		T b=2*(x01*dx+y01*dy);
		T c=x01*x01+y01*y01-r*r;
		if (-b<0) return (c<0);
		if (-b<(2*a)) return (4*a*c-b*b<0);
		return(a+b+c<0);
	}
};
template <typename T>
class TPolygon:public IShape<T>
{
	vector<TPoint<T>> points;
public:
	TPolygon()
	{}
	TPolygon(const vector<TPoint<T>>&p)
	{
		points=p;
	}
	TPolygon(TPolygon<T>&P)
	{
		points=P.points;
	}
	int PolygonSize() const
	{
		return points.size();
	}
	bool HasPoint(const TPoint<T> &point) const
	{
		TPoint<T> max=points[0];
		for (int i=0;i<PolygonSize();i++)
			if (max.X()<points[i].X())
				max=points[i];
		//cout<<max.X()<<' '<<max.Y()<<endl;
		TPoint<T> outp(max.X()+1,max.Y());
		//cout<<outp.X()<<' '<<outp.Y()<<endl;
		TSegment<T> s1(outp,point);
		int count=0;
		for (int i=1;i<PolygonSize();i++)
		{
			TSegment<T>s2(points[i],points[i-1]);
			if (s2.Intersects(s1)) count++;
		//	cout<<s2.Intersects(s1)<<endl;
		}
		TSegment<T> s2(points[0],points[PolygonSize()-1]);
			if (s2.Intersects(s1)) count++;
			//cout<<s2.Intersects(s1)<<endl;
		return (count%2==1);
	}
		
	bool Intersects(const TSegment<T> &segment) const
	{
		TPoint<T> max=points[0];
		//for (int i=0;i<PolygonSize();i++)
		//	if (max.X()<points[i].X())
		//		max=points[i];
		//TPoint<T> outp(max.X()+1,max.Y());
		//TSegment<T> s1 (outp,point);
		for (int i=1;i<PolygonSize();i++)
			{TSegment<T>s2(points[i],points[i-1]);
			if (s2.Intersects(segment)) return 1;
			}	
			TSegment<T> s2(points[0],points[PolygonSize()-1]);
			if (s2.Intersects(segment)) return 1;
			return 0;
	}
};
/*template <typename T>
class IShape
{
public:
        virtual bool HasPoint(const TPoint<T> &point) const=0{};
        virtual bool Intersects(const TSegment<T> &segment) const=0{};
};*/
template <typename T>
double Area(TPoint<T> a, TPoint<T> b, TPoint<T> c)
{
	return (b.X()-a.X())*(c.Y()-a.Y())-(b.Y()-a.Y())*(c.X()-a.X());
};

template <typename T>
bool BoundingBox(T a, T b, T c, T d)
{
	if (a>b) swap(a,b);
	if (c>d) swap (c,d);
	return max(a,c)<=min(b,d);
}
	
int main()
{
	
	TPoint<int> P(0,0);
	TPoint<int> P1(2,0);
	TPoint<int>P2(2,2);
	TPoint<int>P3(0,2);
	TPoint<int>P4(1,1);
	TPoint<int>P5(1,-1);
	TSegment<int>S1(P4,P5);
	TSegment<int>S2(P2,P3);
	//cout<<P.HasPoint(P1)<<endl;
	//cout<<S1.Dlina()<<endl;
	//cout<<S1.HasPoint(P2)<<endl;
	//cout<<S1.Intersects(S2)<<endl;
	TCircle<int> C1(1,P);
	vector<TPoint<int>>V(4);
	V[1]=P1;
	V[2]=P2;
	V[3]=P3;
	V[0]=P;
	TPolygon<int>PG1(V);
	cout<<PG1.HasPoint(P4)<<endl;
	system("pause");
	return 0;
}