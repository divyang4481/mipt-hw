#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum color {BLACK, GREY, WHITE};

struct TNode 
{
	size_t n;
	color col;
	TNode* parent;
	TNode(){
		col = WHITE;
		parent = NULL;
	}
};

void DFSVisit(vector<vector<TNode*>> &g, int p, int &time, int ubersource, vector<vector<int>> &c){
	c[ubersource].push_back(g[p][0]->n+1);
	g[p][0]->col = GREY;
	for (size_t i = 1; i < g[p].size(); ++i){
		if (g[p][i]->col == WHITE){
			g[p][i]->parent = g[p][0];
			DFSVisit(g, g[p][i]->n, time, ubersource, c);
		}
	}
	g[p][0]->col = BLACK;
}

void DFSMain (vector<vector<TNode*>> &g, vector<vector<int>> &c){
	int time = 0;
	for (size_t i = 0; i<g.size(); ++i){
		if (g[i][0]->col == WHITE)
			DFSVisit(g, i, time, i, c);
	}
	
}

void DFSPrint (vector<vector<TNode*>> &g, vector<vector<int>> &c){
	for (size_t i=0; i<g.size(); ++i){
		if (!c[i].empty()){
			cout << "Component of " << i+1 << ": ";
			sort(c[i].begin(), c[i].end());
			for (size_t j=0; j<c[i].size(); ++j){
				cout << c[i][j] << " ";
			}
		cout << endl;
		}
	}
}

int main(){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector<TNode*> ver;
    vector<vector<TNode*>> g(n);
	vector<vector<int>> c(n);
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
	DFSMain (g, c);
	DFSPrint (g, c);
	return 0;
}
