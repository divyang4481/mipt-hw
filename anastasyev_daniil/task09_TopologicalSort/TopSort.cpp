#include <iostream>
#include <vector>
#include <queue>
#include <list>
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

void DFSVisit(vector < vector < TNode* > > &g, size_t s, int &time, list <TNode *> &sorts)
{
	g[s][0]->clr = GREY;
	g[s][0]->open = ++time;
	for (size_t i = 1; i < g[s].size(); ++i)
	{
		if (g[s][i]->clr == WHITE)
		{
			g[s][i]->parent = g[s][0];
			DFSVisit(g, g[s][i]->n, time, sorts);
		}
	}
	g[s][0]->clr = BLACK;
	sorts.push_front(g[s][0]);
	g[s][0]->close = ++time;
}

void TopSort(vector< vector<TNode*> > &g, list <TNode *> &sorts)
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
			DFSVisit(g, i, time, sorts);
	}
}

void DFSChecker(vector < vector < TNode* > > &g, size_t s, int &cycle)
{
	g[s][0]->clr = GREY;
	size_t i=0;
	for (; (i < g[s].size()) && !(0!=i && g[s][i]->clr==GREY && g[s][0]->parent!=g[s][i]); ++i)
	{
		if (g[s][i]->clr == WHITE)
		{
			g[s][i]->parent = g[s][0];
			DFSChecker(g, g[s][i]->n, cycle);
		}
	}
	g[s][0]->clr = BLACK;
	if (i<g[s].size()) cycle++;
}

bool NoCycle(vector< vector<TNode*> > &g)
{
	int cycle = 0;
	for (size_t i = 0; i < g.size(); ++i)
	{
		if (g[i][0]->clr == WHITE)
			DFSChecker(g, i, cycle);
	}
	return cycle == 0;
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
	if (!NoCycle(g))
	{
		cout<<"Graph has cycles"<<endl;
		return 0;
	}
	list <TNode *> sorts;
	TopSort(g, sorts);
	for (list<TNode*>::iterator i=sorts.begin(); i!=sorts.end(); ++i) cout<<(*i)->n+1<<endl; 
	fclose(in);
	return 0;
}