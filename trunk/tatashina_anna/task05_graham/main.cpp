#include <algorithm>
#include <iostream>
#include <vector>
 
using namespace std;
 
struct Point {
        double x, y, a;
        bool operator < (const Point &v) const {
                return a < v.a;
        }
};
 
double vector_product(Point a, Point b, Point c) {
        double ax, ay, cx, cy;
        
		ax = a.x - b.x;
		ay = a.y - b.y;
		cx = c.x - b.x;
		cy = c.y - b.y;
		
		return ax * cy - ay * cx;
}
 
int main() {

        int n;
		cin >> n;
        	
		vector <Point> p(n);
        vector <Point> s(n);

        for (int i = 0; i < n; i++) {
                cin >> p[i].x >> p[i].y;
                p[i].a = atan2(p[i].y, p[i].x);
        }
        
		sort(p.begin(), p.end());
   		int sz = 3;
        
        for (int i = 0; i < 3; i++)
                s[i] = p[i];
        for (int i = 3; i < n; i++) {
                while ((sz > 1) && (vector_product(p[i], s[sz - 1], s[sz - 2]) < 0))
                        sz--;
                s[sz++] = p[i];
        }
      

        while ((sz > 2) && (vector_product(s[0], s[sz - 1], s[sz - 2]) < 0))
                sz--;
        for (int i = 0; i < sz; i++)
                cout << s[i].x << " " << s[i].y << endl;

        return 0;
}