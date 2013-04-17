#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <math.h>
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
	bool operator == (TPoint &a)
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

class GrahamScan
{
	vector< TPoint > points;
	stack < TPoint > my_stack;
	string filename;
public:
	GrahamScan(string &name)
	{
		filename = name;
		//freopen ("1.txt", "r", stdin);
		
	}
	void ToRead()
	{
		FILE* f = fopen(filename.c_str(), "r");
		size_t n;
		fscanf(f, "%d", &n);
		points.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			fscanf(f, "%d %d", &points[i].x, &points[i].y);
		}
		fclose(f);
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
		sort(points.begin() + 1, points.end()); 
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
	void ToPrint(string &name)
	{
		FILE *f = fopen(name.c_str(), "w");
		size_t n = my_stack.size();
		for (size_t i = 0; i < n; ++i)
		{
			 fprintf ( f, "%d point: (%d; %d)\n", i+1, my_stack.top().x, my_stack.top().y);
                        my_stack.pop();
		}
	}

};
int main()
{
	GrahamScan a((string)"input.txt");
	a.scan();
	a.ToPrint((string)"output.txt");
	return 0;
}
