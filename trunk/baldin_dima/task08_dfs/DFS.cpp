#include <iostream>
#include <vector>
using namespace std;
enum clr{WHITE, GRAY, BLACK};
struct _time
{
	int in, out;
};
void ReadGraph(vector< vector <int> > &graph,
	vector<clr> &colour,
	vector<_time> &time,
	vector<int> &parent)
{
	FILE *f = fopen("input.txt", "r");
	int n,m;
	fscanf(f,"%d %d",&n,&m);
	graph.resize(n);
	colour.resize(n, WHITE);
	parent.resize(n,-1);
	time.resize(n);
	int a,b;
	for (int i = 0; i < m; ++i)
	{
		fscanf(f,"%d %d", &a, &b);
		graph[a-1].push_back(b-1);
	}
	fclose(f);
}
void WriteGraph(vector< vector <int> > &graph,
	vector<_time> &time,
	vector< int > &parent)
{
	FILE *f = fopen("output.txt", "w");
	for (size_t i = 0; i < graph.size();++i)
		fprintf(f,"time_in %d, time_out %d, parent %d \n", time[i].in, time[i].out, parent[i]+1);
	fclose(f);
}
void DFS(vector< vector <int> > &graph,
	vector<clr> &colour,
	vector<_time> &time,
	vector< int > &parent, int s, int dfs_timer)
{
	time[s].in = dfs_timer++;
	colour[s] = GRAY;
	for (size_t i = 0; i < graph[s].size(); ++i)
	{
		if (colour[graph[s][i]] == WHITE)
		{
			parent[graph[s][i]] = s;
			DFS(graph, colour, time, parent, graph[s][i], dfs_timer);

		}
	}
	colour[s] = BLACK;
	time[s].out = dfs_timer++;

}
int main()
{
	vector< vector <int> > graph;
	vector<clr> colour;
	vector<_time> time;
	vector< int > parent;
	int dfs_timer = 0;
	ReadGraph(graph,colour, time, parent);
	DFS(graph, colour, time, parent, 0, dfs_timer);
	WriteGraph(graph,time, parent);
	return 0;
}