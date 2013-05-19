#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<stack>
using namespace std;


struct Pair
{
  int x;
  int y;
  int xm;
  int ym;
     Pair()
   {
	   x=0;
	   y=0;
	   xm=0;
	   ym=0;
   }
	 Pair(int a, int b)
	{
       x=a;
	   y=b;
	   xm=0;
	   ym=0;
	}

};
double ctg(Pair p)
{   double yd=p.y;
    double xd=p.x; 
	double ymd=p.ym;
	double xmd=p.xm;
	return (xd-xmd)/(yd-ymd);
}

bool Compare(Pair p1, Pair p2)
{
	 if (p1.y==p1.ym) return false;
	 if (p2.y==p2.ym) return true;
	 return  (ctg (p1)>ctg(p2));
	
}

bool mult(Pair a,Pair b, Pair c)
{
	Pair u=Pair();
	Pair v=Pair();
	u.x=b.x-a.x;
	u.y=b.y-a.y;
	v.x=c.x-a.x;
	v.y=c.y-a.y;
	return (u.x*v.y-v.x*u.y>0);
}

int main()
{
	
	int N=100;
	int x,y;
	vector<Pair>Point;
	vector<Pair>St;
	Pair t=Pair();
    Point.push_back(t);
	for (int i=1; i<N+1; ++i)
	{
		cin>>x;
		cin>>y;
		Pair t(x,y); 
		Point.push_back(t); 
	}
	Pair Min=Point[1];
	for (int i=2;i<N+1;++i)
		if ((Point[i].y<Min.y)||((Point[i].y==Min.y)&&(Point[i].x<Min.x))) 
			{Min=Point[i];
	         swap(Point[i],Point[1]);
	        } 
	         
	for (int i=1;i<N+1;++i)
	{
	  Point[i].xm=Min.x;
	  Point[i].ym=Min.y;
	}
	sort(Point.begin()+2,Point.end(), &Compare);
	cout<<endl;
	St.push_back(t);
	St.push_back(Point[1]);
	St.push_back(Point[2]);
	St.push_back(Point[3]);
	for(int i=4;i<N+1;++i)
	{
		while (!(mult(St[St.size()-2],St[St.size()-1],Point[i])))
		{
			St.pop_back();
		}
		St.push_back(Point[i]);
	}
	for (int i=1;i<St.size();++i)
		cout<<St[i].x<<' '<<St[i].y<<endl;
		system("pause");
    return 0;
}