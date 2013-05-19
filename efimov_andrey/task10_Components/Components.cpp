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

void DFSVisit(vector<vector<TNode*>> &g, int p, int ubersource, vector<vector<bool>> &c){
	c[ubersource][g[p][0]->n]=true;
	g[p][0]->col = GREY;
	for (size_t i = 1; i < g[p].size(); ++i){
		if (g[p][i]->col == WHITE){
			g[p][i]->parent = g[p][0];
			DFSVisit(g, g[p][i]->n, ubersource, c);
		}
	}
	g[p][0]->col = BLACK;
}

void SCCMain (vector<vector<TNode*>> &g, vector<vector<bool>> &c){
	for (size_t i = 0; i<g.size(); ++i){
		for (size_t j = 0; j<g.size(); ++j){
			g[j][0]->col=WHITE;
		}
		DFSVisit(g, i, i, c);
	}
}

void DFSPrint (vector<vector<TNode*>> &g, vector<vector<bool>> &c){
	vector<vector<int>> n;
	n.resize(g.size());
	for (size_t i=0; i<g.size(); ++i){
		for (size_t j=i; j<g.size(); ++j){
			if ((c[i][j])&&(c[j][i]))
				n[i].push_back(j+1);
		}
	}
	for (size_t i=0; i<g.size(); ++i){
		if (!n[i].empty()){
			cout << "Component of " << i+1 << ": ";
			sort(n[i].begin(), n[i].end());
			for (size_t j=0; j<n[i].size(); ++j){
				cout << n[i][j] << " ";
				if (j>0) n[n[i][j]-1].resize(0);
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
	vector<vector<bool>> c(n);
	for (int i=0; i<n; ++i){
		c[i].resize(n, false);
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
	SCCMain (g, c);
	DFSPrint (g, c);
	return 0;
}
