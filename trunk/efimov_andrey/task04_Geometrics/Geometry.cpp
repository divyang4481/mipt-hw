#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


template <typename T>
class IShape;
template <typename T> 
class TPoint{
	T x;
	T y;
public:
	TPoint<T>(){
		x=0;
		y=0;
	}
	TPoint<T>(TPoint<T> &src){
		x=src.x;
		y=src.y;
	}
	TPoint<T>(const TPoint<T> &src){
		x=src.x;
		y=src.y;
	}
	TPoint <T> (T cx, T cy){
		x=cx;
		y=cy;
	}
	T get_x() const{
		return x;
	}
	T get_y() const{
		return y;
	}
	TPoint<T>& operator= (TPoint<T>& a){
		x=a.x;
		y=a.y;
		return a;
	}
	TPoint<T>& operator= (const TPoint<T>& a){
		x=a.x;
		y=a.y;
		return *this;
	}
	TPoint<T>& Lower(TPoint<T> &b){
		if (y>b.get_y())
			return b;
		else if (y<b.get_y())
			return *this;
		else {
			if(x>b.get_x())
				return *this;
			else 
				return b;
		}
		return b;
	}
	const TPoint<T>& Lower(const TPoint<T> &b) const{
		if (y>b.get_y())
			return b;
		else if (y<b.get_y())
			return *this;
		else {
			if(x>b.get_x())
				return *this;
			else 
				return b;
		}
		return b;
	}
	bool operator==(TPoint <T> a){
		if (y==a.get_y() && x==a.get_x())
			return true;
		return false;
	}
};
template <typename T>
double length (const TPoint<T>& p1, const TPoint <T>& p2){
	return sqrt(static_cast<double>((p1.get_x()-p2.get_x())*(p1.get_x()-p2.get_x())+(p1.get_y()-p2.get_y())*(p1.get_y()-p2.get_y())));
}
template <typename T>
double cosine(const TPoint <T>& p, const TPoint <T>& min, const TPoint <T>& an){
	return abs((length(p,min)*length(min,an)))/((p.get_x()-min.get_x())*(an.get_x()-min.get_x()) + (p.get_y()-min.get_y())*(an.get_y()-min.get_y()));
}
template <typename T> 
class TSegment: public IShape<T>{
	TPoint<T> le; //lower end
	TPoint<T> he; //higher end
public:
	TSegment(TPoint<T>& p1, TPoint <T>& p2){
		le=p1.Lower(p2);
		if (le==p1)
			he=p2;
		else 
			he=p1;
	}
	TSegment(const TPoint<T>& p1, const TPoint <T>& p2){
		le=p1.Lower(p2);
		if (le==p1)
			he=p2;
		else 
			he=p1;
	}
	TSegment(){
	}
	TPoint <T> higherend() {
		return he;
	}
	TPoint <T> lowerend () {
		return le;
	}
	TPoint <T> higherend() const  {
		return he;
	}
	TPoint <T> lowerend () const  {
		return le;
	}
	bool HasPoint(const TPoint <T> &p) const {
		double angle;
		if ((he.get_x()-le.get_x())==0)
			angle=0.0;
		else
			angle=static_cast<double>(he.get_y()-le.get_y())/static_cast<double>(he.get_x()-le.get_x());
		if (angle==0.0 && he.get_x()==p.get_x() && p.get_y()>=le.get_y() && p.get_y()<=he.get_y())
			return true;
		else if (angle==0.0)
			return false;
		if (p.get_y() < le.get_y() || p.get_y()>he.get_y())
			return false;
		else if((angle>0 &&  p.get_x() < le.get_x() && p.get_x()>he.get_x()) || (angle<0 &&  p.get_x() > le.get_x() && p.get_x()<he.get_x()) )
				return false;
		if (((static_cast<double>((p.get_y()-le.get_y()))-0.05) <= (angle*static_cast<double>((p.get_x()-le.get_x())))) && ((static_cast<double>((p.get_y()-le.get_y()))) >= (angle*static_cast<double>((p.get_x()-le.get_x()))-0.05)))
			return true;
		return false;
	}
	double min_length (const TPoint<T>& p) const {
		if ((length(le,p)-0.05 <=  length(he, p)) && (length(le,p) >=  length(he, p)-0.05)){
			double x=static_cast<double>(le.get_x()-he.get_x())/2;
			double y=static_cast<double>(le.get_x()-he.get_x())/2;
			return sqrt((static_cast<double> (p.get_x())-x)*(static_cast<double> (p.get_x())-x)+(static_cast<double> (p.get_y())-y)*(static_cast<double> (p.get_y())-y));
		}
		TPoint<T> min, max;
		if (length(le,p) < length(he, p)){
			min=le;
			max=he;
		} else {
			min=he;
			max=le;
		}
		double cos=cosine(p, min, max);
		if (cos<=0)
			return length(p, min);
		return (1.0-cos*cos)*length(p,min);
	}

	bool over(const TPoint <T>& p){
		double angle;
		if ((he.get_x()-le.get_x())==0)
			angle=0.0;
		else
			angle=static_cast<double>(he.get_y()-le.get_y())/static_cast<double>(he.get_x()-le.get_x());
		if((le.get_y()-he.get_y())==0){
			if (p.get_y()>=le.get_y())
				return true;
			else
				return false;
		}
		if (angle==0.0 && he.get_x()<=p.get_x())
			return true;
		else if(angle==0.0 && he.get_x()>p.get_x())
			return false;
		if (static_cast<double>(p.get_y()) >= (angle*static_cast<double>((p.get_x()-le.get_x())))+static_cast<double>(le.get_y()))
			return true;
		return false;
	}
	bool over(const TPoint <T>& p)const {
		double angle;
		if ((he.get_x()-le.get_x())==0)
			angle=0.0;
		else
			angle=static_cast<double>(he.get_y()-le.get_y())/static_cast<double>(he.get_x()-le.get_x());
		if((le.get_y()-he.get_y())==0){
			if (p.get_y()>=le.get_y())
				return true;
			else
				return false;
		}
		if (angle==0.0 && he.get_x()<=p.get_x())
			return true;
		else if(angle==0.0 && he.get_x()>p.get_x())
			return false;
		if (static_cast<double>(p.get_y()) >= (angle*static_cast<double>((p.get_x()-le.get_x())))+static_cast<double>(le.get_y()))
			return true;
		return false;
	}
	bool Intersects(const TSegment <T>& s) const{
		if(HasPoint(s.lowerend()) || HasPoint(s.higherend()) || s.HasPoint(le) || s.HasPoint(he))
			return true;
		if ((over(s.lowerend())==true && over(s.higherend())==true) || (over(s.lowerend())==false && over(s.higherend())==false))
			return false;
		TSegment<T> sg1(s.lowerend(), le);
		TSegment<T> sg2(s.lowerend(), he);
		if (!((sg1.over(s.higherend())==true && sg1.over(he)== true)||(sg1.over(s.higherend())==false && sg1.over(he)==false)))
			return false;
		if (!((sg2.over(s.higherend())==true && sg2.over(le)== true)||(sg2.over(s.higherend())==false && sg2.over(le)==false)))
			return false;
		return true;
	}
};
template <typename T>
class Triangle: public IShape<T>{
	TPoint <T> one;
	TPoint <T> two;
	TPoint <T> three;
public:
	Triangle(TPoint<T> a, TPoint<T> b, TPoint<T> c){
		one=a;
		two=b;
		three=c;
	}
	bool HasPoint(const TPoint <T> &p) const{
		TSegment <T> seg1 (one, two);
		if (seg1.HasPoint(p))
			return true;
		if ((seg1.over(three)==true && seg1.over(p)==false)||(seg1.over(three)==false && seg1.over(p)==true))
			return false;
		TSegment <T> seg2 (one, three);
		if (seg2.HasPoint(p))
			return true;
		if ((seg2.over(two)==true && seg2.over(p)==false)||(seg2.over(two)==false && seg2.over(p)==true))
			return false;
		TSegment <T> seg3 (two, three);
		if (seg3.HasPoint(p))
			return true;
		if ((seg3.over(one)==true && seg3.over(p)==false)||(seg3.over(one)==false && seg3.over(p)==true))
			return false;
		return true;
	}
	bool Intersects(const TSegment <T> &s) const {
		TSegment<T> sg1 (one, two);
		TSegment<T> sg2 (one, three);
		TSegment<T> sg3 (two, three);
		if(sg1.Intersects(s) || sg2.Intersects(s) ||sg3.Intersects(s))
			return true;
		return false;
	}
};
template <typename T> 
class TPolygon: public IShape<T>{
	TPoint<T>* arr;
	int size;
public:
	TPolygon(TPoint<T>* a, int n){			
		arr=new TPoint<T> [n];
		for(int i=0; i<n; ++i)
			arr[i]=a[i];
		size=n;
	}
	TPolygon(TPoint<T>* pts, int n, int except){		
		arr=new TPoint<T> [n-1];
		int k=0;
		for(int i=0; i<n-1; ++i, k++){
			if(except==i)
				k++;
			arr[i]=pts[k];
		}
		size=n-1;
	}	
	~TPolygon(){
		delete[] arr;
	}
	bool HasPoint(const TPoint <T> &p) const{
		for(int i=2; i<size; ++i){
			int n;
			if(i==(size-1))
				n=0;
			else
				n=i+1;
			if (!LiesInside(arr[i-2], arr[i-1], arr[i], arr[n])){
				Triangle<T> tr (arr[i-2], arr[i-1], arr[i]);
				TPolygon<T> pl (arr, size, i-1);
				return (tr.HasPoint(p) || pl.HasPoint(p));
			}
		}
		for (int i=2; i<size; ++i){
			Triangle<T> tr(arr[0], arr[i-1], arr[i]);
			if (tr.HasPoint(p))
				return true;
		}
		return false;
	}
	bool Intersects(const TSegment <T> &s) const{
		for(int i=2; i<size; ++i){
			int n;
			if(i==(size-1))
				n=0;
			else
				n=i+1;
			if (!LiesInside(arr[i-2], arr[i-1], arr[i], arr[n])){
				Triangle<T> tr (arr[i-2], arr[i-1], arr[i]);
				TPolygon<T> pl (arr, size, i-1);
				return (tr.Intersects(s) || pl.Intersects(s));
			}
		}
		for (int i=2; i<size; ++i){
			Triangle<T> tr (arr[0], arr[i-1], arr[i]);
			if (tr.Intersects(s))
				return true;
		}
		return false;
	}

	bool LiesInside(TPoint<T> left, TPoint<T> vertex, TPoint<T> right, TPoint<T> inq) const {
		TSegment <T> sg1 (vertex, left);
		TSegment <T> sg2 (vertex, right);
		if (!((sg1.over(inq)==true && sg1.over(right)== true) ||  (sg1.over(inq)==false && sg1.over(right)== false)))
			return false;
		if (!((sg2.over(inq)==true && sg2.over(left)== true) ||  (sg2.over(inq)==false && sg2.over(left)== false)))
			return false;
		return true;
	}
};
template <typename T> 
class TCircle: public IShape<T>{
	T rad;
	TPoint<T> center;
public:
	TCircle (T r, TPoint<T> c){
		center=c;
		rad=r;
	}
	bool HasPoint(const TPoint <T> &p) const{
		if(((p.get_x()-center.get_x())*(p.get_x()-center.get_x())+(p.get_y()-center.get_y())*(p.get_y()-center.get_y()))<=rad*rad)
			return true;
		return false;
	}
	bool Intersects(const TSegment<T> &s) const{
		if (HasPoint(s.lowerend())||HasPoint(s.higherend()))
			return true;
		if (static_cast<double>(rad)>=s.min_length(center))
			return true;
		return false;
	}

};

template <typename T>
class IShape{
public:
	virtual bool HasPoint(const TPoint <T> &p)  const = 0;
	virtual bool Intersects(const TSegment <T> &s) const = 0;
};

void Testapalooza(){
	//HasPoint and whatnot
	TPoint<double> O(0.0,0.0);
	TCircle<double> Or(10.0, O);
	TPoint<double> A(5.0, 2.5);
	TPoint<double> B(30.0, 15.0);
	cout << Or.HasPoint(A) << " ";  //yes
	cout << Or.HasPoint(B) << endl; //no
	TSegment<double> AB(A, B);
	TPoint<double> C(10.0, 5.0);
	cout << AB.HasPoint(C) << endl; //yes
	//Intersections
	TPoint<double> D(12.0, -6.0);
	TPoint<double> E(12.0, 6.0);
	TSegment<double> DE(D, E);
	TSegment<double> AC(A, C);
	cout << DE.Intersects(AB) << " "; //yes
	cout << DE.Intersects(AC) << endl; //no
	//Intersections (now with circles)
	cout << Or.Intersects(AB) << endl; //yes
	//HasPoint and Intersect (now with polygons)
	vector<TPoint<double>> oad;
	oad.push_back(O);
	oad.push_back(A);
	oad.push_back(D);
	TPolygon<double> OAD(&oad[0], 3);
	TPoint<double> F(1,1);
	TPoint<double> X(15,2);
	cout << OAD.HasPoint(F) << " "; //no - inside
	cout << OAD.HasPoint(X) << " "; //no - outside
	cout << OAD.HasPoint(A) << endl; //yes
	cout << OAD.Intersects(TSegment<double>(X,F)) << endl; //yes
	system("pause");
}

int main(){
	Testapalooza();
	return 0;
}