#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum color {BLACK, GREY, WHITE};

struct TNode 
{
	size_t n;
	color col;
	int opentime;
	int closetime;
	int parent;
	TNode(){
		col = WHITE;
		opentime = 0;
		closetime = 0;
		parent = NULL;
	}
};

void DFSVisit(vector<vector<bool>> &g, vector<TNode> &v, int p, int &time)
{
	v[p].col = GREY;
	v[p].opentime = ++time;
	for (size_t i = 0; i < v.size(); ++i){
		if ((v[i].col == WHITE)&&g[p][i]){
			v[i].parent = p+1;
			DFSVisit(g, v, i, time);
		}
	}
	v[p].col = BLACK;
	v[p].closetime = ++time;
}

void DFSMain (vector<vector<bool>> &g, vector<TNode> &v){
	int time = 0;
	for (size_t i = 0; i<v.size(); ++i){
		if (v[i].col == WHITE)
			DFSVisit(g, v, i, time);
	}
	
}

void DFSPrint (vector<TNode> &v){
	for (size_t i = 0; i < v.size(); ++i){
		cout << i+1 << " Opened At: " << v[i].opentime << "; Closed At: " << v[i].closetime;
		if (v[i].parent)
			cout << "; Parent is " << v[i].parent << endl;
		else
			cout << "; No parent" << endl;
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<TNode> ver;
    vector<vector<bool>> g(n);
	for (int i=0; i<n; ++i){
		TNode t;
		t.n=i;
		ver.push_back(t);
		g[i].resize(n, false);
	}
	int x, y;
	for (int i=0; i<m; ++i){
		cin >> x >> y;
		g[x-1][y-1]=true;
	}
	DFSMain (g, ver);
	DFSPrint (ver);
	return 0;
}
