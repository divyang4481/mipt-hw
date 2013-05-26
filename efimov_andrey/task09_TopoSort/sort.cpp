#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

enum color {BLACK, GREY, WHITE};

vector<vector<bool>> conn;
bool loop=false;

struct TNode{
	size_t n;
	color col;
	int opentime;
	int closetime;
	TNode* parent;
	TNode(){
		col = WHITE;
		opentime = 0;
		closetime = 0;
		parent = NULL;
	}
};

bool mysort(TNode* a, TNode* b){
	return conn[b->n][a->n];
}

void DFSVisit(vector<vector<TNode*>> &g, int p, int ubersource){
	conn[ubersource][g[p][0]->n]=true;
	if ((conn[g[p][0]->n][ubersource]==true)&&(g[p][0]->n!=ubersource)) {
		loop=true;
		return;
	}
	g[p][0]->col = GREY;
	for (size_t i = 1; i < g[p].size(); ++i){
		if (g[p][i]->col == WHITE){
			g[p][i]->parent = g[p][0];
			DFSVisit(g, g[p][i]->n, ubersource);
		}
	}
	g[p][0]->col = BLACK;
}

void SortMain (vector<vector<TNode*>> &g, vector<TNode*> &v){
	for (size_t i = 0; i<g.size(); ++i){
		for (size_t j = 0; j<g.size(); ++j){
			g[j][0]->col=WHITE;
		}
		DFSVisit(g, i, i);
	}
	sort(v.begin(), v.end(), mysort);
}

void DFSPrint (vector<vector<TNode*>> &g, vector<TNode*> v){
	if (loop) cout << "Graph contains loops, no order is correct";
	else
		for (int i=0; i<g.size(); ++i)
			cout << v[i]->n+1 << " ";
}

int main(){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector<TNode*> ver;
    vector<vector<TNode*>> g(n);
	conn.resize(n);
	for (int i=0; i<n; ++i){
		conn[i].resize(n);
	}
	for (int i=0; i<n; ++i){
		TNode *t = new TNode;
		t->n=i;
		ver.push_back(t);
		g[i].push_back(ver[i]);
	}
	int x, y;
	for (int i=0; i<m; ++i){
		cin >> x >> y;
		g[x-1].push_back(ver[y-1]);
	}
	SortMain (g, ver);
	DFSPrint (g, ver);
	return 0;
}
