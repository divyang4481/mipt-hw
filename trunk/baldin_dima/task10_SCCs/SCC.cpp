#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>

using namespace std;

enum clr {WHITE, GRAY,BLACK};

void read_graph(vector< vector <int> > &graph,
	vector< vector <int> > &graphT,
	vector < clr > &color,
	vector <size_t> &links

	)
{

	size_t n,m;
	scanf("%u %u", &n, &m);
	graph.resize(n);
	graphT.resize(n);
	color.resize(n, WHITE);
	links.resize(n,0);
    size_t a,b;
	for ( size_t i = 0; i < m; ++i)
	{
		scanf( "%u %u", &a, &b);
		graph[a-1].push_back(b-1);
		graphT[b-1].push_back(a-1);
	}

}
void dfs_visit(vector< vector <int> > &graph,
	vector < clr > &color,
	vector < size_t > &links,
	int T, int u, size_t &number,
	vector<int> &f, int &last_f)
{
	color[u] = GRAY;
	for (size_t i = 0; i < graph[u].size(); ++i)
	{
		if (color[graph[u][i]] == WHITE) {
		                          dfs_visit(graph, color,links, T, graph[u][i], number,f,last_f);}
	}
	color[u] = BLACK;
	if (T == 1) links[u] = number;
	else f[last_f++] = u;

}

void scc(vector< vector <int> > &graph,
	vector< vector <int> > &graphT,
	vector < clr > &color,
	vector < size_t > &links,
	size_t &number
	)
{

	vector<int> f(links.size(), -1); int last_f = 0;
	for (size_t u = 0; u < graph.size(); ++u)
	{if (color[u] == WHITE) dfs_visit(graph, color, links, 0,u, number, f, last_f);}
	for (size_t i = 0; i < links.size(); color[i] = WHITE, ++i);
	for (size_t (last_f--); last_f >= 0 ; last_f--)
	{if (color[f[last_f]] == WHITE) dfs_visit(graphT, color, links, 1,f[last_f], ++number,f, last_f);}

}
void print_vector(vector <size_t> &links, size_t number)
{

	for (size_t i = 1; i <= number; ++i)
	{
		for (size_t j = 0; j < links.size(); ++j)
			if (links[j] == i) printf("%u ", j + 1);
		printf( "\n");
	}

}
int main()
{
	vector < vector<int> > graph;
	vector <vector<int> > graphT;
	vector < clr > color;
	vector < size_t > links;
	read_graph(graph, graphT, color,links);
	size_t number = 0;
	scc(graph, graphT,color, links, number);
	print_vector(links, number);
	return 0;
}
