#include<iostream>

using namespace std;

template<typename T>
class IShape;

template <typename T>
class point
{
private :
    T x, y;
public :
    point (T a = 0, T b = 0):x(a),y(b) {};
    T getX() const {return x;}
    T getY() const {return y;}
    point& operator=(const T& q)
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
	void SetX(T a) { x = a;}
	void SetY(T b) { y = b;}
	void move(double dx, double dy)
	{
		SetX(x + dx);
		SetY(y + dy);
	}
	void print()
	{
		cout <<'(' << x << ',' << y << ')' << endl;
	}
	//friend istream& operator >> (istream &is, point &a);
	//friend ostream& operator << (ostream &os, const point &a);
};
/*template <typename T>
istream& operator >> (istream &is, point<T> &a) 
{
	is>> a.x >> a.y;
	return is;
}
template <typename T>
ostream& operator << (ostream &os, const point<T> &a) 
{
	return os<<'(' << a.x << ',' << a.y << ')' << endl;
}*/

template <typename T>
double length (point<T> a, point<T> b)
{
        return sqrt((a.getX() - b.getX())*(a.getX() - b.getX()) + (a.getY() - b.getY())*(a.getY() - b.getY()));
}
template <typename T>
double multiplicationV (point<T> a, point<T> b, point<T> c, point<T> d)
{
    double x1 = b.getX() - a.getX(),y1 = b.getY() - a.getY(), x2 = d.getX() - c.getX(), y2 = d.getY() - c.getY();
    return x1*y2 - x2*y1;
}
template <typename T>
double multiplicationS (point<T> a, point<T> b, point<T> c, point<T> d)
{
    return (b.getX() - a.getX()) * (d.getX() - c.getX()) + (b.getY() - a.getY()) * (d.getY() - c.getY());
}

template <typename T>
class segment: public IShape<T>
{
private :
    point<T> a, b;
public :
	point<T> getA() const {return a;}
    point<T> getB() const {return b;}
	void SetA(point<T> c) { a = c;}
	void SetB(point<T> d) { b = d;}
	segment (T q = 0, T p = 0, T x = 0, T y = 0) {a.SetX(q); a.SetY(p); b.SetX(x); b.SetY(y);}
    segment (point<T> x, point<T> y) {a = x; b = y;}
	void print() const {cout << a.getX() << ' ' << a.getY() << '\n' << b.getX() << ' ' << b.getY() << '\n';}
    double distance (point<T> c) const
	{
		double x, l1 = length(c,a), l2 = length(c,b);
		if (multiplicationS(b,a,b,c) > 0 && multiplicationS(a,b,a,c) > 0)
			x = abs(multiplicationV(c,a,c,b)) / length(a,b);
		else
			x = (l1 <= l2) ? l1 : l2;
		return x;
	}
    bool HasPoint (const point<T>& c) const
	{
		bool q;
		if (multiplicationV(c,a,c,b) == 0 && length(c,b) <= length(a,b) && length(a,c) <= length(a,b))
			q = true;
		else q = false;
		return q;
	}
    bool Intersects (const segment<T>& c) const
	{
		bool v;
		double maxY2 = (a.getY() >= b.getY()) ? a.getY() : b.getY(), maxY1 = (c.a.getY() >= c.b.getY()) ? c.a.getY() : c.b.getY(),
			maxX2 = (a.getX() >= b.getX()) ? a.getX() : b.getX(), maxX1 = (c.a.getX() >= c.b.getX()) ? c.a.getX() : c.b.getX(),
			minY2 = (a.getY() <= b.getY()) ? a.getY() : b.getY(), minY1 = (c.a.getY() <= c.b.getY()) ? c.a.getY() : c.b.getY(),
			minX2 = (a.getX() <= b.getX()) ? a.getX() : b.getX(), minX1 = (c.a.getX() <= c.b.getX()) ? c.a.getX() : c.b.getX();
		if ((multiplicationV(a,c.a,a,b) * multiplicationV(a,c.b,a,b) <= 0) &&
			(multiplicationV(c.a,a,c.a,c.b) * multiplicationV(c.a,b,c.a,c.b) <= 0) &&
			maxX1 >= minX2 && maxX2 >= minX1 && maxY1 >= minY2 && maxY2 >= minY1)
			v = true;
		else v = false;
		return v;
	}
};

template <typename T>
double distance (segment<T> s)
{
    return sqrt((s.getA().getX() - s.getB().getX()) * (s.getA().getX()  s.getB().getX()) + (s.getA().getY() - s.getB().getY()) * (s.getA().getY() - s.getB().getY()));
}

template <typename T>
class circle : public IShape<T>
{
        point<T> a;
        T r;
public:
        circle (T x = 0, T y = 0, T R = 1) {a.SetX(x); a.SetY(y); r = R;}
        circle (const point<T> &c, T R) {a = c; r = R;}
		circle (const circle<T> &c) {a = c.a; r = c.r;}
		T getR() const {return r;}
		void SetR(T R) { r = R;}
		bool HasPoint (const point<T> & c) const
		{
			if (length(a,c) <= r) return true;
			else return false;
		}
		bool Intersects (const segment<T> & c) const
		{
			bool b = false;
			if ((length(a,c.getA()) < r) && (length(a,c.getB()) < r)) b = false;
			else
				if (((length(a,c.getA()) <= r) && (length(a,c.getB()) >= r)) || ((length(a,c.getA()) >= r) && (length(a,c.getB()) <= r))) b = true;
				else
					if (multiplicationS(c.getB(),c.getA(),c.getB(),a) > 0 && multiplicationS(c.getA(),c.getB(),c.getA(),a) > 0)
						if (c.distance(a) <= r) b = true;
			return b;
		}
		void print()
		{
			cout << "center ";
			a.print();
			cout << "R = " << r <<'\n';
		}
		//friend istream& operator >> (istream& is, circle &a);
		//friend ostream& operator << (ostream& os, const circle &a );
};
/*template <typename T>
ostream& operator << (ostream& os, const circle &a )
{
	os << (const point &)a;
	os << "r=" << a.r;
	return os;
}
template <typename T>
istream& operator >> (istream& is, circle &a)
{
	return is >> (point &)a >> a.r;
}*/
template <typename T>
double multiplication1 (point<T> a, point<T> b, point<T> c, point<T> d)
{
	double x1=b.getX()-a.getX(),y1=b.getY()-a.getY(),x2=d.getX()-c.getX(),y2=d.getY()-c.getY();
	return x1*y2-x2*y1;
}
template <typename T>
class polygon : public IShape<T>
{
private:
	int n;
	point<T> *arr;
public:
	polygon ()
	{
		n = 3;
		arr = new point<T> [n];
		point<T> P0(0,0), P1(1,0), P2(0,1);
		arr[0] = P0; arr[1] = P1; arr[2] = P2;
	}
	polygon (int k, point<T> *a)
	{
		arr = new point<T> [k];
		n = k;
		for (int i = 0; i < n; i++)
			arr[i] = a[i];
	}
	int N () const {return n;}
	~polygon () {delete [] arr;}
	polygon (const polygon<T>&  q)
	{
		arr = new point [n = q.n];
		for (int i = 0; i < n; i++)
			arr[i] = q.arr[i];
	}
	void print () const
	{
		for (int i = 0; i < n; i++)
			cout << arr[i].getX() << ' ' << arr[i].getY() << endl;
	}
	bool HasPoint (const point<T>& a) const
	{
		int k = 0;
		double maxX = arr[0].getX();
		for (int i = 0; i<n; i++)
			if (arr[i].getX() > maxX)
				maxX = arr[i].getX();
		maxX += 5;
		point<T> c(maxX,a.getY());
		segment<T> z(c,a);
		for (int i = 0; i < n; i++) {
			if (i == n-1) {
				segment<T> s(arr[i], arr[0]);
				if (s.Intersects(z)) {
					if (s.HasPoint(a))
						return true;
					if (z.HasPoint(arr[i]) && z.HasPoint(arr[0]))
						continue;
					if (arr[i].getY() < arr[0].getY() && z.HasPoint(arr[0]))
						continue;
					k++;
				}
			}
			else {
				segment<T> s(arr[i],arr[i+1]);
				if (s.Intersects(z))
				{
					if (s.HasPoint(a))
						return true;
					if (z.HasPoint(arr[i]) && z.HasPoint(arr[i+1]))
						continue;
					if (arr[i].getY() < arr[i + 1].getY() && z.HasPoint(arr[i + 1]))
						continue;
					k++;
				}
			}
		}
		k %= 2;
		if (k == 0) return false;
		else return true;
	}
/*	polygon<T>& operator= (const polygon<T>& from)
	{
		if (this == &from) return *this;
		delete [] this;
		arr = new point<T> [n = from.n];
		for (int i = 0; i < n; i++)
			arr[i] = from.arr[i];
		return *this;
	}
	point<T>& operator[](int c)
	{
		if (c < 0 || c >= n) exit(1);
		else return arr[c];
	}*/
	bool Intersects (const segment<T>& c) const
	{
		bool b = false;
		for (int i = 0; i<n; i++)
		{
			if (b == true) break;
			if (i == n-1) {
				segment<T> s(arr[i], arr[0]);
				if (s.Intersects(c)) b = true;
			}
			else {
				segment<T> s(arr[i],arr[i + 1]);
				if (s.Intersects(c)) b = true;
			}
		}
		return b;
	}
};

template<typename T>
class IShape
{
public:
	virtual bool HasPoint(const point<T>& p) const = 0;
	virtual bool Intersects(const segment <T>& s) const = 0;
};

int main ()
{
/*	//POINT -------------------------------------------------------POINT
	cout << "POINT\n";
	double x, y;
	point<double> P2;
	cin >> x >> y;
	point<double> P(x, y);
	cout << "getX, getY - " << P.getX() <<" "<< P.getY() <<'\n';
	cout << "setX, setY (newPoint) ";
	cin >> x >> y;
	P2.SetX(x); P2.SetY(y);
	P2.print();
	cout << "P2 == P? ";
	if (P2 == P) cout << "yes\n\n";
	if (P2 != P) cout << "no\n\n";
	P2 = P;
	cout << "P2 = P \n"; P2.print(); P.print();
	P2 = 5;
	cout << "P2 = 5 "; P2.print();
	cout << "move point: x + 10; y + 5: \n";
	P2.print(); P2.move(10,5); P2.print();
*/	//-------------------------------------------------------------POINT
	//SEGMENT----------------------------------------------------SEGMENT
/*	cout << "SEGMENT\n";
	double x, y, a, b;
	cout << " x1 and y1: "; cin >> x >> y;
	cout << " x2 and y2: "; cin >> a >> b;
	segment<double> S(x, y, a, b);
	cout << "getA() and getB(): \n";
	S.getA().print(); S.getB().print();
	cout << "setA() and setB()   (for new segment): \n";
	cin >> x >> y >> a >> b;
	point<double> P(x, y), P2(a, b); 
	segment<double> S2;
	S2.SetA(P); S2.SetB(P2);
	S2.print(); 
	P = 0;
	cout << "segment S2 <-> point P(0;0) = ";
	cout << S2.distance(P);
	cout << "\n x and y (for point): "; cin >> x >> y;
	point<double> nP(x, y);
	cout << "does S2 have new point? ";
	if (S2.HasPoint(nP)) cout << "yes\n";
	else cout << "no\n";
	cout << "does S2 intersect S? ";
	if (S2.Intersects(S)) cout << "yes\n";
	else cout << "no\n";
*/  //SEGMENT----------------------------------------------------SEGMENT
	//CIRCLE
/*	cout << "CIRCLE\n";
	double x, y, R, a, b;
	cout << "center and R:\n";
	cin >> x >> y >> R;
	point <double> P(x,y);
	circle<double> C(P,R);
	cout << "getR = " << C.getR();
	cout << "\n set new R - ";
	cin >> R;
	C.SetR(R);
	C.print();
	cout << "x and y (for point): "; cin >> x >> y;
	point<double> nP(x, y);
	cout << "Does circle have new point? ";
	if (C.HasPoint(nP)) cout << "yes\n";
	else cout << "no\n";
	cout << "x1, y1 and x2, y2 (for segment): "; cin >> x >> y >> a >> b;
	point<double> P1(x, y), P2(a, b);
	segment<double> S(P1, P2);
	cout << "Does circle intersect the segment? ";
	if (C.Intersects(S)) cout << "yes\n";
	else cout << "no\n";
*/	//SEGMENT----------------------------------------------------SEGMENT
/*	//POLIGON----------------------------------------------------POLIGON
	cout << "POLYGON\n";
    int n;
	double x, y, a, b;
	cout << "corners: ";
    cin >> n;
	point<double> P;
	cout << n <<" points for polygon:\n";
    point<double> *arr = new point<double> [n];
    for (int i = 0; i < n; i++)
	{
        cin >> x >> y;
		P.SetX(x); P.SetY(y);
		arr[i] = P;
	}
	polygon<double> Pol(n, arr);
	cout << "Our polygon: \n";
	Pol.print();
	cout << "(method N) corners = " << Pol.N();
	
	cout << "\n x and y (for point): "; cin >> x >> y;
	point<double> nP(x, y);
	cout << "Does our poligon have new point? ";
	if (Pol.HasPoint(nP)) cout << "yes\n";
	else cout << "no\n";
	cout << "x1, y1 and x2, y2 (for segment): "; cin >> x >> y >> a >> b;
	point<double> P1(x, y), P2(a, b);
	segment<double> S(P1, P2);
	cout << "Does our poligon intersect the segment? ";
	if (Pol.Intersects(S)) cout << "yes\n";
	else cout << "no\n";
*/	//POLIGON----------------------------------------------------POLIGON
	system ("pause");
    return 0;
}