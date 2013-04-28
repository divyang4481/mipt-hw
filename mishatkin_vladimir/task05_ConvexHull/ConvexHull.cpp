#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
#define X first
#define Y second
template < typename T > T sqr (T a) { return (a) * (a); }
static int const INF = (int)1e9 + 5;
static double const eps = 1e-9;

bool compAngle(pair<pii, double> a, pair<pii, double> b)
{
    if (a.Y == 0 && b.Y != 0)
        return 1;               // b > a
    if (a.Y != 0 && b.Y == 0)
        return 0;               // a > b

    if (a.Y * b.Y >= 0)
        return a.Y < b.Y;

    if (a.Y >= 0 && b.Y <= 0)
        return 1;               // b > a
    //if (a.Y <= 0 && b.Y >= 0)
        return 0;               // a > b
}

double vectorProduct(pii a, pii b)
{
    return a.X * b.Y - b.X * a.Y;
}

double length(pii v)
{
    return sqrt(1.0*sqr(v.X) + 1.0*sqr(v.Y));
}

pii makeVector(pii From, pii To)
{
    return make_pair(To.X - From.X, To.Y - From.Y);
}

void updateLast(vector<pii> dots, pii &last)
{
	last = makeVector(dots[dots.size() - 2], dots.back());
}

int main(int argc, const char * argv[])
{
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

	vector <pair <pii, double> > Dot;
	int x;
	int y;
	while (scanf("%d%d\n", &x, &y) == 2)
	{
		Dot.push_back(make_pair(make_pair(x, y), 0.0));
	}
	int n = (int)Dot.size();

    int id = 0;
    pii low = make_pair(INF, INF);
    for (int i = 0; i < n; ++i)
        if (Dot[i].X.Y < low.Y || (Dot[i].X.Y == low.Y && Dot[i].X.X < low.X))
		{
            id = i;
            low = Dot[i].X;
        }

	swap(Dot[0], Dot[id]);

    for (int i = 0; i < n; ++i)
        Dot[i].Y = (Dot[i].X.X - low.X != 0) ? 1.0 * (Dot[i].X.Y - low.Y) / (Dot[i].X.X - low.X) : INF;

    sort(Dot.begin() + 1, Dot.end(), compAngle);

    vector <pii > ConvexHull;
    ConvexHull.push_back(low);
    ConvexHull.push_back(Dot[1].X);

    pii last = makeVector(low, Dot[1].X);//make_pair(Dot[1].X.X - low.X, Dot[1].X.Y - low.Y);
    int i = 2;
    while (i < (int)Dot.size())
	{
        double Product = vectorProduct(last, makeVector(ConvexHull.back(), Dot[i].X));
        if (abs(Product) < eps)
		{
			if (length(makeVector(ConvexHull.back(), Dot[i].X)) > length(last))
			{
				//pii next = ConvexHull.back();
				ConvexHull.pop_back();
				//    ConvexHull.push_back(Dot[i].X);
				//	ConvexHull.push_back(next);
				//    updateLast(ConvexHull, last);
				//}
				//else
				//{
				ConvexHull.push_back(Dot[i].X);
                updateLast(ConvexHull, last);
			}
        }
        else
        if (Product > 0)
		{                  // left turn
            ConvexHull.push_back(Dot[i].X);
            updateLast(ConvexHull, last);
        }
        else 
        if (Product < 0)
		{                  // right turn
			while (Product < 0)
			{
				ConvexHull.pop_back();
				updateLast(ConvexHull, last);
				Product = vectorProduct(last, makeVector(ConvexHull.back(), Dot[i].X));
			}
            ConvexHull.push_back(Dot[i].X);
            updateLast(ConvexHull, last);
        }

        ++i;
    }

    for (int i = 0; i < (int)ConvexHull.size(); ++i)
        printf("%d %d\n", ConvexHull[i].X, ConvexHull[i].Y);

	return EXIT_SUCCESS;
}
