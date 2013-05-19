#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum color {BLACK, GREY, WHITE};

struct TNode{
	int n;
	color col;
	int dist;
	TNode *parent;
	TNode(){
		col = WHITE;
		dist = -1;
		parent = NULL;
	}
};

void BFS (vector<vector<TNode*>> &g, int s){
	queue <TNode*> q;
	TNode* t;
	g[s][0]->col = GREY;
	g[s][0]->dist = 0;
	g[s][0]->parent = NULL;
	q.push(g[s][0]);
	while (!q.empty()){
		t = q.front();
		q.pop();
		for (int i = 1;  i < g[t->n].size(); ++i){
			if (g[t->n][i]->col == WHITE){
				g[t->n][i]->col = GREY;
				g[t->n][i]->dist = g[t->n][0]->dist+1;
				g[t->n][i]->parent = g[t->n][0];
				q.push(g[t->n][i]);
			}
		}
		t->col = BLACK;
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<TNode*> ver;
	vector<vector <TNode*>> g(n);
	for (int i=0; i<n; ++i){
		TNode *t = new TNode;
		t->n = i;
		ver.push_back(t);
		g[i].push_back(ver[i]);
	}
	int x, y;
	for (int i=0; i<m; ++i){
		cin >> x >> y;
		g[x-1].push_back(ver[y-1]);
	}
	BFS (g, 0);
	for (int i=0; i<n; ++i){
		if (g[i][0]->dist >= 0){
			cout << i+1 << " Distance: " << g[i][0]->dist;
			if (!g[i][0]->parent)
				cout << " No parent" << endl;
			else cout << " parent: " << (g[i][0]->parent->n)+1 << endl;
		}
		else cout << i+1 << " Not connected to initial node"<<endl;
	}
	return 0;
}