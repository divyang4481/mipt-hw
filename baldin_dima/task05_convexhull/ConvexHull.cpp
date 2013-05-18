#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <algorithm>
using namespace std;
const double e = 0.000001;
struct TPoint
{
	int x,y;
	double angle;

	TPoint operator = (TPoint &a)
	{
		x = a.x;
		y = a.y;
		angle = a.angle;
		return *this;
	}
	bool operator == (TPoint a)
	{
		return (abs(angle - a.angle) < e);
	}
	bool operator < (TPoint &a)
	{
		return (angle < a.angle);
	}
	int length( TPoint &a)
	{
		return ((x - a.x)*(x - a.x) + (y - a.y)*(y - a.y));
	}
};
bool cw(TPoint &a, TPoint &b, TPoint &c)
{
	return (((b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y)) > 0);
}
bool compare(TPoint a, TPoint b)
{
    return (a.angle<b.angle);
}
class GrahamScan
{
	vector< TPoint > points;
	stack < TPoint > my_stack;

public:
	GrahamScan()
	{}
	void ToRead()
	{
		size_t n;
		cin >> n;

		TPoint a;a.angle = 0.0;
		for (size_t i = 0; i < n; ++i)
		{


			cin >> a.x >> a.y;
			points.push_back(a);

		}

	}
	void LowestPoint()
	{

		for (size_t i = 1; i < points.size(); ++i)
			if ((points[i].y < points[0].y)||
				((points[i].y == points[0].y)&&
				(points[i].x < points[0].x)))
				swap(points[0], points[i]);
	}

	void PointsSort()
	{
		LowestPoint();
		for (size_t i = 1; i < points.size(); ++i)
			points[i].angle = atan2((double)points[i].y - points[0].y, (double)points[i].x - points[0].x);
		sort((++points.begin()), points.end(),compare);
		for (size_t i = 2; i < points.size(); ++i)
			if (points[i - 1] == points[i])
			{
				if (points[i-1].length(points[0]) < points[i].length(points[0]))
					points.erase(points.begin() + (i--) - 1);
				else points.erase(points.begin() + (i--));
			}
	}
	void scan()
	{
		ToRead();
		PointsSort();
		my_stack.push(points[0]);
		my_stack.push(points[1]);
		my_stack.push(points[2]);
		TPoint top, nexttop;
		for (size_t i = 3; i < points.size(); ++i)
		{
			top = my_stack.top();
			my_stack.pop();
			nexttop = my_stack.top();
			my_stack.push(top);
			for(;!cw(nexttop, top , points[i]);)
			{
				my_stack.pop();
				top = my_stack.top();
				my_stack.pop();
				nexttop = my_stack.top();
				my_stack.push(top);

			}
			my_stack.push(points[i]);
		}
	}
	void ToPrint()
	{

		size_t n = my_stack.size();
		for (size_t i = 0; i < n; ++i)
		{
			cout << (i+1) << " point: (" << my_stack.top().x << "; " << my_stack.top().y << ")" << endl;
			my_stack.pop();
		}
	}

};
int main()
{
	GrahamScan a;
	a.scan();
	a.ToPrint();
	return 0;
}
