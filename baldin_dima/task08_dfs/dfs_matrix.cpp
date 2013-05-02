#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum clr {WHITE, GRAY,BLACK};
int kol = 0;
void read_graph(vector< vector <int> > &graph,
	vector < clr > &color,
	vector < int > &parent,
	vector < int > &timein,
	vector < int > &timeout
	)
{
	FILE *f = fopen("input.txt", "r");
	size_t n,m;
	fscanf(f, "%d %d", &n, &m);
	graph.resize(n);
	for (int i = 0; i < n; ++i)
		graph[i].resize(n,0);
	color.resize(n, WHITE);
	parent.resize(n,-1);
	timein.resize(n,0);
	timeout.resize(n,0);
	int a,b;
	for ( size_t i = 0; i < m; ++i)
	{
		fscanf(f, "%d %d", &a, &b);
		graph[a-1][b-1] = 1;
	}
	fclose(f);
}
void dfs_visit(vector< vector <int> > &graph,
	vector < clr > &color,
	vector < int > &parent,
	vector < int > &timein ,
	vector < int > &timeout,
	int &time, int u)
{
	++kol;
	color[u] = GRAY;
	timein[u] = time++;
	for (size_t i = 0; i < graph[u].size(); ++i)
	{
		if ((color[i] == WHITE) && (graph[u][i] == 1)) { parent[i] = u; 
		                          dfs_visit(graph, color, parent, timein, timeout, time, i);}
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
	FILE *f = fopen("output.txt", "w");
	for (size_t i = 0; i < parent.size(); ++i)
	{
		fprintf(f,"vertex %d parent %d timein %d timeout %d\n", i + 1, parent[i] + 1, timein[i], timeout[i]);
	}
	fclose(f);
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
}
