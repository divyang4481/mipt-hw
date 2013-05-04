#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum color {BLACK, GREY, WHITE};

struct TNode 
{
	size_t n;
	color clr;
	int open;
	int close;
	TNode* parent;
};

void DFSVisit(vector < vector < TNode* > > &g, size_t s, int &time)
{
	g[s][0]->clr = GREY;
	g[s][0]->open = ++time;
	for (size_t i = 1; i < g[s].size(); ++i)
	{
		if (g[s][i]->clr == WHITE)
		{
			g[s][i]->parent = g[s][0];
			DFSVisit(g, g[s][i]->n, time);
		}
	}
	g[s][0]->clr = BLACK;
	g[s][0]->close = ++time;
}

void DFS(vector< vector<TNode*> > &g)
{
	int time = 0;
	for (size_t i = 0; i < g.size(); ++i)
	{
		g[i][0]->clr = WHITE;
		g[i][0]->parent = NULL;
		g[i][0]->open = 0;
		g[i][0]->close = 0;
	}
	for (size_t i = 0; i < g.size(); ++i)
	{
		if (g[i][0]->clr == WHITE)
			DFSVisit(g, i, time);
	}
	
	for (size_t i = 0; i < g.size(); ++i)
	{
		cout << i+1 << ": open time: " << g[i][0]->open << ";   close time: " << g[i][0]->close;
		if (g[i][0]->parent)
			cout << ";   parent: " << g[i][0]->parent->n+1 << endl;
		else
			cout << ";   no parent" << endl;
	}
}

int main()
{
	FILE *in = fopen("in.txt","r");
	size_t N, M;
	fscanf(in, "%d %d", &N, &M);
	vector<TNode*> ver;
	vector<vector <TNode*>> g(N);
	for (size_t i=0; i<N; ++i)
	{
		TNode *t = new TNode;
		t->n = i;
		t->clr = WHITE;
		t->open = 0;
		t->close = 0;
		t->parent = NULL;
		ver.push_back(t);
		g[i].push_back(ver[i]);
	}
	size_t x, y;
	for (size_t i=0; i<M; ++i)
	{
		fscanf(in, "%d %d", &x, &y);
		g[x-1].push_back(ver[y-1]);
	}
	DFS (g);
	fclose(in);
	return 0;
}