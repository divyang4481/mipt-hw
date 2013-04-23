#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void ReadGraph(vector< vector<int> > &graph,
	vector< int > &parents,
	vector< bool > &used,
	vector< int > &length)
{
	FILE *f = fopen("input.txt", "r");
	int n,m;
	fscanf(f,"%d %d",&n,&m);
	graph.resize(n);
	parents.resize(n, -1);
	used.resize(n, false);
	length.resize(n);
	int a,b;
	for (int i = 0; i<m; ++i)
	{
		fscanf(f,"%d %d", &a, &b);
		graph[a-1].push_back(b-1);
	}
	fclose(f);
}
void BFS(vector< vector<int> > &graph,
	vector< int > &parents,
	vector< bool > &used,
	vector< int > &length, int start)
{
	int cur;
	queue<int> q;
	q.push(start);
	used[start] = true;
	for (;q.size() != 0;)
	{
		cur = q.front();
		q.pop();
		for (size_t i = 0; i < graph[cur].size(); ++i)
		{
			if (!used[graph[cur][i]])
			{
				used[graph[cur][i]] = true;
				parents[graph[cur][i]] = cur;
				length[graph[cur][i]] = length[cur] + 1;
				q.push(graph[cur][i]);

			}
		}
	}
}
void WriteGraph(vector< vector<int> > &graph,
	vector< int > &parents,
	vector< int > &length)
{
	FILE *f = fopen("output.txt", "w");
	for (int i = 0; i < graph.size(); ++i)
	{
		fprintf(f,"length %d, parent %d\n", length[i], parents[i] + 1);
	}
	fclose(f);
}
int main()
{
	
	
	vector< vector<int> > graph;
	vector< int > parents;
	vector< bool > used;
	vector< int > length;
	ReadGraph(graph, parents, used, length);
	BFS(graph, parents, used, length, 0);
	WriteGraph(graph, parents, length);

	return 0;
}

