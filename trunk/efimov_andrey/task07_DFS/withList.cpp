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
	TNode* parent;
	TNode(){
		col = WHITE;
		opentime = 0;
		closetime = 0;
		parent = NULL;
	}
};

void DFSVisit(vector<vector<TNode*>> &g, int p, int &time)
{
	g[p][0]->col = GREY;
	g[p][0]->opentime = ++time;
	for (size_t i = 1; i < g[p].size(); ++i){
		if (g[p][i]->col == WHITE){
			g[p][i]->parent = g[p][0];
			DFSVisit(g, g[p][i]->n, time);
		}
	}
	g[p][0]->col = BLACK;
	g[p][0]->closetime = ++time;
}

void DFSMain (vector<vector<TNode*>> &g){
	int time = 0;
	for (int i = 0; i<g.size(); ++i){
		if (g[i][0]->col == WHITE)
			DFSVisit(g, i, time);
	}
	
}

void DFSPrint (vector<vector<TNode*>> &g){
	for (int i = 0; i < g.size(); ++i){
		cout << i+1 << " Opened At: " << g[i][0]->opentime << "; Closed At: " << g[i][0]->closetime;
		if (g[i][0]->parent)
			cout << "; Parent is " << g[i][0]->parent->n+1 << endl;
		else
			cout << "; No parent" << endl;
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector<TNode*> ver;
    vector<vector<TNode*>> g(n);
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
	DFSMain (g);
	DFSPrint (g);
	return 0;
}
