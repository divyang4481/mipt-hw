#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class TPoint
{
	int x, y;
public:
	TPoint (int x1, int y1)
	{
		x = x1;
		y = y1;
	}
	TPoint operator = (TPoint &a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}
	int getX() const
	{
		return x;
	}
	int getY() const
	{
		return y;
	}
};

void ReadPoints(vector <TPoint> &points, FILE *in)
{
	int x, y;
	for (int i=0; fscanf(in, "%d %d", &x, &y)==2; ++i)
	{
		TPoint p(x, y);
		points.push_back(p);
	}
}

void GetMinPoint(vector <TPoint> &points)
{
	int size = points.size();
	for (int i=1; i<size; ++i)
	{
		if (points[0].getX()>points[i].getX() || (points[0].getX()==points[i].getX() && points[0].getY()>points[i].getY()))
			swap(points[0],points[i]);
	}
}

int Rotate(TPoint a, TPoint b, TPoint c)
{
	return (b.getX()-a.getX())*(c.getY()-b.getY())-(b.getY()-a.getY())*(c.getX()-b.getX());
}

void SortPoints(vector <TPoint> &points)
{
	int size = points.size();
	for (int i=2; i<size; ++i)
	{
		TPoint t = points[i];
		int j = i;
		while (j>1 && Rotate(points[0], points[j-1], points[j])<0)
		{
			swap(points[j], points[j-1]);
			--j;
		}
		points[j] = t;
	}
}

void ConvexHullBuild(list <TPoint> &CH, vector <TPoint> &points)
{
	CH.push_back(points[0]);
	CH.push_back(points[1]);
	int size = points.size();
	list <TPoint>::iterator it = CH.begin();
	++it;
	for (int i=2; i<size; ++i)
	{
		TPoint t1 = *(--it);
		TPoint t2 = *(++it);
		while (Rotate(t1, t2, points[i])<0)
		{
			--it;
			CH.pop_back();
			t1 = *(--it);
			t2 = *(++it);
		}
		CH.push_back(points[i]);
		++it;
	}
}

list <TPoint> Graham(const char* fin)
{
	FILE * in = fopen(fin,"r");
	vector <TPoint> points;
	ReadPoints(points, in);
	GetMinPoint(points);
	list <TPoint> ConvexHull;
	SortPoints(points);
	ConvexHullBuild(ConvexHull, points);
	return ConvexHull;
}

int main()
{
	list <TPoint> ConvexHull = Graham("in1.txt");
	FILE * out = fopen("out.txt","w");
	for (list <TPoint>::iterator it=ConvexHull.begin(); it!=ConvexHull.end(); ++it)
		cout << it->getX() << " " << it->getY() << endl;
	return 0;
}