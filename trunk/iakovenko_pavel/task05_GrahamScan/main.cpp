#include <iostream>
#include <stack>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
using namespace std;
int SIZE = 100;


struct TPoint {
	int x;
	int y;
	double angel;
	TPoint operator= (TPoint& a){
		x = a.x;
		y = a.y;
		angel = a.angel;
		return *this;
	}
	bool operator< (TPoint a) {
		return (angel < a.angel);
	}

}point;


int triangle_area_2 (int x1, int y1, int x2, int y2, int x3, int y3) {
	return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

bool counter_clockwise (int x1, int y1, int x2, int y2, int x3, int y3) {
	return triangle_area_2 (x1, y1, x2, y2, x3, y3) > 0;
}

class Graham_scan {
	stack < struct TPoint > st;
	vector < TPoint >  arr;
	vector < TPoint >  arr1;
	char* name_of_file;
public:

	Graham_scan (string& name){
		name_of_file = new char [name.size()+1];
		for ( unsigned int i = 0; i < name.size(); ++i)
			name_of_file[i] = name [i];
		name_of_file[name.size()] = '\0';
	}

	~Graham_scan () {
		delete [] name_of_file;
	}

	void lower () {
		TPoint tp;
		tp = arr [0];
		for ( unsigned int i = 1; i < arr.size(); ++i ){
			if ( arr[i].y < tp.y || ( arr[i].y == tp.y && arr[i].x < tp.x ) ){
				tp = arr [i];
				swap ( arr [i], arr [0]);
			}
		}
	}

	void points_sort(){
		lower ();
		for ( unsigned int i = 1; i < arr.size(); ++i ){
			arr[i].angel = atan2( arr[i].y - arr[0].y , arr[i].x - arr[0].x);
		}
		sort (arr.begin()+1, arr.end());
		for ( unsigned int i = 2; i < arr.size(); ++i ){
			//if ( arr[i-1].angel - 0.00001 <= arr[i].angel && arr[i-1].angel >= arr[i].angel- 0.00001 ){
			if (arr[i-1].angel == arr[i].angel){
				if ( (sqrt ( static_cast <double> (arr[i-1].x * arr[i-1].x + arr[i-1].y * arr[i-1].y))) <= (sqrt (static_cast <double> (arr[i].x * arr[i].x + arr[i].y * arr[i].y)))) 
					arr.erase ( arr.begin() + i - 1);
				else
					arr.erase ( arr.begin() + i);
			}
		}
	}

	void main () {
		FILE* f = fopen ( name_of_file , "r+");
		//int  n;
		//fscanf ( f, "%d", &n);
		if ( SIZE < 3){
			fclose (f);
			f = fopen ( name_of_file , "a");
			fprintf ( f, "ERROR! NUMBER OF POINTS IS LESS THAN 3!\n");
			fclose (f);
			return;
		}
		TPoint tp;
		for ( int i=0; i < SIZE; ++i){
			fscanf (f, "%d %d", &tp.x , &tp.y);
			arr.push_back (tp);
			arr1.push_back (tp);
		}
		points_sort();
		st.push (arr [0]);
		st.push (arr [1]);
		st.push (arr [2]);
		TPoint top;
		TPoint next_to_top;
		for (unsigned int i = 3; i < arr.size();  ++i){
			top = st.top();
			st.pop();
			next_to_top = st.top();
			st.push(top);
			while ( ! counter_clockwise ( next_to_top.x, next_to_top.y, top.x, top.y, arr[i].x, arr[i].y)) {
				st.pop ();
				top = st.top();
				st.pop();
				next_to_top = st.top();
				st.push(top);
			}
			st.push( arr[i] );
		}
		fclose (f);
	}

	void print_to_file (){
		FILE* f = fopen("results_iakovenko.txt", "w");
		unsigned int n = st.size();
		for ( unsigned int i = 0; i < n; ++i){
			fprintf ( f, "%d point: (%d; %d)\n", i+1, st.top().x, st.top().y);
			st.pop();
		}
		fclose(f);
	}

	void print(){
		unsigned int n = st.size();
		for ( unsigned int i = 0; i < n; ++i){
			printf ("%d point: (%d; %d)\n", i+1, st.top().x, st.top().y);
			st.pop();
		}
	}

};



int main(){
	string  path_name;
	getline ( cin, path_name );
	Graham_scan a (path_name);
	a.main();
	a.print_to_file();
	return 0;
}
