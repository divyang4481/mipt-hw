
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum color {BLACK, GREY, WHITE};

struct TNode
{
	int n;
	color clr;
	int dist;
	TNode *parent;
};

void BFS (vector < vector <TNode*> > &g, int s)
{
	queue < TNode* > q;
	for (int i = 0; i < g.size(); ++i)
	{
		g[i][0]->clr = WHITE;
		g[i][0]->dist = -1;
		g[i][0]->parent = NULL;
	}
	g[s][0]->clr = GREY;
	g[s][0]->dist = 0;
	g[s][0]->parent = NULL;
	q.push ( g[s][0]);
	TNode* t;
	while (!q.empty())
	{
		t = q.front();
		q.pop();
		for (int i = 1;  i < g[t->n].size(); ++i)
		{
			if (g[t->n][i]->clr == WHITE)
			{
				g[t->n][i]->clr = GREY;
				g[t->n][i]->dist = g[t->n][0]->dist+1;
				g[t->n][i]->parent = g[t->n][0];
				q.push(g[t->n][i]);
			}
		}
		t->clr = BLACK;
	}
	for (int i = 0; i < g.size(); ++i)
	{
		if (g[i][0]->dist > 0)
		{
			cout << i << " distance: " << g[i][0]->dist << " parent: " << g[i][0]->parent->n << endl;
		}
		else cout << i << " no links or initial node"<<endl;
	}
}

int main()
{
	FILE *in = fopen("in.txt","r");
	int N, M;
	fscanf(in, "%d %d", &N, &M);
	vector<TNode*> ver;
	vector<vector <TNode*>> g(N);
	for (int i=0; i<N; ++i)
	{
		TNode *t = new TNode;
		t->n = i;
		t->clr = WHITE;
		t->dist = -1;
		t->parent = NULL;
		ver.push_back(t);
		g[i].push_back(ver[i]);
	}
	int x, y;
	for (int i=0; i<M; ++i)
	{
		fscanf(in, "%d %d", &x, &y);
		g[x-1].push_back(ver[y-1]);
		g[y-1].push_back(ver[x-1]);
	}
	BFS (g, 0);
	fclose(in);
	return 0;
}