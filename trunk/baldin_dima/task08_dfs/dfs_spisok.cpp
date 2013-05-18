#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>

using namespace std;

enum clr {WHITE, GRAY,BLACK};

void read_graph(vector< vector <int> > &graph,
	vector < clr > &color,
	vector < int > &parent,
	vector < int > &timein,
	vector < int > &timeout
	)
{
	size_t n,m;
	scanf("%u %u", &n, &m);
	graph.resize(n);
	color.resize(n, WHITE);
	parent.resize(n,-1);
	timein.resize(n,0);
	timeout.resize(n,0);
	size_t a,b;
	for ( size_t i = 0; i < m; ++i)
	{
		scanf("%u %u", &a, &b);
		graph[a-1].push_back(b-1);
	}

}
void dfs_visit(vector< vector <int> > &graph,
	vector < clr > &color,
	vector < int > &parent,
	vector < int > &timein ,
	vector < int > &timeout,
	int &time, int u)
{
	color[u] = GRAY;
	timein[u] = time++;
	for (size_t i = 0; i < graph[u].size(); ++i)
	{
		if (color[graph[u][i]] == WHITE) { parent[graph[u][i]] = u;
		                          dfs_visit(graph, color, parent, timein, timeout, time, graph[u][i]);}
	}
	color[u] = BLACK;
	timeout[u] = time++;

}
void dfs(vector< vector <int> > &graph,
	vector < clr > &color,
	vector < int > &parent,
	vector < int > &timein,
	vector < int > &timeout
	)
{
	int time = 0;
	for (size_t u = 0; u < parent.size(); ++u)
		if (color[u] == WHITE) dfs_visit(graph, color, parent, timein, timeout, time, u);

}
void print_vector(vector< vector <int> > &graph,
	vector < int > &parent,
	vector < int > &timein,
	vector < int > &timeout)
{

	for (size_t i = 0; i < parent.size(); ++i)
	{
		printf("vertex %u parent %d timein %d timeout %d\n", i + 1, parent[i] + 1, timein[i], timeout[i]);
	}

}
int main()
{
	vector < vector<int> > graph;
	vector < clr > color;
	vector < int > parent;
	vector < int > timein;
	vector < int > timeout;
	read_graph(graph, color, parent, timein, timeout);
	dfs(graph, color, parent, timein, timeout);
	print_vector(graph, parent, timein, timeout);
	return 0;
}
