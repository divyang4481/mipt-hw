#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> coor;
typedef pair<coor, double> point;

#define X first
#define Y second
#define angle second
#define C first
const int POINTS_NUM = 100;

int p2 (int a){
	return a*a;
}
static int const bigger = (int)1e9;
static double const eps = 1e-9;

bool compAngle(point a, point b){
    if (a.angle == 0 && b.angle != 0)
        return 1;
    if (a.angle != 0 && b.angle == 0)
        return 0;
    if (a.angle * b.angle >= 0)
        return a.angle < b.angle;
    if (a.angle >= 0 && b.angle <= 0)
        return 1;
        return 0;
}

double vectorProduct(coor a, coor b){
    return a.X * b.Y - b.X * a.Y;
}

double length(coor v){
    return sqrt((double)(p2(v.X)) + (double)(p2(v.Y)));
}

coor line(coor A, coor B){
    return make_pair(B.X - A.X, B.Y - A.Y);
}

void updateLast(vector<coor> points, coor &last){
	last = line(points[points.size() - 2], points.back());
}

int main(){
	freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
	vector<point> points;
	int x, y;
	for (int i=0; i<POINTS_NUM; ++i){
		cin >> x >> y;
		points.push_back(make_pair(make_pair(x,y),0.0));
	}
	int n = (int)points.size();
    int id = 0;
    coor start = make_pair(bigger, bigger);
    for (int i = 0; i < n; ++i)
        if (points[i].C.Y < start.Y || (points[i].C.Y == start.Y && points[i].C.X < start.X)){
            id = i;
            start = points[i].C;
        }
	swap(points[0], points[id]);
    for (int i = 0; i < n; ++i)
        points[i].Y = (points[i].C.X - start.X != 0) ? 1.0 * (points[i].C.Y - start.Y) / (points[i].C.X - start.X) : bigger;
    sort(points.begin() + 1, points.end(), compAngle);
    vector <coor> ConvexHull;
    ConvexHull.push_back(start);
    ConvexHull.push_back(points[1].C);
    coor last = line(start, points[1].C);
    int i = 2;
    while (i < (int)points.size())
	{
        double Product = vectorProduct(last, line(ConvexHull.back(), points[i].C));
        if (abs(Product) < eps){
			if (length(line(ConvexHull.back(), points[i].C)) > length(last)){
				ConvexHull.pop_back();
				ConvexHull.push_back(points[i].C);
                updateLast(ConvexHull, last);
			}
        }
        else
        if (Product > 0){
            ConvexHull.push_back(points[i].C);
            updateLast(ConvexHull, last);
        }
        else 
        if (Product < 0){
			while (Product < 0)
			{
				ConvexHull.pop_back();
				updateLast(ConvexHull, last);
				Product = vectorProduct(last, line(ConvexHull.back(), points[i].C));
			}
            ConvexHull.push_back(points[i].C);
            updateLast(ConvexHull, last);
        }

        ++i;
    }
    for (int i = 0; i<(int)ConvexHull.size(); ++i)
        cout << ConvexHull[i].X << "\t" << ConvexHull[i].Y << endl;
	return 0;
}
