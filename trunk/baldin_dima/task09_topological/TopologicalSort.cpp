#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <set>
using namespace std;

enum clr {WHITE, GRAY,BLACK};
int kol = 0;
void read_graph(vector< vector <int> > &graph,
	vector< clr > &color
	)
{
	FILE *f = fopen("input.txt", "r");
	size_t n,m;
	fscanf(f, "%d %d", &n, &m);
	graph.resize(n);
	color.resize(n,WHITE);
	int a,b;
	for ( size_t i = 0; i < m; ++i)
	{
		fscanf(f, "%d %d", &a, &b);
		graph[a-1].push_back(b-1);
	}
	fclose(f);
}
void dfs_visit(vector< vector <int> > &graph,
	vector< clr > &color,
	list<int> &spisok,
	int u)
{
	++kol;
	color[u] = GRAY;
	for (size_t i = 0; i < graph[u].size(); ++i)
	{
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
		for (int i = 0; i < graph[*first].size();++i)
			if ((graph[*first][i] < *first)&&(myset.find(graph[*first][i]) != myset.end())) flag = 1;
	}
	return flag;
}
void print_vector(list<int> &spisok, vector <vector<int> > &graph)
{
	FILE *f = fopen("output.txt", "w");
	if (to_check(spisok, graph)) {fprintf(f, "Graph has cycle\n");}
	else
	for (list<int>::iterator it = spisok.begin(); it != spisok.end(); ++it)
	{
		fprintf(f,"vertex %d\n", (*it)+1);
	}
	fclose(f);
}

int main()
{
	vector < vector<int> > graph;
	vector <clr> color;
	list <int> spisok;
	read_graph(graph, color);
	dag(graph, color, spisok);
	print_vector(spisok, graph);
}
