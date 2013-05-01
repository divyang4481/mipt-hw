#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum color {BLACK, GREY, WHITE};

struct TNode 
{
	int n;
	color clr;
	int open;
	int close;
	int parent;
};

void DFS_VISIT (vector <vector <bool> > &g, vector <TNode> &v, int s, int &time)
{
	v[s].clr = GREY;
	v[s].open = ++time;
	for (int i = 0; i < v.size(); ++i)
	{
		if (g[s][i] && v[i].clr == WHITE)
		{
			v[i].parent = s;
			DFS_VISIT(g, v, i, time);
		}
	}
	v[s].clr = BLACK;
	v[s].close = ++time;
}

void DFS (vector <vector <bool> > &g ,  int s)
{
	int time = 0;
	vector <TNode> v(g.size());
	for (unsigned int i = 0; i < g.size(); ++i)
	{
		v[i].clr = WHITE;
		v[i].parent = 0;
		v[i].open = 0;
		v[i].close = 0;
	}
	for (int i = 0; i < g.size(); ++i)
	{
		if (v[i].clr == WHITE)
			DFS_VISIT (g, v, i, time);
	}
	for (int i = 0; i < v.size(); ++i)
	{
		cout << i << ": open time: " << v[i].open << ";   close time: " << v[i].close;
		if (v[i].parent)
			cout << ";   parent: " << v[i].parent << endl;
		else
			cout << ";   no parent" << endl;
	}
}

int main()
{
	FILE *in = fopen("in.txt","r");
	int N, M;
	fscanf(in, "%d %d", &N, &M);
	vector < vector <bool> > g(N);
	for (int i=0; i<N; ++i)
		for (int j=0; j<N; ++j) 
		{
			g[i].push_back(0);
		}
	int x, y;
	for (int i=0; i<M; ++i)
	{
		fscanf(in, "%d %d", &x, &y);
		g[x-1][y-1] = 1;
	}
	DFS (g, 0);
	fclose(in);
	return 0;
}