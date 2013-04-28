#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum color {BLACK, GREY, WHITE};

struct TNode
{
	color clr;
	int dist;
	int parent;
};

void BFS (vector < vector <bool> > &g, int s)
{
	vector < TNode > v(g.size());
	queue < int > q;
	for (int i = 0; i < g.size(); ++i)
	{
		if ( i != s)
		{
			v[i].clr = WHITE;
			v[i].dist = -1;
			v[i].parent = 0;
		}
	}
	v[s].clr = GREY;
	v[s].dist = 0;
	v[s].parent = 0;
	q.push (s);
	int t;
	while (!q.empty())
	{
		t = q.front();
		q.pop();
		for (int i = 1;  i < g[t].size(); ++i)
		{
			if (g[t][i] && v[i].clr==WHITE)
			{
				v[i].clr = GREY;
				v[i].dist = v[t].dist+1;
				v[i].parent = t;
				q.push(i);
			}
		}
		v[t].clr = BLACK;
	}
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i].dist > 0)
		{
			cout << i+1 << " distance: " << v[i].dist << " parent: " << v[i].parent+1 << endl;
		}
		else cout << i+1 << " no links or initial node"<<endl;
	}
}

int main()
{
	FILE *in = fopen("in.txt","r");
	int N, M;
	fscanf(in, "%d %d", &N, &M);
	vector<TNode*> ver(N);
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
		g[x-1][y-1] =  1;
	}
	BFS (g, 0);
	fclose(in);
	return 0;
}