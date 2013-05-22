#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> 
#include <fstream>

using namespace std;

class point
{
private :
    int x, y;
public :
    point (int a = 0, int b = 0):x(a),y(b) {};
    int getX() const {return x;}
    int getY() const {return y;}
    point& operator=(const int& q)
    {
        x = q;
        y = q;
        return *this;
    }
    point& operator=(const point& q)
    {
        x = q.x;
        y = q.y;
        return *this;
    }
    bool operator==(const point& q) const
        {
        if (x == q.x && y == q.y) return true;
        else return false;
    }
    bool operator!=(const point& q) const
        {
        if (x != q.x || y != q.y) return true;
        else return false;
    }
	void SetX(int a) { x = a;}
	void SetY(int b) { y = b;}
	point move(int dx, int dy)
	{
		SetX(x + dx);
		SetY(y + dy);
		return *this;
	}
	point move(point P)
	{
		SetX(x + P.getX());
		SetY(y + P.getY());
		return *this;
	}
	void print()
	{
		cout <<'(' << x << ',' << y << ')' << endl;
	}
};
double length (point a, point b)
{	
		double sq = sqrt(double((a.getX() - b.getX())*(a.getX() - b.getX()) + (a.getY() - b.getY())*(a.getY() - b.getY())));
        return sq;
}
point NextToTop(stack <point> st) { st.pop(); return st.top();}
point Top(stack <point> st) { return st.top();}
bool one_line (point a, point b, point c)
{
	return (((b.getY() - a.getY())*(c.getX() - a.getX())) == ((c.getY() - a.getY())*(b.getX() - a.getX())));
}
bool notLeftTurn (point a, point b, point c)
{
	if (one_line (a, b, c)) // one line
		return true;
	if (((c.getX() - a.getX())*(b.getY() - a.getY()) - (c.getY() - a.getY())*(b.getX() - a.getX())) < 0)// left turn
		return false;
	return true;
}

bool comp(point a, point b)
{
	double cosA, cosB;
	point P(0,0); 
	cosA = a.getX()/length(P, a);
	cosB = b.getX()/length(P, b);
	if ((abs(cosA - cosB) < DBL_MIN) || ((a.getX() == a.getY()) && (b.getX() == b.getY())))
	{
		if ((length(P, a)) < (length(P, b)))
			return 1; 
		return 0;
	}
	return (cosA > cosB);
}

stack<point> convex_hull(vector < point > v)
{
	int numb = v.size();
	int minY = v[0].getY();
	int minX = v[0].getX();
	int minInd = 0;
	for (int i = 1; i < numb; ++i) //take min point
	{
		if (v[i].getY() < minY)
		{
			minY = v[i].getY();
			minX = v[i].getX();
			minInd = i;
		}
		if (v[i].getY() == minY)
			if (v[i].getX() < minX)
			{
				minInd = i;
				minX = v[i].getX();
			}
	}
	v.erase(v.begin() + minInd);
	for (size_t i = 0; i < v.size(); ++i)
		v[i].move(-minX, -minY);
	sort (v.begin(), v.end(), comp);
	for (size_t i = 0; i < v.size(); ++i)
		v[i].move(minX, minY);
	stack < point > res; 
	point min(minX, minY);
	res.push(min);
	while (1)
	{
		if (!one_line(min, v[0], v[1])) break;
		v.erase(v.begin());
	}
	res.push(v[0]);
	for(size_t i = 1; i < v.size(); ++i)
	{
		while (notLeftTurn(NextToTop(res), Top(res), v[i]))
			res.pop();
		res.push(v[i]);
	}
	return res;
}
int main()
{
	vector < point > v;
	point P;
	int N = 100, x, y;
	ifstream in;
	in.open("in1.txt");
	for (int i = 0; i < N; ++i)
	{
		in >> x >> y;
		P.SetX(x); P.SetY(y);
		v.push_back(P);
	}
	in.close();
	stack <point> st;
	st = convex_hull(v);
	ofstream of("of.txt");
	while (!st.empty())
	{
		of << st.top().getX() << '\t' << st.top().getY() << endl;
		st.pop();
	}
	of.close();
	return 0;
}