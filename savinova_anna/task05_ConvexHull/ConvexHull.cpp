#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class TPoint
{
        int x, y, vx, vy;
public:
        TPoint()
        {
                x = 0;
                y = 0;
                vx = 0;
                vy = 0;
        };
        TPoint(int X, int Y)
        {
                x = X;
                y = Y;
                vx = 0;
                vy = 0;
        }
        int X()
        {
                return x;
        }
        int Y()
        {
                return y;
        }
        int& VX()
        {
                return vx;
        }
        int& VY()
        {
                return vy;
        }
        TPoint operator = (TPoint &a)
        {
                x = a.X();
                y = a.Y();
                vx = a.VX();
                vy = a.VY();
                return *this;
        }
};

int MultV(TPoint a, TPoint b)
{
        return a.VX() * b.VY() - a.VY() * b.VX();
}

int MultP(TPoint a, TPoint b, TPoint c)
{
        int x1 = a.X() - b.X();
        int y1 = a.Y() - b.Y();
        int x2 = c.X() - b.X();
        int y2 = c.Y() - b.Y();
        return x1 * y2 - x2 * y1;
}

bool Comp(TPoint a, TPoint b)
{
        if (MultV(a, b) > 0) return true;
        if (MultV(a, b) < 0) return false;
        return a.X() * a.X() + a.Y() * a.Y() < b.X() * b.X() + b.Y() * b.Y();
}
void Graham(vector<TPoint> &p, vector<TPoint> &h)
{
        for (size_t i = 1; i < p.size(); ++i)
        {
                if ((p[0].Y() > p[i].Y()) || (p[0].Y() == p[i].Y() && p[0].X() > p[i].X()))
                        swap(p[0], p[i]);
        }
        h.push_back(p[0]);
        for (size_t i = 1; i < p.size(); ++i)
        {
                p[i].VX() = p[i].X() - p[0].X();
                p[i].VY() = p[i].Y() - p[0].Y();
        }
        sort(p.begin() + 1, p.end(), &Comp);
        h.push_back(p[1]);
        for (size_t i = 2; i < p.size(); ++i)
        {
                while (MultP(h[h.size() - 2], h[h.size() - 1], p[i]) > 0)
                        h.pop_back();
                h.push_back(p[i]);
        }
}
        
int main()
{
        vector<TPoint> p;
        vector<TPoint> h;
        int x = 0, y = 0, N = 0;
        cin >> N;
        for (int i = 0; i < N; ++i)
        {
                cin >> x >> y;
                TPoint tmp(x, y);
                p.push_back(tmp);
        }
        Graham(p, h);
        for (size_t i = 0; i < h.size(); ++i)
                cout << h[i].X() << '\t' << h[i].Y() << endl;
        return 0;
}
