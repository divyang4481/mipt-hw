#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum color {BLACK, GREY, WHITE};

struct TNode{
	int n;
	color col;
	int dist;
	int parent;
	TNode(){
		col = WHITE;
		dist = -1;
		parent = -1;
	}
};

void BFS (vector<vector<bool>> &g, vector<TNode> &v, int p){
	queue <int> q;
	int t;
	v[p].col = GREY;
	v[p].dist = 0;
	v[p].parent = -1;
	q.push(p);
	while (!q.empty()){
		t = q.front();
		q.pop();
		for (int i=0;  i<v.size(); ++i){
			if ((g[t][i])&&(v[i].col == WHITE)){
				v[i].col = GREY;
				v[i].dist = v[t].dist+1;
				v[i].parent = t;
				q.push(i);
			}
		}
		v[t].col = BLACK;
	}
}

void BFSPrint (vector<vector<bool>> &g, vector<TNode> &v){
	for (int i=0; i<v.size(); ++i){
		if (v[i].dist >= 0){
			cout << i+1 << " Distance: " << v[i].dist;
			if (v[i].parent==-1)
				cout << " No parent" << endl;
			else cout << " parent: " << (v[i].parent)+1 << endl;
		}
		else cout << i+1 << " Not connected to initial node"<<endl;
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<TNode> v;
	vector<vector<bool>> g(n);
	for (int i=0; i<n; ++i){
		TNode t;
		t.n = i;
		v.push_back(t);
		g[i].resize(n, false);
	}
	int x, y;
	for (int i=0; i<m; ++i){
		cin >> x >> y;
		g[x-1][y-1]=true;
	}
	BFS (g, v, 0);
	BFSPrint (g, v);
	return 0;
}