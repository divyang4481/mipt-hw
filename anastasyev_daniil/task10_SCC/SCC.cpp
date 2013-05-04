#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum color {BLACK, GREY, WHITE};

struct TNode 
{
	unsigned int n;
	color clr;
	int open;
	int close;
	TNode* parent;
};

void DFSVisit(vector < vector < TNode* > > &g, unsigned int s, int &time)
{
	g[s][0]->clr = GREY;
	g[s][0]->open = ++time;
	for (unsigned int i = 1; i < g[s].size(); ++i)
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
	for (unsigned int i = 0; i < g.size(); ++i)
	{
		if (g[i][0]->clr == WHITE)
			DFSVisit(g, i, time);
	}
}

void Transpose(vector <vector <TNode *>> &g)
{
	vector <vector <TNode *>> v(g.size());
	for (unsigned int i=0; i<v.size(); ++i)
		v[i].push_back(g[i][0]);
	vector <vector <TNode *>>::iterator it = g.begin();
	for (; it!=g.end(); ++it)
	{
		vector <TNode *>::iterator j = ++it->begin();
		for (; j!=it->end(); ++j)
		{
			v[(*j)->n].push_back(*(it->begin()));
		}
	}
	g = v;
}

bool Comp(vector<TNode *>a, vector <TNode *> b)
{
	return a[0]->close > b[0]->close;
}

unsigned int Number(vector < vector < TNode* > > &g, TNode *node)
{
	unsigned int i = 0;
	while (g[i][0]->n != node->n) i++;
	return i;
}

void DFSVisitTranspose(vector < vector < TNode* > > &g, vector < TNode* > &v, unsigned int s)
{
	g[s][0]->clr = GREY;
	for (unsigned int i = 1; i < g[s].size(); ++i)
	{
		if (g[s][i]->clr == WHITE)
		{
			g[s][i]->parent = g[s][0];
			DFSVisitTranspose(g, v, Number(g, g[s][i]));
		}
	}
	v.push_back(g[s][0]);
	g[s][0]->clr = BLACK;
}

void SCC(vector <vector <TNode *>> &g)
{
	vector <vector <TNode *>> scc(1);
	unsigned int c = 0;
	DFS(g);
	Transpose(g);
	sort(g.begin(), g.end(), Comp);
	for (unsigned int i = 0; i < g.size(); ++i)
		g[i][0]->clr = WHITE;
	for (unsigned int i = 0; i < g.size(); ++i)
	{
		if (g[i][0]->clr == WHITE)
		{
			DFSVisitTranspose(g, scc[c], i);
			if (scc[c].empty()) scc[c].pop_back();
			else
			{
				c++;
				scc.resize(c+1);
			}
		}
	}
	for (unsigned int i=0; i<c; ++i)
	{
		for (unsigned int j=0; j<scc[i].size(); ++j)
			cout<<scc[i][j]->n + 1 << " ";
		cout<<endl;
	}
}

int main()
{
	FILE *in = fopen("in.txt","r");
	unsigned int N, M;
	fscanf(in, "%d %d", &N, &M);
	vector<TNode*> ver;
	vector<vector <TNode*>> g(N);
	for (unsigned int i=0; i<N; ++i)
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
	unsigned int x, y;
	for (unsigned int i=0; i<M; ++i)
	{
		fscanf(in, "%d %d", &x, &y);
		g[x-1].push_back(ver[y-1]);
	}
	SCC(g);
	fclose(in);
	return 0;
}