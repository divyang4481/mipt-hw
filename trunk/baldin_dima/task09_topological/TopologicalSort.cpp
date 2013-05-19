#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

enum clr {WHITE, GRAY,BLACK};

void read_graph(vector< vector <int> > &graph,
	vector< clr > &color
	)
{

	int n,m;
	scanf("%d %d", &n, &m);
	graph.resize(n);
	color.resize(n,WHITE);
	int a,b;
	for ( size_t i = 0; i < m; ++i)
	{
		scanf("%d %d", &a, &b);
		graph[a-1].push_back(b-1);
	}

}
void dfs_visit(vector< vector <int> > &graph,
	vector< clr > &color,
	list<int> &spisok,
	int u)
{

	color[u] = GRAY;
	for (size_t i = 0; i < graph[u].size(); ++i)
	{
		if (color[graph[u][i]] == GRAY) {printf("Graph has a cycle\n"); exit(0);}
		if (color[graph[u][i]] == WHITE) { dfs_visit(graph, color,spisok, graph[u][i]);}
	}
	color[u] = BLACK;
	spisok.push_front(u);



}
void dag(vector< vector <int> > &graph,
	vector < clr > &color,
	list <int> &spisok
	)
{

	for (size_t u = 0; u < color.size(); ++u)
		if (color[u] == WHITE) dfs_visit(graph, color, spisok, u);

}
int to_check(list<int> &spisok, vector< vector <int> > &graph)
{
	int flag = 0;
	list<int>::iterator first = spisok.begin();
	set <int> myset;
	for (; first != spisok.end();++first)
		myset.insert(*first);
	first = spisok.begin();
	for (; first != (spisok.end() ); ++first)
	{
		for (size_t i = 0; i < graph[*first].size();++i)
			if ((graph[*first][i] < *first)&&(myset.find(graph[*first][i]) != myset.end())) flag = 1;
	}
	return flag;
}
void print_vector(list<int> &spisok, vector <vector<int> > &graph)
{
	for (list<int>::iterator it = spisok.begin(); it != spisok.end(); ++it)
	{
		printf("vertex %u\n", (*it)+1);
	}
}
int main()
{
	vector < vector<int> > graph;
	vector <clr> color;
	list <int> spisok;
	read_graph(graph, color);
	dag(graph, color, spisok);
	print_vector(spisok, graph);
	return 0;
}
