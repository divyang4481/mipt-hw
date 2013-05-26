#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class IShape;

template<typename T>
class TSegment;

template<typename T>
class TPoint: public IShape<T> {
	T x, y;
public:
        TPoint() {
			x = 0;
			y = 0;
        };
        T GetX() const {
			return x;
        };
        T GetY() const {
			return y;
        };
        TPoint (T NewX, T NewY) {
			x = NewX;
			y = NewY;
        };
        TPoint& operator = (const TPoint<T>& other) {
			x = other.GetX();
			y = other.GetY();
			return *this;
        };
        bool HasPoint(const TPoint<T>& p) const {
			return ((x == p.GetX()) && (y == p.GetY()));
        };
        bool Intersects(const TSegment <T>& s) const {
                TPoint a(x, y);
                return s.HasPoint(a);
        }


};

template<typename T>
class TSegment:public IShape<T> {
	TPoint <T> beg, end;
public:
	TSegment() {
		beg.x = 0;
		beg.y = 0;
		end.x = 0;
		end.y = 0;
	};
	TSegment(TPoint NewBeg, TPoint NewEnd) {
		beg = NewBeg;
		end = NewEnd;
	};
	bool HasPoint(const TPoint<T>& p) const {
		if ((beg.GetX() <= p.GetX()) && (p.GetX() <= end.GetX()) && (beg.GetY() <= p.GetXY()) && (p.GetY() <= end.GetY()))
			if (Direction(p.GetX() - beg.GetX(), p.GetY() - beg.GetY(), end.GetX() - beg.GetX(), end.GetY() - beg.GetY()) == 0)
				return 1;
		return 0;
	};
    const TPoint<T>& GetBeg() const {
		return beg;
    };
    const TPoint<T>& GetEnd() const {
		return end;
    };
	bool Intersects(const TSegment <T>& s) const {
		T v1 = VectorProduct(s.End().GetX() - s.BeG().GetX(), s.End().GetY() - s.End().GetY(), s.BeG().GetX() - beg.GetX(), beg.GetY() - s.BeG().GetY()); //return (x1 * y2 - x2 * y1);
		T v2 = VectorProduct(s.End().GetX() - s.BeG().GetX(), s.End().GetY() - s.End().GetY(), s.BeG().GetX() - end.GetX(), end.GetY() - s.BeG().GetY());
		T v3 = VectorProduct(end.GetX() - beg.GetX(), end.GetY() - beg.GetY(), s.BeG().GetX() - beg.GetX(), s.BeG().GetY() - beg.GetY());
		T v4 = VectorProduct(end.GetX() - beg.GetX(), end.GetY() - beg.GetY(), s.End().GetX() - beg.GetX(), s.End().GetY() - beg.GetY());

        return (v1 * v2 <= 0) && (v3 * v4 <= 0);
	}
};

template<typename T>
class TCircle:public IShape<T> {
	T r;
	TPoint<T> c;
public:
    TCircle() {
		r = 0;
        c = 0;
    };
    TCircle(T NewR, TPoint<T> NewC) {
		r = NewR;
        c = NewC;
    };
    bool HasPoint(const TPoint<T>& p) const {
		return (((p.GetX() - c.X()) * (p.GetX() - c.GetX()) + (p.GetY() - c.GetY()) * (p.GetY() - c.GetY())) <= r * r);
    };
	
    bool Intersects(const TSegment <T> &s) const {
		if ((HasPoint(s.GetBeg())) && (HasPoint(s.GetEnd()))) 
			return false;
		T A = s.GetEnd().GetY() - s.GetBeg().GetY();
		T B = s.GetBeg().GetX() - s.GetEnd().GetX();
		T C = VectorProduct(s.GetBeg().GetY(), s.GetBeg().GetX(), s.GetEnd().GetY(), s.GetEnd().GetX());
		if (((s.GetBeg().GetX() - c.GetX())*A + (s.GetBeg().GetY() - c.GetY())*B) * ((s.GetEnd().GetX() - c.GetX())*A + (s.GetEnd().GetY() - c.GetY())*B) > 0)
			return false;
		else {
			double d = (A * c.GetX() + B * c.GetY() + C)/(sqrt((double)A*A + B*B));
			return (d <= r);
		}
	}

};

template <typename T>
class TPolygon: public IShape<T> {
	vector<TPoint<T>> polygon;
public:    
	TPolygon() {};
    TPolygon(const vector<TPoint<T>> &p) {
		polygon = p;
        polygon.push_back(p[0]);
    };
    int PolygonSize () const {
		return polygon.size();
    };

	bool HasPoint(const TPoint <T> &p)  const {
		double sum = 0;

		Polygon[PolygonSize()].x := Polygon[0].x;
		Polygon[PolygonSize()].y := Polygon[0].y;

		for (int i = 0; i < PolygonSize(); ++i) {
			TPoint<T> v1.x = Polygon.p[i].x - p.x;
			TPoint<T> v1.y = Polygon.p[i].y - p.y;
			TPoint<T> v2.x = Polygon.p[i + 1].x - p.x;
			TPoint<T> v2.y = Polygon.p[i + 1].y - p.y;
		
			double angle = Atan2(VectorProduct(v1.x, v1.y, v2.x, v2.y), ScalarProduct(v1.x, v1.y, v2.x, v2.y));
			sum = sum + angle;
		}		
		return (abs(sum) > 0);
	};


	bool Intersects(const TSegment <T> &s) const {
		for (int i = 1; i < PolygonSize(); ++i) {
			TSegment<T> a(polygon[i - 1], polygon[i]);
			if (a.Intersects(s)) 
				return true;
		}
		return false;
	}
};


template<typename T>
class IShape {
public:
	virtual bool HasPoint(const TPoint<T>& p) const = 0; // Проверяет, что точка лежит внутри фигуры или на границе
	virtual bool Intersects(const TSegment <T>& s) const = 0; // Проверяет, что отрезок пересекает границу фигуры или касается ее
};


template <typename T>
 T VectorProduct(T x1, T y1, T x2, T y2) {
        return (x1 * y2 - x2 * y1);
};

 template <typename T>
 T ScalarProduct(T x1, T y1, T x2, T y2) {
        return (x1 * x2 + y2 * y1);
};
 int main() {

	 return 0;
 }